package santagame;

import javafx.scene.shape.Rectangle;
import javafx.scene.paint.Color;

public class Present {
    private int x;
    private int y;
    private Rectangle representation;

    public Present(int x, int y) {
        this.x = x;
        this.y = y;
        this.representation = new Rectangle(Main.FIELD_SIZE, Main.FIELD_SIZE, Color.TEAL);
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

    public void setRepresentation(Rectangle representation) {
        this.representation = representation;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }
}
