-- 1. Процедура для формирования экзаменационной ведомости. Входные параметры –
-- название предмета, дата экзамена и номер группы. Действие процедуры –
-- добавление новых строк в таблице «Успеваемость» и соответствующих значений в
-- промежуточную таблицу. Необходимо учитывать, что к экзамену допускаются
-- студенты, сдавшие все зачёты и имеющие менее 50% пропусков занятий по
-- данному предмету. Если в указанную дату назначено более 2 экзаменов для
-- группы, экзамен переносится на следующий день. Выходной параметр –
-- количество студентов, допущенных к экзамену.

-- Создаем дополнительную процедуру
create or replace procedure get_discipline_id_by_title(
	out id_discipline_p int,
	title_discipline_p varchar(50)
)
language plpgsql    
as $$
begin
	select id_discipline
	from a_discipline
	where title = title_discipline_p
	into id_discipline_p;
end;$$

-- Основная функция
create or replace procedure get_students_passed_certification(
	out number_of_students int,
	id_group_p int,
	title_disciplin_p varchar(50),
	exam_date_p date
)
language plpgsql    
as $$
declare
	id_discipline_p int;
	total_number_of_credits int;
	total_number_of_lessons int;
	total_number_of_exams_in_date int;
begin
	
	call get_discipline_id_by_title(id_discipline_p, title_disciplin_p);
	
	select count(id_lesson)
	from a_lesson
	where a_lesson.id_control_type = 2
	into total_number_of_credits;
	
	select count(id_lesson)
	from a_lesson
	where a_lesson.id_discipline = id_discipline_p
	into total_number_of_lessons;
	
	select count(*)
	from (
		select id_student, count(id_student)
		from a_list
		left join a_lesson
		on a_lesson.id_lesson = a_list.id_lesson
		where a_lesson.id_discipline = id_discipline_p and
			  a_lesson.id_control_type = 1 and
			  a_list.id_student in (
				  select id_student
				  from a_list
				  left join a_lesson
				  on a_lesson.id_lesson = a_list.id_lesson
				  where a_lesson.id_control_type = 3
				  group by id_student
				  having count(id_student) = total_number_of_credits
			  )
		group by id_student
		having count(id_student) > total_number_of_lessons * 0.5 ) result_table
	into number_of_students;

	select count(*)
	from a_lesson
	where id_group = id_group_p and
		id_control_type = 3 and
		lesson_date = exam_date_p
	into total_number_of_exams_in_date;

	if (total_number_of_exams_in_date > 2) then
		insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), id_discipline_p, 3, id_group_p, exam_date_p + interval'1 day');
	else 
		insert into a_lesson (id_lesson, id_discipline, id_control_type, id_group, lesson_date) values (nextval('seq_lesson'), id_discipline_p, 3, id_group_p, exam_date_p);
	end if;

end;$$

-- Тестирование процедуры

call get_students_passed_certification(0, 1, 'Русский язык', TO_DATE('27.02.23','DD.MM.RR'));

select *
from a_lesson

-- 2. Процедура для формирования ведомости на пересдачу. Входные параметры –
-- название предмета и фамилия преподавателя. Действие процедуры – добавление
-- записей в соответствующие таблицы. Дату аттестации определить следующим
-- образом – пересдача экзамена возможна через 3 дня после даты последнего
-- экзамена, пересдача зачёта допускается на следующий день. Выходные параметры
-- – номер ведомости и список студентов допущенных к пересдаче.

-- Основная функция
create or replace procedure create_list_of_retakes(
	out id_of_list int,
	out list_id_p int[],
	title_disciplin_p varchar(50),
	teacher_surname_p varchar(50)
)
language plpgsql    
as $$
declare
	f record;
	id_discipline_v int;
	credit_date date;
	exam_date date;
