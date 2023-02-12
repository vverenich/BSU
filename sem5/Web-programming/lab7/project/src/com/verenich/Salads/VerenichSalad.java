package com.verenich.Salads;

import java.util.ArrayList;
import java.util.Collections;

import com.verenich.Entities.Vegetable;
import com.verenich.service.VegetableComparator;

public class VerenichSalad {
	private ArrayList<Vegetable> salad = new ArrayList<Vegetable>();
	
	public VerenichSalad(ArrayList<Vegetable> array)
	{
		this.salad = array;
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
		String result = new String("Verenich salad: \n");
		
		for(int i = 0; i < salad.size(); ++i) {
			result += salad.get(i) + ",\n";
		}
		
        return result;
    }
	
}