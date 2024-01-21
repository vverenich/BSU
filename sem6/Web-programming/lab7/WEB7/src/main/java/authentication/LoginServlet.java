package authentication;

import bean.UserAccount;
import servlet.commands.HomeCommand;
import utils.AppUtils;
import utils.DataDAO;

import javax.annotation.Resource;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.sql.DataSource;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
	private DataDAO dataDao;
	
	@Resource(name="jdbc/test")
	private DataSource dataSource;
 
    public LoginServlet() {
        super();
    }
    
	@Override
	public void init() throws ServletException {

		super.init();
		
		// create our user dao ... and pass in the conn pool / datasource
		try {
			
			dataDao = new DataDAO(dataSource); 
		}
		catch (Exception exc) {
			
			throw new ServletException(exc);
		}
	}
 
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
 
        RequestDispatcher dispatcher //
                = this.getServletContext().getRequestDispatcher("/WEB-INF/view/loginView.jsp");
 
        dispatcher.forward(request, response);
    }
 
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
 
    	try {
	        String userName = request.getParameter("userName");
	        String password = request.getParameter("password");
	        UserAccount userAccount;
			
				userAccount = dataDao.findUser(userName, password);
			
	 
	        if (userAccount == null) {
	            String errorMessage = "Invalid userName or Password";
	 
	            request.setAttribute("errorMessage", errorMessage);
	 
	            RequestDispatcher dispatcher //
	                    = this.getServletContext().getRequestDispatcher("/WEB-INF/views/loginView.jsp");
	 
	            dispatcher.forward(request, response);
	            return;
	        }
	 
	        AppUtils.storeLoginedUser(request.getSession(), userAccount);
	  
	        int redirectId = -1;
	        try {
	        	
	            redirectId = Integer.parseInt(request.getParameter("redirectId"));
	        } catch (Exception e) {
	        	
	        	System.out.println(e);
	        }
	        String requestUri = AppUtils.getRedirectAfterLoginUrl(request.getSession(), redirectId);
	        
	        if (requestUri != null) {
	        	
	            response.sendRedirect(requestUri);
	        } else {
	        	
	            // Default after successful login
	            // redirect to /userInfo page
				new HomeCommand().doGet(request, response, this.getServletContext());
//	            response.sendRedirect(request.getContextPath() + "/userInfo");
	        }
    	} catch (Exception exc) {

			throw new ServletException(exc);
		}
    }
    
}
