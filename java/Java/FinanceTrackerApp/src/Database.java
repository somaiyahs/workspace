import java.sql.Connection;;
import java.sql.DriverManager;


public class Database {

    private static final String URL = "jdbc:sqlite:finance_tracker.db";

    public static Connection connect(){

        try{
            return DriverManager.getConnection(URL);
        } catch (Exception e){
            e.printStackTrace();
            return null;
        }
    }
    
}
