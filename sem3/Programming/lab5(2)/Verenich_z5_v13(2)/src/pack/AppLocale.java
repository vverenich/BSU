package pack;
import java.util.Locale;
import java.util.ResourceBundle;

public class AppLocale
{
    private static final String strMsg = "pack.Msg";
    private static Locale loc = Locale.getDefault();
    private static ResourceBundle res = ResourceBundle.getBundle(AppLocale.strMsg, AppLocale.loc);

    static Locale get()
    {
        return AppLocale.loc;
    }

    static void set(Locale loc)
    {
        AppLocale.loc = loc;
        res = ResourceBundle.getBundle(AppLocale.strMsg, AppLocale.loc);
    }

    static ResourceBundle getBundle() { return AppLocale.res; }

    static String getString(String key)
    {
        return AppLocale.res.getString(key);
    }

    public static final String driver="DRIVER";
    public static final String car = "CAR";
    public static final String route="ROUTE";
    public static final String stateOfTrip="STATE_OF_TRIP";
    public static final String stateOfCar="STATE_OF_CAR";
    public static final String numberOfCar="NUMBER_OF_CAR";
    public static final String creationDate = "CREATION_DATE";
    public static final String bmw = "BMW";
    public static final String opel ="Opel";
    public static final String mercedes = "Mercedes";
    public static final String reno = "Reno";
    public static final String ivan = "Ivan";
    public static final String john = "John";
    public static final String josh="Josh";
    public static final String minskPinsk = "Minsk_Pinsk";
    public static final String minskBrest = "Minsk_Brest";
    public static final String minskMoscow = "Minsk_Moscow";  
}