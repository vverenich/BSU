package com.verenich.Entities;
import java.awt.*;

public class Cabbage extends Cruciferous {
	
	private Color color;
	
	/**
	 * 
	 * @return the color of the Cabbage
	 */
	public Color getColor() {
		return color;
	}
	
	/**
	 * Sets the color of the cabbage
	 * @param color
	 */
	public void setColor(Color color) {
		this.color = color;
	}

	public Cabbage(double calories, double proteins, double fats, double carbohydrates, Color color) {
		super(calories, proteins, fats, carbohydrates);
		this.color = color;
		// TODO Auto-generated constructor stub
	}

	public Cabbage(double calories, double proteins, double fats, double carbohydrates) {
		super(calories, proteins, fats, carbohydrates);
		this.color = new Color(12,12,12);
		// TODO Auto-generated constructor stub
	}

	@Override
	public String toString() {
        return "Cabbage{ " + calories + ", " + proteins + ", " + fats + ", " + carbohydrates + ", " + color + " }";
    }
}
