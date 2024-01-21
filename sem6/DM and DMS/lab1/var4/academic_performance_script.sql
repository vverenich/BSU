
-- Вариант 4. Учет успеваемости.
-- Описание предметной области. В учебной группе ведется учет успеваемости студентов. 
-- Все студенты обучаются по единому учебному плану – состав учебных дисциплин, количество
-- учебных занятий и вид контроля для всех студентов одинаков. Все занятия по каждой из 
-- учебных дисциплин проводит один преподаватель. Преподаватель может проводить занятия 
-- по нескольким учебным дисциплинам. По различным дисциплинам предусматриваются различные 
-- виды контроля – зачет, экзамен, контрольная работа. Для всех учебных дисциплин 
-- устанавливаются сроки сдачи по каждому виды контроля.

-- Задачи. Обеспечить учет успеваемости каждого студента по различным учебным дисциплинам и
--  по каждому виду контроля. Вести учет пропусков учебных занятий  каждого из студентов. 
-- Также необходимо подводить итоги успеваемости за  определенный период по всей группе,
--  по отдельным дисциплинам и по каждому виду контроля. Выявлять задолженности по любому 
-- из видов контроля каждого из студентов.

-- Вариант 4. Учет успеваемости.
-- Дополнительные ограничения:
-- Успеваемость студентов оценивается по 10-балльной системе.
-- Номера учебных групп состоят из 6 символов (две последние цифры года поступления,
--  код специальности и номер группы).
-- Дата аттестации – в пределах учебного года.
-- Оценка на зачете может иметь значения: «Зачтено», «Не зачтено», «Не явился».
-- 

create table a_teacher (
	id_teacher int,
	surname varchar(50),
	first_name varchar(50),
	middle_name varchar(50)
);

alter table a_teacher
add constraint "teacher PK" PRIMARY KEY (id_teacher);

create table a_discipline (
	id_discipline int,
	title varchar(50)
);

alter table a_discipline
add constraint "discipline PK" PRIMARY KEY (id_discipline);

create table a_control_type (
	id_control_type int,
	title varchar(50)
);

alter table a_control_type
add constraint "control_type PK" PRIMARY KEY (id_control_type);

create table a_group (
	id_group int,
	title varchar(50)
);

alter table a_group
add constraint "group PK" PRIMARY KEY (id_group);

create table a_student (
	id_student int,
	id_group int,
	surname varchar(50),
	first_name varchar(50),
	middle_name varchar(50)
);

alter table a_student
add constraint "student PK" PRIMARY KEY (id_student);

alter table a_student
add constraint student_group foreign key
(
	id_group
)
references a_group
(
	id_group
);

create table a_lesson (
	id_lesson int,
	id_discipline int,
	id_control_type int,
	id_group int,
	lesson_date date
);

alter table a_lesson
add constraint "lesson PK" PRIMARY KEY (id_lesson);

alter table a_lesson
add constraint lesson_discipline foreign key
(
	id_discipline
)
references a_discipline
(
	id_discipline
);

alter table a_lesson
add constraint lesson_control_type foreign key
(
	id_control_type
)
references a_control_type
(
	id_control_type
);

alter table a_lesson
add constraint lesson_group foreign key
(
	id_group
)
references a_group
(
	id_group
);

create table a_list(
	id_list int,
	id_lesson int,
	id_student int,
	mark int
);

alter table a_list
add constraint "list PK" PRIMARY KEY (id_list);

alter table a_list
add constraint list_lesson foreign key
(
	id_lesson
)
references a_lesson
(
	id_lesson
);

alter table a_list
add constraint list_student foreign key
(
	id_student
)
references a_student
(
	id_student
);