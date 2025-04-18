import java.io.*;
import java.util.*;
public class InnerFileFormatter {

    public static void main(String args[]) throws Exception{

        File input = new File("input.txt");
        Scanner sc = new Scanner(input); 
        while (sc.hasNextLine()){
            System.out.println("line");
        }
    }
}