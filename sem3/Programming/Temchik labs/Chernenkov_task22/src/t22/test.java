package t22;
import java.util.*;

public class test {
	public static void main(String[] args) {
		Random rand = new Random();
		
		Vector3D[] v = new Vector3D[4];
		v[0] = new Vector3D(
				rand.nextInt(25),
				rand.nextInt(25),
				rand.nextInt(25));
		System.out.println("v1:\n\t" + v[0] + "\n\tVector modulus: " + 
				String.format("%.3f", v[0].length()));
		
		v[1] = new Vector3D(v[0]);
				//rand.nextInt(25),
				//rand.nextInt(25),
				//rand.nextInt(25));
		System.out.println("v2:\n\t" + v[1] + "\n\tVector modulus: " + 
				String.format("%.3f", v[1].length()) + "\n\n");
		
		v[2] = new Vector3D(3, -2, -3);
		System.out.println("v3:\n\t" + v[2] + "\n\tVector modulus: " + 
				String.format("%.3f", v[2].length()));
		
		v[3] = new Vector3D(-1, -3, 1);
		System.out.println("v4:\n\t" + v[3] + "\n\tVector modulus: " + 
				String.format("%.3f", v[3].length()));
		
		System.out.println("\n\n1)\n\tSubtraction v1 and v2: " + v[0].sub(v[1]));
		System.out.println("\tSubtraction v2 and v3: " + v[1].sub(v[2]));
		System.out.println("\tSubtraction v3 and v4: " + v[2].sub(v[3]));
		
		
		System.out.println("2)\n\tAddition v1 and v2: " + v[0].add(v[1]));
		System.out.println("\tAddition v2 and v3: " + v[1].add(v[2]));
		System.out.println("\tAddition v3 and v4: " + v[2].add(v[3]));
		
		
		double co = rand.nextInt(10);
		System.out.println("3)\n\tMultiplying v1 by a constant " + co +
				" : " + v[0].mul(co));
		co = rand.nextInt(10);
		System.out.println("\tMultiplying v2 by a constant " + co +
				" : " + v[1].mul(co));
		co = rand.nextInt(10);
		System.out.println("\tMultiplying v3 by a constant " + co +
				" : " + v[2].mul(co));
		co = rand.nextInt(10);
		System.out.println("\tMultiplying v4 by a constant " + co +
				" : " + v[3].mul(co));
		
		
		System.out.println("4)\n\tDot product v1 and v2: " +
				v[0].dot(v[1]));
		System.out.println("\tDot product v2 and v3: " +
				v[1].dot(v[2]));
		System.out.println("\tDot product v3 and v4: " +
				v[2].dot(v[3]));
		
		
		System.out.println("5)\n\tCollinear/Not collinear:\n\t\t" + (v[0].isCollinear(v[1]) ? 
				"v1 collinear v2" :
					"v1 not collinear v2"));
		System.out.println("\t\t" + (v[0].isOrtogonal(v[1]) ? 
				"v1 orthogonal v2" :
					"v1 not orthogonal v2"));
		
		System.out.println("\t\t" + (v[2].isCollinear(v[3]) ? 
				"v3 collinear v4" :
					"v3 not collinear v4"));
		System.out.println("\t\t" + (v[2].isOrtogonal(v[3]) ? 
				"v3 orthogonal v4" :
					"v3 not orthogonal v4"));
		
	}
}
