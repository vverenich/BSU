-- Курсоры. Задания для самостоятельной работы.

-- 1.Составить программу, которая увеличивает оклад в 1.2 раза всем сотрудникам,
-- информация о которых находится в таблице EMP и у которых суммарная заработная плата
-- (сумма оклада и комиссионных) меньше 1200$.

create or replace function multiply_sal_by_1_2()
returns void
language plpgsql
as $$
declare 
	employee_row record;
	employees_cur cursor for
		select *
		from emp
		where (sal + comm) > 1200;
begin
	open employees_cur;
	
	loop
      fetch employees_cur into employee_row;
      exit when not found;
	  
	  update emp 
	  set sal = employee_row.sal * 1.2
	  where emp.empno = employee_row.empno;
	  
	  raise notice 'notice message %', employee_row.sal * 1.2;
   end loop;
	
	close employees_cur;
end;$$

-- Тестирование
select *
from emp;

select multiply_sal_by_1_2();

-- 2.Составить программу, которая начисляет премию сотрудникам компании, информация о
-- которых находится в таблице EMP. Размер премии не должен превышать оклад сотрудника.
-- Сумма оклада и премии не должна превышать 5000. Поместить в таблицу ТЕМР табельный
-- номер, размер премии и фамилию сотрудника.

create table temp_emp (
	temp_emp_id int,
	empno numeric,
	premium numeric,
	ename varchar(10)
);

alter table temp_emp
add constraint "temp_emp PK" PRIMARY KEY (temp_emp_id);

CREATE SEQUENCE seq_temp_emp
START WITH 1
MAXVALUE 1000
increment by 1;

alter table temp_emp
add constraint emp_temp_emp foreign key
(
	empno
)
references emp
(
	empno
);

create or replace function set_premium(premium numeric)
returns void
language plpgsql
as $$
declare 
	employee_row record;
	employees_cur cursor for
		select *
		from emp;
begin
	open employees_cur;
	
	loop
      fetch employees_cur into employee_row;
      exit when not found;
	  
	  if (employee_row.sal < premium) then
	  	premium = employee_row.sal;
	  end if;
	  
	  if (employee_row.sal + premium > 5000) then
	  	premium = 5000 - employee_row.sal;
	  end if;
	  
	  if (premium < 0) then
	  	premium = 0;
	  end if;
	  
	  insert into temp_emp values (nextval('seq_temp_emp'), employee_row.empno,
								   premium, employee_row.ename);
   end loop;
	
	close employees_cur;
end;$$

--Тестирование
select *
from emp;

select *
from temp_emp;

select set_premium(1);

-- 3.Составить программу, вычисляющую суммарную зарплату служащих 20-го отдела,
-- информация о которых находится в таблице EMP. Подсчитать и вставить в таблицу
-- ТЕМР количество служащих, которые имеют оклад выше 2000$ , количество служащих,
-- у которых комиссионные больше оклада и суммарную зарплату.

create table temp_emp_sal (
	temp_emp_sal_id int,
	more_than_2_thousand numeric,
	comm_more_than_sal numeric,
	sum_sal numeric
);

alter table temp_emp_sal
add constraint "temp_emp_sal PK" PRIMARY KEY (temp_emp_sal_id);

CREATE SEQUENCE seq_temp_emp_sal
START WITH 1
MAXVALUE 1000
increment by 1;

create or replace function get_sal_characteristic()
returns void
language plpgsql
as $$
declare 
	employee_row record;
	employees_cur cursor for
		select *
		from emp;
	count_more_than_2000 numeric;
	count_comm_more_than_sal numeric;
	sum_salary numeric;
begin
	open employees_cur;
	
	count_more_than_2000 = 0;
	count_comm_more_than_sal = 0;
	sum_salary = 0;
	
	loop
      fetch employees_cur into employee_row;
      exit when not found;
	  
	  if (employee_row.sal > 2000) then
	  	count_more_than_2000 = count_more_than_2000 + 1;
	  end if;
	  
	  if (employee_row.sal < employee_row.comm) then
	  	count_comm_more_than_sal = count_comm_more_than_sal + 1;
	  end if;
	  
	  sum_salary = sum_salary + employee_row.sal;
	 
   end loop;
	
	close employees_cur;
	
	insert into temp_emp_sal values (nextval('seq_temp_emp_sal'), count_more_than_2000,
								   count_comm_more_than_sal, sum_salary);
	
