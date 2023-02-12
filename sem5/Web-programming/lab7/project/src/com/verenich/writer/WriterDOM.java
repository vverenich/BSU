package com.verenich.writer;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import com.verenich.Entities.Cucumber;
import com.verenich.Entities.Garlic;
import com.verenich.Entities.Pumpkin;
import com.verenich.Entities.Vegetable;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.util.List;
import java.util.logging.Logger;

/**
 * Class WriterDOM
 *
 */
public class WriterDOM {

    private static Logger LOGGER = Logger.getLogger(WriterDOM.class.getName());

    /**
     * The method write data to XML by DOM.
     * @param pathXml - path to XML
     * @param songs - list of TariffBonus objects
     */
    public void xmlWriterDOM(String pathXml, List<Vegetable> vegetables) {
        try {
            Document document = DocumentBuilderFactory.newInstance().newDocumentBuilder().newDocument();

            LOGGER.info("The method write data to XML by DOM.");

            Element tariffs = document.createElement("vegetables");
            document.appendChild(tariffs);

            for (Vegetable v : vegetables) {
                Element tb = document.createElement(v.getClass().getName());
                tariffs.appendChild(tb);

                Element costTariff = document.createElement("calories");
                costTariff.setTextContent(""+v.getCalories());
                tb.appendChild(costTariff);

                Element costMinuteInNet = document.createElement("proteins");
                costMinuteInNet.setTextContent(""+v.getProteins());
                tb.appendChild(costMinuteInNet);

                Element costSms = document.createElement("fats");
                costSms.setTextContent(""+v.getFats());
                tb.appendChild(costSms);

                Element costMegabyte = document.createElement("carbohydrates");
                costMegabyte.setTextContent(""+v.getCarbohydtrates());
                tb.appendChild(costMegabyte);

                if(v.getClass().getName().equals("Cucumber")) {
                    Element cost = document.createElement("length");
                    cost.setTextContent("" + ((Cucumber)v).getLength() ) ;
                    tb.appendChild(cost);
                }
                else if(v.getClass().getName().equals("Garlic")) {
                    Element cost = document.createElement("cloves");
                    cost.setTextContent("" + ((Garlic)v).getCloves()) ;
                    tb.appendChild(cost);
                }
                else if(v.getClass().getName().equals("Pumpkin")) {
                    Element cost = document.createElement("sort");
                    cost.setTextContent("" + ((Pumpkin)v).getSort()) ;
                    tb.appendChild(cost);
                }
            }

            Transformer t=TransformerFactory.newInstance().newTransformer();
            t.transform(new DOMSource(document), new StreamResult(new FileOutputStream(pathXml)));

            System.out.println("Write completed.");

        } catch (ParserConfigurationException | TransformerException | FileNotFoundException e) {
            e.printStackTrace();
        }
    }
}
