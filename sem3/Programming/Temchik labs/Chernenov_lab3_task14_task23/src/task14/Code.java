package task14;

import java.util.Scanner;

public class Code {
    public static void task_14() {
    	Scanner in = new Scanner(System.in);
    	System.out.print("Size: ");
        int n = in.nextInt();
        int[][] arr = new int[n][n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                arr[i][j] = (int) (Math.random()*(2*(n - 1)+1)) - (n - 1);
            }
        }
        
        System.out.println("Before deleting:\n");
        print(arr);
 
        int max = getMaxElement(arr);
        System.out.println("Max element: " + max + "\n______");
        int c_z = n, r_z = n;
        boolean[] col = new boolean[n],
               row = new boolean[n];
 
        for (int i = 0; i < n; ++i)
            row[i] = col[i] = false;
 
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (arr[i][j] == max) {
                	if (!col[j]) {
                        col[j] = true;
                        --c_z;
                    }
 
                    if (!row[i]) {
                        row[i] = true;
                        --r_z;
                    }
                }
            }
        }
        
        int[][] new_arr = arr_without_max(arr, row, r_z, col, c_z);
        System.out.println(new_arr.length);
        System.out.println("After deleting:\n");
        print(new_arr);
    }
    
    public static void print(boolean[] arr) {
    	for (int i = 0; i < arr.length; ++i)
    		System.out.print(arr[i] + "\t");
    	System.out.println();
    }
    public static void print(int[][] arr) {
        for (int i = 0; i < arr.length; ++i) {
        	for (int j = 0; j < arr[i].length; ++j) {
        		System.out.print(arr[i][j] + "\t");
        	}
        	System.out.println();
        }
        System.out.println("\n\n");
    }
 
    public static int[][] arr_without_max(int[][] arr, boolean[] row, int r_z, boolean[] col, int c_z) {
    int[][] destinationarr = new int[r_z][c_z];
    int p = 0;
    for( int i = 0; i < arr.length; ++i) {
        if (row[i])
            continue;


        int q = 0;
        for( int j = 0; j < arr.length; ++j)
        {
            if ( col[j])
                continue;

            destinationarr[p][q++] = arr[i][j];
        }

        ++p;
    }
    return destinationarr;
}
 
 
    public static int getMaxElement(int[][] matrix) {
        int max = matrix[0][0];
        for (int i = 0; i < matrix.length; i++) {
 
            for(int j = 0; j < matrix[i].length; j++) {
                if (max < matrix[i][j]){
                    max = matrix[i][j];
                }
 
            }
 
        }
        return max;
    }
    
    
}
