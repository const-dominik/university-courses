import java.awt.Color;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

enum GameType {
    ENGLISH, EUROPEAN
}

public class GameState implements Serializable {
    private static final long serialVersionUID = 1L;
    private boolean[][] board;

    public GameType gameType = GameType.ENGLISH;
    public Color pegColor = Color.BLUE;
    public Color selectColor = Color.RED;
    public Color backgroundColor = Color.LIGHT_GRAY;
    public Color cornerColor = Color.GRAY;
    public boolean fillPegs = true;
    public boolean isGameOver = true;

    public GameState() {
        clearBoard();
    }

    public boolean[][] clearBoard() {
        board = new boolean[7][7];
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                board[i][j] = true;
            }
        }
        board[3][3] = false;
        return board;
    }

    public boolean hasPeg(int i, int j) {
        if (!isOnBoard(i, j)) {
            return false;
        }
        return board[i][j];
    }

    public void setPeg(int i, int j, boolean hasPeg) {
        if (isOnBoard(i, j)) {
            board[i][j] = hasPeg;
        }
    }

    public boolean isOnBoard(int i, int j) {
        return i >= 0 && i < 7 && j >= 0 && j < 7 && !isCorner(i, j);
    }

    public boolean isCorner(int i, int j) {
        if (gameType == GameType.ENGLISH) {
            return (i < 2 || i > 4) && (j < 2 || j > 4);
        } else if (gameType == GameType.EUROPEAN) {
            return ((i == 0 || i == 6) && (j < 2 || j > 4)) || ((j == 0 || j == 6) && (i < 2 || i > 4));
        }
        return false;
    }

    public boolean makeMove(int fromI, int fromJ, int toI, int toJ) {
        if (hasPeg(fromI, fromJ) && !hasPeg(toI, toJ) && isOnBoard(toI, toJ)) {
            if (fromI == toI && Math.abs(fromJ - toJ) == 2 && hasPeg(fromI, (fromJ + toJ) / 2)) {
                setPeg(fromI, fromJ, false);
                setPeg(fromI, (fromJ + toJ) / 2, false);
                setPeg(toI, toJ, true);
                save();
                return true;
            } else if (fromJ == toJ && Math.abs(fromI - toI) == 2 && hasPeg((fromI + toI) / 2, fromJ)) {
                setPeg(fromI, fromJ, false);
                setPeg((fromI + toI) / 2, fromJ, false);
                setPeg(toI, toJ, true);
                save();
                return true;
            }
        }
        return false;
    }

    public boolean isGameOver() {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                if (hasPeg(i, j)) {
                    if ((i > 1 && hasPeg(i - 1, j) && !hasPeg(i - 2, j) && !isCorner(i - 2, j)) ||
                            (i < 5 && hasPeg(i + 1, j) && !hasPeg(i + 2, j) && !isCorner(i + 2, j)) ||
                            (j > 1 && hasPeg(i, j - 1) && !hasPeg(i, j - 2) && !isCorner(i, j - 2)) ||
                            (j < 5 && hasPeg(i, j + 1) && !hasPeg(i, j + 2) && !isCorner(i, j + 2))) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    public int countRemainingPegs() {
        int count = 0;
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                if (hasPeg(i, j)) {
                    count++;
                }
            }
        }
        return count;
    }

    public boolean isGameWon() {
        return isGameOver() && hasPeg(3, 3) && countRemainingPegs() == 1;
    }

    public void save() {
        try (ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream("solitaire.ser"))) {
            out.writeObject(this);
        } catch (IOException e) {
            e.printStackTrace();
            System.err.println("Error saving game state: " + e.getMessage());
        }
    }

    public static GameState load() {
        File file = new File("solitaire.ser");
        GameState gameState = new GameState();
        if (file.exists()) {
            try (ObjectInputStream in = new ObjectInputStream(new FileInputStream(file))) {
                gameState = (GameState) in.readObject();
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }
        }
        return gameState;
    }
}