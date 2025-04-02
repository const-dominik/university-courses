import java.util.function.BinaryOperator;
import java.util.function.UnaryOperator;

public class Part3 {
    static UnaryOperator<Integer> collatzLength;
    {
        collatzLength = n -> {
            if (n == 1) {
                return 1;
            } else if (n % 2 == 0) {
                return 1 + collatzLength.apply(n / 2);
            } else {
                return 1 + collatzLength.apply(3 * n + 1);
            }
        };
    };

    BinaryOperator<Integer> gcd;
    {
        gcd = (a, b) -> b == 0 ? a : gcd.apply(b, a % b);
    };

    public static void main(String[] args) {
        Part3 part3 = new Part3();

        System.out.println(collatzLength.apply(11)); // 15
        System.out.println(collatzLength.apply(15)); // 18
        System.out.println(collatzLength.apply(27)); // 112

        System.out.println(part3.gcd.apply(36, 24)); // 12
        System.out.println(part3.gcd.apply(42, 56)); // 14
        System.out.println(part3.gcd.apply(54, 72)); // 18
        System.out.println(part3.gcd.apply(17, 19)); // 1
    }
}
