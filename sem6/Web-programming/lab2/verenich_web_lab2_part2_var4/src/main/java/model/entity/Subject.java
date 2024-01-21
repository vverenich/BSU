package model.entity;

import javax.persistence.*;
import lombok.Data;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.ToString;

import static model.entity.Subject.subjectTable;


@Entity
@Table(name = subjectTable)
@Data
@NoArgsConstructor
@Getter
@Setter
@ToString
public class Subject {

    public static final String subjectTable = "e_subject";
    private static final String subjectId = "subject_id";
    private static final String subjectTitle = "title";

    @Id
    @GeneratedValue
    @Column(name = subjectId)
    private int subject_id;

    @Column(name = subjectTitle)
    private String title;
}