end;$$

--Тестирование
select *
from emp;

select *
from temp_emp_sal;

select get_sal_characteristic();

-- 4.Таблица SKLAD содержит данные о количестве деталей в ячейках склада. Составить
-- программу, которая просматривает ячейки склада, содержащие детали с номером 5469,
-- подсчитывает количество недостающих деталей и дополняет ячейки до 500 штук. Номер
-- детали передать в качестве параметра. В таблицу ТЕМР заносится суммарное количество
-- деталей, вновь поступивших на склад.

create table temp_sklad (
	temp_sklad_id int,
	sum_number numeric
);

alter table temp_sklad
add constraint "temp_sklad PK" PRIMARY KEY (temp_sklad_id);

CREATE SEQUENCE seq_temp_sklad
START WITH 1
MAXVALUE 1000
increment by 1;

create or replace function push_new_products(
	part_num_p numeric,
	prod_number numeric
)
returns void
language plpgsql
as $$
declare 
	sklad_row record;
	sklad_cur cursor(part_num_p numeric) for
		select *
		from sklad
		where part_num = part_num_p;
	prod_added numeric;
begin
	open sklad_cur(part_num_p);
	
	prod_added = 0;
	
	loop
      fetch sklad_cur into sklad_row;
      exit when not found;
	  
	  if (sklad_row.s_detal < prod_number) then
	  	prod_added = prod_added + (prod_number - sklad_row.s_detal);
	  	
		update sklad
		set s_detal = prod_number
		where s_num = sklad_row.s_num;
		
	  end if;
	 
   end loop;
	
	close sklad_cur;
	
	insert into temp_sklad values (nextval('seq_temp_sklad'), prod_added);
	
end;$$

-- Тестирование
select *
from SKLAD;

select *
from temp_sklad;

select push_new_products(5469, 600);

-- 5.Составить программу, которая  проверяет наличие средств у заказчика на счету
-- 106 для покупки 5 телевизоров Panasonic 37 и осуществляет снятие денег со счета,
-- в противном случае вносит запись в таблицу temp, содержащую номер банковского счета
-- (код заказчика), остаток средств на счете и текст сообщения о том, что
-- средств недостаточно. Используются таблицы SPROD И SCUST.

create table temp_purchases (
	temp_purchases_id numeric,
	custid numeric,
	debet numeric,
	temp_message varchar(30)
);

alter table temp_purchases
add constraint "temp_purchases PK" PRIMARY KEY (temp_purchases_id);

CREATE SEQUENCE seq_temp_purchases
START WITH 1
MAXVALUE 1000
increment by 1;

alter table temp_purchases
add constraint temp_purchases_cr_scust foreign key
(
	custid
)
references cr_scust
(
	custid
);

create or replace function get_product(
	custid_p numeric,
	prodid_p numeric,
	number_of_products numeric
)
returns void
language plpgsql
as $$
declare 
	cr_scust_row record;
	cr_scust_cur cursor(custid_p numeric) for
		select *
		from cr_scust
		where custid = custid_p;
	cost_of_products numeric;
	real_number_of_products numeric;
begin
	open cr_scust_cur(custid_p);
	
		select price
		from sprod
		where prodid_p = prodid
		into cost_of_products;
		
		select p_qty
		from sprod
		where prodid = prodid_p
		into real_number_of_products;
		
		if (number_of_products > real_number_of_products) then
			number_of_products = real_number_of_products;
		end if;
		
		cost_of_products = cost_of_products * number_of_products;
		
		fetch cr_scust_cur into cr_scust_row;
		if (cr_scust_row.debet >= cost_of_products) then
		
			update sprod
			set p_qty = p_qty - number_of_products
			where prodid = prodid_p;
			
			update cr_scust
			set debet = debet - cost_of_products
			where custid = custid_p;
			
		else
			insert into temp_purchases values (nextval('seq_temp_purchases'), cr_scust_row.custid,
											  cr_scust_row.debet, 'средств недостаточно');
		end if;
	
	close cr_scust_cur;
	
end;$$

-- Тестирование 
select *
from sprod;

select *
from cr_scust;

select *
from emp;

