package filter;

import bean.UserAccount;
import request.UserRoleRequestWrapper;
import utils.AppUtils;
import utils.SecurityUtils;

import javax.servlet.*;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

@WebFilter("/*")
public class SecurityFilter implements Filter {

	public SecurityFilter() {
    }
 
    public void destroy() {
    }
 
    public void doFilter(ServletRequest req, ServletResponse resp, FilterChain chain)
            throws IOException, ServletException {
    	
        HttpServletRequest request = (HttpServletRequest) req;
        HttpServletResponse response = (HttpServletResponse) resp;
 
        String servletPath = request.getServletPath();
 
        // User information stored in the Session.
        // (After successful login).
        UserAccount loginedUser = AppUtils.getLoginedUser(request.getSession());
 
        if (servletPath.equals("/login")) {
        	
            chain.doFilter(request, response);
            return;
        }
        HttpServletRequest wrapRequest = request;
 
        if (loginedUser != null) {
        	
            // User Name
            String userName = loginedUser.getUserName();
 
            // Roles
            List<String> roles = loginedUser.getRoles();
 
            // Wrap old request by a new Request with userName and Roles information.
            wrapRequest = new UserRoleRequestWrapper(userName, roles, request);
        }
 
        // Pages must be signed in.
        if (SecurityUtils.isSecurityPage(request)) {
 
            // If the user is not logged in,
            // Redirect to the login page.
            if (loginedUser == null) {
 
                String requestUri = request.getRequestURI();
 
                // Store the current page to redirect to after successful login.
                int redirectId = AppUtils.storeRedirectAfterLoginUrl(request.getSession(), requestUri);
 
                response.sendRedirect(wrapRequest.getContextPath() + "/login?redirectId=" + redirectId);
                return;
            }
 
            // Check if the user has a valid role?
            boolean hasPermission = SecurityUtils.hasPermission(wrapRequest);
            if (!hasPermission) {
 
                RequestDispatcher dispatcher //
                        = request.getServletContext().getRequestDispatcher("/WEB-INF/view/accessDeniedView.jsp");
 
                dispatcher.forward(request, response);
                return;
            }
        }
 
        chain.doFilter(wrapRequest, response);
    }

    public void init(FilterConfig fConfig) throws ServletException {
    	 
    }
 
}
