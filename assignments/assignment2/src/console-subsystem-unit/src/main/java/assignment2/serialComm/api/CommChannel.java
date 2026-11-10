package assignment2.serialComm.api;

/**
 * Models an asynchronous communication channel to send and receive messages.
 */
public interface CommChannel {

    /**
     * Sends a message, asynchronously.
     *
     * @param message message to send, without the line terminator
     */
    void sendMessage(String message);

    /**
     * Returns the next received message, waiting until one is available.
     *
     * @return the received message, without the line terminator
     * @throws InterruptedException if the thread is interrupted while waiting
     */
    String receiveMessage() throws InterruptedException;

    /**
     * @return true if a message can be read without waiting
     */
    boolean isMessageAvailable();
}
