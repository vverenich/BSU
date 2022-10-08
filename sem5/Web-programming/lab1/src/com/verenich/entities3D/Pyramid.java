package com.verenich.entities3D;
import java.util.ArrayList;

public class Pyramid {
	private Plane 			   m_plane;
	private ArrayList<Point3D> m_basePoints;
	private Point3D			   m_top;
	
	/**
	 * Constructs the Pyramid with specific plane and top
	 * @param plane -- the plane of base
	 * @param top -- the top of the pyramid
	 */
	public Pyramid(Plane plane, Point3D top) 
	{
		this.m_plane = plane;
		this.m_top  = top;
		m_basePoints = new ArrayList<Point3D>();
	}
	
	/**
	 * Adds the point to the base if the point belongs to the base of pyramid
	 * @param point
	 * @return
	 */
	public boolean addBasePoint(Point3D point)
	{
		if(!m_plane.isPointBelongsToPlane(point) || m_basePoints.contains(point)) {
			return false;
		}
		
		this.m_basePoints.add(point);
		return true;
	}
	
	public void printBasePoints()
	{
		System.out.println("Points of the pyramid base: ");
		for(Point3D point : m_basePoints) {
            System.out.println(point);
        }
	}
	
	/**
     * @return a string representing a Pyramid
     */
    @Override
	public String toString() {
        return "Pyramid{ " + m_plane + ", " + m_top + " }";
    }
    
}
