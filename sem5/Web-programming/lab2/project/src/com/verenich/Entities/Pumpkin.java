package com.verenich.Entities;

public class Pumpkin extends Marrow {
	
	private String sort;
	
	/**
	 * 
	 * @return the sort of the marrow
	 */
	public String getSort() {
		return sort;
	}
	
	/**
	 * Sets the sort of the marrow
	 * @param sort
	 */
	public void setSort(String sort) {
		this.sort = sort;
	}

	public Pumpkin(double calories, double proteins, double fats, double carbohydrates, String sort) {
		super(calories, proteins, fats, carbohydrates);
		this.sort = sort;
		// TODO Auto-generated constructor stub
	}

	@Override
	public String toString() {
        return "Pumpkin{ " + calories + ", " + proteins + ", " + fats + ", " + carbohydrates + ", " + sort + " }";
    }
}