import java.io.Serializable;
import java.util.Scanner;

public class Product implements Serializable {
	static final long serialVersionUID =1L;
	
    String m_storeNumber;
    String m_productCode;
    String m_productName;
    String m_year;
    String m_storage;
    String m_productNumber;
    String m_price;
	
    public static Product read( Scanner fin ) {
        Product product = new Product();
        product.m_storeNumber = fin.nextLine();
        if ( ! fin.hasNextLine()) {
        	return null;
        }
        product.m_productCode = fin.nextLine();
        if ( ! fin.hasNextLine()) {
        	return null;
        }
        product.m_productName = fin.nextLine();
        if ( ! fin.hasNextLine()) {
        	return null;
        }
        product.m_year = fin.nextLine();
        if ( ! fin.hasNextLine()) {
        	return null;
        }
        product.m_storage = fin.nextLine();
        if ( ! fin.hasNextLine()) {
        	return null;
        }
        product.m_productNumber = fin.nextLine();
        if ( ! fin.hasNextLine()) {
        	return null;
        }
        product.m_price = fin.nextLine(); 
        return product;
    }
	
    public Product() {
    }

    public String toString() {
        return new String (
            m_storeNumber + "\t\t|" +
            m_productCode + "\t|" +
            m_productName + "\t|" +
            m_year + "\t|" +
            m_storage + "\t|" +
            m_productNumber+ "\t\t|" +
            m_price			
        );
    }
}
