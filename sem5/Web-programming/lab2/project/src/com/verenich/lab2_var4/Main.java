package com.verenich.lab2_var4;

import com.verenich.Builders.VerenichSaladBuilder;
import com.verenich.Builders.VladSaladBuilder;
import com.verenich.Directors.Director;
import com.verenich.Salads.VerenichSalad;
import com.verenich.Salads.VladSalad;

public class Main {

	public static void main(String[] args) {
		System.out.println("This is lab2.\n\n");
		
		System.out.print("Creating verenichSaladBuilder and VladSaladBuilder...\n\n");
		VerenichSaladBuilder verenichSaladBuilder = new VerenichSaladBuilder();
		VladSaladBuilder vladSaladBuilder = new VladSaladBuilder();
		Director director = new Director();
		
		System.out.print("\nCreating the vladSalad using builder pattern.\n");
		director.makeVladSalad(vladSaladBuilder);
		VladSalad vladSalad = vladSaladBuilder.getSalad();
		System.out.print(vladSalad.toString());
		
		System.out.print("\nSorting the Verenich salad.\n");
		vladSalad.sortByCalories();
		System.out.print(vladSalad.toString());
		
		System.out.print("\nCreating the verenichSalad using builder pattern.\n");
		director.makeVerenichSalad(verenichSaladBuilder);
		VerenichSalad verenichSalad = verenichSaladBuilder.getSalad();
		System.out.print(verenichSalad.toString());
		
		System.out.print("\nSorting the verenich salad.\n");
		verenichSalad.sortByCalories();
		System.out.print(verenichSalad.toString());
	}

}
