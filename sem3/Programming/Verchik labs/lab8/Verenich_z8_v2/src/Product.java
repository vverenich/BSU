import java.io.*;
import java.util.*;

public class Product implements Serializable {
    // class release version:
    private static final long serialVersionUID = 1L;
    // areas with prompts:
    String storageNumber;
    private int numberOfProducts;
    private String productName;
    String productCode;
    String dateTime;
    String duration;
    private float dollarPrice;
    public static final String P_storageNumber = "Storage number";
    public static final String P_numberOfProducts = "Number of products";
    public static final String P_productName = "Product name";
    public static final String P_productCode = "Product code";
    public static final String P_dateTime = "Date&Time";
    public static final String P_duration = "Duration";
    public static final String P_price = "Dollar price";
    // validation methods:

    private static Date curDate = new Date();

    //private static GregorianCalendar curCalendar = new GregorianCalendar();
    static Boolean validDate(long dateMS) {
        return dateMS > 0 && dateMS < curDate.getTime();
    }

    static Boolean validDuration(float dur) {
        return dur > 0;
    }

    static Boolean validPrice(float price) {
        return price > 0;
    }

    public static Boolean nextRead(Scanner fin, PrintStream out) {
        return nextRead(P_storageNumber, fin, out);
    }

    static Boolean nextRead(final String prompt, Scanner fin, PrintStream out) {
        out.print(prompt);
        out.print(": ");
        return fin.hasNextLine();
    }

    public static final String nameDel = ",";

    public static Product read(String[] args, PrintStream out)
            throws IOException, CustomException {
        Product Product = new Product();

        Product.storageNumber = args[0];

        Product.numberOfProducts = Integer.parseInt(args[1]);

        Product.productName = args[2];

        Product.productCode = args[3];

        String str = args[4];

        long ms = Date.parse(str);
        if (!validDate(ms))
            throw new CustomException("Invalid format of date");
        Product.dateTime = str;

        float tmp = Float.parseFloat(args[5]);

        if (!validDuration(tmp))
            throw new CustomException("Invalid duration (must be positive number");
        Product.duration = args[5];

        tmp = Float.parseFloat(args[6]);

        if (!validPrice(tmp))
            throw new CustomException("Invalid dollar price (must be positive number");
        Product.dollarPrice = tmp;
        return Product;

    }

    public Product() {
    }

    public static final String areaDel = "\n";

    public String toString() {
        return //new String (
                storageNumber + "\t|" +
                        numberOfProducts + "\t|"  +
                        productName + "\t|"  +
                        productCode + "\t|"  +
                        dateTime + "\t|"  +
                        duration + "\t|" +
                        dollarPrice
                //)
                ;
    }
}
