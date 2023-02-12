package com.verenich.Entities;

import java.io.Serializable;

public abstract class Vegetable implements Serializable{
	protected double calories;
	protected double proteins;
	protected double fats;
	protected double carbohydrates;
	
	public Vegetable(double calories, double proteins, double fats, double carbohydrates)
	{
		this.calories 	   = calories;
		this.proteins 	   = proteins;
		this.fats          = fats;
		this.carbohydrates = carbohydrates; 
	}

	/**
	 * 
	 * @return number of calories
	 */
	public double getCalories()
	{
		return calories;
	}
	
	/**
	 * 
	 * @return number of proteins
	 */
	public double getProteins()
	{
		return proteins;
	}
	
	/**
	 * 
	 * @return number of fats
	 */
	public double getFats()
	{
		return fats;
	}
	
	/**
	 * 
	 * @return number of carbohydrates
	 */
	public double getCarbohydtrates()
	{
		return carbohydrates;
	}
	
	/**
	 * Sets the number of calories
	 * @param calories
	 */
	public void setCalories(double calories)
	{
		this.calories = calories;
	}
	
	/**
	 * Sets the number of proteins
	 * @param proteins
	 */
	public void setProteins(double proteins)
	{
		this.proteins = proteins;
	}
		
	/**
	 * Sets the number of fats
	 * @param fats
	 */
	public void setFats(double fats)
	{
		this.fats = fats;
	}
	
	/**
	 * Sets the number of carbohydrates
	 * @param carbohydtrates
	 */
	public void setCarbohydtrates(double carbohydtrates)
	{
		this.carbohydrates = carbohydtrates;
	}
}
