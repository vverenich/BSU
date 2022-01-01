/*
import java.io.*;
import java.util.*;

public class Product implements Serializable {
    // class release version:
    private static final long serialVersionUID = 1L;
    // areas with prompts:
    String m_storeNumber; 			
    static final String P_m_storeNumber = "Store Number";
    String m_productCode;				
    static final String P_m_productCode = "Product Code";
    String m_productName;				
    static final String P_m_productName = "Product Name";
    int m_year;				
    static final String P_m_year = "Year";
    String m_storage;			
    static final String P_m_storage = "Storage";
    String m_productNumber;			
    static final String P_m_productNumber = "Product Number";
    double m_price;				
    static final String P_m_price = "Price"; 
	
    // validation methods:
    static Boolean validStoreNumber( String str ) {
    	try {
    		int number = Integer.parseInt(str);
    		return (number>0);
    	}
    	catch(NumberFormatException e){
    		System.out.println("Input value cannot be a Store Number");
    		return false;
    	}
    }
    static Boolean validProductCode( String str ) {
        int i = 0, ndig = 0;
        for ( ; i < str.length(); i++ ) {
            char ch = str.charAt(i);
            if ( Character.isDigit(ch) ) {
                ndig++;
                continue;
            }
            return false;				
        }
        return (ndig == 12);
    }
    private static GregorianCalendar curCalendar = new GregorianCalendar();
    static Boolean validYear( int year ) {
        return year > 0 && year <= curCalendar.get( Calendar.YEAR );
    }
	
    public static Boolean nextRead( Scanner fin, PrintStream out ) {
        return nextRead( P_m_storeNumber, fin, out );
    }
	
    static Boolean nextRead( final String prompt, Scanner fin, PrintStream out ) {
        out.print( prompt );
        out.print( ": " );
        return fin.hasNextLine();
    }

    public static final String storeDel = ",";

    public static Product read( Scanner fin, PrintStream out ) 
            throws IOException {
        String str;
        Product product = new Product();
        product.m_storeNumber = fin.nextLine();
        if ( Product.validStoreNumber( product.m_storeNumber )== false ) {
            throw new IOException("");
        }
        if ( ! nextRead( P_m_productCode, fin, out ))           return null;
        product.m_productCode = fin.nextLine();
        if(Product.validProductCode(product.m_productCode)==false) {
        	throw new IOException("Invalid Product.code value");
        }
        if ( ! nextRead( P_m_productName, fin, out ))             return null;
        product.m_productName = fin.nextLine();
        if ( ! nextRead( P_m_year, fin, out ))             return null;
        str = fin.nextLine();
        product.m_year = Integer.parseInt(str);
        if ( Product.validYear(product.m_year) ==  false ) {
            throw new IOException("Invalid Product.year value");
        }
        if ( ! nextRead( P_m_storage, fin, out ))        return null;
        product.m_storage = fin.nextLine();
        if ( ! nextRead( P_m_productNumber, fin, out ))       return null;
        product.m_productNumber = fin.nextLine();
        if ( ! nextRead( P_m_price, fin, out ))            return null;
        str = fin.nextLine();
        product.m_price = Double.parseDouble(str);
        return product;
    }
		
    public Product() {
    }
	
    public static final String areaDel = "\n";

    public String toString() {
        return //new String (
            m_storeNumber + areaDel +
            m_productCode + areaDel +
            m_productName + areaDel +
            m_year + areaDel +
            m_storage + areaDel +
            m_productNumber + areaDel +
            m_price;
    }
}
*/
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;
import java.io.PrintStream;
import java.io.Serializable;
import java.util.Scanner;

public class Product  implements Serializable {
    int storeNumber_;
    String productCode;
    String productName;
    Date date_;
    int days_;
    int productNumber_;
    double price_;
	
    public static Product read( Scanner fin ) {
        Product product = new Product();
        product.storeNumber = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        product.productCode = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        product.productName = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        product.date = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        product.days = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        product.productNumber = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        product.price = fin.nextLine(); 
        if ( ! fin.hasNextLine()) return null;
        return product;
    }
	
    public Product() {
    }

    public Product(String string, String string2, String string3, String string4, String string5, String string6,
			String string7) {
		storeNumber = string;
		productCode = string2;
		productName = string3;
		date = string4;
		days = string5;
		productNumber = string6;
		price = string7;
	}

	public static ArrayList<Product> createProducts() {
        Product product1 = new Product("100", "123456789012", "pen", "03.10.2001", "10", "10", "12");
        Product product2 = new Product("101", "223456789012", "ball", "02.10.2001", "200", "12", "13");
        Product product3 = new Product("102", "323456789012", "car", "01.10.2001", "1000" , "14", "13");
        Product product4 = new Product("103", "523456789012", "toy", "10.10.2001", "300", "60", "34");
        Product product5 = new Product("104", "423456789012", "gun","12.10.2001", "364", "33", "33");
        ArrayList<Product> products = new ArrayList<>();
        products.add(product1);
        products.add(product2);
        products.add(product3);
        products.add(product4);
        products.add(product5);
        return products;
    }
    
	public static Boolean nextRead( Scanner fin, PrintStream out ) {
        return nextRead( "storeNumber", fin, out );
    }
	
	
	
    static Boolean nextRead( final String prompt, Scanner fin, PrintStream out ) {
    	/*
        out.print( prompt );
        out.print( ": " );
        */
        return fin.hasNextLine();
    }

    public static final String authorDel = ",";

    public static Product read( Scanner fin, PrintStream out )  {
        Product product = new Product();
        if ( ! nextRead( "storeNumber", fin, out ))           return null;
        product.storeNumber = fin.next();
        if ( ! nextRead( "productCode", fin, out ))             return null;
        product.productCode = fin.next();
        if ( ! nextRead( "productName", fin, out ))             return null;
        product.productName = fin.next();
        if ( ! nextRead( "date", fin, out ))        return null;
        product.date = fin.next();
        if ( ! nextRead( "days", fin, out ))       return null;
        product.days = fin.next();
        if ( ! nextRead( "days", fin, out ))       return null;
        product.productNumber = fin.next();
        if ( ! nextRead( "price", fin, out ))       return null;
        product.price = fin.next();
        return product;
    }

	
    public String toString() {
        return new String (
        	storeNumber + "\t|" +
        	productCode + "\t|" +
        	productName + "\t|" +
        	date + "\t|" +
        	days + "\t|" +
        	productNumber + "\t|" +
        	price
        );
    }
    String date;
    String storeNumber;
    String days;
    String productNumber;
    String price;
}


