package DAO;

import DAO.Exceptions.DAOException;
import University.Abiturient;
import University.Book;
import University.Faculty;

import java.sql.SQLException;
import java.util.ArrayList;

public class AdministratorDAO extends DAO {

    private static final String abiturients_of_faculty = """
                                                            select abiturient_id, surname, first_name, middle_name, e_abiturient.faculty_id
                                                            from e_abiturient
                                                            left join e_faculty on e_faculty.faculty_id = e_abiturient.faculty_id
                                                            where e_abiturient.faculty_id =?""";

    private static final String abiturients_with_avg_more_than_avg_of_faculty = """
        select e_abiturient.abiturient_id, e_abiturient.surname, e_abiturient.first_name, e_abiturient.middle_name, sub_table.avg_mark
        from      (select e_list.abiturient_id, avg(mark) as avg_mark
		            from e_list
		            group by (e_list.abiturient_id)
		            having avg(mark) > (select avg(mark)
				  			            from e_list
				  			            left join e_abiturient on e_abiturient.abiturient_id = e_list.abiturient_id
				  			            where e_abiturient.faculty_id = ?)) as sub_table
                    left join e_abiturient on e_abiturient.abiturient_id = sub_table.abiturient_id;""";

    private static final String avg_of_faculty = """
        select avg(mark)
        from e_list
        left join e_abiturient on e_abiturient.abiturient_id = e_list.abiturient_id
        where e_abiturient.faculty_id =?""";

    private static final String register_new_abiturient = """
        insert into e_abiturient (abiturient_id, surname, first_name, middle_name, faculty_id) values (nextval('SEQ_ABITURIENT'),?, ?, ?, ?);""";

    private static final String register_new_abiturient_result = "insert into e_list (list_id, abiturient_id, subject_id, mark) values(nextval('SEQ_LIST'), ?, ?, ?);";


    public ArrayList<Abiturient> getAbiturientsOfFaculty(int faculty_id)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(abiturients_of_faculty);

        try { // Добавляем в запрос нужный ID факультета
            ps.setInt(1, faculty_id);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put faculty_id to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        ArrayList<Abiturient> abiturients = new ArrayList<Abiturient>(); // Список абитуриентов

        try {
            while(rs.next())
            {
                Abiturient next_abiturient = new Abiturient(Integer.parseInt(rs.getString("abiturient_id")),
                        rs.getString("surname"),
                        rs.getString("first_name"),
                        rs.getString("middle_name"),
                        Integer.parseInt(rs.getString("faculty_id")));
                abiturients.add(next_abiturient);
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        return abiturients;
    }

    
    public ArrayList<Abiturient> getAbiturientsWithAverageMoreThanAverageOfFaculty(int faculty_id)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(abiturients_with_avg_more_than_avg_of_faculty);

        try { // Добавляем в запрос нужный ID факультета
            ps.setInt(1, faculty_id);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put faculty_id to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        ArrayList<Abiturient> abiturients = new ArrayList<Abiturient>(); // Список абитуриентов

        try {
            while(rs.next())
            {
                Abiturient next_abiturient = new Abiturient(Integer.parseInt(rs.getString("abiturient_id")),
                        rs.getString("surname"),
                        rs.getString("first_name"),
                        rs.getString("middle_name"),
                        faculty_id);
                abiturients.add(next_abiturient);
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        return abiturients;
    }

    public double getAverageMarkOfFaculty(int faculty_id)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(avg_of_faculty);

        try { // Добавляем в запрос нужный ID факультета
            ps.setInt(1, faculty_id);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put faculty_id to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        double result = 0;

        try {
            while(rs.next())
            {
                result = rs.getDouble("avg");
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        return result;
    }

    public void registerNewAbiturient(String surname, String first_name, String middle_name, int faculty_id) throws SQLException
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(register_new_abiturient);
        try { // Добавляем в запрос нужный ID факультета
            ps.setString(1, surname);
            ps.setString(2, first_name);
            ps.setString(3, middle_name);
            ps.setInt(4, faculty_id);

        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put params to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }


        executeUpdateStatement();
    }

    public void registerNewAbiturient(int abiturient_id, int subject_id, int mark)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(register_new_abiturient_result);
        try { // Добавляем в запрос нужный ID факультета
            ps.setInt(1, abiturient_id);
            ps.setInt(2, subject_id);
            ps.setInt(3, mark);

        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put params to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }


        executeUpdateStatement();
    }

    /* 


    public ArrayList<Book> getBooksWithSpecialName(String book_name)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(SELECT_ALL_BOOKS_WITH_SOME_NAME);
        try { // Добавляем в запрос нужное название книги
            ps.setString(1, book_name);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put book's name to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        ArrayList<Book> books = new ArrayList<Book>(); // Список книг

        try {
            while(rs.next())
            {
                Book next_book = new Book(Integer.parseInt(rs.getString("bID")),
                        rs.getString("bName"),
                        rs.getString("bAuthor"),
                        Integer.parseInt(rs.getString("bAmount")));
                books.add(next_book);
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        return books;
    }

    public ArrayList<Book> getBooksWithSpecialAuthor(String author_name)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(SELECT_ALL_BOOKS_WITH_SOME_AUTHOR);
        try { // Добавляем в запрос нужное название автора книги
            ps.setString(1, author_name);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put author's name to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        ArrayList<Book> books = new ArrayList<Book>(); // Список книг

        try {
            while(rs.next())
            {
                Book next_book = new Book(Integer.parseInt(rs.getString("bID")),
                        rs.getString("bName"),
                        rs.getString("bAuthor"),
                        Integer.parseInt(rs.getString("bAmount")));
                books.add(next_book);
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        return books;
    }

    public Book getBookWithSpecialID(int book_id)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(SELECT_BOOK_BY_BOOK_ID);
        try { // Добавляем в запрос нужный ID книги
            ps.setInt(1, book_id);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put book's ID to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        Book book = null; // Книга

        try {
            if (rs.next())
            {
                book = new Book(Integer.parseInt(rs.getString("bID")),
                        rs.getString("bName"),
                        rs.getString("bAuthor"),
                        Integer.parseInt(rs.getString("bAmount")));
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        return book;
    }

    public int getAmountOfBooksWithSpecialID(int book_id)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(GET_AMOUNT_OF_BOOKS_OF_SPECIAL_ID);
        try { // Добавляем в запрос нужный ID книги
            ps.setInt(1, book_id);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put book's ID to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeStatement();

        int amount = 0; // Количество экземпляров книги

        try {
            if (rs.next())
            {
                amount = Integer.parseInt(rs.getString("bAmount"));
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }



        return amount;
    }

    public void borrowBookWithSpecialID(int book_id)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(BORROW_ONE_BOOK_WITH_SPECIAL_ID);
        try { // Добавляем в запрос нужный ID книги
            ps.setInt(1, book_id);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put book's ID to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeUpdateStatement();
    }

    public void returnBookWithSpecialID(int book_id)
    {
        // Компилируем запрос (скомпилируется в переменную ps)
        compileStatement(RETURN_ONE_BOOK_WITH_SPECIAL_ID);
        try { // Добавляем в запрос нужный ID книги
            ps.setInt(1, book_id);
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't put book's ID to query.", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        // Выполняем запрос (данные запишутся в переменную rs)
        executeUpdateStatement();
    }
    */

}
