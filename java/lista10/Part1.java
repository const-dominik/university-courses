import java.io.*;
import java.util.*;
import java.util.regex.*;

public class Part1 {
    public static void main(String[] args) {
        String regex = "^[ \t]*((\\d+)[ \t]*(//.*)?)[ \t]*$";
        Pattern pattern = Pattern.compile(regex);
        ArrayList<Integer> numbers = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader("data_part1.txt"))) {
            String line;
            while ((line = br.readLine()) != null) {
                Matcher matcher = pattern.matcher(line);
                if (matcher.matches()) {
                    numbers.add(Integer.parseInt(matcher.group(2)));
                } else if (!line.trim().startsWith("//") && !line.trim().isEmpty()) {
                    throw new IllegalArgumentException("Invalid line format: " + line);
                }
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }

        System.out.println("Part 1");
        numbers.stream().sorted(Comparator.reverseOrder()).forEach(System.out::println);

        System.out.println("Part 2");
        numbers.stream().filter(Part1::isPrime).forEach(System.out::println);

        System.out.println("Part 3");
        final int n = 1000;
        int sum = numbers.stream().filter(i -> i < n).mapToInt(Integer::intValue).sum();
        System.out.println(sum);

        System.out.println("Part 4");
        final int m = 7;
        long count = numbers.stream().filter(i -> i % m == 0).count();
        System.out.println(count);
    }

    public static boolean isPrime(int num) {
        if (num <= 1)
            return false;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0)
                return false;
        }
        return true;
    }
}