package servlet;
import servlet.command.*;
import utils.*;

import javax.ejb.EJB;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

@WebServlet("/")
public class MainServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;
    private Map<String, Command> commands;

    public MainServlet() {
        super();
        this.commands = new HashMap<>();
    }

    @EJB
    AdminDAOInterface adminDAOInterface;

    @EJB
    BrigadeDAOInterface brigadeDAOInterface;

    @EJB
    EmployeeDAOInterface employeeDAOInterface;

    @EJB
    PlaneDAOInterface planeDAOInterface;

    @EJB
    RaceDAOInterface raceDAOInterface;

    @Override
    public void init() {
        Command[] commands = {
                new HomeCommand( adminDAOInterface,
                         brigadeDAOInterface,
                         employeeDAOInterface,
                         raceDAOInterface,
                         planeDAOInterface),
                new BrigadePageCommand( adminDAOInterface,
                        brigadeDAOInterface,
                        employeeDAOInterface,
                        raceDAOInterface,
                        planeDAOInterface),
                new AllRacesPageCommand( adminDAOInterface,
                        brigadeDAOInterface,
                        employeeDAOInterface,
                        raceDAOInterface,
                        planeDAOInterface),
                new DelayedRacesPageCommand( adminDAOInterface,
                        brigadeDAOInterface,
                        employeeDAOInterface,
                        raceDAOInterface,
                        planeDAOInterface),
                new CancelRacePageCommand( adminDAOInterface,
                        brigadeDAOInterface,
                        employeeDAOInterface,
                        raceDAOInterface,
                        planeDAOInterface),
                new CancelRaceCommand( adminDAOInterface,
                        brigadeDAOInterface,
                        employeeDAOInterface,
                        raceDAOInterface,
                        planeDAOInterface),
                new BrigadeByRaceCommand( adminDAOInterface,
                        brigadeDAOInterface,
                        employeeDAOInterface,
                        raceDAOInterface,
                        planeDAOInterface),
                new DestinationPageCommand( adminDAOInterface,
                        brigadeDAOInterface,
                        employeeDAOInterface,
                        raceDAOInterface,
                        planeDAOInterface),
                new ChangeDestinationCommand( adminDAOInterface,
                        brigadeDAOInterface,
                        employeeDAOInterface,
                        raceDAOInterface,
                        planeDAOInterface)
        };
        for (Command c : commands) {
            this.commands.put(c.getPattern(), c);
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(true);
        String checkSession = (String) session.getAttribute("check");
        if (checkSession == null) {
            Utils.checkCookies(request, response);
            session.setAttribute("check", "check");
        }
        String command = request.getParameter("command");
        System.out.println(command);
        if (command == null) {
            commands.get("home").doGet(request, response, this.getServletContext());
        } else if (commands.containsKey(command)) {
            commands.get(command).doGet(request, response, this.getServletContext());
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String command = request.getParameter("command");
        if (command == null) {
            commands.get("home").doGet(request, response, this.getServletContext());
        } else if (commands.containsKey(command)) {
            commands.get(command).doPost(request, response, this.getServletContext());
        }
    }
}
