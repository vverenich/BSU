package com.verenich.Builders;
import com.verenich.Entities.Broccoli;
import com.verenich.Entities.Cabbage;
import com.verenich.Entities.Cucumber;
import com.verenich.Entities.Garlic;
import com.verenich.Entities.Onion;
import com.verenich.Entities.Pumpkin;
import com.verenich.Entities.Shallot;

public interface Builder {
	void addBroccoli(Broccoli broccoli);
	void addCabbage(Cabbage cabbage);
	void addCucumber(Cucumber cucumber);
	void addGarlic(Garlic garlic);
	void addOnion(Onion onion);
	void addPumpkin(Pumpkin pumpkin);
	void addShallot(Shallot shallot);
}
