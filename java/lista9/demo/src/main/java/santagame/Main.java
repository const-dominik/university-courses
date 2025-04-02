package santagame;

import javafx.util.Duration;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import javafx.animation.PauseTransition;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class Main extends Application {
    public static final int FIELD_SIZE = 50;
    public static final int BOARD_SIZE = 10;
    private static final int NUM_PRESENTS = 10;
    private static final int NUM_CHILDREN = 8;
    private static final int MS_PER_MOVE = 750;
    public static Santa santa = new Santa(0, 0, NUM_PRESENTS);
    public static GridPane grid;
    public static final List<Child> children = new ArrayList<>();
    public static final List<Present> presents = new ArrayList<>();
    private static boolean isGameOver = false;
    private static Label presentsLabel = new Label();
    private static Thread gameThread;

    @Override
    public void start(Stage primaryStage) throws Exception {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/grid.fxml"));
        grid = loader.load();
        grid.setGridLinesVisible(true);

        VBox layout = new VBox(10);
        layout.getChildren().addAll(presentsLabel, grid);

        Scene scene = new Scene(layout, BOARD_SIZE * FIELD_SIZE, BOARD_SIZE * FIELD_SIZE + 50);
        scene.getStylesheets().add(getClass().getResource("/styles.css").toExternalForm());

        layout.getStyleClass().add("Label");

        scene.setOnKeyPressed(event -> {
            switch (event.getCode()) {
                case UP:
                    santa.moveSanta(0, -1);
                    break;
                case DOWN:
                    santa.moveSanta(0, 1);
                    break;
                case LEFT:
                    santa.moveSanta(-1, 0);
                    break;
                case RIGHT:
                    santa.moveSanta(1, 0);
                    break;
                case SPACE:
                    Present present = santa.dropPresent();
                    if (present == null) {
                        break;
                    }
                    presents.add(present);
                    PauseTransition delay = new PauseTransition(Duration.seconds(15));
                    delay.setOnFinished(ev -> {
                        if (presents.contains(present)) {
                            presents.remove(present);
                            grid.getChildren().remove(present.getRepresentation());

                            if (presents.isEmpty() && santa.getPresents() == 0) {
                                endGame("You don't have presents for the other kids! You lost!");
                                return;
                            }

                            if (presents.size() < children.size()
                                    - children.stream().filter(child -> !child.isGrounded())
                                            .count()) {
                                endGame("You don't have enough presents for the other kids! You lost!");
                                return;
                            }

                        }
                    });
                    delay.play();
                    break;
                default:
                    break;
            }
        });

        primaryStage.setTitle("Santa Game");
        primaryStage.setScene(scene);
        primaryStage.show();
        startGame();
    }

    public static void startGame() {
        children.clear();
        presents.clear();

        Platform.runLater(() -> {
            grid.getChildren().retainAll(grid.getChildren().get(0));
            santa.setX(0);
            santa.setY(0);
            santa.setPresents(NUM_PRESENTS);
            updatePresentsLabel();
            grid.add(santa.getRepresentation(), santa.getX(), santa.getY());

            for (int i = 0; i < NUM_CHILDREN; i++) {
                do {
                    int x = new Random().nextInt(BOARD_SIZE - 3) + 3;
                    int y = new Random().nextInt(BOARD_SIZE - 3) + 3;
                    if (x != santa.getX() || y != santa.getY()) {
                        boolean positionOccupied = false;
                        for (Child existingChild : children) {
                            if (existingChild.getX() == x && existingChild.getY() == y) {
                                positionOccupied = true;
                                break;
                            }
                        }
                        if (!positionOccupied) {
                            Child child = new Child(x, y);
                            grid.add(child.getRepresentation(), x, y);
                            children.add(child);
                            break;
                        }
                    }
                } while (true);
            }

            if (gameThread != null) {
                gameThread.interrupt();
            }

            isGameOver = false;
            gameThread = new Thread(() -> {
                while (!isGameOver) {
                    
                    for (int i = 0; i < NUM_CHILDREN; i++) {
                        Child child = children.get(i);
                        child.move();
                    }
                    try {
                        Thread.sleep(MS_PER_MOVE);
                    } catch (InterruptedException e) {
                        return;
                    }
                }
            });
            gameThread.start();
        });

    }

    public static void endGame(String message) {
        isGameOver = true;
        Platform.runLater(() -> {
            Alert alert = new Alert(Alert.AlertType.CONFIRMATION, message + " Would you like to play again?",
                    ButtonType.YES, ButtonType.NO);
            alert.showAndWait();

            if (alert.getResult() == ButtonType.YES) {
                startGame();
            } else {
                System.exit(0);
            }
        });
    }

    public static void updatePresentsLabel() {
        presentsLabel.setText("Presents: " + santa.getPresents());
    }

    public static void main(String[] args) {
        launch(args);
    }
}