import java.util.ArrayList;
import java.util.Scanner;
import java.io.PrintStream;
import java.io.Serializable;
import java.util.Scanner;

public class Phone  implements Serializable {
    String number;
    String name;
    String surname;
    String patronymic;
    String adress;
    String card_number;
    String debit;
    String credit;
    String time_t;
    String time_g;
	
    public static Phone read( Scanner fin ) {
        Phone phone = new Phone();
        phone.number = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        phone.name = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        phone.surname = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        phone.patronymic = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        phone.adress = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        phone.card_number = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        phone.debit = fin.nextLine(); 
        if ( ! fin.hasNextLine()) return null;
        phone.credit = fin.nextLine(); 
        if ( ! fin.hasNextLine()) return null;
        phone.time_t = fin.nextLine(); 
        if ( ! fin.hasNextLine()) return null;
        phone.time_t = fin.nextLine(); 
        return phone;
    }
	
    public Phone() {
    }

    public Phone(String string, String string2, String string3, String string4, String string5, String string6,
			String string7, String string8, String string9, String string10) {
		number = string;
		name = string2;
		surname = string3;
		patronymic = string4;
		adress = string5;
		card_number = string6;
		debit = string7;
		credit = string8;
		time_t = string9;
		time_g = string10;
	}

	public static ArrayList<Phone> createPhones() {
        Phone phone1 = new Phone("80443096123", "Ilya", "Goncharik", "Ivanovich", "Bogdanovicha", "197432", "123409", "109781", "12:37", "14:34");
        Phone phone2 = new Phone("80294375027", "Ilya", "Goncharik", "Ivanovich", "Bogdanovicha", "197432", "123409", "109781", "12:37", "14:34");
        Phone phone3 = new Phone("80334580918", "Ira", "Gorelaia", "Vitalyevna", "Homel, Hataevicha" , "012834", "324081", "237489", "14:11", "16:09");
        Phone phone4 = new Phone("80259374510", "Kolia", "Ivanov", "Petrovich", "Veri Horuzhey" , "982074", "309845", "089324", "17:10", "19:00");
        Phone phone5 = new Phone("80294387242", "Yura", "Kuryanov","Nikolaevich", "Hataevicha 5*", "234792", "300829", "390248", "20:00", "20:30");
        ArrayList<Phone> phones = new ArrayList<>();
        phones.add(phone1);
        phones.add(phone2);
        phones.add(phone3);
        phones.add(phone4);
        phones.add(phone5);
        return phones;
    }
    
	public static Boolean nextRead( Scanner fin, PrintStream out ) {
        return nextRead( "number", fin, out );
    }
	
    static Boolean nextRead( final String prompt, Scanner fin, PrintStream out ) {
        out.print( prompt );
        out.print( ": " );
        return fin.hasNextLine();
    }

    public static final String authorDel = ",";

    public static Phone read( Scanner fin, PrintStream out )  {
        Phone phone = new Phone();
        if ( ! nextRead( "number", fin, out ))           return null;
        phone.number = fin.next();
        out.println(phone.number);
        if ( ! nextRead( "name", fin, out ))             return null;
        phone.name = fin.next();
        out.println(phone.name);
        if ( ! nextRead( "surname", fin, out ))             return null;
        phone.surname = fin.next();
        out.println(phone.surname);
        if ( ! nextRead( "patronymic", fin, out ))        return null;
        phone.patronymic = fin.next();
        out.println(phone.patronymic);
        if ( ! nextRead( "adress", fin, out ))       return null;
        phone.adress = fin.next();
        out.println(phone.adress);
        if ( ! nextRead( "card number", fin, out ))       return null;
        phone.card_number = fin.next();
        out.println(phone.card_number);
        if ( ! nextRead( "debit", fin, out ))       return null;
        phone.debit = fin.next();
        out.println(phone.debit);
        if ( ! nextRead( "credit", fin, out ))       return null;
        phone.credit = fin.next();
        out.println(phone.credit);
        if ( ! nextRead( "time local", fin, out ))       return null;
        phone.time_t = fin.next();
        out.println(phone.time_t);
        if ( ! nextRead( "time global", fin, out ))       return null;
        phone.time_g = fin.next();
        out.println(phone.time_g + "\n\n");
        return phone;
    }

	
    public String toString() {
        return new String (
        	number + "|" +
        	name + "|" +
        	surname + "|" +
        	patronymic + "|" +
        	adress + "|" +
        	card_number + "|" +
        	debit + "|" +
        	credit + "|" +
        	time_t + "|" +
        	time_g
        );
    }
}
