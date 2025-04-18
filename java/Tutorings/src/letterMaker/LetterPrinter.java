package letterMaker;

public class LetterPrinter {

	public static void main(String[] args) {
		
		/* create a letter object*/
		Letter letter = new Letter("Mary", "John");
		
		/* Adding lines to the letter */
		letter.addLine("I am sorry we must part.");
		letter.addLine("I wish you all the best.");
		
		/* displaying the actual content of the letter */
		System.out.println("Actual: _____________");
		System.out.println(letter.getText());
		
		/* adding extra space between actual and expected letters */
		System.out.println();
		
		/* defining the expected outcome of getText() method*/
		String expected = "Dear John:\n\nI am sorry we must part.\n"
				+ "I wish you all the best.\n\nSincerely,\n\nMary";
		/* Displaying the expected content of the letter */
		System.out.println("Expected: _____________");
		System.out.println(expected);
	}
}
