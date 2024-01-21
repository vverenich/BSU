package servlet;

import servlet.commands.*;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

@WebServlet
public class MainServlet extends HttpServlet
{
    private static final long serialVersionUID = 1L;
    private Map<String, Command> actions;

    public MainServlet() {
        super();
        this.actions = new HashMap<>();
    }

    @Override
    public void init()
    {
        Command[] actions = {new HomeCommand(), new UnpaidReceiptsCommand(),
                new UnconfirmedBookingsCommand(), new PrintRoomsCommand(),
                new CreateBookingCommand(), new PayReceiptCommand(),
                new ConfirmBookingCommand(), new ConfirmBookingRoomsCommand()};

        for (Command c : actions)
        {
            this.actions.put(c.getPattern(), c);
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException
    {
        String command = request.getParameter("command");
        if (command == null)
        {
            //startNewSession(request, response);
            actions.get("home").doGet(request, response, this.getServletContext());
            System.out.println("Opening command: " + "home");
        }
        else if (actions.containsKey(command))
        {
            actions.get(command).doGet(request, response, this.getServletContext());
            System.out.println("Opening command: " + command);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException
    {
        String command = request.getParameter("command");
        if (command == null)
        {
            actions.get("home").doGet(request, response, this.getServletContext());
            System.out.println("Posting command: " + "index");
        }
        else if (actions.containsKey(command))
        {
            actions.get(command).doPost(request, response, this.getServletContext());
            System.out.println("Posting command: " + command);
        }
    }


    protected void startCookies(HttpServletRequest request, HttpServletResponse response)
            throws UnsupportedEncodingException
    {
        SimpleDateFormat formatter = new SimpleDateFormat("dd/MM/yyyy/HH:mm:ss");
        Date date = new Date();

        Cookie lastEnterTime = new Cookie("lastEnterTime", formatter.format(date));
        lastEnterTime.setComment(URLEncoder.encode( "Last-visit:", "UTF-8" ));
        Cookie usageCount = new Cookie("usageCount", URLEncoder.encode( "1", "UTF-8" ));
        usageCount.setComment(URLEncoder.encode("Times-you-have-visited-our-website:", "UTF-8"));

				lastEnterTime.setSecure(true);
				lastEnterTime.setHttpOnly(true);
				
				usageCount.setSecure(true);
				usageCount.setHttpOnly(true);


        Cookie[] cookies = request.getCookies();
        if (cookies != null)
        {
            for (Cookie cookie : cookies)
            {
				
				cookie.setSecure(true);
				cookie.setHttpOnly(true);
                if (cookie.getName().equals("usageCount"))
                {
                    int lastUsageCount = Integer.parseInt(cookie.getValue());
                    lastUsageCount += 1;
                    usageCount.setValue(URLEncoder.encode(Integer.toString(lastUsageCount), "UTF-8"));
                }
            }
        }
        response.addCookie(lastEnterTime);
        response.addCookie(usageCount);
    }

}

