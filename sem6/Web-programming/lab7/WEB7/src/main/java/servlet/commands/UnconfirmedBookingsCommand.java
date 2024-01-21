package servlet.commands;


import model.dao.BookingDAO;
import model.entity.Booking;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

public class UnconfirmedBookingsCommand implements Command
{
    @Override
    public String getPattern() {
        return "unconfirmedBookings";
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException
    {
        RequestDispatcher dispatcher = servletContext.getRequestDispatcher("/WEB-INF/view/unconfirmedBookings.jsp");

        BookingDAO bookingDao = new BookingDAO();
        List<Booking> list = bookingDao.printBookings();
        request.setAttribute("unconfirmedBookingsList", list);

        dispatcher.forward(request, response);
    }
}
