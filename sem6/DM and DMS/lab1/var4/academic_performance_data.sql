insert into a_teacher (id_teacher, surname, first_name, middle_name) values (nextval('seq_teacher'), 'Казарцева', 'Ольга', 'Игоревна');
insert into a_teacher (id_teacher, surname, first_name, middle_name) values (nextval('seq_teacher'), 'Вельб', 'Мария', 'Ивановна');

insert into a_discipline (id_discipline, title) values (nextval('seq_discipline'), 'Русский язык');
insert into a_discipline (id_discipline, title) values (nextval('seq_discipline'), 'Английский язык');

insert into a_group (id_group, title) values (nextval('seq_group'), 'группа 1');
insert into a_group (id_group, title) values (nextval('seq_group'), 'группа 2');

insert into a_control_type (id_control_type, title) values (nextval('seq_control_type'), 'лекция', );
insert into a_control_type (id_control_type, title) values (nextval('seq_control_type'), 'зачет');
insert into a_control_type (id_control_type, title) values (nextval('seq_control_type'), 'экзамен');

insert into a_student (id_student, id_group, surname, first_name, middle_name) values (nextval('seq_student'), 1, 'Веренич', 'Владислав', 'Николаевич');
insert into a_student (id_student, id_group, surname, first_name, middle_name) values (nextval('seq_student'), 1, 'Зарембовский', 'Никита', 'Алексеевич');
insert into a_student (id_student, id_group, surname, first_name, middle_name) values (nextval('seq_student'), 1, 'Бельская', 'Василина', 'Дмитриевна');
insert into a_student (id_student, id_group, surname, first_name, middle_name) values (nextval('seq_student'), 1, 'Кощеева', 'Марина', 'Михайловна');
insert into a_student (id_student, id_group, surname, first_name, middle_name) values (nextval('seq_student'), 1, 'Вишенько', 'Александр', 'Николаевич');
insert into a_student (id_student, id_group, surname, first_name, middle_name) values (nextval('seq_student'), 1, 'Селивонец', 'Валерия', 'Дмитриевна');

insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), 1, 1, 1, TO_DATE('01.02.23','DD.MM.RR'));
insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), 1, 1, 1, TO_DATE('02.02.23','DD.MM.RR'));
insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), 1, 1, 1, TO_DATE('03.02.23','DD.MM.RR'));
insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), 1, 1, 1, TO_DATE('04.02.23','DD.MM.RR'));
insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), 1, 1, 1, TO_DATE('05.02.23','DD.MM.RR'));
insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), 1, 1, 1, TO_DATE('06.02.23','DD.MM.RR'));
insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), 2, 1, 1, TO_DATE('01.02.23','DD.MM.RR'));
insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), 2, 1, 1, TO_DATE('02.02.23','DD.MM.RR'));
insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), 2, 1, 1, TO_DATE('03.02.23','DD.MM.RR'));
insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), 2, 1, 1, TO_DATE('04.02.23','DD.MM.RR'));
insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), 2, 1, 1, TO_DATE('05.02.23','DD.MM.RR'));
insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), 2, 1, 1, TO_DATE('06.02.23','DD.MM.RR'));
insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), 1, 2, 1, TO_DATE('06.02.23','DD.MM.RR'));
insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), 2, 2, 1, TO_DATE('06.02.23','DD.MM.RR'));
insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), 1, 3, 1, TO_DATE('07.02.23','DD.MM.RR'));
insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), 2, 3, 1, TO_DATE('07.02.23','DD.MM.RR'));

insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 1, 1, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 1, 2, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 1, 3, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 1, 4, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 1, 5, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 1, 6, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 2, 1, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 2, 2, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 2, 3, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 2, 4, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 2, 5, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 3, 1, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 3, 2, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 3, 3, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 3, 4, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 4, 1, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 4, 2, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 4, 3, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 5, 1, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 5, 2, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 6, 1, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 7, 1, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 7, 2, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 7, 3, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 7, 4, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 7, 5, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 7, 6, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 8, 1, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 8, 2, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 8, 3, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 8, 4, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 8, 5, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 9, 1, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 9, 2, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 9, 3, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 9, 4, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 4, 1, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 10, 2, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 10, 3, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 11, 1, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 11, 2, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 12, 1, null);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 13, 1, 1);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 13, 2, 1);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 13, 3, 1);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 13, 4, 1);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 13, 5, 0);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 13, 6, 0);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 14, 1, 1);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 14, 2, 1);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 14, 3, 1);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 14, 4, 0);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 14, 5, 0);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 14, 6, 0);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 16, 1, 10);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 16, 2, 9);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 16, 3, 8);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 16, 4, 4);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 16, 5, 3);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 16, 6, 3);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 17, 1, 8);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 17, 2, 8);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 17, 3, 8);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 17, 4, 8);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 17, 5, 3);
insert into a_list (id_list, id_lesson, id_student, mark) values (nextval('seq_list'), 17, 6, 3);