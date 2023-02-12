1 SELECT ADDRESS FROM H_Patient WHERE (SURNAME = 'Паниковский' AND FIRSTNAME = 'Самюэль' AND MIDDLE_NAME = 'Михайлович');
2 SELECT * FROM H_Patient WHERE (ADDRESS = 'г. Урюпинск' OR ADDRESS = 'г. Черноморск');

3 SELECT * FROM H_Services WHERE Price = (SELECT MIN(Price) FROM H_Services);
4 SELECT * FROM H_Visit WHERE (DATE_VISIT <= '20-Sep-2022');
5 SELECT COUNT(*) FROM H_Doctor;
6 SELECT LOWER(FIRSTNAME) FROM H_Doctor WHERE FIRSTNAME LIKE 'А%';
7 SELECT N_Visit,ID_Doctor,ID_Patient,TO_CHAR(DATE_VISIT, 'DD-MONTH-YYYY'),CODE_SRV FROM H_Visit;
8 SELECT CODE_SPEC, CASE WHEN (Title = 'Хирург' OR Title = 'Травматолог') THEN 'Костоправ' ELSE Title END FROM H_Speciality;

9 SELECT AVG(Price) FROM H_Visit INNER JOIN H_Services ON (H_Visit.CODE_SRV = H_Services.CODE_SRV) GROUP BY DATE_VISIT HAVING COUNT(H_Visit.CODE_SRV) >= 3;
10 SELECT H_Doctor.*,H_Speciality.Title FROM H_Doctor INNER JOIN H_Speciality ON H_Doctor.CODE_SPEC = H_Speciality.CODE_SPEC;
11 SELECT h_services.code_srv, h_services.title, h_services.price FROM H_Services INNER JOIN h_visit ON h_services.code_srv = h_visit.code_srv WHERE NOT PRICE >(SELECT MIN(h_services.price) FROM H_Services) + 50 GROUP BY h_services.code_srv, h_services.title, h_services.price;
12 SELECT h_visit.n_visit, h_visit.id_doctor, h_visit.id_patient, h_visit.date_visit, h_services.title FROM H_Services INNER JOIN h_visit ON h_services.code_srv = h_visit.code_srv WHERE PRICE = (SELECT MAX(h_services.price) FROM H_Services);
13 SELECT SURNAME, FIRSTNAME, MIDDLE_NAME, TITLE FROM H_Doctor NATURAL JOIN H_Speciality;
14 SELECT N_Visit, ID_Doctor,FIRSTNAME,DATE_VISIT,CODE_SRV FROM H_Visit INNER JOIN H_PATIENT ON H_Visit.ID_Patient = H_PATIENT.N_CARD;
15 SELECT H_Visit.N_Visit, H_Doctor.FIRSTNAME, H_Patient.FIRSTNAME, H_Visit.DATE_VISIT, H_Visit.CODE_SRV FROM H_Visit,H_Patient, H_Doctor;
16 SELECT H_Doctor.ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec FROM H_Doctor left join H_Visit ON (H_Doctor.ID_DOCTOR = H_Visit.ID_Doctor) WHERE (H_Visit.DATE_VISIT >= '2022-09-11' AND H_Visit.DATE_VISIT <= '2022-09-15');
