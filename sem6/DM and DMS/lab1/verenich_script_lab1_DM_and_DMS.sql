
-- 1. Создайте функцию, вычисляющую премию за всё время начислений для
-- конкретного сотрудника. Входной параметр – фамилия или идентификатор
-- сотрудника. Выходной параметр – значение суммы премии.

-- Создаем вспомогательные процедуру для определения id по фамилии
create or replace procedure get_id_of_doctor_by_surname(
	out id_doctor_p int,
	surname_p varchar(50)
)
language plpgsql    
as $$
begin
	select id_doctor
	from h_doctor
	where surname = surname_p
	into id_doctor_p;
end;$$

create or replace procedure get_id_of_patient_by_surname(
	out id_patient_p int,
	surname_p varchar(50)
)
language plpgsql    
as $$
begin
	select n_card
	from h_patient
	where surname = surname_p
	into id_patient_p;
end;$$

call get_id_of_doctor_by_surname(0, 'Скрябина');
call get_id_of_patient_by_surname(0, 'Безенчук');

-- Создаем дополнительную процедуру(также понадобится в пункте 6)
create or replace procedure get_total_cost_of_services_by_doctor_id(
	out total_cost_p double precision,
	id_doctor_p int
)
language plpgsql    
as $$
begin
	select sum(h_services.price)
	from h_visit
	left join h_services on h_visit.code_srv = h_services.code_srv
	left join h_doctor on h_visit.id_doctor = h_doctor.id_doctor
	where h_doctor.id_doctor = id_doctor_p
	group by h_doctor.id_doctor
	into total_cost_p;
end;$$

create or replace function calculate_bonus(
	id_doctor_p int default null,
	surname_p varchar(50) default null
)
returns double precision
language plpgsql    
as $$
declare
	total_cost_of_services_v double precision;
	bonus_p double precision;
begin
	
	if (id_doctor_p is null and surname_p is not null) then 
		call get_id_of_doctor_by_surname(id_doctor_p, surname_p);
	end if;
	
	call get_total_cost_of_services_by_doctor_id(total_cost_of_services_v, id_doctor_p);
	bonus_p := total_cost_of_services_v * 0.20;
	
	return bonus_p;
end;$$

-- Протестировать функцию с различными вариантами входных параметров.

-- Таблица всех визитов, соответсвующего врача и цены услуги
select  h_visit.n_visit, h_doctor.id_doctor, h_services.price
from h_visit
left join h_services on h_visit.code_srv = h_services.code_srv
left join h_doctor on h_visit.id_doctor = h_doctor.id_doctor

select calculate_bonus(id_doctor_p => 22);
select calculate_bonus(surname_p => 'Корнеев');

-- 2. Создайте функцию, вычисляющую сумму оплаты за услуги для конкретного
-- пациента за указанный период. Входные параметры – фамилия или номер
-- карты пациента, начало и конец периода (необязательный). Выходной
-- параметр – значение суммы.

create or replace function get_payment_for_services(
   start_date_p date,
   end_date_p date default CURRENT_DATE,
   id_patient_p int default null,
   surname_p varchar(50) default null
)
returns double precision
language plpgsql    
as $$
declare
	payment_p double precision;
begin

	if (id_patient_p is null and surname_p is not null) then 
		call get_id_of_patient_by_surname(id_patient_p, surname_p);
	end if;

	select sum(h_services.price)
	from h_visit
	left join h_services on h_services.code_srv = h_visit.code_srv
	where id_patient = id_patient_p 
	AND date_visit >= start_date_p
	AND date_visit <= end_date_p
	group by id_patient
	into payment_p;
	
	return payment_p;
end;$$

-- Протестировать функцию с различными вариантами входных параметров.

select id_patient, date_visit, h_services.price
from h_visit
left join h_services on h_services.code_srv = h_visit.code_srv
order by id_patient;

select get_payment_for_services('0001-09-23 BC', id_patient_p => 216001);
select get_payment_for_services('0001-09-23 BC', surname_p => 'Корейко');

-- 3. Создайте функцию для вычисления размера скидки при оплате услуг для
-- указанного пациента. Входные параметры – фамилия или номер карты
-- пациента. Выходной параметр – размер скидки в процентах. Размер скидки
-- определяется следующим образом: если общая сумма оплаты за услуги
-- составляет менее 50 руб. – размер скидки 3%; от 50 до 100 руб. – 10%; от 100
-- до 200 руб. – 20%; от 200 до 400 руб. – 30%; свыше 400 руб. – 40%.

