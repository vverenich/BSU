package servlet.commands;

import model.dao.RoomDAO;
import model.entity.Room;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.Date;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.List;

public class PrintRoomsCommand  implements Command
{
    @Override
    public String getPattern() {
        return "printRooms";
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response,
                      ServletContext servletContext) throws ServletException, IOException
    {
        RequestDispatcher dispatcher = servletContext.getRequestDispatcher("/WEB-INF/view/allRooms.jsp");
        dispatcher.forward(request, response);
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response,
                       ServletContext servletContext) throws ServletException, IOException
    {
        RoomDAO roomDAO = new RoomDAO();
        int guests = 1;
        String type = request.getParameter("typeIdRoom");

        String arrDate = request.getParameter("arrivalDate-room");
        String depDate = request.getParameter("departureDate-room");
        Date arrivalDate, departureDate;

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        LocalDate utilArrDate = LocalDate.parse(arrDate, formatter);
        LocalDate utilDepDate = LocalDate.parse(depDate, formatter);
        arrivalDate  = Date.valueOf(utilArrDate);
        departureDate = Date.valueOf(utilDepDate);

        List<Room> list = roomDAO.showAvailableRooms(guests, arrivalDate,
                departureDate, type);
        request.setAttribute("printRoomsList", list);
        doGet(request, response, servletContext);
    }
}
