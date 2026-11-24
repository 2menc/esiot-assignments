package assignment2.view.impl.swing;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.SwingConstants;
import javax.swing.WindowConstants;

import assignment2.view.api.SectorStatus;
import assignment2.view.api.View;
import assignment2.view.api.ViewListener;

/**
 * Swing implementation of the console view.
 * Shows the radar state, the sectors drawn as a radar, and the remote controls.
 * It only decides how things look: every action is forwarded to the listener.
 */
public final class RadarView implements View {

    private final JFrame frame;
    private final JLabel stateLabel;
    private final RadarPanel radar;
    private final JButton takeButton;
    private final JButton releaseButton;
    private final JButton resetButton;
    private final JSlider angleSlider;
    private ViewListener listener;

    /**
     * Builds the window, showing the IDLE state and every sector empty.
     * Must be called on the Swing event thread.
     *
     * @param numSectors number of sectors scanned by the radar
     */
    public RadarView(final int numSectors) {
        this.frame = new JFrame("Smart Radar - Console");
        this.frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        this.frame.setLayout(new BorderLayout());

        this.stateLabel = new JLabel("", SwingConstants.CENTER);
        this.stateLabel.setOpaque(true);
        this.stateLabel.setFont(this.stateLabel.getFont().deriveFont(Font.BOLD, 20f));
        this.stateLabel.setBorder(BorderFactory.createEmptyBorder(8, 8, 8, 8));
        this.frame.add(this.stateLabel, BorderLayout.NORTH);

        this.radar = new RadarPanel(numSectors);
        this.frame.add(this.radar, BorderLayout.CENTER);

        this.takeButton = new JButton("TAKE CONTROL");
        this.releaseButton = new JButton("RELEASE CONTROL");
        this.resetButton = new JButton("RESET");
        this.angleSlider = new JSlider(0, 180, 90);
        this.angleSlider.setMajorTickSpacing(30);
        this.angleSlider.setPaintTicks(true);
        this.angleSlider.setPaintLabels(true);
        this.angleSlider.setInverted(true); // 0 degrees on the right, as in the radar drawing

        this.takeButton.addActionListener(e -> {
            if (this.listener != null) {
                this.listener.handleTakeControl();
            }
        });
        this.releaseButton.addActionListener(e -> {
            if (this.listener != null) {
                this.listener.handleReleaseControl();
            }
        });
        this.resetButton.addActionListener(e -> {
            if (this.listener != null) {
                this.listener.handleReset();
            }
        });
        // send the angle only when the user releases the knob, not on every pixel of the drag
        this.angleSlider.addChangeListener(e -> {
            if (!this.angleSlider.getValueIsAdjusting() && this.listener != null) {
                this.listener.handleAngleChanged(this.angleSlider.getValue());
            }
        });

        final JPanel buttons = new JPanel();
        buttons.add(this.takeButton);
        buttons.add(this.releaseButton);
        buttons.add(this.resetButton);
        final JPanel controls = new JPanel(new BorderLayout());
        controls.setBorder(BorderFactory.createTitledBorder("Remote control (alarm only)"));
        controls.add(buttons, BorderLayout.NORTH);
        controls.add(this.angleSlider, BorderLayout.SOUTH);
        this.frame.add(controls, BorderLayout.SOUTH);

        this.setDisplayedState("IDLE");
        this.setControlsEnabled(false);

        this.frame.pack();
        this.frame.setLocationRelativeTo(null);
        this.frame.setVisible(true);
    }

    @Override
    public void setSectorStatus(final int sector, final SectorStatus status, final int distance) {
        this.radar.setSector(sector, status, distance);
    }

    @Override
    public void setDisplayedState(final String state) {
        this.stateLabel.setText("State: " + state);
        this.stateLabel.setBackground(colorOfState(state));
    }

    @Override
    public void setControlsEnabled(final boolean remote) {
        this.takeButton.setEnabled(!remote);
        this.releaseButton.setEnabled(remote);
        this.angleSlider.setEnabled(remote);
    }

    @Override
    public void setListener(final ViewListener listener) {
        this.listener = listener;
    }

    /**
     * @param state state name
     * @return the background colour of the state label
     */
    private static Color colorOfState(final String state) {
        switch (state) {
            case "WORKING":
                return new Color(200, 240, 200);
            case "PRE_ALARM":
                return new Color(255, 200, 120);
            case "ALARM":
                return new Color(255, 120, 120);
            default:
                return Color.LIGHT_GRAY;
        }
    }
}
