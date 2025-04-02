import figury.Line;
import figury.Point;
import figury.Vector;

public class tests {
    public static void main(String[] args) {
        // Vectors:
        Vector v1 = new Vector(5.3, 7.2);
        Vector v2 = new Vector(2.7, 3.8);
        Vector v = Vector.add(v1, v2);
        System.out.println(v);

        // Lines:
        Vector v3 = new Vector(0, -3);
        Line l1 = new Line(5, -1, -5);
        Line l2 = new Line(-0.2, -1, -5);
        Line l3 = new Line(5, -1, -1);

        Line moved = Line.moveByVector(l1, v3);
        System.out.println(moved);
        System.out.println(Line.areParalell(l1, l3));
        System.out.println(Line.arePerpendicular(l1, l2));
        System.out.println(Line.arePerpendicular(l1, l3));
        System.out.println(Line.areParalell(l1, l2));
        System.out.println(Line.intersection(l1, l2));

        // Points:
        Point p1 = new Point(2.3, 3.4);
        Point p2 = new Point(0, 0);
        p1.move(v);
        System.out.println(p1);

        p1.rotate(p2, 180);
        System.out.println(p1);

        p1.reflect(l1);
        System.out.println(p1);
    }
}
