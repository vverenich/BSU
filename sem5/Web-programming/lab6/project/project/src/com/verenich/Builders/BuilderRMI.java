package com.verenich.Builders;

import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import com.verenich.Entities.Broccoli;
import com.verenich.Entities.Cabbage;
import com.verenich.Entities.Cucumber;
import com.verenich.Entities.Garlic;
import com.verenich.Entities.Onion;
import com.verenich.Entities.Pumpkin;
import com.verenich.Entities.Shallot;
import com.verenich.Entities.Vegetable;
import com.verenich.Salads.VladSalad;

public class BuilderRMI implements RemoteBuilder{
	private ArrayList<Vegetable> arrayListSalad = new ArrayList<Vegetable>();
	private Lock saladLock = new ReentrantLock();
	/**
	 * 
	 * @return the salad that was built
	 */
	public VladSalad getSalad() throws RemoteException
	{
		return new VladSalad(arrayListSalad);
	}
	
	@Override
	public void addBroccoli(Broccoli broccoli) throws RemoteException
	{
		saladLock.lock();
		arrayListSalad.add(broccoli);
		saladLock.unlock();
	}

	@Override
	public void addCabbage(Cabbage cabbage) throws RemoteException
	{
		saladLock.lock();
		arrayListSalad.add(cabbage);
		saladLock.unlock();
	}

	@Override
	public void addCucumber(Cucumber cucumber) throws RemoteException
	{
		saladLock.lock();
		arrayListSalad.add(cucumber);
		saladLock.unlock();
	}

	@Override
	public void addGarlic(Garlic garlic) throws RemoteException
	{
		saladLock.lock();
		arrayListSalad.add(garlic);
		saladLock.unlock();
	}

	@Override
	public void addOnion(Onion onion) throws RemoteException
	{
		saladLock.lock();
		arrayListSalad.add(onion);
		saladLock.unlock();
	}

	@Override
	public void addPumpkin(Pumpkin pumpkin) throws RemoteException
	{
		saladLock.lock();
		arrayListSalad.add(pumpkin);
		saladLock.unlock();
	}

	@Override
	public void addShallot(Shallot shallot) throws RemoteException
	{
		saladLock.lock();
		arrayListSalad.add(shallot);
		saladLock.unlock();
	}

	@Override
	public void reset()
	{
		arrayListSalad.clear();
	}
}
