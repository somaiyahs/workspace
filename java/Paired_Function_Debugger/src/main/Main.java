package main;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;
import java.util.Map.Entry;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/*
 * The general format of a line for classes are as follow:
 * C:class1 class2
 *
 * The general format of the line for methods will be as follow:
 * M:Class1:<method1>(arg_types) (typeOfCall)Class2:<Method2>(arg_types)
 */



public class Main {

	/**
	 * Constant REGEX: a colon or (a sequence of opening parenthesis, anything not a closing parenthesis and a closing parenthesis)
	 */
	private static final String REGEX = ":|\\([^\\)]*\\)";
	/**
	 * Constant START_INDEX: specifies the start of the information that we are interested in within the given line
	 */
	private static final int START_INDEX = 2;
	/**
	 * Constant PATTERN_M: Specifies the pattern of a line that provides information on a method
	 */
	private static final Pattern PATTERN_M = Pattern.compile("^[M:]"); 
	/**
	 * Constant PATH: represents the path to the file 
	 * containing the textual format of a call graph 
	 */
	private static final String PATH = "src/callGraph2.txt";
	/**
	 * Constant INIT: to be ignored
	 */
	private static final String INIT = "<init>";
	/**
	 * Constant MAIN: main method to be ignored 
	 */
	private static final Pattern MAIN = Pattern.compile("main\\([^\\\\)]*\\)");
	/**
	 * 
	 * @param args
	 * @throws FileNotFoundException
	 */


	public static void main(String[] args) throws FileNotFoundException{


		// Getting the HashMap version of graph 
		HashMap<String, HashSet<String>> map = cgToMap(new File(PATH));
	//	HashMap<PairedFunction, ArrayList<String>> paired = findPairs(map);

		// Testing
		for (java.util.Map.Entry<String, HashSet<String>> e: map.entrySet()) {
			System.out.println("*************************************************");
			System.out.println("Scope:	" + e.getKey().toString());
			System.out.println("functions:");

			Iterator<String> it = e.getValue().iterator();
			while(it.hasNext()) {
				System.out.println(it.next());
			}
			System.out.println();
		}

		// populate the paired functions 



	}

	/**
	 * takes a HashMap of the scopes and their methods and provides a map 
	 * where keys are the paired functions and values are the scopes 
	 * @param mapScope
	 * @return
	 */
	public static HashMap<PairedFunction, HashSet<String>> findPairs(HashMap<String, HashSet<String>> sMap){

		HashMap<PairedFunction, ArrayList<String>> map = new HashMap<>();
		String first = "";
		for (Entry<String, ArrayList<String>> e: sMap.entrySet()) {
			ArrayList<String> functions = e.getValue();
			for(int i = 0; i < functions.size() - 1; i++)
				for (int j = i + 1; j < functions.size(); j++) {

					PairedFunction p = new PairedFunction(functions.get(i), functions.get(j));
					if(map.containsKey(p)) {
						map.get(p).add(e.getKey());
					}
					else {
						ArrayList<String> val = new ArrayList<>();
						val.add(e.getKey());
						map.put(p, val);
					}
				}
		}

		return map;
	}



	/**
	 * Receives a text file representation of a call graph 
	 * and returns a corresponding HashMap where
	 * Key:		is a Scope made up of class name and method name 
	 * value:	is a HashSet of all the methods used inside the scope 
	 * @param File file
	 * @return HashMap<Scope, HashSet<String>>
	 */
	public static HashMap<String, HashSet<String>> cgToMap(File file){

		// local variables 
		HashMap<String, HashSet<String>> scopeMap = new HashMap<>();// To store the information of the call graph
		Scanner input;
		Matcher matcher;
		String line;

		try{
			input = new Scanner(file);
			scopeMap = new HashMap<>();

			while(input.hasNextLine()) {

				line = input.nextLine();

				// Checking if the line contains information on the methods
				matcher = PATTERN_M.matcher(line);

				if(matcher.find() && !line.contains(INIT)) {

					/* Parsing each line into an array of strings where: 
					 * arr[0] = M
					 * arr[1] = Class1
					 * arr[2] = method1
					 * arr[3] = " "
					 * arr[4] = class2
					 * arr[5] = method2
					 */
					String[] arr = line.split(Main.REGEX);
					//Scope sc = new Scope(arr[1], arr[2]);
					String scope = arr[1]+":	"+arr[2];
					String method = arr[4]+":	"+arr[5];
					if (scopeMap.containsKey(scope)) {

						scopeMap.get(scope).add(method);	
					} 
					else {
						HashSet<String> set = new HashSet<>();
						set.add(method);
						scopeMap.put(scope, set);
					}
				}
			}
			input.close();
		}catch(FileNotFoundException e){
			System.out.println("Error: File not found" + e.getLocalizedMessage());
		}
		return scopeMap;
	}

}
















//HashMap<String, Entry> enrtyMap = new HashMap<>();
//HashMap<String, ArrayList<String>> singleMethodMap = new HashMap<>();
//HashMap<PairedFunction, ArrayList<String>> pairedFunctionMap = new HashMap<>();
//ArrayList<Entry> entries = new ArrayList<Entry>();
//
///*
// * The general format of a line for classes are as follow:
// * C:class1 class2
// */
///* The general format of the line for methods will be as follow:
// * M:Class1:<method1>(arg_types) (typeOfCall)Class2:<Method2>(arg_types)
// * Therefore after splitting the given String using REGEX, we will end up having an array as follow:
// * arr[0] = M
// * arr[1] = Class1
// * arr[2] = method1
// * arr[3] = " "
// * arr[4] = class2
// * arr[5] = method2
// */
//
//
//String prev = "";
//for(Entry e: entries) {
//	String m1 = e.getFirstMethod();
//	String m2 = e.getSecondMethod();
//
//	// Adding paired functions
//	if(prev.isEmpty()) {
//		prev = m2;
//	}
//	else {
//		PairedFunction pair_1 = new PairedFunction(prev, m2);
//		PairedFunction pair_2 = new PairedFunction(m2, prev);
//		if(pairedFunctionMap.containsKey(pair_1) || (pairedFunctionMap.containsKey(pair_2))) {
//			pairedFunctionMap.get(pair_1).add(e.getFirstMethod());
//		}
//		else {
//			ArrayList<String> m1_arr = new ArrayList<String>();
//			m1_arr.add(m1);
//			pairedFunctionMap.put(pair_1, m1_arr);
//		}
//		prev = m2;
//	}
//
//	// adding all the scopes of a single function
//	if(singleMethodMap.containsKey(m2)) {
//		singleMethodMap.get(m2).add(e.getFirstMethod());
//	}
//	else {
//		ArrayList<String> m1_arr = new ArrayList<String>();
//		m1_arr.add(m1);
//		singleMethodMap.put(m2, m1_arr);
//	}	
//}








