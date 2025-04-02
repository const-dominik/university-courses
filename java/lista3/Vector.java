package figury;

public class Vector {
    public final double dx;
    public final double dy;

    public Vector(double dx, double dy) {
        this.dx = dx;
        this.dy = dy;
    }

    @Override public String toString() {
        return String.format("Vector(%.2f, %.2f)", this.dx, this.dy);
    }

    public static Vector add(Vector v1, Vector v2) {
        double newX = v1.dx + v2.dx;
        double newY = v1.dy + v2.dy;
        return new Vector(newX, newY);
    }
}
