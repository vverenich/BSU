-- 1. В одной выборке вывести сведения о специалистах, отсортированных по
-- алфавиту терапевтов, неврологов и хирургов, в обратном порядке –
-- офтальмолог, дерматовенеролог и интерн. По остальным специальностям –
-- без сортировки.

WITH 
    joined_tables AS(
        SELECT * FROM H_Doctor
    	INNER JOIN H_Speciality on H_Doctor.code_spec=H_Speciality.code_spec
    ),
	sorted_doctors AS(
		(SELECT surname,firstname,middle_name,title FROM joined_tables
        GROUP BY title,surname,firstname,middle_name
        HAVING title IN ('Терапевт','Невролог','Хирург')
        ORDER BY title,surname ASC)
		UNION ALL
		(SELECT surname,firstname,middle_name,title FROM joined_tables
        GROUP BY title,surname,firstname,middle_name
        HAVING title IN ('Офтальмолог','Дерматовенеролог','Интерн')
        ORDER BY title,surname DESC)
		UNION ALL
		(SELECT surname,firstname,middle_name,title FROM joined_tables
        GROUP BY title,surname,firstname,middle_name
        HAVING title NOT IN ('Терапевт','Невролог','Хирург','Офтальмолог','Дерматовенеролог','Интерн'))
	)

select * from sorted_doctors;

-- 2. Определить разницу в количестве специалистов каждой специальности
-- (специальности следуют в алфавитном порядке).

WITH 
    spec_amount AS(
        SELECT title, COUNT(*) AS amount 
		FROM H_Doctor
		INNER JOIN H_Speciality on H_Doctor.code_spec=H_Speciality.code_spec
        GROUP BY title
    ),
    sorted_spect_amount AS(    
        SELECT title, amount,
        ROW_NUMBER() over (ORDER BY title) AS counter
        FROM spec_amount)
SELECT DISTINCT s1.title,s1.amount, s2.title,s2.amount, ABS(s1.amount-s2.amount) AS difference
FROM sorted_spect_amount s1
INNER JOIN sorted_spect_amount s2 ON s2.counter!=s1.counter
ORDER BY s1.title;


-- 3. Вывести список фамилий специалистов, которые принимали пациентов с
-- первого дня работы поликлиники.

INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (SEQ_VISIT.NEXTVAL, 18, 216002, TO_DATE('21.09.90','DD.MM.RR'), 110);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (SEQ_VISIT.NEXTVAL, 15, 216002, TO_DATE('21.09.90','DD.MM.RR'), 130);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (SEQ_VISIT.NEXTVAL, 17, 216002, TO_DATE('21.09.90','DD.MM.RR'), 140);

//hospital started 21.09.90

WITH
    JoinTables AS(
        SELECT * FROM H_Doctor
        LEFT JOIN H_Visit ON H_Visit.id_doctor=H_Doctor.id_doctor
    ),
    MinDate AS(
        SELECT surname,firstname,middle_name,date_visit,
               MIN(date_visit) over (PARTITION BY surname,firstname,middle_name) as FirstVisit        
        FROM JoinTables
        )
SELECT DISTINCT surname,firstname,middle_name,firstvisit FROM MinDate
WHERE FirstVisit in (SELECT MIN(DATE_VISIT) AS visit_date FROM H_Visit);


-- 4. Вывести список визитов с указанием следующей даты визита для каждой
-- строки.

WITH JoinTables AS(
    SELECT * FROM H_Doctor
    LEFT JOIN H_Visit ON H_Visit.id_doctor=H_Doctor.id_doctor
    )
SELECT surname,firstname,middle_name,n_visit,id_patient,date_visit, 
       LEAD(date_visit) over (ORDER BY date_visit) AS next_visit        
FROM JoinTables

-- 5. Для каждого визита вывести среднюю стоимость оказанных услуг, разность
-- между средним значением и минимальным, между средним и максимальным.

WITH
    JoinTables AS(
        SELECT * FROM H_Visit
        LEFT JOIN H_Services ON H_Visit.code_srv=H_Services.code_srv
    ),
    TempTable AS(
        SELECT id_patient,date_visit,title,price,
               AVG(price) over() AS AvgPrice,
               MIN(price) over() AS MinPrice,
               MAX(price) over() AS MaxPrice
        FROM JoinTables
        )
SELECT id_patient,date_visit,title,price,
       ROUND(AvgPrice-MinPrice,2) as diifAvgMin,ROUND(AvgPrice-MaxPrice,2) as diffAvgMax
