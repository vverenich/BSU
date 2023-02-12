package com.verenich.lab2_var4;

import java.awt.Color;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

import com.verenich.Builders.RemoteBuilder;
import com.verenich.Entities.Broccoli;
import com.verenich.Entities.Cabbage;
import com.verenich.Entities.Cucumber;
import com.verenich.Entities.Garlic;
import com.verenich.Entities.Onion;
import com.verenich.Entities.Pumpkin;
import com.verenich.Entities.Shallot;
import com.verenich.Salads.VladSalad;

public class Client {
    public static void main(String[] args) {
        Registry reg;
        RemoteBuilder stub;

        try {
            reg = LocateRegistry.getRegistry(9001);
            stub = (RemoteBuilder)reg.lookup("Builder");
        } catch(RemoteException | NotBoundException e) {
            System.out.println(e);
            return;
        }

        try {
            System.out.println("I'm comunicating with the Builder.");

            System.out.println("I'm gonna cook the first version of salad");
            stub.addBroccoli(new Broccoli(1, 2, 3, 4));
            stub.addCucumber(new Cucumber(3, 4, 5, 6, 22));
		    stub.addOnion(new Onion(9, 8, 7, 6, new Color(255, 100, 100)));
		    stub.addShallot(new Shallot(6, 5, 4, 1, new Color(255, 100, 100)));
            VladSalad saladVersion1 = stub.getSalad();
            System.out.println(saladVersion1.toString());
            stub.reset();

            System.out.println("I'm gonna cook the second version of salad");
            stub.addCabbage(new Cabbage(1, 2, 3, 4, new Color(255, 100, 100)));
		    stub.addGarlic(new Garlic(3, 6, 9, 2, 100));
		    stub.addPumpkin(new Pumpkin(2, 5, 6, 8, "Field"));
            VladSalad saladVersion2 = stub.getSalad();
            System.out.println(saladVersion2.toString());
            stub.reset();

        } catch (RemoteException e) {
            System.out.println(e);
        } 
    }
}
