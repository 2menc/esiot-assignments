package assignment2.serialComm;

import assignment2.serialComm.api.CommChannel;
import assignment2.serialComm.api.MessageListener;

/**
 * Thread that keeps reading messages from a channel and forwards them to a listener.
 */
public class MessageReaderAgent extends Thread {

    private static final String STATE_PREFIX = "state:";
    private static final String SECTOR_PREFIX = "sector:";

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
        this.setDaemon(true); // does not keep the program alive when the window is closed
    }

    /**
     * Waits for messages until the thread is interrupted.
     */
    @Override
    public void run() {
        while (!this.isInterrupted()) {
            try {
                final String message = this.channel.receiveMessage(); // waits for a message
                this.parseMessage(message);
            } catch (final InterruptedException e) {
                this.interrupt(); // restore the flag, so the loop ends
            }
        }
    }

    /**
     * Validates a raw message and forwards it to the listener.
     *
     * @param message raw message read from the channel
     */
    private void parseMessage(final String message) {
        final String text = message.trim();

        if(text.startsWith(STATE_PREFIX) || text.startsWith(SECTOR_PREFIX)) {
            this.listener.handleMessageReceived(text);
        }
    }
}
