package santagame;

import java.util.Random;

import javafx.application.Platform;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

public class Child {
    private int x;
    private int y;
    private Rectangle representation;
    private int awakeness;
    private boolean isGrounded;

    /*
     * When awakeness is positive, decrease it by 1 with every move.
     * 
     * When awakeness is positive->0, fall asleep and give it a random
     * negative number.
     * 
     * When awakeness is negative, increase it by 1 with every move.
     * 
     * When awakeness is negative->0, wake up and give it a random positive number.
     */

    public Child(int x, int y) {
        this.x = x;
        this.y = y;
        this.isGrounded = false;
        this.awakeness = new Random().nextInt(20);
        this.representation = new Rectangle(Main.FIELD_SIZE, Main.FIELD_SIZE, Color.BLUE);

    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public Rectangle getRepresentation() {
        return representation;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    public boolean isSleeping() {
        return awakeness < 0;
    }

    public boolean isGrounded() {
        return isGrounded;
    }

    public void wakeUp() {
        int[][] directions = { { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } };
        for (int[] direction : directions) {
            int x = (this.x + direction[0] + Main.BOARD_SIZE) % Main.BOARD_SIZE;
            int y = (this.y + direction[1] + Main.BOARD_SIZE) % Main.BOARD_SIZE;
            if (Main.santa.getX() == x && Main.santa.getY() == y) {
                Main.endGame("Child catches Santa! You lost!");
                return;
            }
            for (Present present : Main.presents) {
                if (present.getX() == x && present.getY() == y) {

                    this.isGrounded = true;
                    boolean allGrounded = true;
                    for (Child child : Main.children) {
                        if (!child.isGrounded)
                            allGrounded = false;
                    }

                    if (allGrounded) {
                        Main.endGame("All children grounded! You won!");
                    }

                    Main.presents.remove(present);
                    this.representation.setFill(Color.GREEN);
                    Platform.runLater(() -> {
                        Main.grid.getChildren().remove(present.getRepresentation());
                        Main.grid.getChildren().remove(this.representation);
                        Main.grid.add(this.representation, x, y);
                    });
                    this.x = x;
                    this.y = y;
                    return;
                }
            }
        }
        this.representation.setFill(Color.BLUE);
    }

    public void move() {
        if (isGrounded)
            return;

        if (awakeness > 0) {
            awakeness--;
            if (awakeness == 0) {
                awakeness = -new Random().nextInt(10);
                this.representation.setFill(Color.YELLOW);
            }
        } else {
            awakeness++;
            if (awakeness == 0) {
                awakeness = new Random().nextInt(20);
                wakeUp();
                if (isGrounded)
                    return;
            } else
                return;
        }

        Platform.runLater(() -> {
            outerLoop: for (int dx = -3; dx <= 3; dx++) {
                for (int dy = -3; dy <= 3; dy++) {
                    int i = (x + dx + Main.BOARD_SIZE) % Main.BOARD_SIZE;
                    int j = (y + dy + Main.BOARD_SIZE) % Main.BOARD_SIZE;
                    if (i == Main.santa.getX() && j == Main.santa.getY()) {
                        int base_x = this.x;
                        int base_y = this.y;

                        if (Math.abs(i - x) > Math.abs(j - y)) {
                            if (Math.abs(i - x) <= Main.BOARD_SIZE / 2)
                                this.x = ((i > x ? this.x + 1 : this.x - 1) + Main.BOARD_SIZE) % Main.BOARD_SIZE;
                            else
                                this.x = ((i > x ? this.x - 1 : this.x + 1) + Main.BOARD_SIZE) % Main.BOARD_SIZE;
                        } else {
                            if (Math.abs(j - y) <= Main.BOARD_SIZE / 2)
                                this.y = ((j > y ? this.y + 1 : this.y - 1) + Main.BOARD_SIZE) % Main.BOARD_SIZE;
                            else
                                this.y = ((j > y ? this.y - 1 : this.y + 1) + Main.BOARD_SIZE) % Main.BOARD_SIZE;
                        }

                        for (Present present : Main.presents) {
                            if (present.getX() == this.x && present.getY() == this.y) {
                                this.x = base_x;
                                this.y = base_y;
                                break outerLoop;
                            }
                        }
                        for (Child child : Main.children) {
                            if (this != child && child.getX() == this.x && child.getY() == this.y) {
                                this.x = base_x;
                                this.y = base_y;
                                break outerLoop;
                            }
                        }
                        if (Main.santa.getX() == this.x && Main.santa.getY() == this.y) {
                            Main.endGame("Child catches Santa! You lost!");
                            return;
                        }

                        Main.grid.getChildren().remove(this.representation);
                        Main.grid.add(this.representation, this.x, this.y);
                        return;
                    }
                }
            }

            boolean validMove = false;
            int dx, dy, newX, newY;
            while (!validMove) {
                dx = new Random().nextInt(3) - 1;
                dy = new Random().nextInt(3) - 1;
                newX = (this.x + dx + Main.BOARD_SIZE) % Main.BOARD_SIZE;
                newY = (this.y + dy + Main.BOARD_SIZE) % Main.BOARD_SIZE;

                boolean occupied = false;
                for (Present present : Main.presents) {
                    if (present.getX() == newX && present.getY() == newY) {
                        occupied = true;
                        break;
                    }
                }
                for (Child child : Main.children) {
                    if (child != this && child.getX() == newX && child.getY() == newY) {
                        occupied = true;
                        break;
                    }
                }

                if (!occupied) {
                    validMove = true;
                    this.x = newX;
                    this.y = newY;
                }
            }

            Main.grid.getChildren().remove(this.representation);
            Main.grid.add(this.representation, x, y);
        });
    }
}
