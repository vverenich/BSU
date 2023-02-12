package com.verenich.parser;

import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;

import com.verenich.Entities.Broccoli;
import com.verenich.Entities.Cabbage;
import com.verenich.Entities.Cucumber;
import com.verenich.Entities.Garlic;
import com.verenich.Entities.Onion;
import com.verenich.Entities.Pumpkin;
import com.verenich.Entities.Shallot;
import com.verenich.Entities.Vegetable;
import com.verenich.exception.ParserException;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;
import java.util.logging.Logger;

/**
 * StAX parser of XML
 */

public class StAXParser implements VegetableParser {

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
        logger.info("Starting Stax parsing");
        List<Vegetable> vegetables = new ArrayList<>();

        XMLInputFactory factory = XMLInputFactory.newInstance();
        XMLEventReader eventReader;
        try {
            eventReader = factory.createXMLEventReader(new FileReader(fileName));
        } catch (XMLStreamException | FileNotFoundException e) {
            throw new ParserException("Configuration StAX parser error", e);
        }
        String currentElement = "";
        boolean parsed;
        parsed = true;

        String calories = "";
        String proteins = "";
        String fats = "";
        String carbohydrates = "";
        String length = "";
        String cloves = "";
        String sort = "";

        while (eventReader.hasNext()) {
            XMLEvent event = null;
            try {
                event = eventReader.nextEvent();
            } catch (XMLStreamException e) {
                throw new ParserException("Fail to get eventReader", e);
            }
            String qName = "";

            switch (event.getEventType()) {
                case XMLStreamConstants.START_ELEMENT:
                    StartElement startElement = event.asStartElement();
                    qName = startElement.getName().getLocalPart();
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
                    break;
                case XMLStreamConstants.CHARACTERS:
                    String value = event.asCharacters().getData();
                    if (!parsed) {
                        switch (currentElement) {
                            case "calories":
                                calories = value;
                                break;
                            case "proteins":
                                proteins=value;
                                break;
                            case "fats":
                                fats =  value;
                                break;
                            case "carbohydrates":
                                carbohydrates = value;
                                break;
                            case "length":
                                length=value;
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
                    break;
                case XMLStreamConstants.END_ELEMENT:
                    EndElement endElement = event.asEndElement();
                    qName = endElement.getName().getLocalPart();
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
                    break;
            }
        }


        return vegetables;
    }
}
