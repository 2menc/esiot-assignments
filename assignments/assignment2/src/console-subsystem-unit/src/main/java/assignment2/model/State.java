package assignment2.model;

/**
 * States of the Radar Subsystem Unit, as reported on the serial line.
 */
public enum State {
    /** Radar off, MCU sleeping. */
    IDLE,
    /** Radar scanning at normal speed. */
    WORKING,
    /** Object between D1 and D2: radar scanning at higher speed. */
    PRE_ALARM,
    /** Object closer than D1: radar controlled manually. */
    ALARM;

    /**
     * Decodes a state received from the radar.
     *
     * @param code state name as sent on the serial line
     * @return the matching state
     * @throws IllegalArgumentException if the code is not a valid state
     */
    public static State get(final String code) {
        return valueOf(code.trim().toUpperCase());
    }
}
