package assignment2.model;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Model of the console: keeps the radar state and the last result of each sector.
 */
public class RadarLogic {

    /** Distance stored for a sector with no object. */
    private static final int NO_DISTANCE = -1;

    private State currentState;
    private final List<Integer> sectorDists;
    private final List<Boolean> sectorDetected;

    /**
     * Creates the model with every sector empty and the radar idle.
     *
     * @param numSectors number of sectors scanned by the radar
     */
    public RadarLogic(final int numSectors) {
        this.currentState = State.IDLE;

        this.sectorDists = new ArrayList<>(Collections.nCopies(numSectors, NO_DISTANCE));
        this.sectorDetected = new ArrayList<>(Collections.nCopies(numSectors, false));
    }

    /**
     * Stores the result of a sector measure.
     *
     * @param sector sector index
     * @param distance object distance in cm, ignored if nothing was detected
     * @param detected true if an object was found in the sector
     */
    public void updateSector(final int sector, final int distance, final boolean detected) {
        this.sectorDists.set(sector, distance);
        this.sectorDetected.set(sector, detected);
    }

    /**
     * Updates the radar state.
     *
     * @param newState state reported by the radar
     */
    public void setState(final State newState) {
        final State prevState = this.currentState;

        this.currentState = newState;
        this.handleLogicState(prevState);
    }

    /**
     * @return the current radar state
     */
    public State getState() {
        return this.currentState;
    }

    /**
     * @param sector sector index
     * @return the last distance measured in the sector, in cm
     */
    public int getSectorDistance(final int sector) {
        return this.sectorDists.get(sector);
    }

    /**
     * @param sector sector index
     * @return true if an object was detected in the sector
     */
    public boolean isSectorDetected(final int sector) {
        return this.sectorDetected.get(sector);
    }

    /**
     * @return the number of sectors
     */
    public int getNumSectors() {
        return this.sectorDists.size();
    }

    /**
     * Keeps the sector data consistent with the state change:
     * the sectors are cleared when the radar stops or restarts after an alarm.
     *
     * @param previousState state before the change
     */
    private void handleLogicState(final State previousState) {
        if(this.currentState == State.IDLE ||
            (previousState == State.ALARM && this.currentState == State.WORKING)
        ) {
            this.clearSectors();
        }
    }

    /**
     * Marks every sector as empty.
     */
    private void clearSectors() {
        Collections.fill(this.sectorDists, NO_DISTANCE);
        Collections.fill(this.sectorDetected, false);
    }
}
