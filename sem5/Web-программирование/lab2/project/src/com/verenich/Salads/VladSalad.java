package com.verenich.Salads;

import java.util.ArrayList;

import com.verenich.Entities.Vegetable;

public class VladSalad {
	private ArrayList<Vegetable> salad = new ArrayList<Vegetable>();
	
	public VladSalad(ArrayList<Vegetable> array)
	{
		this.salad = array;
	}
	
	@Override
	public String toString() {
		String result = new String("Vlad salad: \n");
		
		for(int i = 0; i < salad.size(); ++i) {
			result += salad.get(i) + ",\n";
		}
		
        return result;
    }
}
