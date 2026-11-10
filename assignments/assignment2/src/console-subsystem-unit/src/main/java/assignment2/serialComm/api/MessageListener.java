package assignment2.serialComm.api;

/**
 * Receives the messages read from a communication channel.
 */
public interface MessageListener {

    /**
     * Called for every message received.
     *
     * @param message the received message
     */
    void handleMessageReceived(String message);
}