create or replace function get_discount_in_percent(
   id_patient_p int default null,
   surname_p varchar(50) default null
)
returns double precision
language plpgsql    
as $$
declare 
	min_date_visit_v date;
	payment_v int;
	discount_p double precision;
begin

	if (id_patient_p is null and surname_p is not null) then 
		call get_id_of_patient_by_surname(id_patient_p, surname_p);
	end if;

	-- Получаем дату первого визита
	select min(date_visit)
	from h_visit
	into min_date_visit_v;
	
	-- Получаем плату за услуги для определенного пациента
	select get_payment_for_services(min_date_visit_v, id_patient_p => id_patient_p)
	into payment_v;

	-- Вычисляем размер скидки
	if (payment_v < 50) then 
		discount_p := 3;
	elsif (payment_v < 100) then 
		discount_p := 10;
	elsif (payment_v < 200) then 
		discount_p := 20;
	elsif (payment_v < 400) then 
		discount_p := 30;
	else
		discount_p := 20;
	end if;
	
	return discount_p;
end;$$

-- Тестирование процедуры

select id_patient, date_visit, h_services.price
from h_visit
left join h_services on h_services.code_srv = h_visit.code_srv
order by id_patient;

select get_discount_in_percent(id_patient_p => 216001);
select get_discount_in_percent(surname_p => 'Корейко');

-- 4. Создайте функцию определения количества принятых специалистом
-- пациентов. Входные параметры – фамилия или идентификатор сотрудника.
-- Выходной параметр – количество пациентов.

create or replace function get_patient_number_by_id_doctor(
    id_doctor_p int default null,
	surname_p varchar(50) default null
)
returns int
language plpgsql    
as $$
declare
	patient_number_p int;
begin

	if (id_doctor_p is null and surname_p is not null) then 
		call get_id_of_doctor_by_surname(id_doctor_p, surname_p);
	end if;

	select count(n_visit)
	from h_visit
	left join h_doctor on h_doctor.id_doctor = h_visit.id_doctor
	where h_doctor.id_doctor = id_doctor_p
	group by h_doctor.id_doctor
	into patient_number_p;
	
	return patient_number_p;
end;$$

-- Тестирование процедуры
select n_visit, id_doctor
from h_visit;

select get_patient_number_by_id_doctor(18);
select get_patient_number_by_id_doctor(22);
select get_patient_number_by_id_doctor(surname_p => 'Быков');

-- 5. Создайте функцию, вычисляющую максимальную разность количества
-- принятых специалистом пациентов за определенный период. Входные
-- параметры – начальная дата, конечная дата (необязательный параметр).
-- Выходной параметр – максимальная разность количества пациентов и
-- фамилии специалистов.
------------------------------------------
-- 6. Составьте процедуру начисления премии специалистам. Премия начисляется
-- из суммарной стоимости услуг, оказанных этим специалистом пациентам.
-- Правила начисления: если суммарная стоимость до 50 руб. – премия в
-- размере 10% от суммы;
-- от 50 до 100 руб. – 15%;
-- от 100 до 400 руб. – 30%;
-- более 400 руб. – 50%.
-- Входные параметры: фамилия специалиста, идентификатор, специальность,
-- период начисления, без параметров.
-- Выходные параметры – нет.
-- Действие процедуры:
-- если указана фамилия или идентификатор – начисление премии указанному
-- сотруднику за весь период и запись значения в соответствующей строке;
-- если указана специальность – начисление всем сотрудникам указанной
-- специальности за весь период и запись значений в соответствующих
-- строках;
-- если входной параметр не указан – начисление всем сотрудникам за весь
-- период и запись значений в соответствующих строках.
-- Необходимые предварительные действия: с помощью команды ALTER

-- TABLE H_Doctor добавьте в структуру таблицы столбец bonus, тип
-- NUMBER(9,2).

alter table h_doctor
add bonus double precision;

select *
from h_doctor

-- Создаем вспомогательную процедуру
create or replace procedure get_bonus_by_total_cost_of_services(
	out bonus_p double precision,
	total_cost_p double precision
)
language plpgsql    
as $$
begin
	if (total_cost_p < 50) then 
		bonus_p := total_cost_p * 0.1;
	elsif (total_cost_p < 100) then 
		bonus_p := total_cost_p * 0.15;
	elsif (total_cost_p < 400) then 
		bonus_p := total_cost_p * 0.30;
	else
		bonus_p := total_cost_p * 0.50;
	end if;
end;$$

