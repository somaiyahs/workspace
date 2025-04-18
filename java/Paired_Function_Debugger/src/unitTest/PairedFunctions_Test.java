package unitTest;

import org.junit.Assert;
import org.junit.Before;
import org.junit.jupiter.api.Test;

import main.PairedFunction;

public class PairedFunctions_Test {

	
	PairedFunction pair_1 = new PairedFunction("a", "b");
	PairedFunction pair_2 = new PairedFunction("b", "a");
	PairedFunction pair_3 = new PairedFunction("b", "b");
	PairedFunction pair_4 = new PairedFunction("c", "a");

	@Before
	public void setUp() {
		pair_1 = new PairedFunction("a", "b");
		pair_2 = new PairedFunction("a", "b");
	}
	@Test
	public void test_contains() {
		// The pair contains the given String
		Assert.assertTrue(pair_1.contains("a"));
	}
	
	@Test
	public void test_equals() {
		Assert.assertTrue(pair_1.equals(pair_2));
		Assert.assertTrue(pair_1.equals(pair_2));
	}


}



