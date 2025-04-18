package main;

import java.util.ArrayList;
import java.util.regex.Pattern;

public class Scope {
	private String scopeClass;
	private String scopeMethod;

	
	public Scope(String scopeClass, String scopeMethod) {
		this.scopeClass = scopeClass;
		this.scopeMethod = scopeMethod;
	}


	public String getScopeClass() {
		return scopeClass;
	}


	public void setScopeClass(String scopeClass) {
		this.scopeClass = scopeClass;
	}


	public String getScopeMethod() {
		return scopeMethod;
	}


	public void setScopeMethod(String scopeMethod) {
		this.scopeMethod = scopeMethod;
	}

	

	@Override
	public String toString() {
		return "Scope Class: " + scopeClass + ", Method: " + scopeMethod;
	}
	
	
	
}
