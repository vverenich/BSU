package servlet.commands;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class HomeCommand implements Command
{
    @Override
    public String getPattern() {
        return "home";
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException
    {
        RequestDispatcher dispatcher = servletContext.getRequestDispatcher("/WEB-INF/view/homeClient.jsp");
        dispatcher.forward(request, response);
    }
}
