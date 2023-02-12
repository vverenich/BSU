--СРАВНЕНИЕ БОЛЕЕ ЧЕМ ПО ОДНОМУ ЗНАЧЕНИЮ
--
--3.	Найти имена сотрудников, обслуживающих пациентов Паниковский, Щукина, Корейко.
--
--ОПЕРАТОРЫ ANY/ALL
--
--4.	 Найти сведения о номерах сотрудников, работавших 15, 20 и 24 сентября..

SELECT ID_DOCTOR FROM H_VISIT
  WHERE ID_DOCTOR = Any(
    SELECT ID_DOCTOR FROM H_VISIT
    WHERE DATE_VISIT IN (TO_DATE('15.09.22'), TO_DATE('20.09.22'), TO_DATE('24.09.22'))
  );

--	
--5.	Найти сведения о номерах сотрудников, оказывающих какие-либо услуги из тех,  которые были оказаны 12 и 13 сентября..
--
SELECT DISTINCT ID_DOCTOR FROM H_VISIT
  WHERE ID_DOCTOR = ANY(
    SELECT ID_DOCTOR FROM H_VISIT v join H_SERVICES s on v.code_srv = S.CODE_SRV
    WHERE DATE_VISIT IN (TO_DATE('12.09.22'), TO_DATE('13.09.22'))
  );
--
--ИСПОЛЬЗОВАНИЕ HAVING С ВЛОЖЕННЫМИ ПОДЗАПРОСАМИ
--
--6.	Определить в какие дни были оказаны услуги, средняя суточная стоимость  была больше общей средней стоимости всех имеющихся услуг.
--    
SELECT V.DATE_VISIT, avg(S.PRICE), COUNT(DISTINCT v.CODE_SRV) 
  FROM H_VISIT v JOIN H_SERVICES S ON V.CODE_SRV = S.CODE_SRV
  GROUP BY V.DATE_VISIT
  HAVING AVG(PRICE) > (SELECT AVG(PRICE) FROM H_SERVICES);    

-- для проверки:  
SELECT V.DATE_VISIT, AVG(S.PRICE) FROM H_VISIT V JOIN H_SERVICES S ON V.CODE_SRV = S.CODE_SRV
      GROUP BY DATE_VISIT
      ORDER BY V.DATE_VISIT;
      
--КОРРЕЛИРУЮЩИЕ ПОДЗАПРОСЫ
--
--7. Определить коды специальностей, сотрудников, оказавших услуги во время визитов с 15 по 20 сентября.
--
SELECT distinct D.CODE_SPEC FROM H_DOCTOR D,
  (SELECT d.id_doctor FROM H_DOCTOR D JOIN H_VISIT V ON D.ID_DOCTOR = V.ID_DOCTOR
            JOIN H_SERVICES S ON V.CODE_SRV = S.CODE_SRV
    WHERE V.DATE_VISIT BETWEEN TO_DATE('15.09.22') AND TO_DATE('20.09.22')) SQ
    WHERE D.ID_DOCTOR = SQ.ID_DOCTOR
    order by code_spec;
