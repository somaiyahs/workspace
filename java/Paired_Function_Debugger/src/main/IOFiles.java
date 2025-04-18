package main;
import java.util.*;
import java.io.*;

public class IOFiles {

	public static void main(String [] args) {
		
		try {
			
			Scanner scan = new Scanner(new File("resources\test.csv"));
			scan.useDelimiter(",");
			while (scan.hasNext()) {
				
			}
			
			
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
