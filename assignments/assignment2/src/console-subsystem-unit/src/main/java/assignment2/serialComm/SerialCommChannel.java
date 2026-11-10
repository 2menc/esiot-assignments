package assignment2.serialComm;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

import assignment2.serialComm.api.CommChannel;
import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;

/**
 * Communication channel over a serial port, based on jssc.
 * Incoming bytes are split into lines and queued as messages.
 */
public class SerialCommChannel implements CommChannel, SerialPortEventListener {

    private static final int QUEUE_SIZE = 100;

    private final SerialPort serialPort;
    private final BlockingQueue<String> queue;
    private final StringBuffer currentMessage;

    /**
     * Opens the serial port and starts listening for incoming data.
     *
     * @param port serial port name (e.g. COM3 or /dev/ttyACM0)
     * @param baudRate serial speed in bit/s
     * @throws SerialPortException if the port cannot be opened
     */
    public SerialCommChannel(final String port, final int baudRate) throws SerialPortException {
        this.serialPort = new SerialPort(port);
        this.queue = new ArrayBlockingQueue<>(QUEUE_SIZE);
        this.currentMessage = new StringBuffer();
    }

    @Override
    public void sendMessage(final String message) {
    }

    @Override
    public String receiveMessage() throws InterruptedException {
        return queue.take();
    }

    @Override
    public boolean isMessageAvailable() {
        return !queue.isEmpty();
    }

    /**
     * Closes the serial port.
     */
    public void close() {
    }

    /**
     * Collects incoming bytes and queues a message for every complete line.
     *
     * @param event serial port event raised by jssc
     */
    @Override
    public void serialEvent(final SerialPortEvent event) {
    }
}
