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
    
	public static Boolean nextRead( String[] args, PrintStream out ) {
        return nextRead( "number", 0, args.length, out );
    }
	
    static Boolean nextRead( final String prompt, int i, int l, PrintStream out ) {
        out.print( prompt );
        out.print( ": " );
        return i < l;
    }

    public static final String authorDel = ",";

    public static Phone read( String[] args, PrintStream out )  {
        Phone phone = new Phone();
        if ( ! nextRead( "number", 0, args.length, out ))           return null;
        phone.number = args[0];
        out.println(phone.number);
        if ( ! nextRead( "name", 1, args.length, out ))             return null;
        phone.name = args[1];
        out.println(phone.name);
        if ( ! nextRead( "surname", 2, args.length, out ))             return null;
        phone.surname = args[2];
        out.println(phone.surname);
        if ( ! nextRead( "patronymic", 3, args.length, out ))        return null;
        phone.patronymic = args[3];
        out.println(phone.patronymic);
        if ( ! nextRead( "adress", 4, args.length, out ))       return null;
        phone.adress = args[4];
        out.println(phone.adress);
        if ( ! nextRead( "card number", 5, args.length, out ))       return null;
        phone.card_number = args[5];
        out.println(phone.card_number);
        if ( ! nextRead( "debit", 6, args.length, out ))       return null;
        phone.debit = args[6];
        out.println(phone.debit);
        if ( ! nextRead( "credit", 7, args.length, out ))       return null;
        phone.credit = args[7];
        out.println(phone.credit);
        if ( ! nextRead( "time local", 8, args.length, out ))       return null;
        phone.time_t = args[8];
        out.println(phone.time_t);
        if ( ! nextRead( "time global", 9, args.length, out ))       return null;
        phone.time_g = args[9];
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