create or replace procedure give_bonus(
   start_period_p date,
   end_period_p date,
   id_doctor_p int default null,
   code_spec_p int default null
)
language plpgsql    
as $$
declare 
	bonus_v double precision;
	f record;
begin
	if (id_doctor_p is not null and code_spec_p is null) then 
		
		call get_total_cost_of_services_by_doctor_id(bonus_v, id_doctor_p);
		call get_bonus_by_total_cost_of_services(bonus_v, bonus_v);
		
		update h_doctor
		set bonus = bonus_v
		where id_doctor = id_doctor_p;
		
	elsif (id_doctor_p is null and code_spec_p is not null) then 
		
		for f in 
		   select id_doctor, h_speciality.code_spec
		   from h_doctor
		   left join h_speciality on h_speciality.code_spec = h_doctor.code_spec
		   where h_speciality.code_spec = code_spec_p 
    	loop 
    		call get_total_cost_of_services_by_doctor_id(bonus_v, f.id_doctor);
			call get_bonus_by_total_cost_of_services(bonus_v, bonus_v);
		
			update h_doctor
			set bonus = bonus_v
			where id_doctor = f.id_doctor;
    	end loop;
		
	elsif (id_doctor_p is null and code_spec_p is null) then 
		for f in 
		   select id_doctor
		   from h_doctor
    	loop 
    		call get_total_cost_of_services_by_doctor_id(bonus_v, f.id_doctor);
			call get_bonus_by_total_cost_of_services(bonus_v, bonus_v);
		
			update h_doctor
			set bonus = bonus_v
			where id_doctor = f.id_doctor;
    	end loop;
	end if;
end;$$

-- Протестируйте процедуру с различными вариантами входных параметров.
-- Сравните результат.

-- Таблица всех визитов, соответсвующего врача и цены услуги
select  h_visit.n_visit, h_doctor.id_doctor, h_services.price
from h_visit
left join h_services on h_visit.code_srv = h_services.code_srv
left join h_doctor on h_visit.id_doctor = h_doctor.id_doctor

select *
from h_doctor;

select *
from h_speciality;

call give_bonus('0001-09-23 BC', '0001-09-25 BC');

update h_doctor
set bonus = 0
where id_doctor = 12;

call give_bonus('0001-09-23 BC', '0001-09-25 BC', 12);
call give_bonus('0001-09-23 BC', '0001-09-25 BC', code_spec_p => 1401);

-- 7. Создайте процедуру зачисления нового сотрудника.
-- Входные параметры: фамилия, имя, отчество сотрудника, специальность
-- (необязательный параметр).
-- Выходные параметры – нет.
-- Действие процедуры: формирование новой строки и вставка
-- соответствующих значений в таблицу H_Doctor, если указанная
-- специальность отсутствует в справочнике, добавить сведения об этой
-- специальности в таблице H_Specialty. Если специальность не указана, нового
-- сотрудника зачислить в качестве интерна. Одного из интернов при этом
-- перевести на вакантную специальность или специальность с наименьшим
-- количеством специалистов.

create or replace procedure add_doctor(
   surname_p varchar(50),
   firstname_p varchar(50),
   middle_name_p varchar(50),
   speciality_title varchar(50) default null
)
language plpgsql    
as $$
declare 
	number_of_rows_v bigint;
	code_spec_v int;
begin
	if (speciality_title is not null) then 
		
		select count(1)
		from h_speciality
		where title = speciality_title
		into number_of_rows_v;
		
		if (number_of_rows_v = 0) then
			insert into h_speciality (code_spec, title) values(nextval('seq_spec'), speciality_title);
		end if;
		
		select code_spec
		from h_speciality
		where title = speciality_title
		into code_spec_v;
			
		insert into h_doctor (id_doctor, surname, firstname, middle_name, code_spec) VALUES(nextval('seq_doc'), surname_p, firstname_p, middle_name_p, code_spec_v);
			
	elsif (speciality_title is null) then 
		
		select code_spec
		from h_speciality
		where title = 'Интерн'
		into code_spec_v;
			
		insert into h_doctor (id_doctor, surname, firstname, middle_name, code_spec) VALUES(nextval('seq_doc'), surname_p, firstname_p, middle_name_p, code_spec_v);
		
	end if;
end;$$

-- Тестировнаие процедуры
select * from h_doctor;
select * from h_speciality;

call add_doctor('Быков1', 'Андрей1', 'Евгеньевич1');
call add_doctor('Быков2', 'Андрей2', 'Евгеньевич2', 'Терапевт');
call add_doctor('Быков3', 'Андрей3', 'Евгеньевич3', 'Терапевт1');

