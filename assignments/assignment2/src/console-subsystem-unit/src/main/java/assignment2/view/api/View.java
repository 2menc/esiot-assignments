package assignment2.view.api;

/**
 * Graphical interface of the console: shows the radar state, the sectors and the remote controls.
 * Every method must be called on the Swing event thread.
 */
public interface View {

    /**
     * Shows what the radar found in a sector.
     *
     * @param sector sector index, from 0
     * @param status sector status
     * @param distance object distance in cm, ignored if status is EMPTY
     */
    void setSectorStatus(int sector, SectorStatus status, int distance);

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
