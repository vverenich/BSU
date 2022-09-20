package com.verenich.entities3D;

public class Point3D {
	private double m_x;
	private double m_y;
	private double m_z;
	
	/**
	 * Constructs the point in the space
	 * @param x -- x-coordinate
	 * @param y -- y-coordinate
	 * @param z -- z-coordinate
	 */
	public Point3D(double x, double y, double z)
	{
		this.m_x = x;
		this.m_y = y;
		this.m_z = z;
	}
	
	public void setX(double x)
	{
		this.m_x = x;
	}
	
	public void setY(double y)
	{
		this.m_y = y;
	}
	
	public void setZ(double z)
	{
		this.m_z = z;
	}
	
	public double getX()
	{
		return m_x;
	}
	
	public double getY()
	{
		return m_y;
	}
	
	public double getZ()
	{
		return m_z;
	}
	
	/**
     * @return a string representing a Point3D
     */
    @Override
	public String toString() {
        return "Point3D{ " + m_x + ", " + m_y + ", " + m_z + " }";
    }
}
