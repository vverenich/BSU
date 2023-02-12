package com.verenich.parser;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.LogManager;
import java.util.logging.Logger;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import com.verenich.Entities.Broccoli;
import com.verenich.Entities.Cabbage;
import com.verenich.Entities.Cucumber;
import com.verenich.Entities.Garlic;
import com.verenich.Entities.Onion;
import com.verenich.Entities.Pumpkin;
import com.verenich.Entities.Shallot;
import com.verenich.Entities.Vegetable;
import com.verenich.exception.ParserException;

public class DOMParser implements VegetableParser {

    private static final Logger logger = Logger.getLogger("Parser");
    
    @Override
    public List<Vegetable> parse(String fileName) throws ParserException {
        logger.info("Starting DOM parsing");
        List<Vegetable> vegetables = new ArrayList<>();

        File inputFile = new File(fileName);
        DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder dBuilder = null;
        Document doc = null;
        try {
            dBuilder = dbFactory.newDocumentBuilder();
            doc = dBuilder.parse(inputFile);
        } catch (SAXException | IOException | ParserConfigurationException e) {
            throw new ParserException("Configuration DOM parser error", e);
        }
        doc.getDocumentElement().normalize();


        NodeList broccoliNodes = doc.getElementsByTagName("com.verenich.Entities.Broccoli");
        NodeList cabbageNodes = doc.getElementsByTagName("com.verenich.Entities.Cabbage");
        NodeList cucumberNodes = doc.getElementsByTagName("com.verenich.Entities.Cucumber");
        NodeList garlicNodes = doc.getElementsByTagName("com.verenich.Entities.Garlic");
        NodeList onionNodes = doc.getElementsByTagName("com.verenich.Entities.Onion");
        NodeList pumpkinNodes = doc.getElementsByTagName("com.verenich.Entities.Pumpkin");
        NodeList shallotNodes = doc.getElementsByTagName("com.verenich.Entities.Shallot");


        for (int i = 0; i < broccoliNodes.getLength(); ++i) {
            Node node = broccoliNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String calories = element.getElementsByTagName("calories").item(0).getTextContent();
                String proteins = element.getElementsByTagName("proteins").item(0).getTextContent();
                String fats = element.getElementsByTagName("fats").item(0).getTextContent();
                String carbohydrates = element.getElementsByTagName("carbohydrates").item(0).getTextContent();

                vegetables.add(new Broccoli(Double.parseDouble(calories), 
                                            Double.parseDouble(proteins),
                                            Double.parseDouble(fats),
                                            Double.parseDouble(carbohydrates)));
            }
        }

        for (int i = 0; i < cabbageNodes.getLength(); ++i) {
            Node node = cabbageNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String calories = element.getElementsByTagName("calories").item(0).getTextContent();
                String proteins = element.getElementsByTagName("proteins").item(0).getTextContent();
                String fats = element.getElementsByTagName("fats").item(0).getTextContent();
                String carbohydrates = element.getElementsByTagName("carbohydrates").item(0).getTextContent();

                vegetables.add(new Cabbage(Double.parseDouble(calories), 
                                            Double.parseDouble(proteins),
                                            Double.parseDouble(fats),
                                            Double.parseDouble(carbohydrates)));
            }
        }

        for (int i = 0; i < cucumberNodes.getLength(); ++i) {
            Node node = cucumberNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String calories = element.getElementsByTagName("calories").item(0).getTextContent();
                String proteins = element.getElementsByTagName("proteins").item(0).getTextContent();
                String fats = element.getElementsByTagName("fats").item(0).getTextContent();
                String carbohydrates = element.getElementsByTagName("carbohydrates").item(0).getTextContent();
                //String length = element.getElementsByTagName("length").item(0).getTextContent();

                vegetables.add(new Cucumber(Double.parseDouble(calories), 
                                            Double.parseDouble(proteins),
                                            Double.parseDouble(fats),
                                            Double.parseDouble(carbohydrates),
                                            10));
            }
        }
        
        for (int i = 0; i < garlicNodes.getLength(); ++i) {
            Node node = garlicNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String calories = element.getElementsByTagName("calories").item(0).getTextContent();
                String proteins = element.getElementsByTagName("proteins").item(0).getTextContent();
                String fats = element.getElementsByTagName("fats").item(0).getTextContent();
                String carbohydrates = element.getElementsByTagName("carbohydrates").item(0).getTextContent();
                //String cloves = element.getElementsByTagName("cloves").item(0).getTextContent();

                vegetables.add(new Garlic(Double.parseDouble(calories), 
                                            Double.parseDouble(proteins),
                                            Double.parseDouble(fats),
                                            Double.parseDouble(carbohydrates),
                                            12));
            }
        }

        for (int i = 0; i < onionNodes.getLength(); ++i) {
            Node node = onionNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String calories = element.getElementsByTagName("calories").item(0).getTextContent();
                String proteins = element.getElementsByTagName("proteins").item(0).getTextContent();
                String fats = element.getElementsByTagName("fats").item(0).getTextContent();
                String carbohydrates = element.getElementsByTagName("carbohydrates").item(0).getTextContent();
                
                vegetables.add(new Onion(Double.parseDouble(calories), 
                                            Double.parseDouble(proteins),
                                            Double.parseDouble(fats),
                                            Double.parseDouble(carbohydrates)));
            }
        }

        for (int i = 0; i < pumpkinNodes.getLength(); ++i) {
            Node node = pumpkinNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String calories = element.getElementsByTagName("calories").item(0).getTextContent();
                String proteins = element.getElementsByTagName("proteins").item(0).getTextContent();
                String fats = element.getElementsByTagName("fats").item(0).getTextContent();
                String carbohydrates = element.getElementsByTagName("carbohydrates").item(0).getTextContent();
                //String sort = element.getElementsByTagName("sort").item(0).getTextContent();
                
                vegetables.add(new Pumpkin(Double.parseDouble(calories), 
                                            Double.parseDouble(proteins),
                                            Double.parseDouble(fats),
                                            Double.parseDouble(carbohydrates),
                                            "sort"));
            }
        }

        for (int i = 0; i < shallotNodes.getLength(); ++i) {
            Node node = shallotNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String calories = element.getElementsByTagName("calories").item(0).getTextContent();
                String proteins = element.getElementsByTagName("proteins").item(0).getTextContent();
                String fats = element.getElementsByTagName("fats").item(0).getTextContent();
                String carbohydrates = element.getElementsByTagName("carbohydrates").item(0).getTextContent();

                vegetables.add(new Shallot(Double.parseDouble(calories), 
                                            Double.parseDouble(proteins),
                                            Double.parseDouble(fats),
                                            Double.parseDouble(carbohydrates)));
            }
        }

        logger.info("Finish DOM parsing");
        return vegetables;
    }
}
