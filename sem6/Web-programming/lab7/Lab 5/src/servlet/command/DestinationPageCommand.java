package servlet.command;

import model.Race;
import utils.*;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

public class DestinationPageCommand implements Command {

    final String urlPattern = "destinationPageCommand";
    AdminDAOInterface adminDAOInterface;
    BrigadeDAOInterface brigadeDAOInterface;
    EmployeeDAOInterface employeeDAOInterface;
    PlaneDAOInterface planeDAOInterface;
    RaceDAOInterface raceDAOInterface;

    public DestinationPageCommand(AdminDAOInterface adminDAOInterface,
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
        //request.setAttribute("flag", false);
        List<Race> races = adminDAOInterface.getAllRaces();
        request.setAttribute("raceList", races);
        RequestDispatcher dispatcher = request.getRequestDispatcher("/WEB-INF/view/destination.jsp");
        dispatcher.forward(request, response);
    }
}