begin

	call get_discipline_id_by_title(id_discipline_v, title_disciplin_p);
	
	select max(lesson_date)
	from a_lesson
	where id_discipline = id_discipline_v and
		  id_control_type = 2
	into credit_date;
	
	select max(lesson_date)
	from a_lesson
	where id_discipline = id_discipline_v and
		  id_control_type = 3
	into exam_date;
	
	insert into a_lesson(id_lesson, id_discipline, id_control_type, id_group, lesson_date)
	values (nextval('seq_lesson'), id_discipline_v, 2, null, credit_date);
	
	insert into a_lesson(id_lesson, id_discipline, id_control_type, id_group, lesson_date)
	values (nextval('seq_lesson'), id_discipline_v, 3, null, exam_date);

	RAISE NOTICE '--- exams ---';
	for f in 
		select id_student, avg(mark)
		from a_list
		left join a_lesson
		on a_lesson.id_lesson = a_list.id_lesson
		where a_lesson.id_control_type = 3 and
			  a_lesson.id_discipline = id_discipline_v
		group by id_student
		having avg(mark) < 4
	loop
		RAISE NOTICE 'id: % , mark: %', f.id_student, f.avg;
	end loop;
	
	RAISE NOTICE '--- credits ---';
	for f in 
		select id_student, avg(mark)
		from a_list
		left join a_lesson
		on a_lesson.id_lesson = a_list.id_lesson
		where a_lesson.id_control_type = 2 and
			  a_lesson.id_discipline = id_discipline_v
		group by id_student
		having avg(mark) = 0
	loop
		RAISE NOTICE 'id: % , mark: %', f.id_student, f.avg;
	end loop;
	
end;$$

-- Тестирование процедуры
call create_list_of_retakes(0, '{1}'::int[], 'Русский язык', 'Казарцева');


-- 3. Процедура формирования архива сведений об успеваемости студентов. Входных
-- параметров нет. Действие процедуры – из исходных таблиц удаляются сведения о
-- студентах, завершивших обучение более года назад. В архиве сохранить
-- информацию: фамилия, имя, отчество студента, дата рождения, дата поступления,
-- дата окончания, специальность, средний балл за все время обучения. Выходной
-- параметр – количество архивных записей.

-- Добавим необходимые столбцы в существующую таблицу Студент

alter table a_student
add date_of_birth date;

alter table a_student
add date_of_entrance date;

alter table a_student
add date_of_graduation date;

-- И заполним образовавшиеся ячейки

update a_student
set date_of_entrance = TO_DATE('01.09.20','DD.MM.RR');

update a_student
set date_of_graduation = TO_DATE('01.09.24','DD.MM.RR');

update a_student
set date_of_birth = TO_DATE('01.10.02','DD.MM.RR')
where id_student = 1;

update a_student
set date_of_birth = TO_DATE('02.10.02','DD.MM.RR')
where id_student = 2;

update a_student
set date_of_birth = TO_DATE('03.10.02','DD.MM.RR')
where id_student = 3;

update a_student
set date_of_birth = TO_DATE('04.10.02','DD.MM.RR')
where id_student = 4;

update a_student
set date_of_birth = TO_DATE('05.10.02','DD.MM.RR')
where id_student = 5;

update a_student
set date_of_birth = TO_DATE('06.10.02','DD.MM.RR')
where id_student = 6;

-- Создадим архивную таблицу выпускников

create table a_graduates_archive (
	id_graduate int,
	surname varchar(50),
	first_name varchar(50),
	middle_name varchar(50),
	date_of_birth date,
	date_of_entrance date,
	date_of_graduation date,
	avg_mark int
);

alter table a_graduates_archive
add constraint "graduates_archive PK" PRIMARY KEY (id_graduate);

CREATE SEQUENCE seq_graduates_archive
START WITH 1
MAXVALUE 1000
increment by 1;

-- Основная процедура

create or replace procedure create_graduates_archive(
	out number_of_archive_rows int
)
language plpgsql    
as $$
declare
	f record;
begin
	for f in
		select a_student.id_student, a_student.surname, a_student.first_name,
			   a_student.middle_name, a_student.date_of_birth, a_student.date_of_entrance, 
			   a_student.date_of_graduation, marks.avg as mark
		from a_student
		left join (select id_student, avg(mark)
				   from a_list
				   left join a_lesson
				   on a_lesson.id_lesson = a_list.id_lesson
				   where a_lesson.id_control_type = 3
				   group by id_student) marks
		on a_student.id_student = marks.id_student
		where date_of_graduation > current_date - 2 * interval'1 year'
	loop 
		insert into a_graduates_archive(id_graduate, surname, first_name, middle_name, date_of_birth,
										date_of_entrance, date_of_graduation, avg_mark) 
		values (nextval('seq_graduates_archive'), f.surname, f.first_name, f.middle_name, f.date_of_birth,
				f.date_of_entrance, f.date_of_graduation, f.mark);
				
		delete from a_list
		where id_student = f.id_student;
		
		delete from a_student
		where id_student = f.id_student;
		
	end loop;
	
	select count(*)
	from a_graduates_archive
	into number_of_archive_rows;

end;$$

-- Тестирование процедуры

call create_graduates_archive(0);
