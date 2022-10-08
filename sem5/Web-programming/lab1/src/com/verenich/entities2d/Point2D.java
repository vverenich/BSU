package com.verenich.entities2d;

public class Point2D {
	private double m_x;
	private double m_y;
	
	/**
	 * Constructs the Point2D object
	 * @param x -- x-coordinate
	 * @param y -- y-coordinate
	 */
	public Point2D(double x, double y)
	{
		this.m_x = x;
		this.m_y = y;
	}
	
	public void setX(double x)
	{
		this.m_x = x;
	}
	
	public void setY(double y)
	{
		this.m_y = y;
	}
	
	public double getX()
	{
		return m_x;
	}
	
	public double getY()
	{
		return m_y;
	}
	
	/**
     * @return a string representing a Point2D
     */
    @Override
	public String toString() {
        return "Point2D{ " + m_x + ", " + m_y + " }";
    }
	
}
