package model.entity;

import javax.persistence.*;

import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.ToString;

@Entity
@Table(name = "e_abiturient")
@org.hibernate.annotations.NamedNativeQueries({
        @org.hibernate.annotations.NamedNativeQuery(name = "getAbiturientsOfFaculty",
                query = """
                    select abiturient_id, surname, first_name, middle_name, e_abiturient.faculty_id
                    from e_abiturient
                    left join e_faculty on e_faculty.faculty_id = e_abiturient.faculty_id
                    where e_abiturient.faculty_id = :id""", resultClass = Abiturient.class),
        @org.hibernate.annotations.NamedNativeQuery(name = "getAbiturientsWithAvgMoreThanAvgOfFaculty",
                query = """
                    select e_abiturient.abiturient_id, e_abiturient.surname, e_abiturient.first_name, e_abiturient.middle_name, sub_table.avg_mark
                    from      (select e_list.abiturient_id, avg(mark) as avg_mark
                                from e_list
                                group by (e_list.abiturient_id)
                                having avg(mark) > (select avg(mark)
                                                      from e_list
                                                      left join e_abiturient on e_abiturient.abiturient_id = e_list.abiturient_id
                                                      where e_abiturient.faculty_id = :id)) as sub_table
                                left join e_abiturient on e_abiturient.abiturient_id = sub_table.abiturient_id""", resultClass = Abiturient.class),
        @org.hibernate.annotations.NamedNativeQuery(name = "registerNewAbiturient",
                query = """
                    insert into e_abiturient (abiturient_id, surname, first_name, middle_name, faculty_id) 
                    values (nextval('SEQ_ABITURIENT'),?, ?, ?, ?)
            """, resultClass = Abiturient.class),
        @org.hibernate.annotations.NamedNativeQuery(name = "registerNewAbiturientResult",
        query = "insert into e_list (list_id, abiturient_id, subject_id, mark) values(nextval('SEQ_LIST'), ?, ?, ?)", resultClass = Abiturient.class)
        //     ,
        // @NamedQuery(name = "registerNewAbiturientResult",
        //         query = "insert into e_list (list_id, abiturient_id, subject_id, mark) values(nextval('SEQ_LIST'), ?, ?, ?)")
})
@Data
@NoArgsConstructor
public class Abiturient {

    public static final String TABLE = "e_abiturient";
    public static final String ID = "abiturient_id";
    public static final String FIRST_NAME = "first_name";
    public static final String SURNAME = "surname";
    public static final String MIDDLE_NAME = "middle_name";
    public static final String FACULTY_ID = "faculty_id";

    @Id
    @GeneratedValue
    @Column(name = ID)
    private int abiturientId;

    @Column(name = FIRST_NAME)
    private String firstName; 

    @Column(name = SURNAME)
    private String surname;

    @Column(name = MIDDLE_NAME)
    private String middleName;

    @Column(name = FACULTY_ID)
    private int facultyId;


}
