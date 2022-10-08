package com.verenich.entities2d;
import java.awt.*;

public class Square {
	
	private LineSegment2D m_segment;
	private Color m_color;
	
	/**
	 * Constructs the square using the line segment as the diagonal
	 * @param segment -- the diagonal
	 */
	Square(LineSegment2D segment)
	{
		this.m_segment = segment;
	}
	
	/**
	 * Constructs the square using two points as the diagonal ends
	 * @param begin -- the begin point of diagonal
	 * @param end -- the end point of diagonal
	 */
	public Square(Point2D begin, Point2D end, Color color)
	{
		this.m_segment = new LineSegment2D(begin, end);
		m_color = color;
	}
	
	/** 
	 * @return -- the length of diagonal
	 */
	public double getDiagonal()
	{
		return m_segment.getLength();
	}
	
	/**
	 * @return -- side length of the square
	 */
	public double getSideLength()
	{
		return Math.sqrt(2) * getDiagonal() / 2;
	}
	
	/**
	 * @return -- the area of the square
	 */
	public double getArea()
	{
		return getSideLength() * getSideLength();
	}
	
	/**
	 * Stretches the square to "size" the main diagonal of the square
	 * @param size -- the size to stretch the square
	 */
	public void stretch(double size)
	{
		if(size <= 0) {
			return;
		}
		
		double deltaX = size * this.m_segment.getCos();
		double deltaY = size * this.m_segment.getSin();
		
		this.m_segment.setPointEnd(new Point2D(this.m_segment.getPointEnd().getX() + deltaX, this.m_segment.getPointEnd().getY() + deltaY));
	}
	
	/**
	 * Compresses the square to "size" the main diagonal of the square
	 * @param size -- the size to compress the square
	 */
	public void compress(double size)
	{
		if(size >= getDiagonal()) {
			return;
		}
		
		double deltaX = size * this.m_segment.getCos();
		double deltaY = size * this.m_segment.getSin();
		
		this.m_segment.setPointEnd(new Point2D(this.m_segment.getPointEnd().getX() - deltaX, this.m_segment.getPointEnd().getY() - deltaY));
	}
	
	/**
	 * Rotates the square
	 * @param degrees -- the angle in degrees to rotate the square
	 */
	public void rotate(double degrees)
	{
		this.m_segment.rotate(degrees);
	}
	
	public Color getColor()
	{
		return m_color;
	}
	
	public void setColor(Color color)
	{
		m_color = color;
	}
	
	/**
     * @return a string representing a Square
     */
    @Override
	public String toString() {
        return "Square{ " + this.m_segment + ", " + m_color + " }";
    }
}
