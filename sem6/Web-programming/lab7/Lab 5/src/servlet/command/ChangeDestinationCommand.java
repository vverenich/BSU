package servlet.command;

import utils.*;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class ChangeDestinationCommand implements Command {

    final String urlPattern = "changeDestinationCommand";
    AdminDAOInterface adminDAOInterface;
    BrigadeDAOInterface brigadeDAOInterface;
    EmployeeDAOInterface employeeDAOInterface;
    PlaneDAOInterface planeDAOInterface;
    RaceDAOInterface raceDAOInterface;

    public ChangeDestinationCommand(AdminDAOInterface adminDAOInterface,
                             BrigadeDAOInterface brigadeDAOInterface,
                             EmployeeDAOInterface employeeDAOInterface,
                             RaceDAOInterface raceDAOInterface,
                             PlaneDAOInterface planeDAOInterface) {
        super();
        this.adminDAOInterface = adminDAOInterface;
        this.brigadeDAOInterface = brigadeDAOInterface;
        this.planeDAOInterface = planeDAOInterface;
        this.raceDAOInterface = raceDAOInterface;
        this.employeeDAOInterface = employeeDAOInterface;
    }

    @Override
    public String getPattern() {
        return urlPattern;
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext) throws ServletException, IOException {
        new DestinationPageCommand( adminDAOInterface,
                brigadeDAOInterface,
                employeeDAOInterface,
                raceDAOInterface,
                planeDAOInterface).doGet(request, response, servletContext);
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException {
        Integer raceId = Integer.parseInt(request.getParameter("raceId"));
        String destination = String.valueOf(request.getParameter("destination"));

        adminDAOInterface.updateDestinationById(raceId, destination);
        doGet(request, response, servletContext);
    }
}