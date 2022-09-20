package com.verenich.Entities;

public abstract class Vegetable {
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

	public double getCalories()
	{
		return calories;
	}
	
	public double getProteins()
	{
		return proteins;
	}
	
	public double getFats()
	{
		return fats;
	}
	
	public double getCarbohydtrates()
	{
		return carbohydrates;
	}
	
	public void setCalories(double calories)
	{
		this.calories = calories;
	}
	
	public void setProteins(double proteins)
	{
		this.proteins = proteins;
	}
		
	public void setFats(double fats)
	{
		this.fats = fats;
	}
	
	public void setCarbohydtrates(double carbohydtrates)
	{
		this.carbohydrates = carbohydtrates;
	}
}
