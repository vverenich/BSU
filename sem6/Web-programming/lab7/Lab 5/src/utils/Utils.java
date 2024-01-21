package utils;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class Utils {
    private static String number_of_visits_attr = "NUMBER_OF_VISITS";

    private static String login_time_attr = "LOGIN_TIME_ATTRIBUTE";

    public static void checkCookies(HttpServletRequest request, HttpServletResponse response) {
        String numberOfVisits = getCookieByName(request, number_of_visits_attr);
        Cookie numberOfVisitsCookie;
        if (numberOfVisits == null) {
            numberOfVisitsCookie = new Cookie(number_of_visits_attr, String.valueOf(1));
            numberOfVisitsCookie.setMaxAge(24 * 60 * 60);
        } else {
            int number = Integer.valueOf(numberOfVisits) + 1;
            numberOfVisitsCookie = new Cookie(number_of_visits_attr, String.valueOf(number));
        }
        response.addCookie(numberOfVisitsCookie);
        String loginTime = getCookieByName(request, login_time_attr);
        Cookie cookieLoginTime;
        if (loginTime == null) {
            DateFormat df = new SimpleDateFormat("MM/dd/yyyy HH:mm:ss");
            Date today = Calendar.getInstance().getTime();
            String reportDate = df.format(today);
            cookieLoginTime = new Cookie(login_time_attr, reportDate);
            cookieLoginTime.setMaxAge(24 * 60 * 60);
            response.addCookie(cookieLoginTime);
        }
    }

    private static String getCookieByName(HttpServletRequest request, String name) {
        Cookie[] cookies = request.getCookies();
        if (cookies != null) {
            for (Cookie cookie : cookies) {
                if (name.equals(cookie.getName())) {
                    return cookie.getValue();
                }
            }
        }
        return null;
    }
}
