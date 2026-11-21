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
    private StringBuffer currentMessage;

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
        char[] array = (message + "\n").toCharArray();
        byte[] bytes = new byte[array.length];

        for(int i = 0; i < array.length; i++) {
            bytes[i] = (byte) array[i];
        }

        try {
            synchronized (serialPort) {
                serialPort.writeBytes(bytes);
            }
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public String receiveMessage() throws InterruptedException {
        return this.queue.take();
    }

    @Override
    public boolean isMessageAvailable() {
        return !this.queue.isEmpty();
    }

    /**
     * Closes the serial port.
     */
    public void close() {
        try {
            if(this.serialPort != null) {
                this.serialPort.removeEventListener();
                this.serialPort.closePort();
            } 
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Collects incoming bytes and queues a message for every complete line.
     *
     * @param event serial port event raised by jssc
     */
    @Override
    public void serialEvent(final SerialPortEvent event) {

        // checks if the current event is "receiving character"
        if(event.isRXCHAR()) {
            try {
                String message = this.serialPort.readString(event.getEventValue());
                message = message.replaceAll("\r", "\n");

                this.currentMessage.append(message);

                boolean canGo = true;
                while(canGo) {
                    final String message2 = this.currentMessage.toString();
                    int index = message2.indexOf("\n");

                    if(index >= 0) {
                        this.queue.put(message2.substring(0, index));
                        this.currentMessage = new StringBuffer("");

                        if(index+1 < message2.length()) {
                            this.currentMessage.append(message2.substring(index+1));
                        } else { canGo = false; }
                    }
                }
            } catch(Exception e) {
                e.printStackTrace();
                System.err.println("Error in resolving string from COM port: " + e);
            }
        }
    }
}
