package figury;

import java.lang.Math;

public class Point {
    private double x;
    private double y;

    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double getX() {
        return this.x;
    }

    public double getY() {
        return this.y;
    }

    public String toString() {
        return String.format("Point(%.2f, %.2f)", this.x, this.y);
    }

    public static double distance(Point p1, Point p2) {
        return Math.sqrt(Math.pow(p1.getX() - p2.getX(), 2.0) + Math.pow(p1.getY() - p2.getY(), 2.0));
    }

    public void move(Vector v) {
        this.x += v.dx;
        this.y += v.dy;
    }

    public void rotate(Point p, double angle) {
        angle = angle * (Math.PI / 180.0); // convert to radians

        // back to origin
        this.x -= p.x;
        this.y -= p.y;

        double sin = Math.sin(angle);
        double cos = Math.cos(angle);

        double new_x = this.x * cos - this.y * sin;
        double new_y = this.y * cos + this.x * sin;

        // back to where it was
        this.x = new_x += p.x;
        this.y = new_y += p.y;
    }

    public void reflect(Line l) {
        double perpendToLine = -l.b / l.a;
        // perpendicular to line, going through point and it's reflection:
        // y = ax + b -> ax - y + b = 0 -> Ax -y + C = 0 -> C = -Ax + y
        // A = perpendToLine
        // B = -1
        double C = perpendToLine * this.x + this.y;
        Line perpendicular = new Line(perpendToLine, 1, -C);
        Point intersect = Line.intersection(l, perpendicular);
        this.rotate(intersect, 180);
    }
}
