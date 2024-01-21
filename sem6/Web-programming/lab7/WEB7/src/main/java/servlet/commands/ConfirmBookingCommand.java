package servlet.commands;

import model.dao.ReceiptDAO;
import model.entity.Booking;
import model.entity.Room;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

public class ConfirmBookingCommand implements Command
{
    public  static ReceiptDAO receiptDAO;
    @Override
    public String getPattern() {
        return "confirmBooking";
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response,
                      ServletContext servletContext) throws ServletException, IOException
    {
        RequestDispatcher dispatcher = servletContext.getRequestDispatcher("/WEB-INF/view/confirmBooking.jsp");

        receiptDAO = new ReceiptDAO();
        List<Booking> list = receiptDAO.confirmBookingList();
        request.setAttribute("confirmBookingList", list);

        dispatcher.forward(request, response);
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response,
                       ServletContext servletContext) throws ServletException, IOException
    {
        RequestDispatcher dispatcher = servletContext.getRequestDispatcher("/WEB-INF/view/confirmBookingRooms.jsp");

        receiptDAO = new ReceiptDAO();
        int bookingId = Integer.parseInt(request.getParameter("bookingId"));
        List<Room> list = receiptDAO.confirmBookingRooms(receiptDAO.confirmBookingList(), bookingId);
        request.setAttribute("confirmBookingRoomList", list);
        dispatcher.forward(request, response);
    }
}