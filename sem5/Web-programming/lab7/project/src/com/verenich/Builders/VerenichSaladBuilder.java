package com.verenich.Builders;

import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;

import com.verenich.Entities.Broccoli;
import com.verenich.Entities.Cabbage;
import com.verenich.Entities.Cucumber;
import com.verenich.Entities.Garlic;
import com.verenich.Entities.Onion;
import com.verenich.Entities.Pumpkin;
import com.verenich.Entities.Shallot;
import com.verenich.Entities.Vegetable;
import com.verenich.Salads.VerenichSalad;
import com.verenich.exception.ParserException;
import com.verenich.exception.XMLValidatorException;
import com.verenich.parser.DOMParser;
import com.verenich.parser.ParsingModeEnum;
import com.verenich.parser.SAXParser;
import com.verenich.parser.StAXParser;
import com.verenich.validator.XMLValidator;
import com.verenich.writer.WriterDOM;
import com.verenich.writer.WriterStAX;

public class VerenichSaladBuilder implements Builder{
	private ArrayList<Vegetable> arrayListSalad = new ArrayList<Vegetable>();
	
	private static final Logger logger = Logger.getLogger(VerenichSaladBuilder.class.getName());
	/**
	 * 
	 * @return the salad that was built
	 */
	public VerenichSalad getSalad()
	{
		return new VerenichSalad(arrayListSalad);
	}
	
	@Override
	public void addBroccoli(Broccoli broccoli) 
	{
		arrayListSalad.add(broccoli);
	}

	@Override
	public void addCabbage(Cabbage cabbage) 
	{
		arrayListSalad.add(cabbage);
	}

	@Override
	public void addCucumber(Cucumber cucumber) 
	{
		arrayListSalad.add(cucumber);
	}

	@Override
	public void addGarlic(Garlic garlic) 
	{
		arrayListSalad.add(garlic);
	}

	@Override
	public void addOnion(Onion onion) 
	{
		arrayListSalad.add(onion);
	}

	@Override
	public void addPumpkin(Pumpkin pumpkin) 
	{
		arrayListSalad.add(pumpkin);
	}

	@Override
	public void addShallot(Shallot shallot) 
	{
		arrayListSalad.add(shallot);
	}

	public void addVegetable(Vegetable v)
	{
		arrayListSalad.add(v);
	}

	public List<Vegetable> parseVegetableList(String file, ParsingModeEnum mode) throws ParserException {
        switch (mode) {
            case DOM:
                return (new DOMParser()).parse(file);
            case SAX:
                return (new SAXParser()).parse(file);
            case StAX:
                return (new StAXParser()).parse(file);
            default:
                return null;
        }
    }

	public boolean validate(String file, String schema) throws XMLValidatorException {
        boolean result = XMLValidator.validate(file, schema);
        if (result) {
            logger.info("Validation succeed");
        } else {
            logger.info("Validation failed");
        }
        return result;
    }

	public void writeDOM(String path){
        WriterDOM writerDOM = new WriterDOM();
		arrayListSalad.add(new Broccoli(10, 12, 13, 10));
        
        writerDOM.xmlWriterDOM(path, arrayListSalad);
    }

    public void writeSAX(String path){
        WriterStAX writerStAX = new WriterStAX();
        arrayListSalad.add(new Broccoli(10, 12, 13, 10));
        
        writerStAX.xmlWriterStAX(path, arrayListSalad);
    }
}
