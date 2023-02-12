package com.verenich.lab2_var4;

import java.awt.Color;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

import com.verenich.Builders.RemoteBuilder;
import com.verenich.Entities.Cabbage;

public class ClientAdditional {
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

            System.out.println("I'm gonna add only one ingredient to the salad");
            stub.addCabbage(new Cabbage(1, 2, 3, 4, new Color(255, 100, 100)));
            System.out.println("I'm done!");
            
        } catch (RemoteException e) {
            System.out.println(e);
        } 
    }
}
