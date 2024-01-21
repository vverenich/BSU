package views;



import java.sql.Date;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.logging.Logger;


import java.util.List;
import controller.Administrator;
import controller.Controller;
import model.entity.Abiturient;
import model.entity.Subject;
import model.exception.ControllerException;
import model.exception.DAOException;

public class Main {

    public static void main(String[] args) throws SQLException, DAOException {

        Administrator L = new Administrator("Vladislav");

        System.out.println(L.getStartMessage());
        System.out.println(L.getChoiceMessage());

        Logger logger = Logger.getLogger(Main.class.getName());
        Controller controller = new Controller();
        Scanner in = new Scanner(System.in);

        List<Abiturient> abiturientList;

        // Переменная для ответов читателя1
        String answer = in.nextLine();
        // Переменная для хранения флажка о надобности выйти из библиотеки
        boolean exit_is_needed = false;

        while (!exit_is_needed)
        {
            switch (answer) {
                case "1" -> {
                    try 
                    {
                        System.out.println("Please, enter faculty's ID:");
                        int id = in.nextInt();
                        ArrayList<Abiturient> abiturients = (ArrayList<Abiturient>) controller.getAbiturientsOfFaculty(id);
                        if (abiturients.isEmpty())
                        {
                            System.out.println("We're sorry, but there are no any abiturient");
                        }
                        else
                        {
                            for (Abiturient a : abiturients)
                                System.out.println(a.toString());
                        }
                        System.out.println("\n" + L.getChoiceMessage());
                        answer = in.nextLine();
                    } catch (ControllerException e) {
                        logger.info(e.getMessage());
                    }
                }
                case "2" -> {
                    try 
                    {
                        ArrayList<Subject> subjects = (ArrayList<Subject>) controller.getListOfSubjects();
                        if (subjects.isEmpty())
                        {
                            System.out.println("We're sorry, but there are no any abiturient");
                        }
                        else
                        {
                            for (Subject a : subjects)
                                System.out.println(a.toString());
                        }
                        System.out.println("\n" + L.getChoiceMessage());
                        answer = in.nextLine();
                        
                    } catch (ControllerException e) {
                        logger.info(e.getMessage());
                    }
                }
                case "3" -> {
                    try 
                    {
                        System.out.println("Please, enter faculty's ID:");
                        int id = in.nextInt();
                        ArrayList<Abiturient> abiturients = (ArrayList<Abiturient>) controller.getAbiturientsOfFaculty(id);
                        if (abiturients.isEmpty())
                        {
                            System.out.println("We're sorry, but there are no any abiturient");
                        }
                        else
                        {
                            for (Abiturient a : abiturients)
                                System.out.println(a.toString());
                        }
                        System.out.println("\n" + L.getChoiceMessage());
                        answer = in.nextLine();
                        
                    } catch (ControllerException e) {
                        logger.info(e.getMessage());
                    }
                }
                case "4" -> {
                    try 
                    {
                        System.out.println("Please, enter abiturient_id:");
                        int abiturient_id = in.nextInt();
                        System.out.println("Please, enter new mark:");
                        int mark = in.nextInt();
                        
                        controller.changeResultOfAbiturient(abiturient_id, mark);

                        System.out.print("Abiturient has been updated successfully");

                        
                        System.out.println("\n" + L.getChoiceMessage());
                        answer = in.nextLine();
                        
                    } catch (ControllerException e) {
                        logger.info(e.getMessage());
                    }
                }
                case "5" -> {
                    try 
                    {
                        System.out.println("Please, enter abiturient ID:");
                        int abiturient_id = in.nextInt();
                        System.out.println("Please, enter subject_id:");
                        int subject_id = in.nextInt();
                        System.out.println("Please, enter mark:");
                        int mark = in.nextInt();
                        
                        controller.registerNewAbiturientResult(abiturient_id, subject_id, mark);

                        System.out.print("Abiturient has been added successfully");

                        
                        System.out.println("\n" + L.getChoiceMessage());
                        answer = in.nextLine();
                        
                    } catch (ControllerException e) {
                        logger.info(e.getMessage());
                    }
                }
                case "exit" -> {
                    exit_is_needed = true;
                    System.out.println(L.getExitMessage());
                }
                default -> {
                    System.out.println(L.getMistakeMessage() + "\n" + L.getChoiceMessage());
                    answer = in.nextLine();
                }
            }
        }
    }
}
