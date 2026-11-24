package assignment2;

import java.util.ArrayList;
import java.util.List;

import javax.swing.SwingUtilities;

import assignment2.controller.RadarController;
import assignment2.model.RadarLogic;
import assignment2.serialComm.MessageReaderAgent;
import assignment2.serialComm.SerialCommChannel;
import assignment2.serialComm.api.CommChannel;
import assignment2.view.api.View;
import assignment2.view.impl.cli.CliView;
import assignment2.view.impl.logger.LoggerView;
import assignment2.view.impl.swing.RadarView;

/**
 * Entry point of the Console Subsystem Unit.
 * Creates model, view and serial channel and wires them to the controller.
 */
public final class Launcher {

    /** Number of sectors, same as NUM_SECTORS in config.h. */
    private static final int NUM_SECTORS = 18;
    /** Serial speed, same as in setUpper.cpp. */
    private static final int BAUD_RATE = 9600;
    /** Port used when none is given on the command line. */
    private static final String DEFAULT_PORT = "COM5";

    private Launcher() {
    }

    /**
     * Starts the console.
     *
     * @param args command line arguments: the serial port name (e.g. COM3)
     */
    public static void main(final String[] args) throws Exception {
        final String port = args.length > 0 ? args[0] : DEFAULT_PORT;

        final CommChannel channel;
        try {
            channel = new SerialCommChannel(port, BAUD_RATE);
        } catch(Exception e) {
            e.printStackTrace();
            System.exit(1);
            return;
        }
        final RadarLogic model = new RadarLogic(NUM_SECTORS);

        final List<View> views = new ArrayList<>();
        // the views are created on the Swing thread, like every other view call
        SwingUtilities.invokeAndWait(() -> {
            views.add(new LoggerView());
            views.add(new RadarView(NUM_SECTORS));
            // CliView and LoggerView both write on the terminal and would mix their output:
            // use the CLI alone, in place of the two lines above
            // views.add(new CliView(NUM_SECTORS));
        });

        final RadarController controller = new RadarController(model, channel, views);
        new MessageReaderAgent(channel, controller).start();
    }
}
