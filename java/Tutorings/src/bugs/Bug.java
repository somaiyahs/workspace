package bugs;

public class Bug {
	private int bugPosition;
	private int direction = 1;
	
	public Bug(int initialPosition) {
		bugPosition = initialPosition;
	}
	
	public void turn() {
		direction = direction * -1;
	}
	
	public void move() {
		bugPosition += direction;
	}
	
	public int getPosition() {
		return bugPosition;
	}
}
