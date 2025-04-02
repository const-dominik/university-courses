public class Wymierna implements Comparable<Wymierna> {
    private int licznik, mianownik = 1;

    public Wymierna() {
        this(0, 1);
    }

    public Wymierna(int n) {
        this(n, 1);
    }

    public Wymierna(int k, int m) {
        if (m == 0) {
            throw new IllegalArgumentException("Mianownik nie może być równy 0.");
        }

        if (m < 0) {
            k = -k;
            m = -m;
        }

        int nwd = nwd(Math.abs(k), Math.abs(m));
        this.licznik = k / nwd;
        this.mianownik = m / nwd;
    }

    private int nwd(int a, int b) {
        return b == 0 ? a : nwd(b, a % b);
    }

    public int getLicznik() {
        return licznik;
    }

    public int getMianownik() {
        return mianownik;
    }

    @Override
    public String toString() {
        if (mianownik == 1) {
            return Integer.toString(licznik);
        } else {
            return licznik + "/" + mianownik;
        }
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null || getClass() != obj.getClass())
            return false;
        Wymierna wymierna = (Wymierna) obj;
        return licznik == wymierna.licznik && mianownik == wymierna.mianownik;
    }

    @Override
    public int compareTo(Wymierna other) {
        int thisValue = licznik * other.mianownik;
        int otherValue = other.licznik * mianownik;
        return Integer.compare(thisValue, otherValue);
    }

    public float toFloat() {
        return (float) licznik / (float) mianownik;
    }

    public static Wymierna dodaj(Wymierna a, Wymierna b) {
        int k = a.licznik * b.mianownik + b.licznik * a.mianownik;
        int m = a.mianownik * b.mianownik;
        return new Wymierna(k, m);
    }

    public static Wymierna odejmij(Wymierna a, Wymierna b) {
        int k = a.licznik * b.mianownik - b.licznik * a.mianownik;
        int m = a.mianownik * b.mianownik;
        return new Wymierna(k, m);
    }

    public static Wymierna pomnoz(Wymierna a, Wymierna b) {
        int k = a.licznik * b.licznik;
        int m = a.mianownik * b.mianownik;
        return new Wymierna(k, m);
    }

    public static Wymierna podziel(Wymierna a, Wymierna b) {
        if (b.licznik == 0) {
            throw new ArithmeticException("Nie można dzielić przez 0.");
        }
        int k = a.licznik * b.mianownik;
        int m = a.mianownik * b.licznik;
        return new Wymierna(k, m);
    }
}
