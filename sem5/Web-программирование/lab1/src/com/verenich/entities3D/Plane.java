package com.verenich.entities3D;

public class Plane {
	private double m_a;
	private double m_b;
	private double m_c;
	private double m_d;
	
	/**
	 * Constructs the plane using the parameters
	 * @param a -- coefficient at x
	 * @param b -- coefficient at y
	 * @param c -- coefficient at z
	 * @param d -- free member
	 */
	public Plane(double a, double b, double c, double d)
	{
		m_a = a;
		m_b = b;
		m_c = c;
		m_d = d;
	}
	
	/**
	 * Checks if the point belongs to the plane
	 * @param point -- the point to check
	 * @return -- true if point belongs and false otherwise
	 */
	public boolean isPointBelongsToPlane(Point3D point)
	{
		return this.m_a * point.getX() + this.m_b * point.getY() + this.m_c * point.getZ() == -this.m_d;
 	}
	
	/**
     * @return a string representing a Plane
     */
    @Override
	public String toString() {
        return "Plane{ " + m_a + ", " + m_b + ", " + m_c + ", " + m_d + " }";
    }
	
}
