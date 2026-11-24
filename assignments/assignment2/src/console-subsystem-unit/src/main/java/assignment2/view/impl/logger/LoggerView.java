package assignment2.view.impl.logger;

import java.time.LocalTime;
import java.time.format.DateTimeFormatter;

import assignment2.view.api.SectorStatus;
import assignment2.view.api.View;
import assignment2.view.api.ViewListener;

/**
 * View that writes every update to the standard output, one timestamped line each.
 * It has no user input, so it never notifies the listener.
 */
public final class LoggerView implements View {

    private static final DateTimeFormatter TIME = DateTimeFormatter.ofPattern("HH:mm:ss.SSS");

    /**
     * Creates the logger.
     */
    public LoggerView() {
        this.log("Logger started");
    }

    @Override
    public void setSectorStatus(final int sector, final SectorStatus status, final int distance) {
        final String content = status == SectorStatus.EMPTY
                ? "no object"
                : "object at " + distance + " cm (" + status + ")";
        this.log(String.format("Sector %2d | %s", sector + 1, content));
    }

    @Override
    public void setDisplayedState(final String state) {
        this.log("State changed to " + state);
    }

    @Override
    public void setControlsEnabled(final boolean remote) {
        this.log("Remote control " + (remote ? "taken" : "released"));
    }

    /**
     * Ignored: the logger has no input to forward.
     *
     * @param listener listener of the user actions
     */
    @Override
    public void setListener(final ViewListener listener) {
        // nothing to notify
    }

    /**
     * Prints a message with the current time.
     *
     * @param message message to print
     */
    private void log(final String message) {
        System.out.println("LOG [" + LocalTime.now().format(TIME) + "]->" + message);
    }
}