delete from h_doctor
where surname = 'Быков1' or surname = 'Быков2' or surname = 'Быков3';
	
delete from h_speciality
where title = 'Терапевт1';


-- 8. Создайте процедуру регистрации нового пациента.
-- Входные параметры: фамилия, имя, отчество пациента, адрес
-- (необязательный параметр).
-- Выходные параметры – нет.
-- Действие процедуры: формирование новой строки и вставка
-- соответствующих значений в таблицу H_Patient. При формировании номера
-- карты учитывать адрес пациента. Пациенты из Артемовска, Черноморска,
-- Верхнехолмска и Южногорска относятся к участку №1. Пациенты из
-- Бердянска, Прокопьевска, Криворукова и Урюпинска – к участку №2.
-- Прочие пациенты регистрируются на участке №3.

-- Создаем новую последовательность для участка 3
CREATE SEQUENCE SEQ_Patient_3
START WITH 316001
MAXVALUE 316999
increment by 1;

create or replace procedure add_patient(
   surname_p varchar(50),
   firstname_p varchar(50),
   middle_name_p varchar(50),
   address_p varchar(50) default null
)
language plpgsql    
as $$
declare 
	number_of_rows_v bigint;
	code_spec_v int;
begin
	if (address_p = 'г. Артемовск' or address_p = 'г. Черноморск' or
	    address_p = 'г. Верхнехолмск' or address_p = 'г. Южногорск') then 
		
		insert into h_patient (n_card, surname, firstname, middle_name, address, phone) VALUES(nextval('seq_patient_1'),surname_p, firstname_p, middle_name_p, address_p, null);	
	
	elsif (address_p = 'г. Бердянск' or address_p = 'г. Прокопьевск' or
	    address_p = 'г. Криворуков' or address_p = 'г. Урюпинск') then 
		
		insert into h_patient (n_card, surname, firstname, middle_name, address, phone) VALUES(nextval('seq_patient_2'),surname_p, firstname_p, middle_name_p, address_p, null);
	
	else
	
		insert into h_patient (n_card, surname, firstname, middle_name, address, phone) VALUES(nextval('seq_patient_3'),surname_p, firstname_p, middle_name_p, address_p, null);
	
	end if;
end;$$

-- Протестируйте процедуру с различными вариантами входных параметров.
select * 
from h_patient;

call add_patient('Безенчук1', 'Федор', 'Николаевич', 'г. Артемовск');
call add_patient('Безенчук1', 'Федор', 'Николаевич', 'г. Артемовскdw');
call add_patient('Безенчук1', 'Федор', 'Николаевич', 'г. Урюпинск');

delete from h_patient
where surname = 'Безенчук1';

-- 9. Создайте процедуру для переноса визитов на другую дату.
-- Входные параметры: начальная дата, конечная дата.
-- Выходной параметр – количество перенесенных визитов.
-- Действие процедуры: изменение значения столбца Date_Visit в таблице
-- H_Visit с начальной даты на конечную.

create or replace procedure change_date_visit(
   out number_of_changed_visits_p int,
   start_date_p date,
   new_date_p date
)
language plpgsql    
as $$
begin
	select count(n_visit)
	from h_visit
	where date_visit = start_date_p
	into number_of_changed_visits_p;
	
	update h_visit
	set date_visit = new_date_p
	where date_visit = start_date_p;
end;$$

-- Протестируйте процедуру.

select *
from h_visit;

call change_date_visit(0, '0001-09-20 BC', '0003-09-20 BC');
call change_date_visit(0, '0003-09-20 BC', '0001-09-20 BC');

-- 10.Создайте процедуру для удаления сведений о визитах, состоявшихся в
-- указанный период.
-- Входной параметр: количество дней периода (необязательный).
-- Выходной параметр – количество удаленных строк.
-- Действие процедуры:
-- формирование строк архивной таблицы для сохранения информации о
-- визитах (дата визита, специальность, ФИО специалиста, количество
-- принятых пациентов, суммарная стоимость оказанных услуг);
-- удаление строк в таблице H_Visit, где дата входит в период указанного
-- количества дней, начиная с первой даты визита.

-- Архивная таблица
create table h_archive (
	date_visit date,
	speciality varchar(50),
	surname varchar(50),
	first_name varchar(50),
	middle_name varchar(50),
	number_of_patients int,
	total_cost_of_services double precision
);

