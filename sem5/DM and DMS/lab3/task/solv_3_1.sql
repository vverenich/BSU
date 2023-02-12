--HAVING:
--
--9.	Определите среднюю стоимость услуг которые оказывались не менее 3 раз в день..
SELECT AVG(PRICE) FROM 
  H_VISIT V JOIN H_SERVICES S ON (V.CODE_SRV = S.CODE_SRV)
  GROUP BY V.DATE_VISIT
  HAVING COUNT(DISTINCT V.CODE_SRV) >= 3;
  
-- проверка:  
SELECT V.DATE_VISIT, COUNT(DISTINCT V.CODE_SRV) 
FROM H_VISIT V JOIN H_SERVICES S ON (V.CODE_SRV = S.CODE_SRV)
GROUP BY V.DATE_VISIT;

SELECT AVG(PRICE) FROM
H_VISIT V JOIN H_SERVICES S ON (V.CODE_SRV = S.CODE_SRV)
where V.DATE_VISIT = TO_DATE('19.09.22');
--
--СОЕДИНЕНИЕ ПО РАВЕНСТВУ:
--
--10.	Выдать сведения о специалистах каждой специальности..
SELECT * FROM H_SPECIALITY, H_DOCTOR
  WHERE H_SPECIALITY.CODE_SPEC = H_DOCTOR.CODE_SPEC;  

--
--ЕСТЕСТВЕННОЕ:
--
--13.	Найдите  сведения о сотрудниках каждой специальности.
SELECT * FROM 
  H_SPECIALITY NATURAL JOIN H_DOCTOR;
--

--
--ВНЕШНЕЕ ОБЪЕДИНЕНИЕ:
--
--16.	ВЫДАЙТЕ СВЕДЕНИЯ О СПЕЦИАЛИСТАХ, ОБСЛУЖИВАЮЩИХ ВИЗИТЫ В ПЕРИОД С 11 ПО 15 СЕНТЯБРЯ С УКАЗАНИЕМ ИХ ИМЁН. ВЫДАЙТЕ СВЕДЕНИЯ О ВАКАНТНЫХ СПЕЦИАЛЬНОСТЯХ. КАКОЙ ВИД ВНЕШНЕГО ОБЪЕДИНЕНИЯ ВЫ ИСПОЛЬЗОВАЛИ? СОСТАВЬТЕ ЗАПРОС С ИСПОЛЬЗОВАНИЕМ ПРОТИВОПОЛОЖНОГО ВИДА СОЕДИНЕНИЯ. СОСТАВЬТЕ ЗАПРОС С ИСПОЛЬЗОВАНИЕМ ПОЛНОГО ВНЕШНЕГО СОЕДИНЕНИЯ. 
SELECT D.FIRSTNAME as Имя, D.SURNAME as Фамилия, V.DATE_VISIT FROM
  H_DOCTOR D LEFT JOIN H_VISIT V ON (D.ID_DOCTOR = V.ID_DOCTOR)
  WHERE V.DATE_VISIT BETWEEN TO_DATE('11.09.22') AND TO_DATE('15.09.22');
  
SELECT * FROM H_SPECIALITY LEFT JOIN H_DOCTOR ON H_SPECIALITY.CODE_SPEC = H_DOCTOR.CODE_SPEC
  WHERE H_DOCTOR.CODE_SPEC is NULL;
  
