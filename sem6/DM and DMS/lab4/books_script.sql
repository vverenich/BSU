CREATE  TABLE  KNIGA (
	КОД_КНИГИ  NUMERIC,
	НАЗВАНИЕ VARCHAR(20)  NOT  NULL, 
	АВТОР  VARCHAR(20),
	ЦЕНА  NUMERIC, 
	ИЗДАТЕЛЬСТВО  VARCHAR(15),  
	ЖАНР  VARCHAR(15)
); 

alter table KNIGA
add constraint "kniga PK" PRIMARY KEY (КОД_КНИГИ);

CREATE TABLE EMP (
 EMPNO               NUMERIC,         --личный номер
 ENAME               VARCHAR(10),                       --имя и фамилия
 JOB                 VARCHAR(9),                              --должность
 MGR                 NUMERIC,   --номер начальника
 HIREDATE            DATE,                           --дата поступления на работу
 SAL                 NUMERIC,                    --зарплата
 COMM                NUMERIC,                --комиссионные
 DEPTNO              NUMERIC
);

alter table EMP
add constraint "EMP_PRIMARY_KEY" PRIMARY KEY (EMPNO);

ALTER TABLE EMP 
    ADD CONSTRAINT EMP_FOREIGN_KEY FOREIGN KEY 
    ( 
     DEPTNO
    ) 
    REFERENCES DEPT 
    ( 
     DEPTNO
    ) 
;

CREATE TABLE DEPT (
 DEPTNO              NUMERIC,                 --номер отдела
 DNAME               VARCHAR(14),                               --название отдела
 LOC                 VARCHAR(13)
);

alter table DEPT
add constraint "DEPT_PRIMARY_KEY" PRIMARY KEY (DEPTNO);

CREATE TABLE SCUST 
(    CUSTID NUMERIC,
     NAME_ VARCHAR(100),                               --название   
     ZIP VARCHAR(6),                                       --почтовый индекс
     CITY VARCHAR(50),                                  --город
     ADR VARCHAR(40),                                   --адрес
     PHONE VARCHAR(6),                                 --телефон
     PREDOPLATA NUMERIC
);                        --размер предоплаты

alter table SCUST
add constraint "PK_CUSTID" PRIMARY KEY (CUSTID);

CREATE TABLE SORD(
	ORDID         NUMERIC,
	ORDERDATE      DATE,
	CUSTID          NUMERIC,
	SHIPDATE         DATE,
	SUMMA         NUMERIC
);

alter table SORD
add constraint "PK_ORDERID" PRIMARY KEY (ORDID);

CREATE TABLE SITEM (
	ORDID NUMERIC, 
    PRODID NUMERIC,
    PRICE NUMERIC,
    QTY NUMERIC,
    SUMMA NUMERIC
);

CREATE TABLE SPROD (
	PRODID NUMERIC,
    DESCRIP VARCHAR(140),	--название товара
    PRICE NUMERIC,	--цена товара
    P_QTY NUMERIC
);	--количество товара

alter table SPROD
add constraint "PK_PRODID" PRIMARY KEY (PRODID);

CREATE TABLE SALS (
 JOBS               VARCHAR(12),
 MINSAL               NUMERIC,
 MAXSAL               NUMERIC
);

create table SKLAD (
	s_num numeric,
	part_num numeric,
	s_detal numeric
);

alter table SKLAD
add constraint "SKLAD PK" PRIMARY KEY (s_num);

CREATE SEQUENCE seq_sklad
START WITH 1
MAXVALUE 1000
increment by 1;

create table CR_SCUST (
	custid numeric,
	debet numeric,
	kredit numeric
);

alter table CR_SCUST
add constraint "CR_SCUST PK" PRIMARY KEY (custid);

CREATE SEQUENCE seq_cr_scust
START WITH 1
MAXVALUE 1000
increment by 1;

create table H_EMP (
	ename numeric,
	empno numeric,
	job numeric,
	deptno numeric,
	sdate date
);


create table ord_prod (
	prodid numeric,
	descrip varchar(30),
	p_qty numeric
);

alter table ord_prod
add constraint "ord_prod PK" PRIMARY KEY (prodid);


