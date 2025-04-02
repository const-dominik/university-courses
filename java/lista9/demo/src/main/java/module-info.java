module santagame {
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.graphics;

    opens santagame to javafx.fxml;

    exports santagame;
}
