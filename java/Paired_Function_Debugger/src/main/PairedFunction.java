package main;

import java.util.Objects;

public class PairedFunction {
	
	private String method_1;
	private String method_2;
	private int frequency;
	
	public PairedFunction(String method_1, String method_2, int frequency) {
		this.method_1 = method_1;
		this.method_2 = method_2;
		this.frequency = frequency;
	}
	public PairedFunction(String method_1, String method_2) {
		this.method_1 = method_1;
		this.method_2 = method_2;
		this.frequency = 1;
	}

	public String getMethod_1() {
		return method_1;
	}

	public String getMethod_2() {
		return method_2;
	}

	public int getFrequency() {
		return frequency;
	}

	public void setMethod_1(String method_1) {
		this.method_1 = method_1;
	}

	public void setMethod_2(String method_2) {
		this.method_2 = method_2;
	}

	public void setFrequency(int frequency) {
		this.frequency = frequency;
	}
	
	public boolean contains(String method) {
		boolean result = false;
		if (this.method_1.equals(method) || this.method_2.equals(method)) {
			result = true;
		}
		return result;
	}

	@Override
	public int hashCode() {
		return Objects.hash(frequency, method_1, method_2);
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		PairedFunction other = (PairedFunction) obj;
		if ((this.getMethod_1().hashCode() == other.getMethod_1().hashCode() ||
				this.getMethod_1().hashCode() == other.getMethod_2().hashCode()) &&
				(this.getMethod_2().hashCode() == other.getMethod_1().hashCode() ||
						this.getMethod_2().hashCode() == other.getMethod_2().hashCode())) {
			return true;
		}
		
				return  false;
	}
	@Override
	public String toString() {
		return "[" + method_1 + ",	" + method_2 + "]";
	}
	
	
	

}
