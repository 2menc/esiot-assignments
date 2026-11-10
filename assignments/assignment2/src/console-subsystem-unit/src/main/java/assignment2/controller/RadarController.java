package assignment2.controller;

import assignment2.model.RadarLogic;
import assignment2.serialComm.api.CommChannel;
import assignment2.serialComm.api.MessageListener;
import assignment2.view.api.View;
import assignment2.view.api.ViewListener;

/**
 * Controller of the console.
 * Updates model and view with the messages from the radar,
 * and turns the user actions into commands sent to the radar.
 */
public class RadarController implements MessageListener, ViewListener {

    private final RadarLogic model;
    private final View view;
    private final CommChannel channel;

    /**
     * Creates the controller and registers it as listener of the view.
     *
     * @param model console model
     * @param channel channel to the radar
     * @param view console view
     */
    public RadarController(final RadarLogic model, final CommChannel channel, final View view) {
        this.model = model;
        this.channel = channel;
        this.view = view;
    }

    /**
     * Decodes a message from the radar (state or sector measure)
     * and updates model and view.
     *
     * @param message message received from the radar
     */
    @Override
    public void handleMessageReceived(final String message) {
    }

    /**
     * Sends the take command to the radar.
     */
    @Override
    public void handleTakeControl() {
    }

    /**
     * Sends the release command to the radar.
     */
    @Override
    public void handleReleaseControl() {
    }

    /**
     * Sends the reset command to the radar.
     */
    @Override
    public void handleReset() {
    }

    /**
     * Sends the requested radar angle.
     *
     * @param angle requested angle, from 0 to 180 degrees
     */
    @Override
    public void handleAngleChanged(final int angle) {
    }
}
