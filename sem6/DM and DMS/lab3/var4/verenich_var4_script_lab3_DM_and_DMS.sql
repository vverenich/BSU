-- 1. Формирование экзаменационной ведомости. (формирование новой записи,
-- формирование списка студентов, допущенных к экзамену, определение даты
-- проведения экзамена).

-- создаем схему
create schema examination_sheet;

-- ------------------- формирование новой записи 
create or replace procedure examination_sheet.add_new_list_row(
	id_lesson_p int,
	id_student_p int,
	mark_p int
)
language plpgsql    
as $$
begin
	insert into a_list(id_list, id_lesson, id_student, mark) values (nextval('seq_list'), id_lesson_p, id_student_p, mark_p);
end;$$

-- тестирование
call examination_sheet.add_new_list_row(1, 1, 77);

delete from a_list
where mark = 77;

-- ---------- формирование списка студентов, допущенных к экзамену 

-- Необходимо учитывать, что к экзамену допускаются студенты, сдавшие все зачёты
-- и имеющие менее 50% пропусков занятий по данному предмету.

-- Основная функция
create or replace function examination_sheet.get_students_passed_certification(
	id_group_p int,
	id_discipline_p int default null,
	title_disciplin_p varchar(50) default null
)
returns table (
	id_student_c int,
	surname_c varchar(50),
	first_name_c varchar(50),
	middle_name_c varchar(50)
)
language plpgsql    
as $$
declare
	number_of_students int;
	total_number_of_credits int;
	total_number_of_lessons int;
begin
	
	if (id_discipline_p is null and title_disciplin_p is not null) then 
		call get_discipline_id_by_title(id_discipline_p, title_disciplin_p);
	end if;
	
	select count(id_lesson)
	from a_lesson
	where a_lesson.id_control_type = 2
	into total_number_of_credits;
	
	select count(id_lesson)
	from a_lesson
	where a_lesson.id_discipline = id_discipline_p
	into total_number_of_lessons;
	
	return query
		select additional.id_student, surname, first_name, middle_name
		from a_student
		right join(
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
			having count(id_student) > total_number_of_lessons * 0.5 ) additional
		on additional.id_student = a_student.id_student;
	
end;$$

-- тестирование
select examination_sheet.get_students_passed_certification(1, 1);

-- --------------------- определение даты проведения экзамена

-- Действие процедуры – добавление
-- записей в соответствующие таблицы. Дату аттестации определить следующим
-- образом – пересдача экзамена возможна через 3 дня после даты последнего
-- экзамена. 

-- Основная функция
create or replace procedure examination_sheet.create_list_of_retakes(
	title_disciplin_p varchar(50)
)
language plpgsql    
as $$
declare
	id_discipline_v int;
	exam_date date;
begin

	call get_discipline_id_by_title(id_discipline_v, title_disciplin_p);
	
	select max(lesson_date)
	from a_lesson
	where id_discipline = id_discipline_v and
		  id_control_type = 3
	into exam_date;
	
	insert into a_lesson(id_lesson, id_discipline, id_control_type, id_group, lesson_date)
	values (nextval('seq_lesson'), id_discipline_v, 3, null, exam_date);
	
end;$$

-- тестирование 
call examination_sheet.create_list_of_retakes('Русский язык');

select *
from a_lesson

delete from a_lesson
where id_lesson = 23

-- 2. Анализ успеваемости. (определение среднего балла успеваемости
-- в разрезе группы, учебной дисциплины,
-- список неуспевающих студентов, список лучших студентов)

-- создаем схему
create schema academic_performance_analysis;

-- -------- определение среднего балла успеваемости в разрезе группы

-- Основная функция
create or replace function examination_sheet.get_average_mark_group(
	id_group_p int default null,
	group_title_p varchar(50) default null
)
returns int
language plpgsql    
as $$
declare
	avg_mark int;
begin
	
	if (id_group_p is null and group_title_p is not null) then 
		select id_group 
		from a_group
		where title = group_title_p
		into id_group_p;
	end if;
	
	select avg(mark)
	from a_list
	left join a_lesson
	on a_lesson.id_lesson = a_list.id_lesson
	where a_lesson.id_control_type = 3 and
		  a_lesson.id_group = id_group_p
	group by id_student
	into avg_mark;
	
	return avg_mark;
end;$$

-- тестирование

select examination_sheet.get_average_mark_group(1);

-- -------- определение среднего балла успеваемости в разрезе учебной дисциплины

-- Основная функция
create or replace function examination_sheet.get_average_mark_discipline(
	id_discipline_p int default null,
	title_p varchar(50) default null
)
returns int
language plpgsql    
as $$
declare
	avg_mark int;
begin
	
	if (id_discipline_p is null and title_p is not null) then 
		select id_discipline
		from a_discipline
		where title = title_p
		into id_discipline_p;
	end if;
	
	select avg(mark)
	from a_list
	left join a_lesson
	on a_lesson.id_lesson = a_list.id_lesson
	where a_lesson.id_control_type = 3 and
		  a_lesson.id_discipline = id_discipline_p
	group by id_student
	into avg_mark;
	
	return avg_mark;
end;$$

-- тестирование

select examination_sheet.get_average_mark_discipline(title_p => 'Русский язык');

-- ----------------- список лучших студентов
-- Основная функция
create or replace function examination_sheet.get_best_students(
	
)
returns table (
	id_student_c int,
	surname_c varchar(50),
	first_name_c varchar(50),
	middle_name_c varchar(50),
	avg_mark_c numeric
)
language plpgsql    
as $$
declare
	number_of_students int;
	total_number_of_credits int;
	total_number_of_lessons int;
begin
	
	return query
		select a_student.id_student, surname, first_name, middle_name, additional.avg_mark
		from a_student
		right join (
			select id_student, avg(mark) as avg_mark
			from a_list
			left join a_lesson
			on a_lesson.id_lesson = a_list.id_lesson
			where a_lesson.id_control_type = 3
			group by id_student
			having avg(mark) > 7
			) additional
		on additional.id_student = a_student.id_student;
	
end;$$
-- тестирование

select examination_sheet.get_best_students();

-- ----------------- список неуспевающих студентов
-- Основная функция
create or replace function examination_sheet.get_worst_students(
	
)
returns table (
	id_student_c int,
	surname_c varchar(50),
	first_name_c varchar(50),
	middle_name_c varchar(50),
	avg_mark_c numeric
)
language plpgsql    
as $$
declare
	number_of_students int;
	total_number_of_credits int;
	total_number_of_lessons int;
begin
	
	return query
		select a_student.id_student, surname, first_name, middle_name, additional.avg_mark
		from a_student
		right join (
			select id_student, avg(mark) as avg_mark
			from a_list
			left join a_lesson
			on a_lesson.id_lesson = a_list.id_lesson
			where a_lesson.id_control_type = 3
			group by id_student
			having avg(mark) < 4
			) additional
		on additional.id_student = a_student.id_student;
	
end;$$
-- тестирование

select examination_sheet.get_worst_students();






