import javafx.application.Application;
import javafx.stage.Stage;


public class App extends Application {

    @Override
    public void start(Stage primaryStage){
        primStage.setTitle("Finance Tracker App");

        // Call UI component or controllers here 
        primaryStage.show();
    }
    public static void main(String[] args) {
        launch(args);
    }
}
