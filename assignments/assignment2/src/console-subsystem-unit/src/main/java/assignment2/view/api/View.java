package assignment2.view.api;

import java.awt.Color;

/**
 * Graphical interface of the console: shows the radar and its controls.
 */
public interface View {

    /**
     * Changes the colour of a sector.
     *
     * @param sector sector index
     * @param color new colour of the sector
     */
    void setSectorColor(int sector, Color color);

    /**
     * Shows the current radar state.
     *
     * @param state state name to display
     */
    void setDisplayedState(String state);

    /**
     * Enables or disables the remote control inputs.
     *
     * @param remote true if the console has control of the radar
     */
    void setControlsEnabled(boolean remote);

    /**
     * Registers the object notified of the user actions.
     *
     * @param listener listener of the user actions
     */
    void setListener(ViewListener listener);
}
