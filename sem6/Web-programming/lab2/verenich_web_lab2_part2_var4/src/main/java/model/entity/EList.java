package model.entity;

import javax.persistence.*;
import lombok.Data;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.ToString;

import static model.entity.EList.listTable;


@Entity
@Table(name = listTable)
@Data
@NoArgsConstructor
@Getter
@Setter
@ToString
public class EList {

    public static final String listTable = "e_list";
    private static final String listId = "list_id";
    private static final String listAbiturientId = "abiturient_id";
    private static final String listSubjectId = "subject_id";
    private static final String listMark = "mark";

    @Id
    @GeneratedValue
    @Column(name = listId)
    private int list_id;

    @Column(name = listAbiturientId)
    private int abiturient_id;

    @Column(name = listSubjectId)
    private int subject_id;

    @Column(name = listMark)
    private int mark;
}
