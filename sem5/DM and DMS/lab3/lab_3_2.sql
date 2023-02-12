-- 1.	Найти имена специалистов, оказавших услуги с минимальной стоимостью.
REM   Script: SELECT 3_2
REM   SELECT 3_2

-- 2.	Найти имена сотрудников, работавших в тот же день, когда был визит пациента с именем Безенчук Федор Николаевич.
SELECT * FROM H_Doctor 
WHERE ID_Doctor IN (SELECT ID_doctor FROM H_Visit WHERE date_visit IN (SELECT date_visit FROM H_Visit WHERE id_patient=(SELECT N_CARD FROM H_Patient WHERE surname='Безенчук')));

-- 3.	Найти имена сотрудников, обслуживающих пациентов Паниковский, Щукина, Корейко.
SELECT * FROM H_Doctor 
WHERE ID_Doctor IN (SELECT ID_doctor FROM H_Visit WHERE ID_patient IN (SELECT patient_ID FROM H_Patient WHERE surname IN ('Паниковский','Щукина','Корейко')));

-- 4.	 Найти сведения о номерах сотрудников, работавших 15, 20 и 24 сентября.
SELECT * FROM H_Doctor 
WHERE ID_Doctor IN (SELECT ID_Doctor FROM H_Visit WHERE date_visit = ANY (TO_DATE('15-09-22','DD-MM-YY'),TO_DATE('20-09-22','DD-MM-YY'),TO_DATE('24-09-22','DD-MM-YY')));

-- 5.	Найти сведения о номерах сотрудников, оказывающих какие-либо услуги из тех,  которые были оказаны 12 и 13 сентября..
SELECT * FROM H_Doctor 
WHERE ID_Doctor IN (SELECT ID_Doctor FROM H_Visit WHERE date_visit = ALL (TO_DATE('12-09-22','DD-MM-YY'),TO_DATE('13-09-22','DD-MM-YY')));

-- 6.	Определить в какие дни были оказаны услуги, средняя суточная стоимость  была больше общей средней стоимости всех имеющихся услуг.
SELECT date_visit FROM H_Visit,H_Services 
WHERE H_Visit.code_srv=H_Services.code_srv 
GROUP BY date_visit 
HAVING AVG(price)>= (SELECT AVG(price) FROM H_Services);

-- 7. Определить коды специальностей, сотрудников, оказавших услуги во время визитов с 15 по 20 сентября.
SELECT code_spec FROM H_Doctor 
WHERE ID_doctor NOT IN (SELECT ID_doctor FROM H_VISIT WHERE date_visit BETWEEN TO_DATE('15-09-22','DD-MM-YY') AND TO_DATE('20-09-22','DD-MM-YY') AND ID_Doctor IS NOT NULL);

-- 8.	Определить коды специальностей сотрудников, обслуживающих пациентов, которым были оказаны услуги с кодами 110 - 150.
SELECT code_spec FROM H_Doctor 
WHERE ID_doctor IN (SELECT ID_doctor FROM H_VISIT WHERE code_srv BETWEEN 110 AND 150);

-- 9. Определить коды специальностей сотрудников, которые не обслуживали пациентов в период с 15 по 20 сентября.
SELECT code_spec FROM H_Doctor 
WHERE ID_doctor NOT IN (SELECT ID_doctor FROM H_VISIT WHERE date_visit BETWEEN TO_DATE('15-09-22','DD-MM-YY') AND TO_DATE('20-09-22','DD-MM-YY') AND ID_Doctor IS NOT NULL);

-- 10. Вывести сведения о специальности сотрудников с указанием названий вместо их кодов.
SELECT ID_Doctor,surname,firstname,middle_name,title FROM H_Doctor 
LEFT OUTER JOIN H_Speciality ON H_Doctor.code_spec=H_Speciality.code_spec;

-- 11.Определить целую часть средней стоимости услуг, по датам.
SELECT date_visit,FLOOR(AVG(price)) FROM H_Visit,H_Services 
WHERE H_Visit.code_srv=H_Services.code_srv 
GROUP BY date_visit 
ORDER BY date_visit;

-- 12. Разделите список услуг по стоимостным категориям: A) до 5 руб.; B) 5 - 10 руб.; C) 10 – 50 руб.;    D) более 50 руб.
SELECT code_srv,title, 
CASE 
    WHEN price < 5 THEN 'до 5 руб' 
    WHEN price >= 5 AND price < 10 THEN '5-10 руб' 
    WHEN price >= 10 AND price < 50 THEN '10-50 руб' 
    ELSE 'больше 50 рублей' 
END  
FROM H_Services 
ORDER BY price;

-- 13. Перекодируйте номера пациентов, добавив перед номером буквы AM для номеров <=200000,  буквы  NV для номеров >=20000.
SELECT surname,firstname,middle_name,address,phone, 
CASE  
    WHEN patient_ID <=200000 THEN CONCAT('AM',patient_ID) 
    ELSE CONCAT('NV',patient_ID) 
END AS ID 
FROM H_Patient;


-- 14. Выдать информацию о сотрудниках из, заменив отсутствие имени или отчество строкой, состоящей из 5 пробелов.
SELECT ID_Doctor,COALESCE(firstname,'_____') AS firstname,COALESCE(surname,'_____') AS surname,COALESCE(middle_name,'_____') AS middle_name,code_spec FROM H_Doctor;

