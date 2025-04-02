import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputEvent;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class PegSolitaire extends JFrame {
    private final JPanel gameBoardPanel;
    private final JLabel gameStatusLabel;
    private final JMenu movesMenu = new JMenu("Ruchy");
    private final JMenu settingsMenu = new JMenu("Ustawienia");
    private final GameState gameState = GameState.load();
    private Point animatedPeg = null;
    private int selectedPegRow = 0;
    private int selectedPegCol = 2;
    private double animatedPegX = -1;
    private double animatedPegY = -1;
    private double animatedPegEndX = -1;
    private double animatedPegEndY = -1;
    private final int cellSize = 80;
    private final int boardSize = 7;

    public PegSolitaire() {
        setTitle("Samotnik - Peg Solitaire");
        setSize(cellSize * 7 + 40, cellSize * 8 + 40);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        gameBoardPanel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);

                Graphics2D g2d = (Graphics2D) g;
                g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
                g2d.setStroke(new BasicStroke(3));

                for (int i = 0; i < boardSize; i++) {
                    for (int j = 0; j < boardSize; j++) {
                        int x = j * cellSize;
                        int y = i * cellSize;

                        if (gameState.isCorner(i, j)) {
                            g.setColor(gameState.cornerColor);
                        } else {
                            g.setColor(gameState.backgroundColor);
                        }
                        g.fillRect(x, y, cellSize, cellSize);
                    }
                }

                for (int i = 0; i < boardSize; i++) {
                    for (int j = 0; j < boardSize; j++) {
                        int x = j * cellSize;
                        int y = i * cellSize;

                        if (animatedPeg != null && i == animatedPegEndX && j == animatedPegEndY) {
                            continue;
                        }

                        g.setColor(gameState.pegColor);
                        if (animatedPeg != null && i == animatedPeg.x && j == animatedPeg.y) {
                            if (gameState.fillPegs) {
                                g.fillOval((int) (animatedPegX * cellSize) + 10, (int) (animatedPegY * cellSize) + 10,
                                        cellSize - 20, cellSize - 20);

                                g.setColor(gameState.selectColor);
                                g.drawOval((int) (animatedPegX * cellSize + 10), (int) (animatedPegY * cellSize + 10),
                                        cellSize - 20,
                                        cellSize - 20);
                            } else {
                                g.setColor(gameState.selectColor);
                                g.drawOval((int) (animatedPegX * cellSize) + 10, (int) (animatedPegY * cellSize) + 10,
                                        cellSize - 20, cellSize - 20);
                            }
                        } else if (gameState.hasPeg(i, j)) {
                            if (gameState.fillPegs) {
                                g.fillOval(x + 10, y + 10, cellSize - 20, cellSize - 20);
                            } else {
                                g.drawOval(x + 10, y + 10, cellSize - 20, cellSize - 20);
                            }
                        }

                        if (i == selectedPegRow && j == selectedPegCol) {
                            g.setColor(gameState.selectColor);
                            g.drawOval(x + 10, y + 10, cellSize - 20, cellSize - 20);
                        }
                    }
                }
            }
        };

        gameBoardPanel.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if (gameState.isGameOver) {
                    return;
                }
                if (e.isShiftDown()) {
                    switch (e.getKeyCode()) {
                        case KeyEvent.VK_UP:
                            takePegUp();
                            break;
                        case KeyEvent.VK_DOWN:
                            takePegDown();
                            break;
                        case KeyEvent.VK_LEFT:
                            takePegLeft();
                            break;
                        case KeyEvent.VK_RIGHT:
                            takePegRight();
                            break;
                    }
                } else {
                    switch (e.getKeyCode()) {
                        case KeyEvent.VK_UP:
                            moveUp();
                            break;
                        case KeyEvent.VK_DOWN:
                            moveDown();
                            break;
                        case KeyEvent.VK_LEFT:
                            moveLeft();
                            break;
                        case KeyEvent.VK_RIGHT:
                            moveRight();
                            break;
                    }
                }
            }
        });
        gameBoardPanel.setFocusable(true);

        gameBoardPanel.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                handleMouseClick(e.getX(), e.getY());
            }
        });

        if (gameState.isGameOver)
            gameStatusLabel = new JLabel("Stan gry: nierozpoczęta");
        else
            gameStatusLabel = new JLabel("Stan gry: pozostało " + gameState.countRemainingPegs() + " pionów.");

        gameStatusLabel.setFont(new Font(gameStatusLabel.getFont().getName(), Font.PLAIN, 20));

        Container container = getContentPane();
        container.setLayout(new BorderLayout());
        container.add(gameBoardPanel, BorderLayout.CENTER);
        container.add(gameStatusLabel, BorderLayout.SOUTH);

        createMenu();
        setVisible(true);
    }

    // menu
    private void createMenu() {
        JMenuBar menuBar = new JMenuBar();
        JMenu gameMenu = new JMenu("Gra");
        gameMenu.setMnemonic(KeyEvent.VK_G);

        JMenuItem newGameItem = new JMenuItem("Start");
        newGameItem.setMnemonic(KeyEvent.VK_Z);

        JMenuItem stopGameItem = new JMenuItem("Stop");
        stopGameItem.setMnemonic(KeyEvent.VK_X);

        JMenuItem exitItem = new JMenuItem("Koniec");
        exitItem.setMnemonic(KeyEvent.VK_C);

        newGameItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                startGame();
                gameState.save();
            }
        });

        stopGameItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                endGame();
                gameState.save();
            }
        });

        exitItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });

        gameMenu.add(newGameItem);
        gameMenu.addSeparator();
        gameMenu.add(stopGameItem);
        gameMenu.addSeparator();
        gameMenu.add(exitItem);

        JMenuItem moveUpItem = new JMenuItem("Przeskok w górę");
        moveUpItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_W, 0));

        JMenuItem moveDownItem = new JMenuItem("Przeskok w dół");
        moveDownItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, 0));

        JMenuItem moveLeftItem = new JMenuItem("Przeskok w lewo");
        moveLeftItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_A, 0));

        JMenuItem moveRightItem = new JMenuItem("Przeskok w prawo");
        moveRightItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_D, 0));

        moveUpItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                moveUp();
            }
        });

        moveDownItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                moveDown();
            }
        });

        moveLeftItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                moveLeft();
            }
        });

        moveRightItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                moveRight();
            }
        });

        JMenuItem takeUpItem = new JMenuItem("Zabierz w górę");
        takeUpItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_W, InputEvent.SHIFT_DOWN_MASK));

        JMenuItem takeDownItem = new JMenuItem("Zabierz w dół");
        takeDownItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, InputEvent.SHIFT_DOWN_MASK));

        JMenuItem takeLeftItem = new JMenuItem("Zabierz w lewo");
        takeLeftItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_A, InputEvent.SHIFT_DOWN_MASK));

        JMenuItem takeRightItem = new JMenuItem("Zabierz w prawo");
        takeRightItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_D, InputEvent.SHIFT_DOWN_MASK));

        takeUpItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                takePegUp();
            }
        });

        takeDownItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                takePegDown();
            }
        });

        takeLeftItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                takePegLeft();
            }
        });

        takeRightItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                takePegRight();
            }
        });

        ButtonGroup boardTypeGroup = new ButtonGroup();
        JRadioButtonMenuItem britishBoardItem = new JRadioButtonMenuItem("Brytyjska");
        britishBoardItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                gameState.gameType = GameType.ENGLISH;
                gameState.clearBoard();
                gameState.save();
                gameBoardPanel.repaint();
            }
        });
        boardTypeGroup.add(britishBoardItem);
        settingsMenu.add(britishBoardItem);

        JRadioButtonMenuItem europeanBoardItem = new JRadioButtonMenuItem("Europejska");
        europeanBoardItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                gameState.gameType = GameType.EUROPEAN;
                gameState.clearBoard();
                gameState.save();
                gameBoardPanel.repaint();

            }
        });
        boardTypeGroup.add(europeanBoardItem);
        settingsMenu.add(europeanBoardItem);

        if (gameState.gameType == GameType.ENGLISH) {
            britishBoardItem.setSelected(true);
        } else if (gameState.gameType == GameType.EUROPEAN) {
            europeanBoardItem.setSelected(true);
        }

        JMenuItem boardColorItem = new JMenuItem("Kolor planszy");
        boardColorItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Color newColor = JColorChooser.showDialog(null, "Wybierz kolor", gameState.backgroundColor);
                if (newColor != null) {
                    gameState.backgroundColor = newColor;
                    gameBoardPanel.repaint();
                    gameState.save();

                }
            }
        });
        settingsMenu.add(boardColorItem);

        JMenuItem cornerColorItem = new JMenuItem("Kolor rogów");
        cornerColorItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Color newColor = JColorChooser.showDialog(null, "Wybierz kolor", gameState.backgroundColor);
                if (newColor != null) {
                    gameState.cornerColor = newColor;
                    gameBoardPanel.repaint();
                    gameState.save();

                }
            }
        });
        settingsMenu.add(cornerColorItem);

        JMenuItem selectedColor = new JMenuItem("Kolor obramowania");
        selectedColor.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Color newColor = JColorChooser.showDialog(null, "Wybierz kolor", gameState.selectColor);
                if (newColor != null) {
                    gameState.selectColor = newColor;
                    gameBoardPanel.repaint();
                    gameState.save();

                }
            }
        });
        settingsMenu.add(selectedColor);

        JMenuItem pegColorItem = new JMenuItem("Kolor pionów");
        pegColorItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Color newColor = JColorChooser.showDialog(null, "Wybierz kolor", gameState.pegColor);
                if (newColor != null) {
                    gameState.pegColor = newColor;
                    gameBoardPanel.repaint();
                    gameState.save();

                }
            }
        });
        settingsMenu.add(pegColorItem);

        JCheckBoxMenuItem fillPegsItem = new JCheckBoxMenuItem("Wypełnianie kolorem wnętrza pionów");
        fillPegsItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                gameState.fillPegs = fillPegsItem.isSelected();
                gameBoardPanel.repaint();
                gameState.save();

            }
        });

        JMenu helpMenu = new JMenu("Pomoc");

        JMenuItem aboutGameItem = new JMenuItem("O grze");
        aboutGameItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JOptionPane.showMessageDialog(null, "Zasady gry w Samotnika:\n\n" +
                        "1. Możesz wykonać ruch przeskakując pionkiem nad pionkiem w puste pole.\n"
                        +
                        "2. Przeskoczony pionek jest usuwany.\n" +
                        "3. Celem gry jest usunięcie wszystkich pionków oprócz jednego, który powinien znaleźć się w centrum planszy.\n"
                        +
                        "4. Możesz przeskakiwać pionki tylko pionowo i poziomo o 1.\n\n" +
                        "Możesz rozpocząć grę z menu Gra -> Start. \n" +
                        "Możesz poruszać się za pomocą menu ruchów, klawiatury lub myszy. \nUżyj strzałek/WASD do poruszania się, a Shift + strzałka/WASD do zabierania pionków. \n",
                        "O grze",
                        JOptionPane.INFORMATION_MESSAGE);
            }
        });
        helpMenu.add(aboutGameItem);

        JMenuItem aboutAppItem = new JMenuItem("O aplikacji");
        aboutAppItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JOptionPane.showMessageDialog(null, "O aplikacji:\n" +
                        "Autor: Dominik Kiełbowicz \n" +
                        "Wersja: 1.0 \n" +
                        "Data powstania: 31.01.2024", "O aplikacji",
                        JOptionPane.INFORMATION_MESSAGE);
            }
        });
        helpMenu.add(aboutAppItem);

        fillPegsItem.setSelected(gameState.fillPegs);
        settingsMenu.add(fillPegsItem);

        movesMenu.setEnabled(!gameState.isGameOver);
        settingsMenu.setEnabled(gameState.isGameOver);

        movesMenu.add(takeUpItem);
        movesMenu.add(takeDownItem);
        movesMenu.add(takeLeftItem);
        movesMenu.add(takeRightItem);

        movesMenu.add(moveUpItem);
        movesMenu.add(moveDownItem);
        movesMenu.add(moveLeftItem);
        movesMenu.add(moveRightItem);

        menuBar.add(gameMenu);
        menuBar.add(movesMenu);
        menuBar.add(settingsMenu);
        menuBar.add(Box.createHorizontalGlue());
        menuBar.add(helpMenu);

        setJMenuBar(menuBar);
    }

    // moves
    private void moveUp() {
        if (gameState.isOnBoard(selectedPegRow - 1, selectedPegCol)) {
            selectedPegRow -= 1;
            gameBoardPanel.repaint();
        }
    }

    private void moveDown() {
        if (gameState.isOnBoard(selectedPegRow + 1, selectedPegCol)) {
            selectedPegRow += 1;
            gameBoardPanel.repaint();
        }
    }

    private void moveLeft() {
        if (gameState.isOnBoard(selectedPegRow, selectedPegCol - 1)) {
            selectedPegCol -= 1;
            gameBoardPanel.repaint();
        }
    }

    private void moveRight() {
        if (gameState.isOnBoard(selectedPegRow, selectedPegCol + 1)) {
            selectedPegCol += 1;
            gameBoardPanel.repaint();
        }
    }

    private void takePegUp() {
        makeAnimatedMove(selectedPegRow - 2, selectedPegCol);
    }

    private void takePegDown() {
        makeAnimatedMove(selectedPegRow + 2, selectedPegCol);
    }

    private void takePegLeft() {
        makeAnimatedMove(selectedPegRow, selectedPegCol - 2);
    }

    private void takePegRight() {
        makeAnimatedMove(selectedPegRow, selectedPegCol + 2);
    }

    // moves tech
    private void animateMove(int endRow, int endCol) {
        double dx = (endCol - animatedPegX) / 100.0;
        double dy = (endRow - animatedPegY) / 100.0;
        animatedPegEndX = endRow;
        animatedPegEndY = endCol;
        for (int i = 0; i < 100; i++) {
            animatedPegX += dx;
            animatedPegY += dy;
            try {
                Thread.sleep(2);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            repaint();
        }
        animatedPeg = null;
        animatedPegEndX = -1;
        animatedPegEndY = -1;
        selectedPegCol = endCol;
        selectedPegRow = endRow;
        repaint();
    }

    private void makeAnimatedMove(int row, int col) {
        if (gameState.makeMove(selectedPegRow, selectedPegCol, row, col)) {
            animatedPeg = new Point(selectedPegRow, selectedPegCol);
            animatedPegX = selectedPegCol;
            animatedPegY = selectedPegRow;
            selectedPegRow = -1;
            selectedPegCol = -1;
            new Thread(() -> animateMove(row, col)).start();
            if (gameState.isGameOver()) {
                endGame();
            } else {
                gameStatusLabel.setText("Stan gry: pozostało " + gameState.countRemainingPegs() + " pionów.");
            }
        }
    }

    private void handleMouseClick(int mouseX, int mouseY) {
        gameBoardPanel.requestFocusInWindow();
        if (gameState.isGameOver) {
            return;
        }
        int row = mouseY / cellSize;
        int col = mouseX / cellSize;

        if (!gameState.isOnBoard(row, col)) {
            return;
        }

        makeAnimatedMove(row, col);
        if (gameState.hasPeg(row, col)) {
            selectedPegRow = row;
            selectedPegCol = col;
        }

        repaint();
    }

    // state management

    private void startGame() {
        gameState.clearBoard();
        gameState.isGameOver = false;
        movesMenu.setEnabled(true);
        settingsMenu.setEnabled(false);
        selectedPegRow = 0;
        selectedPegCol = 2;
        gameStatusLabel.setText("Stan gry: pozostało " + gameState.countRemainingPegs() + " pionów.");
    }

    private void endGame() {
        gameState.isGameOver = true;
        movesMenu.setEnabled(false);
        settingsMenu.setEnabled(true);

        if (gameState.isGameWon()) {
            gameStatusLabel.setText("Stan gry: Wygrałeś! Pozostał jeden pion na środku planszy.");
        } else {
            int remainingPegs = gameState.countRemainingPegs();
            gameStatusLabel.setText("Stan gry: Przegrałeś! Pozostało " + remainingPegs + " pionów.");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new PegSolitaire());
    }
}