select *
from temp_purchases;

select get_product(1, 100004, 4);

-- 6.При покупке телевизоров предприятие предоставляет систему скидок: 5% - покупка
-- более 10 штук; 10% - более 100 штук. Составить программу, которая при оформлении
-- заказа на покупку партии телевизоров снимает деньги со счета заказчика, учитывая
-- систему скидок. Использовать в программе курсор с параметрами. В качестве параметров
-- передать: номер счета заказчика, количество единиц и код товара (102, 15, 100063).
-- Используются таблицы SPROD и SCUST.

create or replace function get_product_with_discount(
	custid_p numeric,
	prodid_p numeric,
	number_of_products numeric
)
returns void
language plpgsql
as $$
declare 
	cr_scust_row record;
	cr_scust_cur cursor(custid_p numeric) for
		select *
		from cr_scust
		where custid = custid_p;
	cost_of_products numeric;
	real_number_of_products numeric;
begin
	open cr_scust_cur(custid_p);
	
		select price
		from sprod
		where prodid_p = prodid
		into cost_of_products;
		
		select p_qty
		from sprod
		where prodid = prodid_p
		into real_number_of_products;
		
		if (number_of_products > real_number_of_products) then
			number_of_products = real_number_of_products;
		end if;
		
		cost_of_products = cost_of_products * number_of_products;
		
		if (number_of_products > 10) then
			cost_of_products = 0.95 * cost_of_products;
		elseif (number_of_products > 100) then
			cost_of_products = 0.9 * cost_of_products;
		end if;
		
		fetch cr_scust_cur into cr_scust_row;
		if (cr_scust_row.debet >= cost_of_products) then
		
			update sprod
			set p_qty = p_qty - number_of_products
			where prodid = prodid_p;
			
			update cr_scust
			set debet = debet - cost_of_products
			where custid = custid_p;
			
		end if;
	
	close cr_scust_cur;
	
end;$$

-- Тестирование 
select *
from sprod;

select *
from cr_scust;

select *
from emp;

select *
from temp_purchases;

select get_product_with_discount(1, 100004, 11);

-- Процедуры. Задания для самостоятельной работы.

-- 1. Составить процедуру, вносящую изменения в таблицу SPROD при поступлении очередной
-- партии товара. В качестве параметров передавать код товара, наименование, цену и
-- количество. Количество суммируется, если в таблице SPROD уже имеется аналогичный товар
-- Таблица SPROD приведена ниже.

create or replace procedure add_new_products(
	prod_id_p int,
	descrip_p varchar(50),
	price_p numeric,
	p_qty_p numeric
)
language plpgsql    
as $$
declare 
	rows_with_prodid int;
begin
	select count(*)
	from SPROD
	where prod_id_p = prodid
	into rows_with_prodid;
	
	if (rows_with_prodid = 0) then 
		insert into SPROD(prodid, descrip, price, p_qty) 
					values(prodid_p, descrip_p, price_p, p_qty_p);
	else 
		update SPROD
		set p_qty = p_qty + p_qty_p
		where prodid = prod_id_p;
		
	end if;

end;$$

-- Тестирование процедуры
select *
from SPROD;

call add_new_products(100001, 'd', 120, 1);

-- 2. Составить процедуру, обеспечивающую изменение цены при переоценке товара в таблице
-- SPROD. В качестве параметров передавать код товара и изменение цены. Поместить в таблицу
-- TEMP сообщение, если код товара отсутствует в таблице SPROD. Таблица SPROD приведена ниже.

create table temp_sprod (
	temp_sprod_id int,
	description varchar(50)
);

alter table temp_sprod
add constraint "temp_sprod PK" PRIMARY KEY (temp_sprod_id);

CREATE SEQUENCE seq_temp_sprod
START WITH 1
MAXVALUE 1000
increment by 1;

create or replace procedure reassess_product(
	prod_id_p int,
	price_p numeric
)
language plpgsql    
as $$
declare 
	rows_with_prodid int;
	description_p varchar(50);
begin
	select count(*)
	from SPROD
	where prod_id_p = prodid
	into rows_with_prodid;
	
	if (rows_with_prodid = 0) then 
		description_p = 'try to add product with prodid = ' || prod_id_p::text;
		insert into temp_sprod(temp_sprod_id, description) 
					values(nextval('seq_temp_sprod'), description_p);
	else 
		update SPROD
		set price = price_p
		where prodid = prod_id_p;
		
	end if;

