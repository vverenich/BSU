package com.verenich.writer;

import javax.xml.stream.*;

import com.verenich.Entities.Vegetable;
import com.verenich.Entities.Cucumber;
import com.verenich.Entities.Garlic;
import com.verenich.Entities.Pumpkin;

import java.io.FileWriter;
import java.io.IOException;
import java.util.List;
import java.util.logging.Logger;

/**
 * Class WriterStAX
 */
public class WriterStAX {

    private static Logger LOGGER = Logger.getLogger(WriterStAX.class.getName());

    /**
     * The method write data to XML by StAX.
     * @param pathXml - path to XML
     * @param songs - list of TariffBonus objects
     */
    public void xmlWriterStAX(String pathXml, List<Vegetable> vegetables) {
        try{
            XMLOutputFactory output = XMLOutputFactory.newInstance();
            XMLStreamWriter writer = output.createXMLStreamWriter(new FileWriter(pathXml));

            LOGGER.info("Write data to XML by StAX.");
            writer.writeStartDocument("1.0");
            writer.writeStartElement("vegetables");

            for (Vegetable v : vegetables) {
                writer.writeStartElement(v.getClass().getName());

             
                writer.writeStartElement("calories");
                writer.writeCharacters("" + v.getCalories());
                writer.writeEndElement();

    
                writer.writeStartElement("proteins");
                writer.writeCharacters("" + v.getProteins());
           
                writer.writeStartElement("fats");
                writer.writeCharacters("" + v.getFats());
                writer.writeEndElement();
               
                writer.writeStartElement("carbohydrates");
                writer.writeCharacters("" + v.getCarbohydtrates());
                writer.writeEndElement();

                if(v.getClass().getName().equals("Cucumber"))
                {
                    writer.writeStartElement("length");
                    writer.writeCharacters("" + ((Cucumber)v).getLength());
                    writer.writeEndElement();
                }
                else if(v.getClass().getName().equals("Garlic"))
                {
                    writer.writeStartElement("cloves");
                    writer.writeCharacters("" + ((Garlic)v).getCloves());
                    writer.writeEndElement();
                }
                else if(v.getClass().getName().equals("Pumpkin"))
                {
                    writer.writeStartElement("sort");
                    writer.writeCharacters("" + ((Pumpkin)v).getSort());
                    writer.writeEndElement();
                }

                writer.writeEndElement();
            }
            writer.writeEndElement();

            writer.writeEndDocument();
            writer.flush();
            writer.close();
        } catch(XMLStreamException | IOException e){
            e.printStackTrace();
        }
    }
}
