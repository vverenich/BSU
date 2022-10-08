package com.verenich.Entities;

public class Cucumber extends Marrow {
	
	private int length;
	
	/**
	 * 
	 * @return the length of the marrow
	 */
	public int getLength() {
		return length;
	}
	
	/**
	 * Sets the length of the marrow
	 * @param length
	 */
	public void setLength(int length) {
		this.length = length;
	}

	public Cucumber(double calories, double proteins, double fats, double carbohydrates, int length) {
		super(calories, proteins, fats, carbohydrates);
		this.length = length;
		// TODO Auto-generated constructor stub
	}

	@Override
	public String toString() {
        return "Cucumber{ " + calories + ", " + proteins + ", " + fats + ", " + carbohydrates + ", " + length + " }";
    }
	
	@Override
	public String getVegetableName() {
		return "Cucumber";
	}
}