end;$$

-- Тестирование процедуры
select *
from SPROD;

select *
from temp_sprod;

call reassess_product(100000,  121);

-- 3. Составить процедуру, добавляющую новые записи в таблицу EMP при оформлении на работу
-- новых служащих компании. В качестве параметров передавать имя, должность, табельный
-- номер начальника, оклад, размер комиссионных,  номер отдела.

CREATE SEQUENCE seq_emp
START WITH 1
MAXVALUE 8000
increment by 1;

create or replace procedure add_employee(
	ename_p varchar(10),
	job_p varchar(10),
	mrg_p numeric,
	hiredate_p date,
	sal_p numeric,
	comm_p numeric,
	deptno_p numeric
)
language plpgsql    
as $$
begin
	
	insert into emp(empno, ename, job, mgr, hiredate, sal, comm, deptno) 
	values(nextval('seq_emp'), ename_p, job_p, mrg_p, hiredate_p, sal_p, comm_p, deptno_p);

end;$$

-- Тестирование процедуры
select *
from EMP

call add_employee('VLAD', 'PRESIDENT', 7698, TO_DATE('15.04.23','DD.MM.RR'), 5555, 0, 20);

-- 4. Составить процедуру, удаляющую запись из таблицы EMP при увольнении сотрудника.
-- В качестве параметра передавать табельный номер уволенного сотрудника.

create or replace procedure delete_employee(
	empno_p numeric
)
language plpgsql    
as $$
begin
	
	delete from emp
	where empno = empno_p;

end;$$

-- Тестирование процедуры
select *
from EMP

call delete_employee(1);


-- 5. Составить процедуру, увеличивающую оклад служащего в таблице EMP. В качестве
-- параметров передавать табельный номер сотрудника и заданную в процентах величину,
-- на которую необходимо увеличить оклад.

create or replace procedure rise_sal(
	empno_p numeric,
	percentage_p double precision
)
language plpgsql    
as $$
begin
	
	update emp
	set sal = sal * (1 + percentage_p / 100)
	where empno = empno_p;

end;$$

-- Тестирование процедуры
select *
from EMP

call rise_sal(7839, 10);

-- 6. Составить процедуру, начисляющую премию сотрудникам компании в таблице EMP.
-- В качестве параметров передавать величину (в процентах), определяющую размер премии
-- от оклада, и величину (в процентах), определяющую размер премии от комиссионных.
-- Размер начисленной премии должен равняться сумме премии от оклада и комиссионных.
-- Информацию о премировании занести в таблицу P_EMP.

create table p_emp (
	p_emp_id numeric,
	empno numeric,
	premium double precision
);

alter table p_emp
add constraint "p_emp PK" PRIMARY KEY (p_emp_id);

alter table p_emp
add constraint emp_p_emp foreign key
(
	empno
)
references emp
(
	empno
);

CREATE SEQUENCE seq_p_emp
START WITH 1
MAXVALUE 8000
increment by 1;


create or replace procedure accrue_a_premium(
	sal_percentage_p double precision,
	comm_percentage_p double precision
)
language plpgsql    
as $$
declare
	f record;
	sal_p numeric;
	comm_p numeric;
begin
	
	for f in
		select *
		from emp
	loop 
	
		if (f.sal = null) then
			sal_p = 0;
		else 
			sal_p = f.sal;
		end if;
		
		if (f.comm = null) then
			comm_p = 0;
		else 
			comm_p = f.comm;
		end if;
		
		insert into p_emp(p_emp_id, empno, premium)
			values(nextval('seq_p_emp'),f.empno, ( sal_p * (1 + sal_percentage_p / 100)) + 
				   (comm_p * (1 + comm_percentage_p / 100)));
		
	end loop;

end;$$

-- Тестирование процедуры
select *
from P_EMP

call accrue_a_premium(10, 10);


-- 7. Составить процедуру, обеспечивающую загрузку партии деталей в ячейки склада в
-- таблице SKLAD. В качестве параметров передавать номер партии и количество деталей,
-- а также максимальное количество деталей, которое можно поместить в одну ячейку склада.
-- Таблица SKLAD приведена ниже.

