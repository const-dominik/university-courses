package figury;

public class Triangle {
    private Point p1;
    private Point p2;
    private Point p3;

    public Triangle(Point p1, Point p2, Point p3) {
        Line l1 = Line.crossing(p1, p2);
        Line l2 = Line.crossing(p2, p3);
        if (Line.areParalell(l1, l2)) {
            throw new IllegalArgumentException("Can't build a triangle from points laying on one line.");
        }
        this.p1 = p1;
        this.p2 = p2;
        this.p3 = p3;
    }

    public Point getP1() {
        return this.p1;
    }

    public Point getP2() {
        return this.p2;
    }

    public Point getP3() {
        return this.p3;
    }

    public String toString() {
        return String.format("Triangle(%s, %s, %s)", this.p1, this.p2, this.p3);
    }

    public void move(Vector v) {
        p1.move(v);
        p2.move(v);
        p3.move(v);
    }

    public void rotate(Point p, double angle) {
        p1.rotate(p, angle);
        p2.rotate(p, angle);
        p3.rotate(p, angle);
    }

    public void reflect(Line l) {
        p1.reflect(l);
        p2.reflect(l);
        p3.reflect(l);
    }
}
