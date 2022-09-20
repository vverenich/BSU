package com.verenich.entities2d;

public class LineSegment2D {
	private Point2D m_pointBegin;
	private Point2D m_pointEnd;
	
	/**
	 * Constructs the line segment from two points
	 * @param begin -- begin point
	 * @param end -- end point
	 */
	public LineSegment2D(Point2D begin, Point2D end)
	{
		this.m_pointBegin = begin;
		this.m_pointEnd   = end;
	}

	public void setPointBegin(Point2D begin)
	{
		this.m_pointBegin = begin;
	}
	
	public void setPointEnd(Point2D end)
	{
		this.m_pointEnd = end;
	}
	
	public Point2D getPointBegin()
	{
		return this.m_pointBegin;
	}
	
	public Point2D getPointEnd()
	{
		return this.m_pointEnd;
	}
	
	/**
	 * @return -- the length of line segment
	 */
	public double getLength()
	{
		return Math.sqrt((m_pointBegin.getX() - m_pointEnd.getX()) * 
				(m_pointBegin.getX() - m_pointEnd.getX()) + 
				(m_pointBegin.getY() - m_pointEnd.getY()) * 
				(m_pointBegin.getY() - m_pointEnd.getY()));
	}
	
	/**
	 * @return -- sin of the slope of the segment with respect to the origin
	 */
	public double getSin()
	{
		return (this.m_pointEnd.getY() - this.m_pointBegin.getY()) / this.getLength(); 
	}
	
	/**
	 * @return -- cos of the slope of the segment with respect to the origin
	 */
	public double getCos()
	{
		return (this.m_pointEnd.getX() - this.m_pointBegin.getX()) / this.getLength(); 
	}
	
	/**
	 * Rotates the square
	 * @param degrees -- the angle in degrees to rotate square
	 */
	public void rotate(double degrees)
	{
		if(degrees >= 90) {
			return;
		}
		
		double xEnd = -Math.sin(Math.toRadians(degrees)) * (this.m_pointEnd.getY() - this.m_pointBegin.getY()) +
					  Math.cos(Math.toRadians(degrees)) * (this.m_pointEnd.getX() - this.m_pointBegin.getX()) + 
					  this.m_pointBegin.getX();
		
		double yEnd = Math.cos(Math.toRadians(degrees)) * (this.m_pointEnd.getY() - this.m_pointBegin.getY()) +
				  	  Math.sin(Math.toRadians(degrees)) * (this.m_pointEnd.getX() - this.m_pointBegin.getX()) + 
				      this.m_pointBegin.getY();
		
		this.m_pointEnd = new Point2D(xEnd, yEnd);
	}
	
	/**
     * @return a string representing a LineSegment2D
     */
    @Override
    public String toString() {
        return "LineSegment2D{ " + this.m_pointBegin.toString() + ", " + this.m_pointEnd.toString() + " }";
    }
}
