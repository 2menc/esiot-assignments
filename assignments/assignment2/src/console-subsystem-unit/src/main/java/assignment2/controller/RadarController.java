package assignment2.controller;

import java.util.List;

import javax.swing.SwingUtilities;

import assignment2.model.RadarLogic;
import assignment2.model.State;
import assignment2.serialComm.api.CommChannel;
import assignment2.serialComm.api.MessageListener;
import assignment2.view.api.SectorStatus;
import assignment2.view.api.View;
import assignment2.view.api.ViewListener;

/**
 * Controller of the console.
 * Updates model and view with the messages from the radar,
 * and turns the user actions into commands sent to the radar.
 * Model and view are only touched on the Swing event thread.
 */
public final class RadarController implements MessageListener, ViewListener {

    // protocol: radar -> console
    private static final String STATE_PREFIX = "state:";
    private static final String SECTOR_PREFIX = "sector:";

    // protocol: console -> radar, must match CommandParser on Arduino
    private static final String CMD_TAKE = "cmd:TAKE";
    private static final String CMD_RELEASE = "cmd:RELEASE";
    private static final String CMD_RESET = "cmd:RESET";
    private static final String CMD_ANGLE = "cmd:value:";

    // distance thresholds in cm, same values as D1 and D2 in config.h
    private static final int D1 = 20;
    private static final int D2 = 50;

    private final RadarLogic model;
    private final List<View> views;
    private final CommChannel channel;
    private boolean remote;

    /**
     * Creates the controller and registers it as listener of the view.
     *
     * @param model console model
     * @param channel channel to the radar
     * @param view console view
     */
    public RadarController(final RadarLogic model, final CommChannel channel, final List<View> views) {
        this.model = model;
        this.channel = channel;
        this.views = views; // no need to create a defensive copy
        this.remote = false;

        for(var view : this.views) {
            view.setListener(this);
        }
    }

    /**
     * Hands a message from the radar to the Swing event thread, where it is decoded.
     *
     * @param message message received from the radar
     */
    @Override
    public void handleMessageReceived(final String message) {
        SwingUtilities.invokeLater(() -> this.decode(message));
    }

    /**
     * Sends the take command, only while the radar is in alarm.
     */
    @Override
    public void handleTakeControl() {
        if (this.model.getState() == State.ALARM) {
            this.channel.sendMessage(CMD_TAKE);
            this.remote = true;

            for(var view : this.views) {
                view.setControlsEnabled(true);
            }
        }
    }

    /**
     * Sends the release command, only while the console has control.
     */
    @Override
    public void handleReleaseControl() {
        if (this.remote) {
            this.channel.sendMessage(CMD_RELEASE);
            this.remote = false;
            
            for(var view : this.views) {
                view.setControlsEnabled(false);
            }
        }
    }

    /**
     * Sends the reset command, only while the radar is in alarm.
     */
    @Override
    public void handleReset() {
        if (this.model.getState() == State.ALARM) {
            this.channel.sendMessage(CMD_RESET);
        }
    }

    /**
     * Sends the requested radar angle, only while the console has control.
     *
     * @param angle requested angle, from 0 to 180 degrees
     */
    @Override
    public void handleAngleChanged(final int angle) {
        if (this.remote && angle >= 0 && angle <= 180) {
            this.channel.sendMessage(CMD_ANGLE + angle);
        }
    }

    /**
     * Decodes a state or sector message and updates model and view.
     * Malformed messages are ignored.
     *
     * @param message message received from the radar
     */
    private void decode(final String message) {
        try {
            if (message.startsWith(STATE_PREFIX)) {
                this.handleState(State.get(message.substring(STATE_PREFIX.length())));
            } else if (message.startsWith(SECTOR_PREFIX)) {
                this.handleSector(message.substring(SECTOR_PREFIX.length()));
            }
        } catch (final IllegalArgumentException e) {
            // also catches NumberFormatException: a corrupted line must not stop the console
            System.err.println("Ignored malformed message: " + message);
        }
    }

    /**
     * Stores the new state and refreshes the view; leaving the alarm ends remote control.
     *
     * @param state state reported by the radar
     */
    private void handleState(final State state) {
        this.model.setState(state);
        if (state != State.ALARM) {
            this.remote = false;
        }
        
        for(var view : this.views) {
            view.setDisplayedState(state.name());
            view.setControlsEnabled(this.remote);
        }

        this.refreshSectors(); // the model may have cleared the sectors
    }

    /**
     * Stores a sector measure and shows it.
     *
     * @param body message without prefix, as "sector:detected:distance", sector from 1 to N
     * @throws IllegalArgumentException if the message is malformed
     */
    private void handleSector(final String body) {
        final String[] parts = body.split(":");
        if (parts.length != 3) {
            throw new IllegalArgumentException("wrong number of fields");
        }
        final int sector = Integer.parseInt(parts[0]) - 1; // radar counts from 1, model from 0
        if (sector < 0 || sector >= this.model.getNumSectors()) {
            throw new IllegalArgumentException("sector out of range");
        }
        final boolean detected = "1".equals(parts[1]);
        final int distance = Integer.parseInt(parts[2]);

        this.model.updateSector(sector, distance, detected);
        this.showSector(sector);
    }

    /**
     * Shows every sector as stored in the model.
     */
    private void refreshSectors() {
        for (int i = 0; i < this.model.getNumSectors(); i++) {
            this.showSector(i);
        }
    }

    /**
     * Shows one sector as stored in the model.
     *
     * @param sector sector index, from 0
     */
    private void showSector(final int sector) {
        final boolean detected = this.model.isSectorDetected(sector);
        final int distance = this.model.getSectorDistance(sector);
                
        for(var view : this.views) {
            view.setSectorStatus(sector, statusOf(detected, distance), distance);
        }
    }

    /**
     * Classifies a measure against the distance thresholds.
     *
     * @param detected true if an object was found
     * @param distance object distance in cm
     * @return the sector status
     */
    private static SectorStatus statusOf(final boolean detected, final int distance) {
        if (!detected) {
            return SectorStatus.EMPTY;
        } else if (distance < D1) {
            return SectorStatus.DANGER;
        } else if (distance < D2) {
            return SectorStatus.NEAR;
        }
        return SectorStatus.FAR;
    }
}
