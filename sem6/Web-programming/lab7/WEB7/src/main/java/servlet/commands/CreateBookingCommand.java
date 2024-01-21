package servlet.commands;

import bean.UserAccount;
import model.dao.BookingDAO;
import utils.AppUtils;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

public class CreateBookingCommand implements Command
{

    @Override
    public String getPattern() {
        return "createBooking";
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response,
                      ServletContext servletContext) throws ServletException, IOException
    {
        RequestDispatcher dispatcher = servletContext.getRequestDispatcher("/WEB-INF/view/createBooking.jsp");
        dispatcher.forward(request, response);
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response,
                       ServletContext servletContext) throws ServletException, IOException
    {
        BookingDAO bookingDAO = new BookingDAO();

        HttpSession session = request.getSession(false);
        UserAccount loginedUser = AppUtils.getLoginedUser(request.getSession());
        int clientID = loginedUser.getId();

        String type = request.getParameter("typeId");
        int guests = Integer.parseInt(request.getParameter("guestsNum"));

        String arrDate = request.getParameter("arrivalDate");
        String depDate = request.getParameter("departureDate");
        java.sql.Date arrivalDate, departureDate;

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        LocalDate utilArrDate = LocalDate.parse(arrDate, formatter);
        LocalDate utilDepDate = LocalDate.parse(depDate, formatter);
        arrivalDate  = java.sql.Date.valueOf(utilArrDate);
        departureDate = java.sql.Date.valueOf(utilDepDate);

        bookingDAO.createBooking(type, guests, arrivalDate, departureDate, clientID, 0);

        doGet(request, response, servletContext);
    }
}
