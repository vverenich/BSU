package lab4_var10_Chernenkov;

import java.util.ArrayList;
import java.util.*;

public class test {
	public static void printArr(Angle[] arr) {
		System.out.println("__________________________________________________");
		System.out.println("    minutes     |    degrees     |     Radians    ");
		System.out.println("________________|________________|________________");
		
		
		for (int i = 0; i < arr.length; ++i) {
			System.out.println(arr[i]);
		}
		System.out.println();
	}
	public static void printArr(ArrayList<Angle> arr) {
		System.out.println("__________________________________________________");
		System.out.println("    minutes     |    degrees     |     Radians    ");
		System.out.println("________________|________________|________________");
		
		
		ListIterator<Angle> it = arr.listIterator();
		while(it.hasNext()){
	         
            System.out.println(it.next());
        }
	}
	
	public static Angle[] reverse(Angle[] arr) {
		Angle[] arr2 = new Angle[arr.length];
		for (int i = 0; i < arr.length; ++i) {
			arr2[arr.length - i - 1] = arr[i];
		}
		return arr2;
	}
	
	public static void main (String[] args) throws java.lang.Exception {
		Angle[] arr = {
				new Angle("45.8"),
				new Angle("78.30"),
				new Angle("13.3"),
				new Angle("100.0")
		};
		
		
		System.out.println("Source array:");
		printArr(arr);
		
		System.out.println("\nThrough iterator:");
		printArr(copyArr(arr));
		
		
		System.out.println("\n\nSorted by " + Angle.getSortByName(0));
		Arrays.sort(arr, Angle.getComparator(0));
		printArr(arr);
		
		Angle[] arr2 = {
				arr[0],
				arr[1]
		};
		
		System.out.println("\n\nSum of next elements:");
		printArr(arr2);
		System.out.println("===================================================");
		System.out.println(Angle.sum(arr[0], arr[1]));
		
		System.out.println("\n\nSubstraction of next elements:");
		printArr(arr2);
		System.out.println("==================================================");
		System.out.println(Angle.sub(arr[0], arr[1]));

		System.out.println("\n\nMultiplication of next elements:");
		printArr(arr2);
		System.out.println("===================================================");
		System.out.println(Angle.mult(arr[0], arr[1]));

		System.out.println("\n\nDividing of next elements:");
		printArr(reverse(arr2));
		System.out.println("===================================================");
		System.out.println(Angle.div(arr[1], arr[0]));
		
	}
	
	
	public static ArrayList<Angle> copyArr(Angle[] angles) {
		ArrayList<Angle> ang = new ArrayList<Angle>();
		for (int i = 0; i < angles.length; ++i) {
			ang.add(new Angle(angles[i]));
		}
		return ang;
	}
	}
