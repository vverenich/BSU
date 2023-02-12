package com.verenich.parser;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import com.verenich.Entities.Broccoli;
import com.verenich.Entities.Cabbage;
import com.verenich.Entities.Cucumber;
import com.verenich.Entities.Garlic;
import com.verenich.Entities.Onion;
import com.verenich.Entities.Pumpkin;
import com.verenich.Entities.Shallot;
import com.verenich.Entities.Vegetable;
import com.verenich.exception.ParserException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParserFactory;
import java.io.File;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;
import java.util.logging.Logger;



public class SAXParser implements VegetableParser {

    private static final Logger logger = Logger.getLogger("Parser");

    /**
     * Parse XML file to collective using DOM parser
     *
     * @param fileName name of the file that contains songs stored in XML format
     * @return parsed songs list
     * @throws ParserException if some error occurred while parsing XML file
     */
    @Override
    public List<Vegetable> parse(String fileName) throws ParserException {
        logger.info("Starting SAX parsing");
        List<Vegetable> vegetables;

        try {
            File inputFile = new File(fileName);
            SAXParserFactory factory = SAXParserFactory.newInstance();
            javax.xml.parsers.SAXParser saxParser = factory.newSAXParser();
            Handler handler = new Handler();
            saxParser.parse(inputFile, handler);
            vegetables = handler.getVegetables();
        } catch (IOException | SAXException | ParserConfigurationException e) {
            throw new ParserException("Configuration SAX parser error", e);
        }

        logger.info("Finish SAX parsing");
        return vegetables;
    }

    /**
     * Tags handler
     */
    private class Handler extends DefaultHandler {

        private List<Vegetable> vegetables = new ArrayList<>();

        private boolean parsed = true;
        private String currentElement;

        private String calories;
        private String proteins;
        private String fats;
        private String carbohydrates;
        private String length = "1";
        private String cloves = "1";
        private String sort;



        @Override
        public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {
            currentElement = qName;
            if (qName.equals("calories") ||
                    qName.equals("proteins") ||
                    qName.equals("fats") ||
                    qName.equals("carbohydrates") ||
                    qName.equals("length") ||
                    qName.equals("cloves") ||
                    qName.equals("sort")) {
                parsed = false;
            }
        }

        @Override
        public void endElement(String uri, String localName, String qName) throws SAXException {
            switch (qName) {
                case "com.verenich.Entities.Broccoli":
                vegetables.add(new Broccoli(Double.parseDouble(calories), 
                    Double.parseDouble(proteins),
                    Double.parseDouble(fats),
                    Double.parseDouble(carbohydrates)));
                    break;
                case "com.verenich.Entities.Cabbage":
                vegetables.add(new Cabbage(Double.parseDouble(calories), 
                    Double.parseDouble(proteins),
                    Double.parseDouble(fats),
                    Double.parseDouble(carbohydrates)));
                    break;
                case "com.verenich.Entities.Cucumber":
                    vegetables.add(new Cucumber(Double.parseDouble(calories), 
                    Double.parseDouble(proteins),
                    Double.parseDouble(fats),
                    Double.parseDouble(carbohydrates),
                    Integer.parseInt(length)));
                    break;
                case "com.verenich.Entities.Garlic":
                    vegetables.add(new Garlic(Double.parseDouble(calories), 
                    Double.parseDouble(proteins),
                    Double.parseDouble(fats),
                    Double.parseDouble(carbohydrates),
                    Integer.parseInt(cloves)));
                    break;
                case "com.verenich.Entities.Onion":
                    vegetables.add(new Onion(Double.parseDouble(calories), 
                    Double.parseDouble(proteins),
                    Double.parseDouble(fats),
                    Double.parseDouble(carbohydrates)));
                    break;
                case "com.verenich.Entities.Pumpkin":
                    vegetables.add(new Pumpkin(Double.parseDouble(calories), 
                    Double.parseDouble(proteins),
                    Double.parseDouble(fats),
                    Double.parseDouble(carbohydrates),
                    sort));
                    break;
                case "com.verenich.Entities.Shallot":
                    vegetables.add(new Shallot(Double.parseDouble(calories), 
                    Double.parseDouble(proteins),
                    Double.parseDouble(fats),
                    Double.parseDouble(carbohydrates)));
                    break;

            }
        }

        @Override
        public void characters(char[] ch, int start, int length) throws SAXException {
            String value = new String(ch, start, length);
            if (!parsed) {
                switch (currentElement) {
                    case "calories":
                        calories = value;
                        break;
                    case "proteins":
                        proteins=value;
                        break;
                    case "fats":
                        fats = value;
                        break;
                    case "carbohydrates":
                        carbohydrates = value;
                        break;
                    case "length":
                        this.length = value;
                        break;
                    case "cloves":
                        cloves = value;
                        break;
                    case "sort":
                        sort = value;
                        break;
                }

                parsed = true;
            }
        }


        public List<Vegetable> getVegetables() {
            return vegetables;
        }
    }
}
