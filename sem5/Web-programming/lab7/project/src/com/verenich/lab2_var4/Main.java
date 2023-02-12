package com.verenich.lab2_var4;

import java.awt.Color;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;

import com.verenich.Builders.VerenichSaladBuilder;
import com.verenich.Entities.Broccoli;
import com.verenich.Entities.Cucumber;
import com.verenich.Entities.Onion;
import com.verenich.Entities.Shallot;
import com.verenich.Entities.Vegetable;
import com.verenich.exception.ParserException;
import com.verenich.exception.XMLValidatorException;
import com.verenich.parser.DOMParser;
import com.verenich.parser.SAXParser;

public class Main {

	private static final String FILE_XML = "D:/BSU/BSU/sem5/Web-programming/lab7/project/vegetables.xml";
    private static final String FILE_XSD = "D:/BSU/BSU/sem5/Web-programming/lab7/project/xsd_schema.xsd";
	
	private static final Logger logger = Logger.getLogger(Main.class.getName());
	
	public static void main(String[] args) throws ParserException {
		
		logger.info("Start work");
		System.out.println("This is lab2.\n\n");
		
		// Verenich builder is the only builder that is able
		// to work with XML 
		logger.info("Create verenich salad builder");
		System.out.print("Creating verenichSaladBuilder\n\n");
		VerenichSaladBuilder verenichSaladBuilder = new VerenichSaladBuilder();
	

        
		boolean result = false;
        try {
            result = verenichSaladBuilder.validate(FILE_XML, FILE_XSD);
        } catch (XMLValidatorException e) {
        }

        if (result) {
            logger.info("Valid xml");
        } else {
            logger.info("Failed to validate xml");
            return;
        }
        

        
        verenichSaladBuilder.addBroccoli(new Broccoli(1, 2, 3, 4));
		verenichSaladBuilder.addCucumber(new Cucumber(3, 4, 5, 6, 22));
		verenichSaladBuilder.addOnion(new Onion(9, 8, 7, 6, new Color(255, 100, 100)));
		verenichSaladBuilder.addShallot(new Shallot(6, 5, 4, 1, new Color(255, 100, 100)));

		verenichSaladBuilder.writeSAX(FILE_XML);
        SAXParser parserSAX = new SAXParser();
        List<Vegetable> vegetablesSAX = new ArrayList<>();
        vegetablesSAX = parserSAX.parse(FILE_XML);
        System.out.println(vegetablesSAX);

        verenichSaladBuilder.writeDOM(FILE_XML);
        DOMParser parserDOM = new DOMParser();
        List<Vegetable> vegetablesDOM = new ArrayList<>();
        vegetablesDOM = parserDOM.parse(FILE_XML);
        System.out.println(vegetablesDOM);
	}

}
