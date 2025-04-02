import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.logging.Level;
import java.util.logging.LogManager;
import java.util.logging.Logger;

public class Okno extends Frame {
    private static final Logger logger = Logger.getLogger(Okno.class.getName());

    private TextField licznikField, mianownikField;
    private Button wyslijButton, nowaGraButton, rezygnujButton;
    private Scrollbar zakresScrollbar;
    private Label iloscProb, licznikLabel, mianownikLabel, zakresLabel, statusLabel, lewyZakresLabel, prawyZakresLabel,
            proponowanaLabel;

    private float maxLeft = 0, maxRight = 1;

    private Gra gra;

    public Okno() {
        super("Gra w odgadywanie ułamka");
        gra = new Gra();
        konfigurujLogowanie();

        setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);

        licznikLabel = new Label("Licznik:");
        mianownikLabel = new Label("Mianownik:");
        licznikField = new TextField(5);
        mianownikField = new TextField(5);
        wyslijButton = new Button("Wyslij propozycję");
        nowaGraButton = new Button("Nowa gra");
        rezygnujButton = new Button("Rezygnuj");
        iloscProb = new Label();
        zakresLabel = new Label();
        zakresScrollbar = new Scrollbar(Scrollbar.HORIZONTAL, 4, 1, 4, 20);
        statusLabel = new Label("Status: ");
        proponowanaLabel = new Label("");
        lewyZakresLabel = new Label("Lewy zakres: 0");
        prawyZakresLabel = new Label("Prawy zakres: 1");

        gbc.gridx = 0;
        gbc.gridy = 0;
        add(licznikLabel, gbc);

