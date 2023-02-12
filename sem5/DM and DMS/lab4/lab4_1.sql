-- 1. Поднимите нижнюю границу стоимости услуг в таблице Services до 1 руб.

UPDATE H_Services
    SET Price = 1
    WHERE Price < 1;

-- 2.Поднимите стоимость услуг в таблице Services на 10% для услуг ценовой категории C (см. запрос 12 из ЛР 3_2),
-- кроме рентгеноскопии.

UPDATE H_Services
    SET Price = Price * 1.1
    WHERE NOT TITLE = N'Ренгеноскопия' AND Price BETWEEN 10 AND 50

-- 3.Поднимите стоимость услуг в таблице Services на 10% для услуг терапевтов и на 20% для неврологов (одним оператором).

UPDATE H_Services
    SET Price = Price * CASE
                            WHEN H_Services.CODE_SRV IN (SELECT DISTINCT code_srv FROM H_Visit INNER JOIN H_Doctor HD on H_Visit.ID_Doctor = HD.ID_DOCTOR
                                INNER JOIN H_Speciality HS on HS.CODE_SPEC = HD.code_spec
                                WHERE HS.Title = N'Терапевт') THEN 1.1
                            WHEN H_Services.CODE_SRV IN (SELECT DISTINCT code_srv FROM H_Visit INNER JOIN H_Doctor HD on H_Visit.ID_Doctor = HD.ID_DOCTOR
                                INNER JOIN H_Speciality HS on HS.CODE_SPEC = HD.code_spec
                                WHERE HS.Title = N'Невролог') THEN 1.2
                            ELSE 1
                        END

-- 4.Установите минимальную стоимость услуг хирурга равной 90% от средней стоимости услуг терапевта.

do $$
declare
   average_therapeutic_service_cost integer;
begin
   SELECT AVG(Price)
   into average_therapeutic_service_cost
   FROM H_Services
        WHERE H_Services.CODE_SRV IN
              (SELECT DISTINCT code_srv FROM H_Visit
                    WHERE ID_Doctor IN (
                        SELECT ID_DOCTOR FROM H_Doctor
                            WHERE H_Doctor.code_spec IN (
                                SELECT CODE_SPEC FROM H_Speciality
                                    WHERE H_Speciality.Title = N'Терапевт'
                                )
                        )
              );

	
	WITH surgeon_services AS (SELECT DISTINCT CODE_SRV 
							  FROM H_Visit INNER JOIN H_Doctor
    						  ON H_Visit.ID_Doctor = H_Doctor.ID_DOCTOR INNER JOIN H_Speciality
    						  ON H_Doctor.code_spec = H_Speciality.CODE_SPEC
    WHERE H_Speciality.Title = N'Хирург')
    UPDATE H_Services
    SET PRICE = 0.9 * average_therapeutic_service_cost
    WHERE (CODE_SRV IN (SELECT CODE_SRV FROM surgeon_services) AND (Price < 0.9 * average_therapeutic_service_cost
                OR Price = (SELECT MIN(Price) FROM H_Services WHERE CODE_SRV in (SELECT CODE_SRV FROM surgeon_services))));

end $$;


-- 5.Приведите в таблице Doctor имена специалистов, начинающиеся на букву ‘С’, к нижнему регистру.
UPDATE H_Doctor
    SET FIRSTNAME = UPPER(FIRSTNAME)
    WHERE SUBSTRING(FIRSTNAME, 1, 1) = N'С'

-- 6.Измените в таблице Doctor фамилии специалистов, состоящие из двух слов, так, чтобы оба слова в имени
-- начинались с заглавной буквы, а продолжались прописными
-- (например, фамилия Бендер-задунайский изменяется на Бендер Задунайский).

CREATE FUNCTION first_letter_to_upper(word VARCHAR(100))
RETURNS VARCHAR(100) AS $$
DECLARE result VARCHAR(100);
BEGIN
		select CONCAT(UPPER(SUBSTRING(word, 1, 1)), SUBSTRING(word, 2, 100)) as result;
        return result;
END;
$$ LANGUAGE plpgsql



UPDATE H_Doctor
    SET SURNAME = (SELECT STRING_AGG(dbo.first_letter_to_upper(some_alias), N' ') FROM (SELECT STRING_TO_ARRAY(SURNAME, '-') AS parts) AS some_alias)
    WHERE SURNAME LIKE N'%-%'


-- 7.Приведите в таблице Doctor фамилии специалистов к верхнему регистру.

UPDATE H_Doctor
    SET SURNAME = UPPER(SURNAME)

-- 8.Перенесите визиты исследований (Visit) к другому специалисту той же специальности (Specialty).

WITH other_doctor AS
    (SELECT TOP 1 ID_DOCTOR FROM H_Doctor
        WHERE NOT ID_DOCTOR = 20 AND code_spec = (SELECT code_spec FROM H_Doctor WHERE ID_DOCTOR = 20))
UPDATE H_Visit
    SET ID_Doctor = (SELECT ID_DOCTOR FROM other_doctor)
    WHERE ID_Doctor = 20;


-- 9.Добавьте нового сотрудника в таблицу Doctor. Его имя и фамилия должны совпадать с Вашими,
-- записанными латинскими буквами согласно паспорту, дата рождения также совпадает с Вашей.

INSERT INTO H_Doctor(ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec)
    VALUES(NEXT VALUE FOR SEQ_DOC, N'verenich', N'Vladislav', N'Nikolaevich', 0510)

-- 10.Определите нового сотрудника (см. предыдущее задание) на работу в качестве интерна.
-- Назначьте ему первый визит на текущую дату.

UPDATE H_Doctor
    SET code_spec = 1408
    WHERE ID_DOCTOR = 25;

