package config;

import java.util.*;
 
public class SecurityConfig {
 
    public static final String ROLE_ADMIN = "ADMIN";
    public static final String ROLE_USER = "USER";
 
    // String: Role
    // List<String>: urlPatterns.
    private static final Map<String, List<String>> mapConfig = new HashMap<String, List<String>>();
 
    static {
    	
        init();
    }
 
    private static void init() {
 
        // Configure For "EMPLOYEE" Role.
        List<String> urlPatterns1 = new ArrayList<String>();

        urlPatterns1.add("command=createBooking");
        urlPatterns1.add("command=payReceipt");
        urlPatterns1.add("command=confirmBooking");
 
        mapConfig.put(ROLE_USER, urlPatterns1);

        List<String> urlPatterns2 = new ArrayList<String>();

        urlPatterns2.add("command=unpaidReceipts");
        urlPatterns2.add("command=printRooms");
        urlPatterns2.add("command=unconfirmedBookings");
 
        mapConfig.put(ROLE_ADMIN, urlPatterns2);
    }
 
    public static Set<String> getAllAppRoles() {
    	
        return mapConfig.keySet();
    }
 
    public static List<String> getUrlPatternsForRole(String role) {
    	
        return mapConfig.get(role);
    }
 
}
