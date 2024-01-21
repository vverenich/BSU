create table e_faculty(
	faculty_id int,
	title varchar(50)
);

alter table e_faculty
add constraint "faculty PK" primary key (faculty_id);

create table e_abiturient(
	abiturient_id int,
	surname varchar(50),
	first_name varchar(50),
	middle_name varchar(50),
	faculty_id int
);

CREATE SEQUENCE SEQ_ABITURIENT
  START WITH 100
  MAXVALUE 1000;

alter table e_abiturient
add constraint "abiturient PK" primary key (abiturient_id);

alter table e_abiturient
add constraint abiturient_faculty foreign key
(
	faculty_id
)
references e_faculty
(
	faculty_id
);

create table e_subject(
	subject_id int,
	title varchar(50)
);

alter table e_subject
add constraint "subject PK" primary key (subject_id);

create table e_list(
	list_id int,
	abiturient_id int,
	subject_id int,
	mark int
);

CREATE SEQUENCE SEQ_LIST
  START WITH 100
  MAXVALUE 100000;

alter table e_list
add constraint "list PK" primary key (list_id);

alter table e_list
add constraint list_abiturient foreign key
(
	abiturient_id
)
references e_abiturient
(
	abiturient_id
);

alter table e_list
add constraint list_subject foreign key
(
	subject_id
)
references e_subject
(
	subject_id
);

insert into e_faculty (faculty_id, title) values (0, 'Faculty of Biology');
insert into e_faculty (faculty_id, title) values (1, 'Military Faculty');
insert into e_faculty (faculty_id, title) values (2, 'Faculty of Geography and Geoinformatics');
insert into e_faculty (faculty_id, title) values (3, 'Faculty of Journalism');
insert into e_faculty (faculty_id, title) values (4, 'Faculty of History');
insert into e_faculty (faculty_id, title) values (5, 'Faculty of Mechanics and Mathematics');
insert into e_faculty (faculty_id, title) values (6, 'FAMCS');
insert into e_faculty (faculty_id, title) values (7, 'Faculty of Radiophysics and Computer Technologies');

insert into e_abiturient (abiturient_id, surname, first_name, middle_name, faculty_id) values (0, 'Verenich', 'Vladislav', 'Nikolaevich', 6);
insert into e_abiturient (abiturient_id, surname, first_name, middle_name, faculty_id) values (1, 'Verenich1', 'Vladislav', 'Nikolaevich', 6);
insert into e_abiturient (abiturient_id, surname, first_name, middle_name, faculty_id) values (2, 'Verenich2', 'Vladislav', 'Nikolaevich', 6);
insert into e_abiturient (abiturient_id, surname, first_name, middle_name, faculty_id) values (3, 'Verenich3', 'Vladislav', 'Nikolaevich', 6);
insert into e_abiturient (abiturient_id, surname, first_name, middle_name, faculty_id) values (4, 'Verenich4', 'Vladislav', 'Nikolaevich', 6);
insert into e_abiturient (abiturient_id, surname, first_name, middle_name, faculty_id) values (5, 'Verenich5', 'Vladislav', 'Nikolaevich', 6);
insert into e_abiturient (abiturient_id, surname, first_name, middle_name, faculty_id) values (6, 'Verenich6', 'Vladislav', 'Nikolaevich', 6);
insert into e_abiturient (abiturient_id, surname, first_name, middle_name, faculty_id) values (7, 'Verenich7', 'Vladislav', 'Nikolaevich', 6);
insert into e_abiturient (abiturient_id, surname, first_name, middle_name, faculty_id) values (8, 'Verenich8', 'Vladislav', 'Nikolaevich', 6);
insert into e_abiturient (abiturient_id, surname, first_name, middle_name, faculty_id) values (9, 'Verenich9', 'Vladislav', 'Nikolaevich', 6);
insert into e_abiturient (abiturient_id, surname, first_name, middle_name, faculty_id) values (10, 'Verenich10', 'Vladislav', 'Nikolaevich', 6);
insert into e_abiturient (abiturient_id, surname, first_name, middle_name, faculty_id) values (11, 'Verenich11', 'Vladislav', 'Nikolaevich', 6);
insert into e_abiturient (abiturient_id, surname, first_name, middle_name, faculty_id) values (12, 'Verenich12', 'Vladislav', 'Nikolaevich', 6);

insert into e_subject (subject_id, title) values (0, 'Mathematics');
insert into e_subject (subject_id, title) values (1, 'Physics');
insert into e_subject (subject_id, title) values (2, 'English');

insert into e_list (list_id, abiturient_id, subject_id, mark) values (0, 0, 1, 90);
insert into e_list (list_id, abiturient_id, subject_id, mark) values (1, 1, 1, 90);
insert into e_list (list_id, abiturient_id, subject_id, mark) values (2, 2, 1, 90);
insert into e_list (list_id, abiturient_id, subject_id, mark) values (3, 3, 1, 90);
insert into e_list (list_id, abiturient_id, subject_id, mark) values (4, 4, 1, 90);
insert into e_list (list_id, abiturient_id, subject_id, mark) values (5, 5, 1, 90);
insert into e_list (list_id, abiturient_id, subject_id, mark) values (6, 6, 1, 80);
insert into e_list (list_id, abiturient_id, subject_id, mark) values (7, 7, 1, 80);
insert into e_list (list_id, abiturient_id, subject_id, mark) values (8, 8, 1, 80);
insert into e_list (list_id, abiturient_id, subject_id, mark) values (9, 9, 1, 80);
insert into e_list (list_id, abiturient_id, subject_id, mark) values (10, 10, 1, 80);
insert into e_list (list_id, abiturient_id, subject_id, mark) values (12, 11, 1, 80);


-- Вывести информацию обо всех абитуриентах, зарегистрировавшихся на факультет.
select abiturient_id, surname, first_name, middle_name, e_abiturient.faculty_id
from e_abiturient
left join e_faculty on e_faculty.faculty_id = e_abiturient.faculty_id
where e_abiturient.faculty_id = 6;
-- Вывести информацию об абитуриентах, со средним баллом выше среднего по заданному факультету.

select e_abiturient.abiturient_id, e_abiturient.surname, e_abiturient.first_name, e_abiturient.middle_name, sub_table.avg_mark
from (select e_list.abiturient_id, avg(mark) as avg_mark
		   from e_list
		   group by (e_list.abiturient_id)
		   having avg(mark) > (select avg(mark)
				  			   from e_list
				  			   left join e_abiturient on e_abiturient.abiturient_id = e_list.abiturient_id
				  			   where e_abiturient.faculty_id = 6)) as sub_table
left join e_abiturient on e_abiturient.abiturient_id = sub_table.abiturient_id;
-- Вывести информацию о среднем балле по заданному факультету.
select avg(mark)
from e_list
left join e_abiturient on e_abiturient.abiturient_id = e_list.abiturient_id
where e_abiturient.faculty_id = 6;
-- Зарегистрировать нового абитуриента
insert into e_abiturient (abiturient_id, surname, first_name, middle_name, faculty_id) values (nextval('SEQ_ABITURIENT'),'Verenich50', 'Vladislav', 'Nikolaevich', cast ('1' as int));
-- Зафиксировать результаты сдачи экзамена по предмету
insert into e_list (list_id, abiturient_id, subject_id, mark) values(nextval('SEQ_LIST'), 1, 2, 20);
