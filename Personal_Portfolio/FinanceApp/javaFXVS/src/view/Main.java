/* package view;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("hellofx.fxml"));
        primaryStage.setTitle("Hello World");
        primaryStage.setScene(new Scene(root, 400, 300));
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
} */
package view;


import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) {

        /* Creating a GridPane Layout  */

        GridPane gridPane = new GridPane();
        gridPane.setAlignment(Pos.CENTER);
        gridPane.setHgap(10);
        gridPane.setVgap(10);
        gridPane.setPadding(new Insets(25, 25, 25, 25));

        /* Creating the scence */
        Scene scene = new Scene(gridPane, 300, 250);
        primaryStage.setScene(scene);

        /* Initializing the stylesheets variable */
        scene.getStylesheets().add(Main.class.getResource("stylesheet.css").toExternalForm());

        /* Adding Text  */
        Text scenceTitle = new Text("Welcome");
        scenceTitle.setId("welcome-text");
        gridPane.add(scenceTitle, 0, 0, 2, 1);

        /* Adding Label  */
        Label username = new Label("Username: ");     
        gridPane.add(username, 0, 1);

        /* Adding text feild for username  */
        TextField userTextField = new TextField();
        gridPane.add(userTextField, 1, 1);

        /* Adding Label to Password Box */
        Label password = new Label("Password");
        gridPane.add(password, 0, 2);

        /* Adding text field for password box */
        PasswordField passwordField = new PasswordField();
        gridPane.add(passwordField, 1, 2);

        /****** Adding a button ********/
        Button btn = new Button("Sign in"); 
        HBox hbBtn = new HBox(10);
        hbBtn.setAlignment(Pos.BOTTOM_RIGHT);
        hbBtn.getChildren().add(btn);
        gridPane.add(hbBtn, 1, 4);
        

        /* Adding Text control for displaying the message.  */
        final Text actionTarget = new Text();
        gridPane.add(actionTarget, 1, 6);
        actionTarget.setId("actionTarget");
        btn.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event){
                actionTarget.setText("Sign in button pressed");
            }
        });

        primaryStage.setTitle("Finance Tracker App");
        
       // TransactionsController tc = new TransactionsController();
       // tc.addTransaction(STYLESHEET_MODENA, STYLESHEET_CASPIAN, 0);
        // Call UI components or controllers here
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
