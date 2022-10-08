package com.verenich.Entities;

public class Garlic extends Allium {
	
	private int cloves;
	
	/**
	 * 
	 * @return the number of cloves
	 */
	public int getCloves() {
		return cloves;
	}
	
	/**
	 * Sets the number of cloves
	 * @param cloves
	 */
	public void setCloves(int cloves) {
		this.cloves = cloves;
	}

	public Garlic(double calories, double proteins, double fats, double carbohydrates, int cloves) {
		super(calories, proteins, fats, carbohydrates);
		this.cloves = cloves;
		// TODO Auto-generated constructor stub
	}
	
	@Override
	public String toString() {
        return "Garlic{ " + calories + ", " + proteins + ", " + fats + ", " + carbohydrates + ", " + cloves + " }";
    }

}