package lista1;

import java.util.Scanner;

public class zad1 {
	private String name;
	private int birthyear;

	private static String[] romanNumerals = {
			"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"
	};
	private static int[] values = {
			1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
	};

	public static void main(String[] args) {
		zad1 self = new zad1();
		self.getData();
		self.greet();
		zad1.printRoman(self.birthyear);
		self.printChinesePatron(self.birthyear);
	}

	public void getData() {
		Scanner scanner = new Scanner(System.in);

		System.out.print("Enter your name: ");
		name = scanner.nextLine();

		System.out.print("Enter birth year: ");
		birthyear = scanner.nextInt();

		scanner.close();
	}

	public void greet() {
		System.out.println("Hello, " + name + "!");
	}

	public static void printRoman(int year) {
		if (year < 1 || year > 3999) {
			throw new IllegalArgumentException("liczba " + year + " spoza zakresu 1-3999");
		}

		StringBuilder romanYear = new StringBuilder();
		int i = 0;

		while (year > 0) {
			if (year - values[i] >= 0) {
				romanYear.append(romanNumerals[i]);
				year -= values[i];
			} else {
				i++;
			}
		}

		System.out.println(romanYear);
	}

	public void printChinesePatron(int year) {
		String[] chineseZodiacSigns = {
				"Szczur", "Bawół", "Tygrys", "Królik", "Smok", "Wąż", "Koń", "Owca", "Małpa", "Kurczak", "Pies",
				"Świnia"
		};

		int zodiacIndex = (year - 4) % 12;

		if (zodiacIndex < 0) {
			zodiacIndex += 12;
		}

		String patron = switch (zodiacIndex) {
			case 0 -> chineseZodiacSigns[zodiacIndex];
			case 1 -> chineseZodiacSigns[zodiacIndex];
			case 2 -> chineseZodiacSigns[zodiacIndex];
			case 3 -> chineseZodiacSigns[zodiacIndex];
			case 4 -> chineseZodiacSigns[zodiacIndex];
			case 5 -> chineseZodiacSigns[zodiacIndex];
			case 6 -> chineseZodiacSigns[zodiacIndex];
			case 7 -> chineseZodiacSigns[zodiacIndex];
			case 8 -> chineseZodiacSigns[zodiacIndex];
			case 9 -> chineseZodiacSigns[zodiacIndex];
			case 10 -> chineseZodiacSigns[zodiacIndex];
			case 11 -> chineseZodiacSigns[zodiacIndex];
			default -> "blad";
		};

		System.out.println(patron);
	}
}
