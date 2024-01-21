package servlet.commands;

import model.dao.ReceiptDAO;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class ConfirmBookingRoomsCommand implements Command
{
    @Override
    public String getPattern() {
        return "confirmBookingRooms";
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response,
                      ServletContext servletContext) throws ServletException, IOException
    {
        RequestDispatcher dispatcher = servletContext.getRequestDispatcher("/WEB-INF/view/confirmBookingRooms.jsp");
        dispatcher.forward(request, response);
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response,
                       ServletContext servletContext) throws ServletException, IOException
    {
        ReceiptDAO receiptDAO = ConfirmBookingCommand.receiptDAO;
        int roomId = Integer.parseInt(request.getParameter("confirmRoomId"));
        receiptDAO.createBookingFinale(1, roomId);

        new ConfirmBookingCommand().doGet(request, response, servletContext);
    }
}