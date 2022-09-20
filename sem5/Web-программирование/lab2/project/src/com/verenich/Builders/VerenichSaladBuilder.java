package com.verenich.Builders;

import java.util.ArrayList;

import com.verenich.Entities.Broccoli;
import com.verenich.Entities.Cabbage;
import com.verenich.Entities.Cucumber;
import com.verenich.Entities.Garlic;
import com.verenich.Entities.Onion;
import com.verenich.Entities.Pumpkin;
import com.verenich.Entities.Shallot;
import com.verenich.Entities.Vegetable;
import com.verenich.Salads.VerenichSalad;

public class VerenichSaladBuilder implements Builder{
	private ArrayList<Vegetable> arrayListSalad = new ArrayList<Vegetable>();
	
	VerenichSalad getSalad()
	{
		return new VerenichSalad(arrayListSalad);
	}
	
	@Override
	public void addBroccoli(Broccoli broccoli) 
	{
		arrayListSalad.add(broccoli);
	}

	@Override
	public void addCabbage(Cabbage cabbage) 
	{
		arrayListSalad.add(cabbage);
	}

	@Override
	public void addCucumber(Cucumber cucumber) 
	{
		arrayListSalad.add(cucumber);
	}

	@Override
	public void addGarlic(Garlic garlic) 
	{
		arrayListSalad.add(garlic);
	}

	@Override
	public void addOnion(Onion onion) 
	{
		arrayListSalad.add(onion);
	}

	@Override
	public void addPumpkin(Pumpkin pumpkin) 
	{
		arrayListSalad.add(pumpkin);
	}

	@Override
	public void addShallot(Shallot shallot) 
	{
		arrayListSalad.add(shallot);
	}
}
