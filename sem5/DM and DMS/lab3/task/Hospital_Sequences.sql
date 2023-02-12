-- последовательность для генерации ключей таблицы Speciality
CREATE SEQUENCE SEQ_SPEC
  START WITH 1401
  MAXVALUE 1755;
  
-- последовательность для генерации ключей таблицы Doюctor
CREATE SEQUENCE  SEQ_DOC
  MINVALUE 1 MAXVALUE 999 INCREMENT BY 1 START WITH 11 CACHE 20 ;
  
-- последовательность для генерации ключей таблицы Services
CREATE SEQUENCE SEQ_srv
  START WITH 110
  MAXVALUE 990
  increment by 10;
  
-- последовательность для генерации ключей таблицы Patient
-- (участок 1)
CREATE SEQUENCE SEQ_Patient_1 
  START WITH 116001
  MAXVALUE 116999
  increment by 1; 
-- последовательность для генерации ключей таблицы Patient
-- (участок 2)
CREATE SEQUENCE SEQ_Patient_2
  START WITH 216001
  MAXVALUE 216999
  increment by 1;

-- последовательность для генерации ключей таблицы Visit
CREATE SEQUENCE  SEQ_Visit
  MINVALUE 1 INCREMENT BY 1 CACHE 20;

