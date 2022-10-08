package com.verenich.Salads;

import java.util.ArrayList;
import java.util.Collections;

import com.verenich.Entities.Vegetable;
import com.verenich.service.VegetableComparator;

public class VladSalad {
	private ArrayList<Vegetable> salad = new ArrayList<Vegetable>();
	private String name;
	
	public VladSalad(ArrayList<Vegetable> array)
	{
		this.salad = array;
	}
	
	public String getName()
	{
		return name;
	}
	
	public void setName(String name)
	{
		this.name = name;
	}
			
	/**
	 * Sorts the salad by calories
	 */
	public void sortByCalories() {
		VegetableComparator comparator = new VegetableComparator();
		Collections.sort(salad, comparator);
	}
	
	@Override
	public String toString() {
		String result = new String("Vlad salad: \n");
		
		for(int i = 0; i < salad.size(); ++i) {
			result += salad.get(i) + ",\n";
		}
		
        return result;
    }
	
	public double getCalories() {
		double calories = 0;
		
		for(int i = 0; i < salad.size(); ++i) {
			calories += salad.get(i).getCalories();
		}
		
		return calories;
	}
	
	public double getProteins() {
		double proteins = 0;
		
		for(int i = 0; i < salad.size(); ++i) {
			proteins += salad.get(i).getProteins();
		}
		
		return proteins;
	}
	
	public double getFats() {
		double fats = 0;
		
		for(int i = 0; i < salad.size(); ++i) {
			fats += salad.get(i).getFats();
		}
		
		return fats;
	}
	
	public double getCarbohydrates() {
		double carbohydrates = 0;
		
		for(int i = 0; i < salad.size(); ++i) {
			carbohydrates += salad.get(i).getCarbohydrates();
		}
		
		return carbohydrates;
	}
	
}
