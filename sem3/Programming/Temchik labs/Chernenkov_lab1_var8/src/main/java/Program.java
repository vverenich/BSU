import java.util.*;
import java.lang.*;
import java.io.*;
	
public class Program {
    public static double my_arctan(double x, double eps) throws Exception {
        if (x >= 1 || x <= -1)
            throw new Exception("x must be less, than 1, and more, than -1");
        double step = x;
        double result = step;
        double numerator = step;
        for(int i = 1; Math.abs(step) > eps; i++){
            numerator *= - x * x;
            step = numerator / (2 * i + 1);
            result += step;
        }
        return result;
    }
 
    public static void main (String[] args) throws java.lang.Exception
    {
        double x,eps;
        int k;
        x = Double.parseDouble(args[0]); 
        k = Integer.parseInt(args[1]) + 1;
        eps = Math.pow(10, -k);
        try {
            double y1=my_arctan(x, eps);
            double y2=Math.atan(x);
            String fmt = "%." + args[1] + "f\n";
            System.out.printf("my_arctan: " + fmt + "\nMath.atan: " + fmt, y1, y2);
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
    }
}
