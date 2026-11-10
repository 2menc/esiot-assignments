package assignment2.view.api;

/**
 * Receives the user actions performed on the view.
 */
public interface ViewListener {

    /**
     * Called when the user presses TAKE CONTROL.
     */
    void handleTakeControl();

    /**
     * Called when the user presses RELEASE CONTROL.
     */
    void handleReleaseControl();

    /**
     * Called when the user presses RESET.
     */
    void handleReset();

    /**
     * Called when the user moves the radar position control.
     *
     * @param angle requested angle, from 0 to 180 degrees
     */
    void handleAngleChanged(int angle);
}
