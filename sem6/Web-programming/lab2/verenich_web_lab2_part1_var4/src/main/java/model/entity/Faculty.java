package model.entity;

import javax.persistence.*;
import lombok.Data;
import lombok.NoArgsConstructor;
import static model.entity.Faculty.facultyTable;

@Entity
@Table(name = facultyTable)
@org.hibernate.annotations.NamedNativeQueries({
        @org.hibernate.annotations.NamedNativeQuery(name = "getAvgOfFaculty",
                query = """
                    select avg(mark)
                    from e_list
                    left join e_abiturient on e_abiturient.abiturient_id = e_list.abiturient_id
                    where e_abiturient.faculty_id = :id""", resultClass = Faculty.class),
        
})

@Data
@NoArgsConstructor
public class Faculty {

    public static final String facultyTable = "faculties";
    private static final String facultyId = "fID";
    private static final String facultyTitle = "fTitle";

    @Id
    @GeneratedValue
    @Column(name = facultyId)
    private int faculty_id;

    @Column(name = facultyTitle)
    private String title;
}
