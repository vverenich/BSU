package controller;

import model.dao.DAOAbiturient;
import model.dao.DAOFaculty;
import model.entity.Abiturient;
import model.entity.Subject;
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

    public List<Subject> getListOfSubjects() throws ControllerException {
        List<Subject> subject_list;
        daoAbiturient = new DAOAbiturient();
        subject_list = daoAbiturient.getListOfAllSubjects();
        return subject_list;
    }

    public void changeResultOfAbiturient(int abiturient_id, int new_mark) throws ControllerException, DAOException {
        daoAbiturient = new DAOAbiturient();
        daoAbiturient.changeResultOfAbiturient(abiturient_id, new_mark);
    }

    public void registerNewAbiturientResult(int abiturient_id, int subject_id, int mark) throws ControllerException, DAOException {
        daoAbiturient = new DAOAbiturient();
        daoAbiturient.registerNewAbiturientResult(abiturient_id, subject_id, mark);
    }

    public double getAverageMarkOfTheFaculty(int id) {
        daoFaculty = new DAOFaculty();
        return daoFaculty.getAverageMarkOfTheFaculty(id);
    }
}
