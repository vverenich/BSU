-- 1. Создайте представление, содержащее данные о терапевтах.

CREATE OR REPLACE VIEW Therapists AS
SELECT *
FROM H_Doctor
WHERE code_spec = (SELECT code_spec FROM H_Speciality WHERE Title = 'Терапевт');

-- 2. Создайте представление, содержащее данные о сотрудниках, не работавших на визитах: фамилия, имя сотрудника, дата визита, специальность.

CREATE OR REPLACE VIEW Doctors_Without_Visits AS
SELECT HD.SURNAME, HD.FIRSTNAME, HS.Title
FROM H_Doctor AS HD
         LEFT JOIN H_Speciality HS on HS.CODE_SPEC = HD.code_spec
WHERE ID_DOCTOR NOT IN (SELECT DISTINCT ID_Doctor 
				FROM H_Visit 
				WHERE H_Visit.ID_Doctor IS NOT NULL);

-- 3. Создайте представление, содержащее фамилию сотрудника, специальность, количество принятых пациентов за период
-- с 15.09.22 по 19.09.22 включительно. Первый столбец назвать Sotrudnik, второй – Specialty, третий – Kol_patients.

CREATE OR REPLACE VIEW Doctors_Stats AS
SELECT HD.ID_DOCTOR,
       HD.SURNAME                               AS Sotrudnik,
       HS.Title                                 AS Specialty,
       (SELECT COUNT(*)
        FROM H_Visit
        WHERE H_Visit.DATE_VISIT BETWEEN '2022-09-15' AND '2022-09-19'
          AND H_Visit.ID_Doctor IS NOT NULL
          AND HD.ID_DOCTOR = H_Visit.ID_Doctor) AS Kol_patients
FROM H_Doctor HD
         INNER JOIN H_Speciality HS on HS.CODE_SPEC = HD.code_spec

-- 4. На основе представления из задания 3 и таблицы Services создайте представление, содержащее данные о сотрудниках,
-- обслуживающих пациентов в период с 15.09.22 по 19.09.22, которые оказывали более 2 платных услуг в день.
-- В созданном представлении число даты визита зарплаты и сумму стоимости оказанных услуг вывести в одном столбце,
-- в качестве разделителя использовать запятую.

CREATE OR REPLACE VIEW Doctors_Services_Price_Per_Day AS
SELECT HV.ID_DOCTOR, CONCAT((HV.DATE_VISIT), ',', Sum(H_Services.Price)) AS Sum_price
FROM Doctors_Stats
         INNER JOIN H_Visit HV
                    ON Doctors_Stats.ID_DOCTOR = HV.ID_Doctor
         INNER JOIN H_Services
                    ON HV.CODE_SRV = H_Services.CODE_SRV
WHERE HV.DATE_VISIT BETWEEN '2022-09-15' AND '2022-09-19'
  AND H_Services.Price > 0
GROUP BY HV.ID_Doctor, HV.DATE_VISIT
HAVING Count(HV.CODE_SRV) > 2