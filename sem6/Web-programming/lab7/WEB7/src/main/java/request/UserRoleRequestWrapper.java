package request;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletRequestWrapper;
import java.security.Principal;
import java.util.List;
 
/**
 * An extension for the HTTPServletRequest that overrides the getUserPrincipal()
 * and isUserInRole(). We supply these implementations here, where they are not
 * normally populated unless we are going through the facility provided by the
 * container.
 * <p>
 * If he user or roles are null on this wrapper, the parent request is consulted
 * to try to fetch what ever the container has set for us. This is intended to
 * be created and used by the UserRoleFilter.
 * 
 * @author thein
 *
 */
public class UserRoleRequestWrapper extends HttpServletRequestWrapper {
 
    private String user;
    private List<String> roles = null;
    private HttpServletRequest realRequest;
 
    public UserRoleRequestWrapper(String user, List<String> roles, HttpServletRequest request) {
    	
        super(request);
        this.user = user;
        this.roles = roles;
        this.realRequest = request;
    }
 
    @Override
    public boolean isUserInRole(String role) {
    	
        if (roles == null) {
        	
            return this.realRequest.isUserInRole(role);
        }
        return roles.contains(role);
    }
 
    @Override
    public Principal getUserPrincipal() {
    	
        if (this.user == null) {
        	
            return realRequest.getUserPrincipal();
        }
 
        // Make an anonymous implementation to just return our user
        return new Principal() {
            
            public String getName() {
            	
                return user;
            }
        };
    }
}

