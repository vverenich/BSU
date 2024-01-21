package servlet.command;

import model.Employee;
import utils.*;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

public class BrigadeByRaceCommand implements Command {

    final String urlPattern = "getBrigadeByRaceCommand";
    AdminDAOInterface adminDAOInterface;
    BrigadeDAOInterface brigadeDAOInterface;
    EmployeeDAOInterface employeeDAOInterface;
    PlaneDAOInterface planeDAOInterface;
    RaceDAOInterface raceDAOInterface;

    public BrigadeByRaceCommand(AdminDAOInterface adminDAOInterface,
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
        RequestDispatcher dispatcher = request.getRequestDispatcher("/WEB-INF/view/brigade.jsp");
        dispatcher.forward(request, response);
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext) throws ServletException, IOException {
        Integer raceId = Integer.parseInt(request.getParameter("raceId"));

        List<Employee> emps = raceDAOInterface.readRace(raceId).getBrigade().getEmployees();
        for(int i = 0; i < 3; i++){
            System.out.println(emps.get(i).getName());
        }
        request.setAttribute("emps", emps);

        request.setAttribute("flag", true);

        new BrigadePageCommand( adminDAOInterface,
                 brigadeDAOInterface,
                 employeeDAOInterface,
                 raceDAOInterface,
                 planeDAOInterface).doGet(request,response,servletContext);
    }
}


