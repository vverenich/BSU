package com.verenich.Entities;

public class Broccoli extends Cruciferous {

	public Broccoli(double calories, double proteins, double fats, double carbohydrates) {
		super(calories, proteins, fats, carbohydrates);
		// TODO Auto-generated constructor stub
	}

	@Override
	public String toString() {
        return "Broccoli{ " + calories + ", " + proteins + ", " + fats + ", " + carbohydrates + " }";
    }
}
