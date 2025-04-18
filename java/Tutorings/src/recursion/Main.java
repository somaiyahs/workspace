package recursion;

import java.util.Scanner;

public class Main {

	public static int find(char ch, String str)
	{

		if(str.length() == 0 || str == null)
		{
			return -1;
		}
		else if(str.charAt(0) == ch)
		{
			return 0;
		}
		int subIndex = find(ch, str.substring(1));
		// condition ? true : false 
		return subIndex == -1 ? -1 : 1 + subIndex;
	}
	
	public static void main(String args[])
	{
		//Scanner sc = new Scanner(System.in);
		//System.out.print("\nEnter a string: ");
		//String str=sc.nextLine();
		//printReverse(str);
		//System.out.println("\n");
		//System.out.print(trim(str));
		Scanner bb = new Scanner(System.in);
		Character ch=bb.next().charAt(0);

		String sttr=bb.next();

		System.out.print(find(ch, sttr));

	}

}
