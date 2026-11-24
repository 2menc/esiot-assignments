package assignment2.view.impl.cli;

import java.util.Arrays;

import assignment2.view.api.SectorStatus;
import assignment2.view.api.View;
import assignment2.view.api.ViewListener;

/**
 * Text implementation of the console view: redraws the whole screen
 * with the radar state and one coloured line per sector.
 * 
 * ! CANNOT CONTOL THE SERVO!!!
 */
public final class CliView implements View {

    private static final String ESC = "\u001B[";
    private static final String RESET = ESC + "0m";
    private static final String BOLD = ESC + "1m";
    private static final String HOME = ESC + "H";
    private static final String CLEAR_LINE = ESC + "K";
    private static final String CLEAR_BELOW = ESC + "J";

    private final SectorStatus[] statuses;
    private final int[] distances;
    private String state;
    private boolean remote;
    private ViewListener listener;

    /**
     * Creates the view showing the IDLE state and every sector empty.
     *
     * @param numSectors number of sectors scanned by the radar
     */
    public CliView(final int numSectors) {
        this.statuses = new SectorStatus[numSectors];
        this.distances = new int[numSectors];
        Arrays.fill(this.statuses, SectorStatus.EMPTY);
        Arrays.fill(this.distances, -1);
        this.state = "IDLE";
        this.remote = false;
        System.out.print(ESC + "2J"); // clear once at start, then only overwrite
        this.render();
    }

    @Override
    public void setSectorStatus(final int sector, final SectorStatus status, final int distance) {
        this.statuses[sector] = status;
        this.distances[sector] = distance;
        this.render();
    }

    @Override
    public void setDisplayedState(final String state) {
        this.state = state;
        this.render();
    }

    @Override
    public void setControlsEnabled(final boolean remote) {
        this.remote = remote;
        this.render();
    }

    @Override
    public void setListener(final ViewListener listener) {
        this.listener = listener;
    }

    /**
     * Redraws the screen from the top, overwriting the previous one to avoid flickering.
     */
    private void render() {
        final StringBuilder out = new StringBuilder(HOME);
        out.append(BOLD).append("State: ").append(this.state).append(RESET).append(CLEAR_LINE).append('\n');
        out.append(this.remote ? "Remote control: ON" : "Remote control: off").append(CLEAR_LINE).append("\n\n");

        for (int i = 0; i < this.statuses.length; i++) {
            final String content = this.statuses[i] == SectorStatus.EMPTY
                    ? "no object"
                    : "object at " + this.distances[i] + " cm";
            out.append(colorOf(this.statuses[i]))
               .append(String.format("Sector %2d | %s", i + 1, content))
               .append(RESET).append(CLEAR_LINE).append('\n');
        }
        out.append(CLEAR_BELOW);
        System.out.print(out);
        System.out.flush();
    }

    /**
     * @param status sector status
     * @return the ANSI colour of a sector line
     */
    private static String colorOf(final SectorStatus status) {
        switch (status) {
            case DANGER:
                return ESC + "31m";       // red
            case NEAR:
                return ESC + "38;5;208m"; // orange
            case FAR:
                return ESC + "33m";       // yellow
            default:
                return ESC + "32m";       // green
        }
    }
}