create or replace procedure load_detail(
	part_num_p numeric,
	s_detal_p numeric,
	max_number_of_detail_in_cell_p numeric
)
language plpgsql    
as $$
declare
	number_of_detail_in_current_insertion numeric;
begin
	
	while (s_detal_p <> 0) loop
		if (s_detal_p > max_number_of_detail_in_cell_p) then
			number_of_detail_in_current_insertion = 
			max_number_of_detail_in_cell_p;
		else 
			number_of_detail_in_current_insertion = 
			s_detal_p;
		end if;
		
		s_detal_p = s_detal_p - number_of_detail_in_current_insertion;
    	
		insert into sklad values (nextval('seq_sklad'), part_num_p,
								 number_of_detail_in_current_insertion);
   	end loop;

end;$$

-- Тестирование
select *
from SKLAD

call load_detail(6666, 10000, 500);

-- 8.	Составить функцию, подсчитывающую общее количество деталей одного вида на
-- складе в таблице SKLAD. При вызове функция должна принимать в качестве аргумента
-- номер партии деталей. Таблица SKLAD приведена ниже.

create or replace procedure count_detail(
	part_num_p numeric,
	out number_of_products numeric
)
language plpgsql    
as $$
begin
	
	select count(*)
	from sklad
	where part_num = part_num_p
	into number_of_products;

end;$$

-- Тестирование
call count_detail(6666, 1);

-- Триггеры. Задания для самостоятельной работы.

-- 1.  Создать триггер, запрещающий обновлять данные о сотрудниках в таблице EMP
-- в нерабочее время.

CREATE OR REPLACE FUNCTION check_working_hours() 
RETURNS TRIGGER 
AS $$
DECLARE
  	current_time TIME := CURRENT_TIME;
BEGIN
  	IF current_time < '09:00:00' OR current_time > '18:00:00' THEN
    	RAISE EXCEPTION 'Обновление данных сотрудников в нерабочее время запрещено';
  	END IF;
  	RETURN NEW;
END;$$ 
LANGUAGE plpgsql;

CREATE TRIGGER forbid_emp_update
BEFORE UPDATE ON emp
FOR EACH ROW
EXECUTE FUNCTION check_working_hours();


-- 2.  Создать триггер, фиксирующий изменения таблицы SCUST в протокольной таблице
-- H_SCUST.

CREATE SEQUENCE seq_h_scust
START WITH 1
MAXVALUE 8000
increment by 1;

CREATE OR REPLACE FUNCTION log_updates_of_scust() 
RETURNS TRIGGER 
AS $$
DECLARE
  	current_time TIME := CURRENT_TIME;
BEGIN
  	INSERT INTO H_SCUST VALUES (nextval('seq_h_scust'), current_date, 'scust', 'update', new.custid);
	
  	RETURN NEW;
END;$$ 
LANGUAGE plpgsql;

CREATE TRIGGER forbid_emp_update
AFTER UPDATE ON scust
FOR EACH ROW
EXECUTE FUNCTION log_updates_of_scust();

-- Тестирование
select *
from SCUST;

select *
from H_SCUST;

update scust
set predoplata = 4001
where custid = 100;

-- 3. Создать триггер,  который при добавлении нового заказа в таблицу SORD проверяет
-- наличие  информации о данном заказчике в таблице SCUST.

CREATE OR REPLACE FUNCTION check_custid_in_scust() 
RETURNS TRIGGER 
AS $$
DECLARE
  	number_of_rows numeric;
BEGIN
	
	select count(*)
	from SCUST
	where NEW.custid = SCUST.custid
	into number_of_rows;
	
	if (number_of_rows = 0) then
    	RAISE EXCEPTION 'Информация о заказчике с данным ID отсутствует';
	end if;
	
  	RETURN NEW;
END;$$ 
LANGUAGE plpgsql;

CREATE or replace TRIGGER insertion_in_sord
BEFORE insert ON sord
FOR EACH ROW
EXECUTE FUNCTION check_custid_in_scust();

-- Тестирование 
select *
from sord;

select *
from SCUST;

insert into sord  values(624,to_date('20.02.1996','dd.mm.yyyy'),200,to_date('22.02.1996','dd.mm.yyyy'),0);