-- Вспомогательные процедуры
create or replace procedure get_number_of_patients_by_id_in_period(
	out number_of_patients_p int,
	id_doctor_p int,
	number_of_days_p int,
	start_date_p date
)
language plpgsql    
as $$
begin
	select count(n_visit)
	from h_visit
	where h_visit.id_doctor = id_doctor_p and
		  date_visit >= start_date_p and
	      date_visit < (start_date_p + number_of_days_p * interval'1 day')
	into number_of_patients_p;
end;$$

create or replace procedure get_total_cost_of_services_by_id_doctor_in_period(
	out total_cost_of_services double precision,
	id_doctor_p int,
	number_of_days_p int,
	start_date_p date
)
language plpgsql    
as $$
begin
	select sum(h_services.price)
	from h_visit
	left join h_services on h_visit.code_srv = h_services.code_srv
	where h_visit.id_doctor = id_doctor_p and
		  date_visit >= start_date_p and
	      date_visit < (start_date_p + number_of_days_p * interval'1 day')
	into total_cost_of_services;
end;$$

-- Основная процедура
create or replace procedure delete_visit(
   out number_of_deleted_visits_p int,
   number_of_days_p int default null
)
language plpgsql    
as $$
declare 
	f record;
	min_date_visit_v date;
	number_of_patients_v int;
	total_cost_of_services_v double precision;
begin

	-- Получаем дату первого визита
	select min(date_visit)
	from h_visit
	into min_date_visit_v;
	
	-- Если период не был задан
	if (number_of_days_p is null) then
		number_of_days_p := -1;
	end if;
	
	-- Подсчитываем кол-во
	select count(n_visit)
	from h_visit
	where date_visit >= min_date_visit_v and
	      date_visit < (min_date_visit_v + number_of_days * interval'1 day')
	into number_of_deleted_visits_p;
	
	-- Формирование строк архивной таблицы
	
	for f in 
		select n_visit, date_visit, h_visit.id_doctor, h_speciality.title, h_doctor.surname, h_doctor.firstname,
	   			h_doctor.middle_name
		from h_visit
		left join h_doctor on h_doctor.id_doctor = h_visit.id_doctor
		left join h_speciality on h_speciality.code_spec = h_doctor.code_spec
		where date_visit >= min_date_visit_v and
	      	date_visit < min_date_visit_v + 5 * interval'1 day'

    loop 
		
		call get_number_of_patients_by_id_in_period(number_of_patients_v, f.id_doctor, number_of_days_p);
		call get_total_cost_of_services_by_id_doctor_in_period(total_cost_of_services_v, f.id_doctor, number_of_days_p);
	
    	insert into h_archive(date_visit, speciality, surname, first_name, middle_name, number_of_patients, total_cost_of_services)
		values (f.date_visit, f.title, f.surname, f.first_name, f.middle_name, number_of_patients_v, total_cost_of_services_v);

    end loop;
	
	-- Удаление строк
	
	delete from h_visit
	where date_visit >= min_date_visit_v and
	      date_visit < (min_date_visit_v + number_of_days_p * interval'1 day');
	
end;$$

-- Протестируйте процедуру.

select *
from h_visit;


select *
from h_visit
where date_visit >= '0001-09-20 BC' and
	  date_visit < (date '0001-09-20 BC' + 2 * interval'1 day');
	
	
insert into h_archive(date_visit, speciality, surname, first_name, middle_name, number_of_patients, total_cost_of_services)
values ('2002-10-05 BC', 'test speciality', 'Verenich', 'Vladislav', 'Nikolaevich', 100, 100);

select *
from h_archive;

delete from h_archive
where date_visit = '2002-10-05 BC';

select * 
from h_doctor;

select n_visit, date_visit,
			   h_doctor.surname as surname, h_doctor.firstname as first_name,
			   h_doctor.middle_name as middle_name, count(id_patient)
		from h_visit
		left join h_doctor on h_doctor.id_doctor = h_visit.id_doctor
		where date_visit >= '0001-09-20 BC' and
	      	date_visit < date '0001-09-20 BC' + 5 * interval'1 day'
		group by n_visit
		
select n_visit, date_visit, h_visit.id_doctor, h_speciality.title, h_doctor.surname, h_doctor.firstname,
	   h_doctor.middle_name
from h_visit
left join h_doctor on h_doctor.id_doctor = h_visit.id_doctor
left join h_speciality on h_speciality.code_spec = h_doctor.code_spec
where date_visit >= '0001-09-20 BC' and
	      	date_visit < date '0001-09-20 BC' + 5 * interval'1 day';
