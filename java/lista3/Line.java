package figury;

public class Line {
    public final double a;
    public final double b;
    public final double c;

    public Line(double a, double b, double c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }

    public String toString() {
        return String.format("Line(%.2fx + %.2fy + %.2f)", this.a, this.b, this.c);
    }

    public static Line moveByVector(Line l, Vector v) {
        return new Line(l.a, l.b, (l.c + v.dy - l.a * v.dx));
    }

    public static boolean areParalell(Line l1, Line l2) {
        return l1.a / l1.b == l2.a / l2.b;
    }

    public static boolean arePerpendicular(Line l1, Line l2) {
        return (l1.a / -l1.b) * (l2.a / -l2.b) == -1.0;
    }

    public static Point intersection(Line l1, Line l2) {
        if (Line.areParalell(l1, l2)) {
            throw new IllegalArgumentException("Lines are paralell.");
        }
        // -By = Ax + C
        // y = (Ax + C)/-B
        // (A1x + C1)/-B1 = (A2x + C2)/-B2 // *-B1B2
        // (A1x + C1)*B2 = (A2x + C2)*B1
        // A1B2x + C1B2 = A2B1x + C2B1
        // (A1B2 - A2B1)x = C2B1 - C1B2
        // x = (C2B1 - C1B2) / (A1B2 - A2B1)
        double x = (l2.c * l1.b - l1.c * l2.b) / (l1.a * l2.b - l2.a * l1.b);
        double y = (l1.a * x + l1.c) / -l1.b;

        return new Point(x, y);
    }

    public static Line crossing(Point p1, Point p2) {
        // y1 = ax1 + b
        // b = y1 - ax1

        // y2 = ax2 + b
        // y2 = ax2 + y1 - ax1
        // y2 = a(x2-x1) + y1
        // a = (y2-y1)/(x2-x1)
        double a = (p2.getY() - p1.getY()) / (p2.getX() - p1.getX());
        double b = p1.getY() - a * p1.getX();
        // y = ax + b
        // 0 = ax - y + b
        return new Line(a, -1, b);
    }
}