        gbc.gridx = 1;
        gbc.gridy = 0;
        add(licznikField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 1;
        add(mianownikLabel, gbc);

        gbc.gridx = 1;
        gbc.gridy = 1;
        add(mianownikField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 2;
        add(wyslijButton, gbc);

        gbc.gridx = 1;
        gbc.gridy = 2;
        add(nowaGraButton, gbc);

        gbc.gridx = 0;
        gbc.gridy = 3;
        add(iloscProb, gbc);

        gbc.gridx = 1;
        gbc.gridy = 3;
        add(zakresLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy = 4;
        gbc.gridwidth = 2;
        add(zakresScrollbar, gbc);

        gbc.gridx = 0;
        gbc.gridy = 5;
        add(statusLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy = 6;
        add(rezygnujButton, gbc);

        gbc.gridx = 0;
        gbc.gridy = 7;
        add(lewyZakresLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy = 8;
        add(prawyZakresLabel, gbc);

        gbc.gridx = 0;
        gbc.gridy = 9;
        add(proponowanaLabel, gbc);

        wyslijButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                wyslijPropozycje();
                pack();
                repaint();
            }
        });

        wyslijButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                wyswietlLiczbeZmiennopozycyjna();
            }

            @Override
            public void mouseExited(MouseEvent e) {
                ukryjLiczbeZmiennopozycyjna();
            }
        });

        nowaGraButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (gra.getStanGry() == Gra.StanGry.NIEAKTYWNA) {
                    rozpocznijNowaGre();
                } else {
                    gra.nieaktywna();
                    setElements();
                }
            }
        });

        rezygnujButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                gra.rezygnuj();
                setElements();
            }
        });

        zakresScrollbar.addAdjustmentListener(new AdjustmentListener() {
            public void adjustmentValueChanged(AdjustmentEvent e) {
                gra.zmienZakres(zakresScrollbar.getValue());
                setZakres(gra.getZakres());
            }
        });

        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                zakonczAplikacje();
            }
        });

        setZakres(4);
        setElements();

        pack();
        setVisible(true);
    }

    private void setIloscProb() {
        iloscProb.setText(String.format("Liczba prób: %d/%d", gra.getLicznikProb(), gra.getMaksLiczbaProb()));
    }

    private void setZakres(int l) {
        zakresLabel.setText(String.format("Zakres: %d", l));
    }

    private void setStatus(String status) {
        statusLabel.setText("Status: " + status);
    }

    private void setElements() {
        switch (gra.getStanGry()) {
            case NIEAKTYWNA:
                licznikField.setVisible(false);
                mianownikField.setVisible(false);
                wyslijButton.setVisible(false);
                iloscProb.setVisible(false);
                licznikLabel.setVisible(false);
                mianownikLabel.setVisible(false);
                zakresLabel.setVisible(true);
                zakresScrollbar.setVisible(true);
                nowaGraButton.setVisible(true);
                rezygnujButton.setVisible(false);
                lewyZakresLabel.setVisible(false);
                prawyZakresLabel.setVisible(false);
                setStatus("Gra nieaktywna");
                break;

            case AKTYWNA:
                licznikField.setVisible(true);
                mianownikField.setVisible(true);
                wyslijButton.setVisible(true);
                iloscProb.setVisible(true);
                licznikLabel.setVisible(true);
                mianownikLabel.setVisible(true);
                zakresLabel.setVisible(false);
                zakresScrollbar.setVisible(false);
                nowaGraButton.setVisible(false);
                rezygnujButton.setVisible(true);
                lewyZakresLabel.setVisible(true);
                prawyZakresLabel.setVisible(true);
                setStatus("Gra aktywna");
                break;

            case REZYGNAJCJA:
                setStatus("Gracz zrezygnował. Szukana wartość to: " + gra.getLiczba());
                logger.log(Level.INFO, generateLog("Gra zakończona rezygnacją."));
                rezygnujButton.setVisible(false);
                zakresScrollbar.setEnabled(true);
                nowaGraButton.setVisible(true);
                lewyZakresLabel.setVisible(false);
                prawyZakresLabel.setVisible(false);
                break;

            case PORAZKA:
                setStatus("Przegrana. Wykorzystano wszystkie próby. Szukana wartość to: " + gra.getLiczba());
                logger.log(Level.INFO, generateLog("Gra zakończona porażką."));
                rezygnujButton.setVisible(false);
                zakresScrollbar.setEnabled(true);
                nowaGraButton.setVisible(true);
                lewyZakresLabel.setVisible(false);
                prawyZakresLabel.setVisible(false);
                break;

            case ZWYCIESTWO:
                setStatus("Gratulacje! Udało się odgadnąć ułamek.");
                rezygnujButton.setVisible(false);
                zakresScrollbar.setEnabled(true);
                nowaGraButton.setVisible(true);
                lewyZakresLabel.setVisible(false);
                prawyZakresLabel.setVisible(false);
                break;
        }

        setIloscProb();
        pack();
        revalidate();
    }

    private void wyswietlLiczbeZmiennopozycyjna() {
        try {
            int licznik = Integer.parseInt(licznikField.getText());
            int mianownik = Integer.parseInt(mianownikField.getText());

            float l = (float) licznik / (float) mianownik;

            proponowanaLabel.setText(String.format("Proponowana: %.2f", l));
            proponowanaLabel.setVisible(true);
            pack();
            revalidate();
        } catch (NumberFormatException ex) {
            logger.log(Level.WARNING, generateLog("Niepoprawny format liczby do wyświetlenia"));
        }
    }

    private void ukryjLiczbeZmiennopozycyjna() {
        proponowanaLabel.setVisible(false);
        pack();
        revalidate();
    }

    private void konfigurujLogowanie() {
        try {
            LogManager.getLogManager().readConfiguration(Okno.class.getResourceAsStream("/logging.properties"));
        } catch (IOException e) {
            logger.log(Level.CONFIG, "Błąd konfiguracji logowania", e);
        }
    }

    private void wyslijPropozycje() {
        try {
            int licznik = Integer.parseInt(licznikField.getText());
            int mianownik = Integer.parseInt(mianownikField.getText());
            if (mianownik > gra.getZakres()) {
                logger.log(Level.INFO, generateLog("Mianownik większy niz zakres."));
                return;
            }
            float fl = (float) licznik / (float) mianownik;
            if (fl > 1.0) {
                logger.log(Level.INFO, generateLog("Liczba większa niż 1."));
                return;
            }
            Wymierna propozycja = new Wymierna(licznik, mianownik);

            int porownanie = propozycja.compareTo(gra.getLiczba());

            if (porownanie < 0) {
                setStatus("Szukana wartość jest większa.");
                if (fl > maxLeft) {
                    maxLeft = fl;
                    lewyZakresLabel.setText(String.format("Lewy zakres: %.2f", (float) licznik / (float) mianownik));
                }
            } else if (porownanie > 0) {
                setStatus("Szukana wartość jest mniejsza.");
                if (fl < maxRight) {
                    maxRight = fl;
                    prawyZakresLabel.setText(String.format("Prawy zakres: %.2f", (float) licznik / (float) mianownik));
                }
            } else {
                setStatus("Gratulacje! Udało się odgadnąć ułamek.");
                logger.log(Level.INFO, generateLog("Gra zakończona zwycięstwem."));
            }

            gra.odgadnij(propozycja);

            if (gra.getStanGry() == Gra.StanGry.AKTYWNA) {
                logger.log(Level.INFO, generateLog(String.format("Proba odgadnięcia: %s", propozycja)));
                setIloscProb();
            } else {
                setElements();
            }
        } catch (NumberFormatException ex) {
            logger.log(Level.WARNING, generateLog("Wysłano niepoprawny format liczby"));
        }
    }

    private void rozpocznijNowaGre() {
        gra.start(zakresScrollbar.getValue());
        licznikField.setText("");
        mianownikField.setText("");
        maxLeft = 0;
        maxRight = 1;

        lewyZakresLabel.setText("Lewy zakres: 0");
        prawyZakresLabel.setText("Prawy zakres: 1");

        setZakres(4);
        setElements();
        logger.log(Level.INFO, generateLog("Rozpoczęto nową grę"));
    }

    private String generateLog(String log) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("[yyyy-MM-dd HH:mm:ss]");
        String formattedDate = dateFormat.format(new Date());
        return String.format("[%s] %s", formattedDate, log);
    }

    private void zakonczAplikacje() {
        System.exit(0);
    }

    public static void main(String[] args) {
        new Okno();
    }
}
