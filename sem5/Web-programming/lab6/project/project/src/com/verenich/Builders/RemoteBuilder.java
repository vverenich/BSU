package com.verenich.Builders;
import java.rmi.Remote;
import java.rmi.RemoteException;

import com.verenich.Entities.Broccoli;
import com.verenich.Entities.Cabbage;
import com.verenich.Entities.Cucumber;
import com.verenich.Entities.Garlic;
import com.verenich.Entities.Onion;
import com.verenich.Entities.Pumpkin;
import com.verenich.Entities.Shallot;
import com.verenich.Salads.VladSalad;

public interface RemoteBuilder extends Remote {

	/**
	 * 
	 * @return
	 * @throws RemoteException
	 */
	public VladSalad getSalad() throws RemoteException;
	/**
	 * Adds broccoli to the salad
	 * @param broccoli
	 */
	void addBroccoli(Broccoli broccoli) throws RemoteException;
	
	/**
	 *  Adds cabbage to the salad
	 * @param cabbage
	 */
	void addCabbage(Cabbage cabbage) throws RemoteException;
	
	/**
	 *  Adds cucumber to the salad
	 * @param cucumber
	 */
	void addCucumber(Cucumber cucumber) throws RemoteException;
	
	/**
	 *  Adds garlic to the salad
	 * @param garlic
	 */
	void addGarlic(Garlic garlic) throws RemoteException;
	
	/**
	 *  Adds onion to the salad
	 * @param onion
	 */
	void addOnion(Onion onion) throws RemoteException;
	
	/**
	 *  Adds pumpkin to the salad
	 * @param pumpkin
	 */
	void addPumpkin(Pumpkin pumpkin) throws RemoteException;
	
	/**
	 *  Adds shallot to the salad
	 * @param shallot
	 */
	void addShallot(Shallot shallot) throws RemoteException;

	/**
	 * 
	 * @throws RemoteException
	 */
    void reset() throws RemoteException;
}
