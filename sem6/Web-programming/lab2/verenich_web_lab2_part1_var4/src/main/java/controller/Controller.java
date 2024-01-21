package controller;

import model.dao.DAOAbiturient;
import model.dao.DAOFaculty;
import model.entity.Abiturient;
import model.exception.ControllerException;
import model.exception.DAOException;

import java.util.List;

public class Controller {

    /**
     * DAOReader object to work with table reader
     */
    private DAOAbiturient daoAbiturient;
    /**
     * DAOBook object to work with table reader
     */
    private DAOFaculty daoFaculty;

    public List<Abiturient> getAbiturientsOfFaculty(int id) throws ControllerException {
        List<Abiturient> abiturient_list;
        daoAbiturient = new DAOAbiturient();
        abiturient_list = daoAbiturient.getAbiturientsOfFaculty(id);
        return abiturient_list;
    }

    public List<Abiturient> getAbiturientsWithAvgMoreThanAvgOfFaculty(int id) throws ControllerException {
        List<Abiturient> abiturient_list;
        daoAbiturient = new DAOAbiturient();
        abiturient_list = daoAbiturient.getAbiturientsWithAvgMoreThanAvgOfFaculty(id);
        return abiturient_list;
    }

    public void registerNewAbiturient(String surname, String first_name, String middle_name, int faculty_id) throws ControllerException, DAOException {
        daoAbiturient = new DAOAbiturient();
        daoAbiturient.registerNewAbiturient(surname, first_name, middle_name, faculty_id);
    }

    public void registerNewAbiturientResult(int abiturient_id, int subject_id, int mark) throws ControllerException, DAOException {
        daoAbiturient = new DAOAbiturient();
        daoAbiturient.registerNewAbiturientResult(abiturient_id, subject_id, mark);
    }
}
