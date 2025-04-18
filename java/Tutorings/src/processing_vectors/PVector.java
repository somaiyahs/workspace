package processing_vectors;


/**
 * This is a 
 * @author somaiyahsultani
 * Date: Dec, 2022
 */
public class PVector {

	private float x;
	private float y;
	
	public PVector(float _x, float _y) {
		this.x = _x;
		this.y = _y;
	}
	
	public float getX() {
		return this.x;
	}
	
	public float getY() {
		return this.y;
	}
	
	public void setX(float _x) {
		this.x = _x;
	}
	
	public void setY(float _y) {
		this.y = _y;
	}
	
	
	public void add(PVector v) {
		this.setX(this.getX() + v.getX());
		this.setY(this.getY() + v.getY());
	}

}