-- 4. Создать триггер, который формирует дополнительный заказ в таблице ORD_PROD  на
-- поставку товара, если количество этого товара  в таблице SPROD становится меньше
-- 10 единиц.

CREATE OR REPLACE FUNCTION check_number_of_products_left_func() 
RETURNS TRIGGER 
AS $$
DECLARE
  	number_of_rows numeric;
BEGIN
	
	if (new.p_qty < 10) then
		insert into ord_prod values(new.prodid, 'кол-во товара критич.', new.p_qty);
	end if;
	
  	RETURN NEW;
END;$$ 
LANGUAGE plpgsql;

CREATE or replace TRIGGER check_number_of_products_left
AFTER UPDATE ON SPROD
FOR EACH ROW
EXECUTE FUNCTION check_number_of_products_left_func();

-- Тестирование 

select *
from ORD_PROD;

select *
from SPROD;

update SPROD
set p_qty = 6
where prodid = 100070;

-- 5. Создать триггер,  который  запрещает устанавливать границу минимальной зарплаты
-- в таблице SALS  ниже 600.

CREATE OR REPLACE FUNCTION min_sal_update_fnc() 
RETURNS TRIGGER 
AS $$
BEGIN
	
	if (new.minsal < 600) then
		RAISE EXCEPTION 'Запрещено устанавливать величину ЗП, меньшую 600';
	end if;
	
  	RETURN NEW;
END;$$ 
LANGUAGE plpgsql;

CREATE TRIGGER trg_min_sal_update
BEFORE UPDATE ON sals
FOR EACH ROW
EXECUTE FUNCTION min_sal_update_fnc();

-- Тестирование 
select *
from sals;

update sals
set minsal = 500
where jobs = 'CLERK';

-- 6.  Создать триггер,  который при добавлении нового служащего в таблицу EMP или
-- при изменении должности или оклада какого-либо служащего обеспечивает, что зарплата
-- попадает в пределы, установленные для данной должности в таблице SALS.

CREATE OR REPLACE FUNCTION check_sal_boundaries_fnc() 
RETURNS TRIGGER 
AS $$
DECLARE
  	min_sal numeric;
	max_sal numeric;
BEGIN
	
	select minsal
	from sals
	where jobs = new.job
	into min_sal;
	
	select maxsal
	from sals
	where jobs = new.job
	into max_sal;
	
	if (new.sal > max_sal or new.sal < min_sal) then
		RAISE EXCEPTION 'Запрещено устанавливать величину ЗП, 
		не соответствующую пределам ЗП для данной специальности';
	end if;
	
  	RETURN NEW;
END;$$ 
LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_check_sal_boundaries
BEFORE UPDATE OR INSERT ON emp
FOR EACH ROW
EXECUTE FUNCTION check_sal_boundaries_fnc();

-- Тестирование
select *
from emp;

select *
from sals;

update emp
set sal = 600
where empno = 7900;

-- 7. Создать триггер,  который при добавлении нового заказчика в таблицу SCUST вносит
-- соответствующие изменения в таблицу CR_SCUST.

CREATE OR REPLACE FUNCTION add_cr_scust_notes_fnc() 
RETURNS TRIGGER 
AS $$
BEGIN
	
	insert into CR_SCUST values(new.custid, 0, 0);
	
  	RETURN NEW;
END;$$ 
LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_add_cr_scust_notes
AFTER INSERT ON scust
FOR EACH ROW
EXECUTE FUNCTION add_cr_scust_notes_fnc();

-- Тестирование
select *
from SCUST;

select *
from CR_SCUST;

insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (118, 'СДЮСШОР N1', '200004', 'Гомель',
        'ул.Металлистов,22', '254563', 1200);

-- 8. Создать триггер,  который при добавлении нового заказа  в таблицу SITEM
-- подсчитывает сумму заказа в таблице SORD.

CREATE OR REPLACE FUNCTION add_item_fnc() 
RETURNS TRIGGER 
AS $$
BEGIN
	
	insert into SORD values(new.ordid, current_date, null, null, new.summa);
	
  	RETURN NEW;
END;$$ 
LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_add_item
AFTER INSERT ON  SITEM
FOR EACH ROW
EXECUTE FUNCTION add_item_fnc();

-- Тестирование 
select *
from SITEM;

select *
from SORD;

