package View;

import DAO.AdministratorDAO;
import DAO.Exceptions.DAOException;
import University.Abiturient;
import University.Manager.Administrator;

import java.sql.Date;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Scanner;

import Connector.Exceptions.JDBCConnectionException;

public class Main {

    public static void main(String[] args) throws JDBCConnectionException, DAOException, SQLException {

        Administrator L = new Administrator("Vladislav");

        System.out.println(L.getStartMessage());
        System.out.println(L.getChoiceMessage());

        Scanner in = new Scanner(System.in);

        // Переменная для ответов читателя
        String answer = in.nextLine();
        // Переменная для хранения флажка о надобности выйти из библиотеки
        boolean exit_is_needed = false;

        while (!exit_is_needed)
        {
            switch (answer) {
                case "1" -> {
                        AdministratorDAO A = new AdministratorDAO();
                        System.out.println("Please, enter faculty's ID:");
                        int id = in.nextInt();
                        ArrayList<Abiturient> abiturients = A.getAbiturientsOfFaculty(id);
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
                }
                case "2" -> {
                        AdministratorDAO A = new AdministratorDAO();
                        System.out.println("Please, enter faculty's ID:");
                        int id = in.nextInt();
                        ArrayList<Abiturient> abiturients = A.getAbiturientsWithAverageMoreThanAverageOfFaculty(id);
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
                }
                case "3" -> {
                        AdministratorDAO A = new AdministratorDAO();
                        System.out.println("Please, enter faculty's ID:");
                        int id = in.nextInt();
                        double result = A.getAverageMarkOfFaculty(id);
                        
                        System.out.print("average mark of faculty: ");
                        System.out.print(result);

                        System.out.println("\n" + L.getChoiceMessage());
                        answer = in.nextLine();
                }
                case "4" -> {
                        AdministratorDAO A = new AdministratorDAO();
                        System.out.println("Please, enter surname:");
                        String surname = in.nextLine();
                        System.out.println("Please, enter first name:");
                        String first_name = in.nextLine();
                        System.out.println("Please, enter middle name:");
                        String middle_name = in.nextLine();
                        System.out.println("Please, enter faculty's ID:");
                        int id = in.nextInt();
                        
                        A.registerNewAbiturient(surname, first_name, middle_name, id);

                        System.out.print("Abiturient has been added successfully");

                        
                        System.out.println("\n" + L.getChoiceMessage());
                        answer = in.nextLine();
                }
                case "5" -> {
                        AdministratorDAO A = new AdministratorDAO();
                        System.out.println("Please, enter abiturient ID:");
                        int abiturient_id = in.nextInt();
                        System.out.println("Please, enter subject_id:");
                        int subject_id = in.nextInt();
                        System.out.println("Please, enter mark:");
                        int mark = in.nextInt();
                        
                        A.registerNewAbiturient(abiturient_id, subject_id, mark);

                        System.out.print("Abiturient has been added successfully");

                        
                        System.out.println("\n" + L.getChoiceMessage());
                        answer = in.nextLine();
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
