package assignment2.view;

import java.awt.Color;

import assignment2.view.api.View;
import assignment2.view.api.ViewListener;

/**
 * Swing implementation of the console view.
 */
public class RadarView implements View {

    private ViewListener listener;

    @Override
    public void setSectorColor(final int sector, final Color color) {
    }

    @Override
    public void setDisplayedState(final String state) {
    }

    @Override
    public void setControlsEnabled(final boolean remote) {
    }

    @Override
    public void setListener(final ViewListener listener) {
        this.listener = listener;
    }

    /**
     * Renders the displayed state: label text and colour.
     */
    private void handleDisplayState() {
    }

    /**
     * Repaints the radar on the Swing event thread.
     */
    private void update() {
    }
}
