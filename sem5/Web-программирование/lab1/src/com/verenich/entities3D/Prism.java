package com.verenich.entities3D;
import java.util.ArrayList;

public class Prism {
	private ArrayList<Point3D> m_base;
	private Plane 	m_plane;
	private double  m_height;
	
	/**
     * Constructs a prism with a base 'plane' and height 'height'
     * @param base -- a base of a prism
     * @param height -- a height of a prism
     */
	public Prism(Plane plane, double height)
	{
		m_plane = plane;
		m_height = height;
	    m_base = new ArrayList<Point3D>();

	}
	
	public double getHeight()
	{
		return m_height;
	}
	
	public void setHeight(double height)
	{
		m_height =  height;
	}
	
	/**
	 * Adds the point to the base, if the point belongs to the plane of base
	 * @param point -- the point to add
	 * @return
	 */
	public boolean addBasePoint(Point3D point)
	{
		if(! m_plane.isPointBelongsToPlane(point)) {
			return false;
		}
		
		m_base.add(point);
		return true;
	}
	
	public void printBasePoints()
	{
		System.out.println("Points of the prism base: ");
		for(Point3D point : m_base) {
            System.out.println(point);
        }
	}
	
	/**
     * @return a string representing a Prism
     */
    @Override
	public String toString()
    {
        return "Prism{ " + m_plane + ", " + m_height + " }";
    }
    
	
}
