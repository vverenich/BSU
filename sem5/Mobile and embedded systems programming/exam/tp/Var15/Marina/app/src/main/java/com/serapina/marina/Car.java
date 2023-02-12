package com.serapina.marina;

import java.util.ArrayList;

public class Car {
    public int id, year;
    public double price;
    public String model;

    public Car(int id, int year, double price, String model)
    {
        this.id = id;
        this.year = year;
        this.price = price;
        this.model = model;
    }

    public static Car[] getDefaultInstances()
    {
        Car[] cars = new Car[]
        {
                new Car(1, 2004, 620000, "Hundai NF"),
                new Car(2, 2003, 520000, "Mitsubishi eK classy"),
                new Car(3, 2010, 820000, "BMW 1M"),
                new Car(4, 1969, 400000, "Opel Diplomat"),
                new Car(5, 2004, 50000, "Opel Tigra")
        };

        return cars;
    }
}
