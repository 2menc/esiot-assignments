package assignment2.view.api;

/**
 * What the radar found in a sector, as shown by the view.
 */
public enum SectorStatus {
    /** No object detected. */
    EMPTY,
    /** Object farther than D2. */
    FAR,
    /** Object between D1 and D2: pre-alarm range. */
    NEAR,
    /** Object closer than D1: alarm range. */
    DANGER
}
