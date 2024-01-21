-- Вариант 4. Учет успеваемости.
-- 1. Функция для определения количества студентов, прошедших аттестацию.
-- Необходимо учитывать, что к экзамену допускаются студенты, сдавшие все зачёты
-- и имеющие менее 50% пропусков занятий по данному предмету. Входной
-- параметры – название или код предмета, номер группы, дата. Выходной параметр –
-- количество студентов, допущенных к экзамену и успешно прошедших аттестацию.

-- Создаем дополнительную процедуру
create or replace procedure get_discipline_id_by_title(
	out id_discupline_p int,
	title_discipline_p varchar(50)
)
language plpgsql    
as $$
begin
	select id_discipline
	from a_discipline
	where title = title_discipline_p
	into id_discupline_p;
end;$$

-- Основная функция
create or replace function get_students_passed_certification(
	id_group_p int,
	id_discipline_p int default null,
	title_disciplin_p varchar(50) default null
)
returns int
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
	
	return number_of_students;
end;$$

-- Тестирование функции

select get_students_passed_certification(1, 1);

-- 2. Функция для определения среднего балла успеваемости в текущей
-- экзаменационной сессии. Входной параметр – фамилия и инициалы студента или
-- номер зачётной книжки. Выходной параметр – средний балл успеваемости
-- студента.

-- Вспомогательная процедура
create or replace procedure get_id_by_surname(
	out id_student_p int,
	surname_p varchar(50)
)
language plpgsql    
as $$
begin
	select id_student
	from a_student
	where surname = surname_p
	into id_student_p;
end;$$

-- Основная функция
create or replace function get_average_mark(
	surname_p varchar(50) default null,
	id_student_p int default null
)
returns int
language plpgsql    
as $$
declare
	avg_mark int;
begin
	
	if (id_student_p is null and surname_p is not null) then 
		call get_id_by_surname(id_student_p, surname_p);
	end if;
	
	select avg(mark)
	from a_list
	left join a_lesson
	on a_lesson.id_lesson = a_list.id_lesson
	where a_lesson.id_control_type = 3 and
		  id_student = id_student_p
	group by id_student
	into avg_mark;
	
	return avg_mark;
end;$$

-- Тестирование функции

select get_average_mark(surname_p => 'Веренич');

-- 3. Функция для определения возможной даты пересдачи. Входной параметр –
-- название или код предмета. Выходной параметр – дата пересдачи. Дата пересдачи
-- определяется следующим образом: если количество студентов, получивших
-- неудовлетворительные оценки, составляет менее 50% от численности студентов –
-- дата пересдачи назначается через 3 дня после проведения экзамена (учитывать
-- выходные и праздничные дни); в противном случае дата пересдачи назначается
-- через неделю после последнего экзамена.

select lesson_date
from a_lesson
where a_lesson.id_control_type = 3 and
	  a_lesson.id_discipline = 1
into transfer_date;

create or replace function get_transfer_exam_date(
	discipline_title_p varchar(50) default null,
	id_discipline_p int default null
)
returns date
language plpgsql    
as $$
declare
	transfer_date date;
	super_guys int;
	all_guys int;
begin
	
	if (id_discipline_p is null and discipline_title_p is not null) then 
		call get_dsicipline_id_by_title(id_discipline_p, discipline_title_p);
	end if;
	
	select count(id_list)
	from a_list
	left join a_lesson
	on a_lesson.id_lesson = a_list.id_lesson
	where id_control_type = 3 and
		  a_list.mark >= 4 and
		  a_lesson.id_discipline = id_discipline_p
	group by a_list.id_lesson
	into super_guys;
	
	select count(id_student)
	from a_student
	into all_guys;
	
	if (super_guys > 0.5 * all_guys) then 
		select lesson_date
		from a_lesson
		where a_lesson.id_control_type = 3 and
			  a_lesson.id_discipline = id_discipline_p
		into transfer_date;
		
		transfer_date := transfer_date + 3 * interval'1 day';
	else
		select max(lesson_date)
		from a_lesson
		where a_lesson.id_control_type = 3
		into transfer_date;
		
		transfer_date := transfer_date + 7 * interval'1 day';
		
	end if;
	
	return transfer_date;
end;$$

-- Тестирование функции

select get_transfer_exam_date(id_discipline_p => 1);