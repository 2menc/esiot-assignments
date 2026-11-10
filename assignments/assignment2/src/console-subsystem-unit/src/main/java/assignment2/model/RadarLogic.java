package assignment2.model;

/**
 * Model of the console: keeps the radar state and the last result of each sector.
 */
public class RadarLogic {

    private State currentState;
    private final int[] sectorDists;
    private final boolean[] sectorDetected;

    /**
     * Creates the model with every sector empty and the radar idle.
     *
     * @param numSectors number of sectors scanned by the radar
     */
    public RadarLogic(final int numSectors) {
        this.currentState = State.IDLE;
        this.sectorDists = new int[numSectors];
        this.sectorDetected = new boolean[numSectors];
    }

    /**
     * Stores the result of a sector measure.
     *
     * @param sector sector index
     * @param distance object distance in cm, ignored if nothing was detected
     * @param detected true if an object was found in the sector
     */
    public void updateSector(final int sector, final int distance, final boolean detected) {
    }

    /**
     * Updates the radar state.
     *
     * @param newState state reported by the radar
     */
    public void setState(final State newState) {
    }

    /**
     * @return the current radar state
     */
    public State getState() {
        return currentState;
    }

    /**
     * @param sector sector index
     * @return the last distance measured in the sector, in cm
     */
    public int getSectorDistance(final int sector) {
        return sectorDists[sector];
    }

    /**
     * @param sector sector index
     * @return true if an object was detected in the sector
     */
    public boolean isSectorDetected(final int sector) {
        return sectorDetected[sector];
    }

    /**
     * @return the number of sectors
     */
    public int getNumSectors() {
        return sectorDists.length;
    }

    /**
     * Keeps the sector data consistent with the current state,
     * e.g. clears every sector when the radar goes idle.
     */
    private void handleLogicState() {
    }
}
