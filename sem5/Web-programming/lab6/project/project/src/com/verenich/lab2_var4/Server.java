package com.verenich.lab2_var4;

import java.nio.channels.AlreadyBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

import com.verenich.Builders.BuilderRMI;
import com.verenich.Builders.RemoteBuilder;

public class Server {
    public static void main(String[] args) throws java.rmi.AlreadyBoundException {

        BuilderRMI builder = new BuilderRMI();

        System.out.println("Create builder");

        try {
            RemoteBuilder stub = (RemoteBuilder) UnicastRemoteObject.exportObject(builder, 0);
            Registry reg = LocateRegistry.createRegistry(9001);
            reg.bind("Builder", stub);
            System.out.println("Remote salad builder is ready to work!");
        } catch(RemoteException | AlreadyBoundException e) {
            System.out.println(e);
        }
    }
}
