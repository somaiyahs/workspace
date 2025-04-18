package letterMaker;

public class Letter {
	
	/**
	 * Constant: prefix of the name of the receiver 
	 */
	public static String PREFIX = "Dear";
	
	/**
	 * Constant: signature of the letter
	 */
	public static String SIGNITURE = "Sincerely,\n";
	/**
	 * Name of the sender
	 */
	private String sender;
	/***
	 * Name of the receiver 
	 */
	private String receiver;
	/**
	 * Body of the letter
	 */
	private String body;
	
	/**
	 * constructs a letter with the given sender and receiver 
	 */
	public Letter(String from, String to) {
		this.sender = from;
		this.receiver = to;
		this.body = "\n";
	}
	
	/**
	 * Adding a new line to the body of the letter.
	 * @param line
	 */
	public void addLine(String line) {
		this.body = this.body.concat(line).concat("\n");
	}
	
	public String getText() {
		/* creating an empty letter */
		String letter = "";
		
		/* adding the name of the receiver */
		letter = letter.concat(PREFIX).concat(" ").concat(this.receiver)
				.concat(":").concat("\n");
		
		/* adding the body of the letter */
		letter = letter.concat(this.body).concat("\n");
		
		/* adding the signature of the letter */
		letter = letter.concat(SIGNITURE).concat("\n").concat(this.sender);
		
		return letter;
	}

}
