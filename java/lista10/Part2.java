import java.io.*;
import java.util.*;
import java.util.regex.*;

class Triangle {
    double a, b, c;

    public Triangle(double a, double b, double c) {
        if (a + b <= c || a + c <= b || b + c <= a)
            throw new IllegalArgumentException("Invalid sides: " + a + ", " + b + ", " + c);
        this.a = a;
        this.b = b;
        this.c = c;
    }

    public double circumference() {
        return a + b + c;
    }

    public boolean isRect() {
        double[] sides = new double[] { a, b, c };
        Arrays.sort(sides);
        return Math.abs(Math.pow(sides[0], 2) + Math.pow(sides[1], 2) - Math.pow(sides[2], 2)) < 1e-10;
    }

    public boolean isEquil() {
        return a - b == 0 && b - c == 0;
    }

    public double area() {
        double p = circumference() / 2;
        return Math.sqrt(p * (p - a) * (p - b) * (p - c));
    }

    @Override
    public String toString() {
        return String.format("Triangle(%.2f, %.2f, %.2f)", a, b, c);
    }
}

public class Part2 {
    public static void main(String[] args) {
        String regex = "^[ \t]*((\\d+(\\.\\d+)?)[ \t]+(\\d+(\\.\\d+)?)[ \t]+(\\d+(\\.\\d+)?)[ \t]*(//.*)?)[ \t]*$";
        Pattern pattern = Pattern.compile(regex);
        LinkedList<Triangle> triangles = new LinkedList<>();

        try (BufferedReader br = new BufferedReader(new FileReader("data_part2.txt"))) {
            String line;
            while ((line = br.readLine()) != null) {
                Matcher matcher = pattern.matcher(line);
                if (matcher.matches()) {
                    triangles.add(
                            new Triangle(Double.parseDouble(matcher.group(2)), Double.parseDouble(matcher.group(4)),
                                    Double.parseDouble(matcher.group(6))));
                } else if (!line.trim().startsWith("//") && !line.trim().isEmpty()) {
                    throw new IllegalArgumentException("Invalid line format: " + line);
                }
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }

        System.out.println("Part 1");
        triangles.stream().sorted(Comparator.comparing(Triangle::circumference))
                .forEach(t -> System.out.println("Circumference: " + t.circumference() + ", " + t));

        System.out.println("Part 2");
        triangles.stream().filter(Triangle::isRect).forEach(t -> System.out.println(t));

        System.out.println("Part 3");
        long count = triangles.stream().filter(Triangle::isEquil).count();
        System.out.println(count);

        System.out.println("Part 4");
        Triangle min = triangles.stream().min(Comparator.comparing(Triangle::area)).orElse(null);
        Triangle max = triangles.stream().max(Comparator.comparing(Triangle::area)).orElse(null);
        System.out.println(min.area());
        System.out.println(max.area());
    }
}