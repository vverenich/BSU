package DAO;

import DAO.Exceptions.DAOException;
import University.Abiturient;
import University.Faculty;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import com.mysql.cj.conf.ConnectionUrlParser;

import Connector.Exceptions.JDBCConnectionException;

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

    public AdministratorDAO() throws JDBCConnectionException {
    }

    public ArrayList<Abiturient> getAbiturientsOfFaculty(int faculty_id) throws DAOException, JDBCConnectionException
    {
        ConnectionUrlParser.Pair<PreparedStatement, ResultSet> ps_rs = executeStatement(abiturients_of_faculty, 1, Integer.toString(faculty_id));

        ArrayList<Abiturient> abiturients = new ArrayList<Abiturient>(); // Список абитуриентов

        try {
            while(ps_rs.right.next())
            {
                Abiturient next_abiturient = new Abiturient(Integer.parseInt(ps_rs.right.getString("abiturient_id")),
                        ps_rs.right.getString("surname"),
                        ps_rs.right.getString("first_name"),
                        ps_rs.right.getString("middle_name"),
                        Integer.parseInt(ps_rs.right.getString("faculty_id")));
                abiturients.add(next_abiturient);
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        closePreparedStatement(ps_rs.left);

        closeResultSet(ps_rs.right);

        return abiturients;
    }

    
    public ArrayList<Abiturient> getAbiturientsWithAverageMoreThanAverageOfFaculty(int faculty_id) throws DAOException, JDBCConnectionException
    {
        ConnectionUrlParser.Pair<PreparedStatement, ResultSet> ps_rs = executeStatement(abiturients_with_avg_more_than_avg_of_faculty, 2, Integer.toString(faculty_id));

        ArrayList<Abiturient> abiturients = new ArrayList<Abiturient>(); // Список абитуриентов

        try {
            while(ps_rs.right.next())
            {
                Abiturient next_abiturient = new Abiturient(Integer.parseInt(ps_rs.right.getString("abiturient_id")),
                        ps_rs.right.getString("surname"),
                        ps_rs.right.getString("first_name"),
                        ps_rs.right.getString("middle_name"),
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

        closePreparedStatement(ps_rs.left);

        closeResultSet(ps_rs.right);

        return abiturients;
    }

    public double getAverageMarkOfFaculty(int faculty_id) throws DAOException, JDBCConnectionException
    {
        ConnectionUrlParser.Pair<PreparedStatement, ResultSet> ps_rs = executeStatement(avg_of_faculty, 3, Integer.toString(faculty_id));

        double result = 0;

        try {
            while(ps_rs.right.next())
            {
                result = ps_rs.right.getDouble("avg");
            }
        } catch (SQLException throwables) {
            try {
                throw new DAOException("Error! Can't get data from ResultSet!", throwables);
            } catch (DAOException e) {
                e.printStackTrace();
            }
        }

        closePreparedStatement(ps_rs.left);

        closeResultSet(ps_rs.right);

        return result;
    }

    public void registerNewAbiturient(String surname, String first_name, String middle_name, int faculty_id) throws SQLException, DAOException, JDBCConnectionException
    {
        executeUpdateStatement(register_new_abiturient, 4, surname + "|" + first_name + "|" + middle_name + "|" + faculty_id );
    }

    public void registerNewAbiturient(int abiturient_id, int subject_id, int mark) throws SQLException, DAOException, JDBCConnectionException
    {
        String info = new String( Integer.toString(abiturient_id) + "|" + Integer.toString(subject_id) + "|" + Integer.toString(mark));
        executeUpdateStatement(register_new_abiturient_result, 5, info);
    }

}
