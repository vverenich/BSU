package com.verenich.service;

import java.util.Comparator;

import com.verenich.Entities.Vegetable;

public class VegetableComparator implements Comparator<Vegetable>{
	
	@Override
	public int compare(Vegetable a, Vegetable b) {
		return Double.valueOf(a.getCalories()).compareTo(Double.valueOf(b.getCalories()));
	}
}
