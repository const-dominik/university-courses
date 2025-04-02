package santagame;

import javafx.scene.shape.Rectangle;
import javafx.scene.paint.Color;

public class Santa {
    private int x;
    private int y;
    private Rectangle representation;
    private int presents;

    public Santa(int x, int y, int presents) {
        this.x = x;
        this.y = y;
        this.presents = presents;
        this.representation = new Rectangle(Main.FIELD_SIZE, Main.FIELD_SIZE, Color.RED);
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

    public int getPresents() {
        return this.presents;
    }

    public void setPresents(int presents) {
        this.presents = presents;
    }

    public Present dropPresent() {
        if (this.presents == 0) {
            return null;
        }
        this.presents--;
        Main.updatePresentsLabel();

        Present present = new Present(this.x, this.y);
        Main.grid.add(present.getRepresentation(), this.x, this.y);
        return present;
    }

    public void moveSanta(int dx, int dy) {
        int newX = (this.x + dx + Main.BOARD_SIZE) % Main.BOARD_SIZE;
        int newY = (this.y + dy + Main.BOARD_SIZE) % Main.BOARD_SIZE;

        // Check if the new position is occupied by a present or a child
        for (Present present : Main.presents) {
            if (present.getX() == newX && present.getY() == newY) {
                return;
            }
        }
        for (Child child : Main.children) {
            if (child.getX() == newX && child.getY() == newY) {
                return;
            }
        }

        Main.grid.getChildren().remove(this.representation);
        this.x = newX;
        this.y = newY;
        Main.grid.add(representation, this.x, this.y);
    }
}