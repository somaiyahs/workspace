import javafx.application.Application;
import javafx.stage.Stage;

public class App extends Application {
    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Finance Tracker App");
        // Call UI components or controllers here
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}