public class Gra {
    private int zakres;
    private Wymierna liczba;
    private int maksIlośćPrób;
    private int licznikPrób;

    public enum StanGry {
        NIEAKTYWNA, AKTYWNA, REZYGNAJCJA, PORAZKA, ZWYCIESTWO
    }

    private StanGry stanGry;

    public Gra() {
        stanGry = StanGry.NIEAKTYWNA;
    }

    public void start(int z) {
        stanGry = StanGry.NIEAKTYWNA;
        if (z < 4 || z > 20) {
            throw new IllegalArgumentException("Zakres powinien być w przedziale [4, 20).");
        }
        zakres = z;

        maksIlośćPrób = (int) Math.ceil(3 * Math.log(zakres));

        licznikPrób = 0;

        int licz, mian;
        licz = (int) (Math.random() * zakres) + 1;
        mian = (int) (Math.random() * zakres) + 1;

        liczba = new Wymierna(licz, mian);
        try {
            assert liczba.compareTo(new Wymierna()) > 0 && liczba.compareTo(new Wymierna(1)) < 0;
        } catch (AssertionError e) {
            System.out.println("Trying to generate new number");
            start(z);
            return;
        }

        stanGry = StanGry.AKTYWNA;
    }

    public void rezygnuj() {
        if (stanGry == StanGry.AKTYWNA) {
            stanGry = StanGry.REZYGNAJCJA;
        }
    }

    public void nieaktywna() {
        stanGry = StanGry.NIEAKTYWNA;
    }

    public void odgadnij(Wymierna propozycja) {
        if (stanGry != StanGry.AKTYWNA) {
            throw new IllegalStateException("Gra nie jest w stanie aktywnym.");
        }

        licznikPrób++;

        if (propozycja.equals(liczba)) {
            stanGry = StanGry.ZWYCIESTWO;
        } else if (licznikPrób >= maksIlośćPrób) {
            stanGry = StanGry.PORAZKA;
        }
    }

    public StanGry getStanGry() {
        return stanGry;
    }

    public int getLicznikProb() {
        return licznikPrób;
    }

    public int getMaksLiczbaProb() {
        return maksIlośćPrób;
    }

    public int getZakres() {
        return zakres;
    }

    public void zmienZakres(int liczba) {
        zakres = liczba;
    }

    public Wymierna getLiczba() {
        return liczba;
    }

    public String getPrzedzial() {
        return String.format("[4, %d)", zakres);
    }
}