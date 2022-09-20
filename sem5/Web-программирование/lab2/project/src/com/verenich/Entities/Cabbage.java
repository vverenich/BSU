package com.verenich.Entities;
import java.awt.*;

public class Cabbage extends Cruciferous {
	
	private Color color;
	
	public Color getColor() {
		return color;
	}
	
	public void setColor(Color color) {
		this.color = color;
	}

	public Cabbage(double calories, double proteins, double fats, double carbohydrates, Color color) {
		super(calories, proteins, fats, carbohydrates);
		this.color = color;
		// TODO Auto-generated constructor stub
	}

	@Override
	public String toString() {
        return "Cabbage{ " + calories + ", " + proteins + ", " + fats + ", " + carbohydrates + ", " + color + " }";
    }
}
