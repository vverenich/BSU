package com.verenich.Entities;

import java.awt.*;

public class Onion extends Allium {
	private Color color;
	
	/**
	 * 
	 * @return the color of Onion
	 */
	public Color getColor() {
		return color;
	}
	
	/**
	 * Sets the color of Onion
	 * @param color
	 */
	public void setColor(Color color) {
		this.color = color;
	}
	
	public Onion(double calories, double proteins, double fats, double carbohydrates, Color color) {
		super(calories, proteins, fats, carbohydrates);
		this.color = color;
		// TODO Auto-generated constructor stub
	}

	@Override
	public String toString() {
        return "Onion{ " + calories + ", " + proteins + ", " + fats + ", " + carbohydrates + ", " + color + " }";
    }
	
	@Override
	public String getVegetableName() {
		return "Onion";
	}
}

