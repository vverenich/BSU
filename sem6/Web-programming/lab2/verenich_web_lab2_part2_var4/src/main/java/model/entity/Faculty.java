package model.entity;

import javax.persistence.*;
import lombok.Data;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.ToString;

import static model.entity.Faculty.facultyTable;

// @Entity
// @Table(name = facultyTable)
// @org.hibernate.annotations.NamedNativeQueries({
//         @org.hibernate.annotations.NamedNativeQuery(name = "getAvgOfFaculty",
//                 query = """
//                     select avg(mark)
//                     from e_list
//                     left join e_abiturient on e_abiturient.abiturient_id = e_list.abiturient_id
//                     where e_abiturient.faculty_id = :id""", resultClass = Faculty.class),
        
// })

@Entity
@Table(name = facultyTable)
@Data
@NoArgsConstructor
@Getter
@Setter
@ToString
public class Faculty {

    public static final String facultyTable = "e_faculty";
    private static final String facultyId = "faculty_id";
    private static final String facultyTitle = "title";

    @Id
    @GeneratedValue
    @Column(name = facultyId)
    private int faculty_id;

    @Column(name = facultyTitle)
    private String title;
}
