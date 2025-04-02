package figury;

public class Segment {
    private Point p1;
    private Point p2;

    public Segment(Point p1, Point p2) {
        if (p1.getX() == p2.getX() && p1.getY() == p2.getY()) {
            throw new IllegalArgumentException("Points defining segment can't be the same.");
        }
        this.p1 = p1;
        this.p2 = p2;
    }

    public Point getP1() {
        return this.p1;
    }

    public Point getP2() {
        return this.p2;
    }

    public String toString() {
        return String.format("Segment(%s, %s)", this.p1, this.p2);
    }

    public void move(Vector v) {
        p1.move(v);
        p2.move(v);
    }

    public void rotate(Point p, double angle) {
        p1.rotate(p, angle);
        p2.rotate(p, angle);
    }

    public void reflect(Line l) {
        p1.reflect(l);
        p2.reflect(l);
    }
}
