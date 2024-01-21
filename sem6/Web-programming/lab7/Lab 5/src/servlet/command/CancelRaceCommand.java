package servlet.command;

import utils.*;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class CancelRaceCommand implements Command {

    final String urlPattern = "cancelRaceCommand";
    AdminDAOInterface adminDAOInterface;
    BrigadeDAOInterface brigadeDAOInterface;
    EmployeeDAOInterface employeeDAOInterface;
    PlaneDAOInterface planeDAOInterface;
    RaceDAOInterface raceDAOInterface;

    public CancelRaceCommand(AdminDAOInterface adminDAOInterface,
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
        new CancelRacePageCommand( adminDAOInterface,
                 brigadeDAOInterface,
                 employeeDAOInterface,
                 raceDAOInterface,
                 planeDAOInterface).doGet(request, response, servletContext);
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException {
        Integer raceId = Integer.parseInt(request.getParameter("raceId"));
        adminDAOInterface.cancelRaceById(raceId);
        doGet(request, response, servletContext);
    }
}
