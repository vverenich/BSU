package com.verenich.Builders;
import com.verenich.Entities.Broccoli;
import com.verenich.Entities.Cabbage;
import com.verenich.Entities.Cucumber;
import com.verenich.Entities.Garlic;
import com.verenich.Entities.Onion;
import com.verenich.Entities.Pumpkin;
import com.verenich.Entities.Shallot;

public interface Builder {
	/**
	 * Adds broccoli to the salad
	 * @param broccoli
	 */
	void addBroccoli(Broccoli broccoli);
	
	/**
	 *  Adds cabbage to the salad
	 * @param cabbage
	 */
	void addCabbage(Cabbage cabbage);
	
	/**
	 *  Adds cucumber to the salad
	 * @param cucumber
	 */
	void addCucumber(Cucumber cucumber);
	
	/**
	 *  Adds garlic to the salad
	 * @param garlic
	 */
	void addGarlic(Garlic garlic);
	
	/**
	 *  Adds onion to the salad
	 * @param onion
	 */
	void addOnion(Onion onion);
	
	/**
	 *  Adds pumpkin to the salad
	 * @param pumpkin
	 */
	void addPumpkin(Pumpkin pumpkin);
	
	/**
	 *  Adds shallot to the salad
	 * @param shallot
	 */
	void addShallot(Shallot shallot);
}
