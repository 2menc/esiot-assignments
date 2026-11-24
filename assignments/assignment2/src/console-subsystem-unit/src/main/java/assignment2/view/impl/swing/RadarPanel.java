package assignment2.view.impl.swing;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.geom.Arc2D;
import java.util.Arrays;

import javax.swing.JPanel;

import assignment2.view.api.SectorStatus;

/**
 * Panel drawing the radar as a half circle split into sectors.
 * Sector 1 starts at 0 degrees (right) and the sectors go counter-clockwise to 180 degrees (left).
 * Every sector is coloured by its status; a detected object is drawn as a dot at its distance,
 * with the distance written outside the half circle.
 */
final class RadarPanel extends JPanel {

    private static final long serialVersionUID = 1L;

    /** Distance drawn on the outer border, in cm. */
    private static final int MAX_RANGE_CM = 200;
    /** Distance between two range rings, in cm. */
    private static final int RING_STEP_CM = 50;
    /** Space around the half circle for the labels, in pixels. */
    private static final int MARGIN = 50;
    private static final int DOT_SIZE = 10;

    private final SectorStatus[] statuses;
    private final int[] distances;

    /**
     * Creates the panel with every sector empty.
     *
     * @param numSectors number of sectors
     */
    RadarPanel(final int numSectors) {
        this.statuses = new SectorStatus[numSectors];
        this.distances = new int[numSectors];
        Arrays.fill(this.statuses, SectorStatus.EMPTY);
        Arrays.fill(this.distances, -1);
        this.setBackground(new Color(20, 30, 20));
        this.setPreferredSize(new Dimension(720, 420));
    }

    /**
     * Stores the status of a sector and repaints the radar.
     *
     * @param sector sector index, from 0
     * @param status sector status
     * @param distance object distance in cm, ignored if status is EMPTY
     */
    void setSector(final int sector, final SectorStatus status, final int distance) {
        this.statuses[sector] = status;
        this.distances[sector] = distance;
        this.repaint();
    }

    @Override
    protected void paintComponent(final Graphics graphics) {
        super.paintComponent(graphics);
        final Graphics2D g = (Graphics2D) graphics.create();
        g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        // centre at the bottom middle, radius limited by width and height
        final int radius = Math.min(this.getWidth() / 2, this.getHeight()) - MARGIN;
        final int cx = this.getWidth() / 2;
        final int cy = this.getHeight() - MARGIN / 2;
        final double width = 180.0 / this.statuses.length;

        for (int i = 0; i < this.statuses.length; i++) {
            this.paintSector(g, i, cx, cy, radius, width);
        }
        this.paintRings(g, cx, cy, radius);
        for (int i = 0; i < this.statuses.length; i++) {
            this.paintLabels(g, i, cx, cy, radius, width);
        }
        g.dispose();
    }

    /**
     * Fills a sector with the colour of its status and draws its border.
     */
    private void paintSector(final Graphics2D g, final int i, final int cx, final int cy,
            final int radius, final double width) {
        final Arc2D wedge = new Arc2D.Double(cx - radius, cy - radius, 2.0 * radius, 2.0 * radius,
                i * width, width, Arc2D.PIE);
        g.setColor(colorOf(this.statuses[i]));
        g.fill(wedge);
        g.setColor(new Color(0, 0, 0, 90));
        g.setStroke(new BasicStroke(1f));
        g.draw(wedge);
    }

    /**
     * Draws the range rings, so the distance of a dot can be read at a glance.
     */
    private void paintRings(final Graphics2D g, final int cx, final int cy, final int radius) {
        g.setFont(new Font(Font.SANS_SERIF, Font.PLAIN, 11));
        g.setStroke(new BasicStroke(1f, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER,
                10f, new float[] {4f, 4f}, 0f));
        for (int cm = RING_STEP_CM; cm <= MAX_RANGE_CM; cm += RING_STEP_CM) {
            final int r = radius * cm / MAX_RANGE_CM;
            g.setColor(new Color(255, 255, 255, 110));
            g.draw(new Arc2D.Double(cx - r, cy - r, 2.0 * r, 2.0 * r, 0, 180, Arc2D.OPEN));
            g.setColor(Color.WHITE);
            g.drawString(cm + " cm", cx + r - 36, cy + 14);
        }
    }

    /**
     * Draws the object dot inside a sector and its number and distance outside the half circle.
     */
    private void paintLabels(final Graphics2D g, final int i, final int cx, final int cy,
            final int radius, final double width) {
        final double mid = Math.toRadians((i + 0.5) * width);
        final double cos = Math.cos(mid);
        final double sin = Math.sin(mid);

        if (this.statuses[i] != SectorStatus.EMPTY) {
            final int r = radius * Math.min(this.distances[i], MAX_RANGE_CM) / MAX_RANGE_CM;
            final int x = cx + (int) Math.round(r * cos);
            final int y = cy - (int) Math.round(r * sin);
            g.setColor(Color.WHITE);
            g.fillOval(x - DOT_SIZE / 2, y - DOT_SIZE / 2, DOT_SIZE, DOT_SIZE);
            g.setColor(Color.BLACK);
            g.drawOval(x - DOT_SIZE / 2, y - DOT_SIZE / 2, DOT_SIZE, DOT_SIZE);
        }

        g.setFont(new Font(Font.SANS_SERIF, Font.BOLD, 11));
        g.setColor(Color.WHITE);
        this.drawCentered(g, String.valueOf(i + 1), cx + (radius - 14) * cos, cy - (radius - 14) * sin);

        final String text = this.statuses[i] == SectorStatus.EMPTY ? "-" : this.distances[i] + "cm";
        g.setFont(new Font(Font.SANS_SERIF, Font.PLAIN, 11));
        g.setColor(this.statuses[i] == SectorStatus.EMPTY ? Color.GRAY : colorOf(this.statuses[i]));
        this.drawCentered(g, text, cx + (radius + 20) * cos, cy - (radius + 20) * sin);
    }

    /**
     * Draws a string centred on a point.
     */
    private void drawCentered(final Graphics2D g, final String text, final double x, final double y) {
        final FontMetrics fm = g.getFontMetrics();
        g.drawString(text, (int) Math.round(x - fm.stringWidth(text) / 2.0),
                (int) Math.round(y + fm.getAscent() / 2.0 - 1));
    }

    /**
     * @param status sector status
     * @return the colour of a sector
     */
    private static Color colorOf(final SectorStatus status) {
        switch (status) {
            case DANGER:
                return new Color(230, 60, 60);
            case NEAR:
                return new Color(240, 150, 40);
            case FAR:
                return new Color(230, 210, 70);
            default:
                return new Color(40, 120, 60);
        }
    }
}
