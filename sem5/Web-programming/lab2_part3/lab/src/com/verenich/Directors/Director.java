package com.verenich.Directors;
import java.awt.*;

import com.verenich.Builders.Builder;
import com.verenich.Entities.Broccoli;
import com.verenich.Entities.Cabbage;
import com.verenich.Entities.Cucumber;
import com.verenich.Entities.Garlic;
import com.verenich.Entities.Onion;
import com.verenich.Entities.Pumpkin;
import com.verenich.Entities.Shallot;

public class Director {
	/**
	 * Makes the Vlad Salad
	 * @param builder
	 */
	public void makeVladSalad(Builder builder)
	{
		builder.addBroccoli(new Broccoli(1, 2, 3, 4));
		builder.addCucumber(new Cucumber(3, 4, 5, 6, 22));
		builder.addOnion(new Onion(9, 8, 7, 6, new Color(255, 100, 100)));
		builder.addShallot(new Shallot(6, 5, 4, 1, new Color(255, 100, 100)));
	}
	
	/**
	 * Makes the Verenich Salad
	 * @param builder
	 */
	public void makeVerenichSalad(Builder builder)
	{
		builder.addCabbage(new Cabbage(1, 2, 3, 4, new Color(255, 100, 100)));
		builder.addGarlic(new Garlic(3, 6, 9, 2, 100));
		builder.addPumpkin(new Pumpkin(2, 5, 6, 8, "Field"));
	}
}
