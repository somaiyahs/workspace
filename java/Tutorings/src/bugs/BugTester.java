package bugs;

public class BugTester {

	public static void main(String[] args) {
		Bug bugsy = new Bug(10);
		bugsy.move(); // Now the position is 11
		System.out.println("Actual: " + bugsy.getPosition());
		System.out.println("Expected: 11");
		
		bugsy.turn();
		bugsy.move(); // Now the position is 10
		System.out.println("Actual: " + bugsy.getPosition());
		System.out.println("Expected: 10");
	}
}
