package assignment2.serialComm;

import assignment2.serialComm.api.CommChannel;
import assignment2.serialComm.api.MessageListener;

/**
 * Thread that keeps reading messages from a channel and forwards them to a listener.
 */
public class MessageReaderAgent extends Thread {

    private final CommChannel channel;
    private final MessageListener listener;

    /**
     * Creates the agent; call {@link #start()} to begin reading.
     *
     * @param channel channel to read from
     * @param listener listener notified for every message
     */
    public MessageReaderAgent(final CommChannel channel, final MessageListener listener) {
        this.channel = channel;
        this.listener = listener;
    }

    /**
     * Waits for messages until the thread is interrupted.
     */
    @Override
    public void run() {
    }

    /**
     * Validates a raw message and forwards it to the listener.
     *
     * @param message raw message read from the channel
     */
    private void parseMessage(final String message) {
    }
}