INSERT INTO H_Visit(N_Visit, ID_Doctor, ID_Patient, DATE_VISIT, CODE_SRV)
    VALUES(NEXT VALUE FOR SEQ_Visit,
           25,
           (SELECT TOP 1 H_Patient.N_CARD FROM H_Patient WHERE SURNAME = N'Грицацуева'),
           GETDATE(),
           (SELECT H_Services.CODE_SRV FROM H_Services WHERE H_Services.TITLE = N'Физиолечение'))

-- 11.Создайте таблицу TMP_Doc со структурой, аналогичной структуре таблицы Doctor.
-- Добавьте в нее информацию о сотрудниках, которые работали с пациентами на всем протяжении зарегистрированных визитов.

CREATE TABLE TMP_Doc(
    ID_DOCTOR   int not null,
    SURNAME     nvarchar(50),
    FIRSTNAME   nvarchar(50),
    MIDDLE_NAME nvarchar(50),
    code_spec   int not null
)
ALTER TABLE TMP_Doc
    ADD CONSTRAINT "TMP_Doc PK" PRIMARY KEY ( ID_Doctor ) ;

ALTER TABLE TMP_Doc
    ADD CONSTRAINT Spec_TMP_Doc FOREIGN KEY
    (
     code_spec
    )
    REFERENCES H_Speciality
    (
     code_spec
    )
;

INSERT INTO TMP_Doc(ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec)
    SELECT DISTINCT HD.ID_DOCTOR, HD.SURNAME, HD.FIRSTNAME, HD.MIDDLE_NAME, HD.code_spec
           FROM H_Visit LEFT JOIN H_Doctor HD on H_Visit.ID_Doctor = HD.ID_DOCTOR
            WHERE NOT H_Visit.ID_Doctor is NULL

-- 12.Удалите из таблицы TMP_Doc всю информацию.

DELETE FROM TMP_Doc;

-- 13.Добавьте в таблицу TMP_Doc информацию о тех сотрудниках,
-- которые не работали с пациентами в период с 12 по 17 сентября.

INSERT INTO TMP_Doc(ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec)
    SELECT DISTINCT HD.ID_DOCTOR, HD.SURNAME, HD.FIRSTNAME, HD.MIDDLE_NAME, HD.code_spec
           FROM H_Visit LEFT JOIN H_Doctor HD on H_Visit.ID_Doctor = HD.ID_DOCTOR
            WHERE NOT H_Visit.ID_Doctor is NULL AND DATE_VISIT BETWEEN '2022-09-12' AND '2022-09-17'

-- 14.Выполните тот же запрос для тех сотрудников, которые никогда не работали на визитах.

INSERT INTO TMP_Doc(ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec)
    SELECT * FROM H_Doctor WHERE ID_DOCTOR NOT IN (SELECT DISTINCT ID_DOCTOR FROM H_Visit)

-- 15. Создайте таблицу TMP_Spec со структурой, аналогичной структуре таблицы Specialty.
-- Добавьте в нее информацию по тем специальностям, которые в настоящий момент являются вакантными.

CREATE TABLE TMP_Spec
    (
     CODE_SPEC INTEGER  NOT NULL,
     Title NVARCHAR(50)
    )
;

ALTER TABLE TMP_Spec
    ADD CONSTRAINT "TMP_Spec PK" PRIMARY KEY ( Code_Spec ) ;

INSERT INTO TMP_Spec
    SELECT H_Speciality.* FROM H_Speciality LEFT JOIN H_Doctor HD on H_Speciality.CODE_SPEC = HD.code_spec WHERE ID_DOCTOR IS NULL

-- 16.Удалите данные о визитах за первую неделю.


do $$
declare
   	first_visit_date DATE;
begin
   	SELECT MIN(DATE_VISIT) AS visit_date 
	INTO first_visit_date
	FROM H_Visit;
	
	DELETE FROM H_Visit
    WHERE H_Visit.DATE_VISIT BETWEEN first_visit_date AND (select first_visit_date + INTERVAL '7 day');
end $$;

-- 17.Удалите информацию о визитах сотрудников, которые в последний день не работали с пациентами.
WITH doctors_without_visits_last_day AS (SELECT ID_DOCTOR FROM H_Doctor WHERE NOT ID_DOCTOR IN
                (SELECT DISTINCT ID_DOCTOR FROM H_Visit
                    WHERE DATE_VISIT = (SELECT MAX(DATE_VISIT) AS visit_date FROM H_Visit)))
DELETE FROM H_Visit
       WHERE ID_Doctor IN (SELECT ID_DOCTOR FROM doctors_without_visits_last_day)

-- 18.Удалите информацию об оказанных услугах сотрудников, которые в последний день не работали с пациентами
-- (можно использовать результаты работы предыдущего запроса).
WITH doctors_without_visits_last_day AS (SELECT ID_DOCTOR FROM H_Doctor WHERE NOT ID_DOCTOR IN
                (SELECT DISTINCT ID_DOCTOR FROM H_Visit
                    WHERE DATE_VISIT = (SELECT MAX(DATE_VISIT) AS visit_date FROM H_Visit)))
DELETE FROM H_Services
    WHERE CODE_SRV IN (SELECT CODE_SRV FROM H_Visit WHERE ID_Doctor IN (SELECT ID_DOCTOR FROM doctors_without_visits_last_day))

-- 19.Удалите записи из таблицы Doctor для тех сотрудников, которые никогда не работали на визитах.
-- DELETE FROM H_Doctor

DELETE FROM H_Doctor
    WHERE ID_DOCTOR NOT IN (SELECT DISTINCT ID_DOCTOR FROM H_Visit)

-- 20.Удалите из таблиц TMP_Doc и TMP_Spec всю информацию.
DELETE FROM TMP_Spec;
DELETE FROM TMP_Doc;
