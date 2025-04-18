import java.util.*;
import java.io.File;

public class App {
    public static void main(String[] args) throws Exception {
        // String test = "This is a    sample text that    will be formatted. It contains   multiple   spaces and punctuation.  This   is   a single  paragraph ! !";
        // String result = TextFormatter.formatText(test);
        // System.out.println(result);
        File inputFile = new File(args[0]);
        Scanner scanner = new Scanner(inputFile);
        while (scanner.hasNextLine()) {
            String str = scanner.nextLine();
            String text = TextFormatter.formatText(str);
            System.out.println("Formmatted text: " + text);
        }
        scanner.close();
    }
}