FROM TempTable;

-- 6. Отобразить для каждого специалиста ранжирование по количеству принятых пациентов за все время работы.

with ranking as 
    (select d.id_doctor as did, coalesce(count(v.n_visit), 0) as vn 
    from h_doctor d left join h_visit v on d.id_doctor = v.id_doctor
    group by d.id_doctor
    )
select d.*, r.vn as visits_number,
rank() over(order by r.vn desc) as rank
from h_doctor d join ranking r on d.id_doctor = r.did 

-- 7. Определить максимальную разность в стоимости услуг по каждой специальности доктора и вывести наименование этих услуг.

select distinct sp.code_spec, s.code_srv, s.title, s.price,
max(s.price) over(partition by sp.code_spec) as max,
min(s.price) over(partition by sp.code_spec) as min,
max(s.price) over(partition by sp.code_spec) - min(s.price) over(partition by sp.code_spec) as max_difference
from h_speciality sp 
join h_doctor d on sp.code_spec = d.code_spec
join h_visit v on v.id_doctor = d.id_doctor
join h_services s on s.code_srv = v.code_srv

-- 8. Для каждого специалиста вывести предполагаемую дату следующего визита.

WITH
    JoinTables AS(
        SELECT * FROM H_Doctor
        LEFT JOIN H_Visit ON H_Visit.id_doctor=H_Doctor.id_doctor
    ),
    TempTable AS(
        SELECT surname,firstname,middle_name,n_visit,id_patient,date_visit,code_srv,
               AVG(cast(to_char(date_visit, 'J') as integer)) over (PARTITION BY surname) AS DiffBtwVisits,
               MAX(cast(to_char(date_visit, 'J') as integer)) over (PARTITION BY surname) AS MaxVisitNum,
               MAX(date_visit) over (PARTITION BY surname) AS MaxVisit
        FROM JoinTables
    )
SELECT DISTINCT surname,firstname,middle_name,
     MaxVisit+cast(round(MaxVisitNum-DiffBtwVisits) as integer) AS NextVisit
FROM TempTable
WHERE date_visit IS NOT NULL;

SELECT * FROM H_Doctor
LEFT OUTER JOIN H_Visit ON H_Doctor.id_doctor=H_Visit.id_doctor
WHERE H_Visit.id_doctor IS NULL;

-- 9. Отобразить список специалистов, которые в период с 15.09.22 по 19.09.22
-- обслуживали наибольшее количество пациентов, наименьшее количество.

WITH ranking_doctor_in_date_range as (
    SELECT d.id_doctor AS did, coalesce(count(v.n_visit), 0) AS vn 
    FROM h_doctor d 
    LEFT JOIN h_visit v on d.id_doctor = v.id_doctor
    WHERE v.date_visit between TO_DATE('15.09.22','DD.MM.RR') and TO_DATE('19.09.22','DD.MM.RR')
    GROUP BY d.id_doctor)


SELECT * 
FROM
(
    SELECT d.*, rd.vn AS max_visit_count,
    RANK() OVER (ORDER BY rd.vn desc) AS rk
    FROM h_doctor d 
    JOIN ranking_doctor_in_date_range rd ON d.id_doctor = rd.did
) x
WHERE x.rk = 1;

--10.Вывести список фамилий пациентов в убывающем порядке количества
-- визитов. Для каждого из них определить превышение суммы стоимости
-- услуг, оказанных пациенту среднего значения стоимости всех услуг.

WITH ranking_patient AS (
    SELECT p.n_card AS pid, coalesce(count(v.n_visit), 0) AS vn 
    FROM h_patient p 
    LEFT JOIN h_visit v ON p.n_card = v.id_patient
    GROUP BY p.n_card),

    services_patient AS (SELECT p.n_card AS pid, coalesce(sum(s.price), 0) sum_services 
				FROM h_patient p 
				LEFT JOIN h_visit v ON p.n_card = v.id_patient 
				JOIN h_services s ON s.code_srv = v.code_srv
    				GROUP BY p.n_card)
        

SELECT p.*, r.vn AS visits_number, 
ROUND(sp.sum_services - (SELECT AVG(s.price) AS avg_price 
				FROM h_visit v natural 
				JOIN h_services s), 4) AS excess_amount,
RANK() OVER(ORDER BY r.vn desc) AS rank
FROM h_patient p 
JOIN ranking_patient r ON p.n_card = r.pid JOIN services_patient sp ON sp.pid = r.pid;

