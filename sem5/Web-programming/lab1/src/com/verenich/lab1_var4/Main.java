package com.verenich.lab1_var4;
import java.awt.*;
import com.verenich.entities2d.*;
import com.verenich.entities3D.*;

public class Main {
    public static void main(String[] args) {
    	
        System.out.println("Creating the point2D objects:");
        Point2D pointBegin = new Point2D(0, 0);
        Point2D pointEnd = new Point2D(4, 4);
        System.out.println(pointBegin.toString());
        System.out.println(pointEnd.toString());
        
        
        System.out.println();
        
        
        System.out.println("Creating the LineSegment2D object:");
        LineSegment2D lineSegment = new LineSegment2D(pointBegin, pointEnd);
        System.out.println(lineSegment.toString());
        
        
        System.out.println();
        
        
        System.out.println("Creating the Square object:");
        Color color1 = new Color(255, 100, 100);
        Square square = new Square(pointBegin, pointEnd, color1);
        System.out.println(square.toString());
        
        
        System.out.println();
        
        
        System.out.println("Stretching the Square object:");
        square.stretch(4);
        System.out.println(square.toString());
        
        
        System.out.println();
        
        
        System.out.println("Compressing the Square object:");
        square.compress(4);
        System.out.println(square.toString());
        
        
        System.out.println();
        
        
        System.out.println("Rotating the Square object:");
        square.rotate(45);
        System.out.println(square.toString());
        
        
        System.out.println();
        
        
        System.out.println("Changing the color of the square:");
        Color color2 = new Color(100, 100, 100);
        square.setColor(color2);
        System.out.println(square.toString());
        

        System.out.println();
        
        
        System.out.println("Creating the pyramid:");
        Point3D top = new Point3D(0, 0, 0);
        Plane plane = new Plane(0, 0, 5, -25);
        Pyramid pyramid = new Pyramid(plane, top);
        Point3D basePoint1 = new Point3D(1, 2, 5);
        Point3D basePoint2 = new Point3D(2, 5, 5);
        Point3D basePoint3 = new Point3D(7, 2, 5);
        Point3D basePoint4 = new Point3D(1, 2, 6);
        pyramid.addBasePoint(basePoint1);
        pyramid.addBasePoint(basePoint2);
        pyramid.addBasePoint(basePoint3);
        pyramid.addBasePoint(basePoint4);
        System.out.println(pyramid.toString());
        pyramid.printBasePoints();
        
        
        System.out.println();
        
        
        System.out.println("Creating the prism:");
        double height = 10;
        Prism prism = new Prism(plane, height);
        Point3D basePoint5 = new Point3D(1, 2, 5);
        Point3D basePoint6 = new Point3D(2, 5, 5);
        Point3D basePoint7 = new Point3D(7, 2, 5);
        Point3D basePoint8 = new Point3D(1, 2, 6);
        prism.addBasePoint(basePoint5);
        prism.addBasePoint(basePoint6);
        prism.addBasePoint(basePoint7);
        prism.addBasePoint(basePoint8);
        System.out.println(prism.toString());
        prism.printBasePoints();
    }
}