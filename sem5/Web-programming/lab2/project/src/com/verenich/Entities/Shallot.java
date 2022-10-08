package com.verenich.Entities;
import java.awt.*;

public class Shallot extends Allium {

	private Color color;
	
	/**
	 * 
	 * @return the color of the Shallot
	 */
	public Color getColor() {
		return color;
	}
	
	/**
	 * Sets the color of the Shallot
	 * @param color
	 */
	public void setColor(Color color) {
		this.color = color;
	}
	
	public Shallot(double calories, double proteins, double fats, double carbohydrates, Color color) {
		super(calories, proteins, fats, carbohydrates);
		this.color = color;
		// TODO Auto-generated constructor stub
	}
	
	@Override
	public String toString() {
        return "Shallot{ " + calories + ", " + proteins + ", " + fats + ", " + carbohydrates + ", " + color +" }";
    }

}

