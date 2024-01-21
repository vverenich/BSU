INSERT INTO KNIGA VALUES(1,'Дюна','Герберт',268,'Аст', 'Фантастика');
INSERT INTO KNIGA VALUES(2,'Ингвар и Ольха', 'Никитин', 168, 'Аст', 'Роман');
INSERT INTO KNIGA VALUES(3,'Гибель Богов','Перумов',345,'Аст', 'Фантастика');
INSERT INTO KNIGA VALUES(4,'Мифы','Асприн',266,'Аст','Детектив');
INSERT INTO KNIGA VALUES(5,'Казаки','Толстой',5568,'Нова','Роман');
INSERT INTO KNIGA VALUES(6,'Еретики Дюны', 'Герберт', 368, 'Аст', 'Фантастика');
INSERT INTO KNIGA VALUES(7,'Князь Рус','Никитин',1168,'Аст', 'Роман');
INSERT INTO KNIGA VALUES(8,'Страсть','Перумов',1385,'Аст', 'Детектив');
INSERT INTO KNIGA VALUES(9,'Мифотолкование', 'Асприн', 2265, 'Нова', 'Детектив');
INSERT INTO KNIGA VALUES(10,'Война и мир', 'Толстой', 4588, 'Нова', 'Роман');
INSERT INTO KNIGA VALUES(11,'Еретики Дюны', 'Герберт', 2668, 'Нова', 'Фантастика');
INSERT INTO KNIGA VALUES(12,'Владимир','Никитин',568,'Аст', 'Детектив');
INSERT INTO KNIGA VALUES(13,'Гибель Титана', 'Кристи', 2345, 'Аст', 'Роман');

INSERT INTO EMP VALUES (7839,'KING','PRESIDENT',NULL,'17.11.1981',5000,NULL,10);
INSERT INTO EMP VALUES (7698,'BLAKE','MANAGER',7839,'1.05.1981',2850,NULL,30);
INSERT INTO EMP VALUES (7782,'CLARK','MANAGER',7839,'9.06.1981',2450,NULL,10);
INSERT INTO EMP VALUES (7566,'JONES','MANAGER',7839,'2.04.1981',2975,NULL,20);
INSERT INTO EMP VALUES (7654,'MARTIN','SALESMAN',7698,'28.09.1981',1250,1400,30);
INSERT INTO EMP VALUES (7499,'ALLEN','SALESMAN',7698,'20.02.1981',1600,300,30);
INSERT INTO EMP VALUES (7844,'TURNER','SALESMAN',7698,'8.09.1981',1500,0,30);
INSERT INTO EMP VALUES (7900,'JAMES','CLERK',7698,'3.12.1981',950,NULL,30);
INSERT INTO EMP VALUES (7521,'WARD','SALESMAN',7698,'22.02.1981',1250,500,30);
INSERT INTO EMP VALUES (7902,'FORD','ANALYST',7566,'3.12.1981',3000,NULL,20);
INSERT INTO EMP VALUES (7369,'SMITH','CLERK',7902,'17.12.1980',800,NULL,20);
INSERT INTO EMP VALUES (7788,'SCOTT','ANALYST',7566,'09.12.1982',3000,NULL,20);
INSERT INTO EMP VALUES (7876,'ADAMS','CLERK',7788,'12.01.1983',1100,NULL,20);
INSERT INTO EMP VALUES (7934,'MILLER','CLERK',7782,'23.01.1982',1300,NULL,10);

INSERT INTO DEPT VALUES (10,'ACCOUNTING','NEW YORK');   
INSERT INTO DEPT VALUES (20,'RESEARCH','DALLAS');              
INSERT INTO DEPT VALUES (30,'SALES','CHICAGO');                    
INSERT INTO DEPT VALUES (40,'OPERATIONS','BOSTON');

INSERT INTO EMP VALUES (7839,'KING','PRESIDENT',NULL,'17.11.1981',5000,NULL,10);
INSERT INTO EMP VALUES (7698,'BLAKE','MANAGER',7839,'1.05.1981',2850,NULL,30);
INSERT INTO EMP VALUES (7782,'CLARK','MANAGER',7839,'9.06.1981',2450,NULL,10);
INSERT INTO EMP VALUES (7566,'JONES','MANAGER',7839,'2.04.1981',2975,NULL,20);
INSERT INTO EMP VALUES (7654,'MARTIN','SALESMAN',7698,'28.09.1981',1250,1400,30);
INSERT INTO EMP VALUES (7499,'ALLEN','SALESMAN',7698,'20.02.1981',1600,300,30);
INSERT INTO EMP VALUES (7844,'TURNER','SALESMAN',7698,'8.09.1981',1500,0,30);
INSERT INTO EMP VALUES (7900,'JAMES','CLERK',7698,'3.12.1981',950,NULL,30);
INSERT INTO EMP VALUES (7521,'WARD','SALESMAN',7698,'22.02.1981',1250,500,30);
INSERT INTO EMP VALUES (7902,'FORD','ANALYST',7566,'3.12.1981',3000,NULL,20);
INSERT INTO EMP VALUES (7369,'SMITH','CLERK',7902,'17.12.1980',800,NULL,20);
INSERT INTO EMP VALUES (7788,'SCOTT','ANALYST',7566,'09.12.1982',3000,NULL,20);
INSERT INTO EMP VALUES (7876,'ADAMS','CLERK',7788,'12.01.1983',1100,NULL,20);
INSERT INTO EMP VALUES (7934,'MILLER','CLERK',7782,'23.01.1982',1300,NULL,10);

insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (100, 'ДЮСШ ЮНОСТЬ', '220100', 'Минск',
        'ул.Кедышко,35', '641222', 4000);
insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (101, 'СШ N110', '220025', 'Минск',
        'ул.Чкалова,27', '271222', 2400);
insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (102, 'Лицей при БГУ', '220006', 'Минск',
        'ул.Маяковского,96', '250063', 1500);
insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (103, 'Гимназия N54', '220088', 'Минск',
        'ул.Захарова,58', '322244', 2600);
insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (104, 'Гимназия N111', '220107', 'Минск',
        'ул.Васнецова,10', '450044', 1500);
insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (105, 'Гимназия N199', '220037', 'Минск',
        'ул.Менделеева,14', '382233', 2000);
insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (106, 'Гимназия N1', '220101', 'Минск',
        'пр.Рокоссовского,138', '456402', 3200);
insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (107, 'ДЮСШ ДИНАМО', '210035', 'Витебск',
        'ул.Черняховского,34', '350618', 4900);
insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (108, 'СДЮШОР СПАРТАК', '210038', 'Витебск',
        'ул.Свердлова,5', '320806', 2900);
insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (109, 'СШ N2', '210001', 'Витебск',
        'ул.Кирова,16', '372463', 1000);
insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (110, 'СДЮСШ СМЕНА', '212008', 'Могилев',
        'ул.Первомайская,24', '207455', 2000);
insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (111, 'Лицей N1', '212004', 'Могилев',
        'пр.Мира,22', '240018', 1100);
insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (112, 'СДЮСШ ДИНАМО', '212024', 'Могилев',
        'ул.Космонавтов,18', '280010', 4200);
insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (113, 'ДЮСШ N1', '230004', 'Брест',
        'ул.Московская,32', '330084', 3000);
insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (114, 'Институт туризма', '230084', 'Брест',
        'пр.Строителей,28', '289604', 3000);
insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (115, 'СДЮСШ СПАРТАК', '231020', 'Гродно',
        'ул.Васнецова,56', '360001', 1100);
insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (116, 'Институт физкультуры', '231004', 'Гродно',
        'ул.Замковая,12', '385432', 3100);
insert into scust (custid, name_, zip, city, adr, phone, predoplata)
values (117, 'СДЮСШОР N1', '200004', 'Гомель',
        'ул.Металлистов,22', '254563', 1200);

 insert into sord  values(601,to_date('07.02.1995','dd.mm.yyyy'),106,to_date('10.02.1995','dd.mm.yyyy'),0);
 insert into sord  values(602,to_date('27.02.1995','dd.mm.yyyy'),102,to_date('01.03.1995','dd.mm.yyyy'),0);
 insert into sord  values(603,to_date('01.03.1995','dd.mm.yyyy'),102,to_date('02.03.1995','dd.mm.yyyy'),0);
 insert into sord  values(604,to_date('10.03.1995','dd.mm.yyyy'),106,to_date('11.03.1995','dd.mm.yyyy'),0);
 insert into sord  values(605,to_date('27.03.1995','dd.mm.yyyy'),106,to_date('29.03.1995','dd.mm.yyyy'),0);
insert into sord  values(606,to_date('17.04.1995','dd.mm.yyyy'),100,to_date('19.04.1995','dd.mm.yyyy'),0);
 insert into sord  values(607,to_date('18.04.1995','dd.mm.yyyy'),112,to_date('20.04.1995','dd.mm.yyyy'),0);
 insert into sord  values(608,to_date('25.04.1995','dd.mm.yyyy'),112,to_date('27.04.1995','dd.mm.yyyy'),0);
 insert into sord  values(609,to_date('02.05.1995','dd.mm.yyyy'),115,to_date('08.05.1995','dd.mm.yyyy'),0);
 insert into sord  values(610,to_date('07.01.1996','dd.mm.yyyy'),101,to_date('10.01.1996','dd.mm.yyyy'),0);
 insert into sord  values(611,to_date('10.01.1996','dd.mm.yyyy'),105,to_date('12.01.1996','dd.mm.yyyy'),0);
 insert into sord  values(612,to_date('15.01.1996','dd.mm.yyyy'),104,to_date('16.01.1996','dd.mm.yyyy'),0);
 insert into sord  values(613,to_date('20.02.1996','dd.mm.yyyy'),108,to_date('22.02.1996','dd.mm.yyyy'),0);
 insert into sord  values(614,to_date('25.02.1996','dd.mm.yyyy'),116,to_date('28.02.1996','dd.mm.yyyy'),0);
 insert into sord  values(615,to_date('04.03.1996','dd.mm.yyyy'),110,to_date('10.03.1996','dd.mm.yyyy'),0);
 insert into sord  values(616,to_date('12.03.1996','dd.mm.yyyy'),107,to_date('18.03.1996','dd.mm.yyyy'),0);
 insert into sord  values(617,to_date('20.03.1996','dd.mm.yyyy'),113,to_date('25.03.1996','dd.mm.yyyy'),0);
 insert into sord  values(618,to_date('27.03.1996','dd.mm.yyyy'),112,to_date('31.03.1996','dd.mm.yyyy'),0);
insert into sord  values(619,to_date('01.04.1996','dd.mm.yyyy'),103,to_date('03.04.1996','dd.mm.yyyy'),0);
 insert into sord  values(620,to_date('02.04.1996','dd.mm.yyyy'),100,to_date('04.04.1996','dd.mm.yyyy'),0);
insert into sord  values(621,to_date('04.04.1996','dd.mm.yyyy'),116,to_date('08.04.1996','dd.mm.yyyy'),0);
insert into sord  values(622,to_date('05.04.1996','dd.mm.yyyy'),117,to_date('09.04.1996','dd.mm.yyyy'),0);

insert into sitem (ordid, prodid, price, qty, summa)
values (610, 100001, 120, 10,1200);
insert into sitem (ordid, prodid, price, qty, summa)
values (611, 100050, 60, 30,1800);
insert into sitem (ordid, prodid, price, qty, summa)
values (612, 100061, 295, 1,295);
insert into sitem (ordid, prodid, price, qty, summa)
values (601, 100002, 160, 20,3200);
insert into sitem (ordid, prodid, price, qty, summa)
values (602, 100067, 486, 1,486);
insert into sitem (ordid, prodid, price, qty, summa)
values (604, 100070, 500, 2,1000);
insert into sitem (ordid, prodid, price, qty, summa)
values (604, 100069, 335, 1,335);
insert into sitem(ordid, prodid, price, qty, summa)
values (604, 100064, 300, 1,300);
insert into sitem (ordid, prodid, price, qty, summa)
values (605, 100002, 160, 20,3200);
insert into sitem (ordid, prodid, price, qty, summa)
values (606, 100004, 60, 10,600);
insert into sitem (ordid, prodid, price, qty, summa)
values (607, 100002, 160, 10,1600);
insert into sitem (ordid, prodid, price, qty, summa)
values (608, 100002, 160, 10,1600);
insert into sitem(ordid, prodid, price, qty, summa)
values (603, 100070, 500, 2,1000);
insert into sitem (ordid, prodid, price, qty, summa)
values (610, 100010, 6, 100,600);
insert into sitem (ordid, prodid, price, qty, summa)
values (610, 100064, 300, 2,600);
insert into sitem (ordid, prodid, price, qty, summa)
values (613, 100052, 60, 20,1200);
insert into sitem (ordid, prodid, price, qty, summa)
values (614, 100041, 60, 10,600);
insert into sitem (ordid, prodid, price, qty, summa)
values (614, 100040, 80, 10,800);
insert into sitem (ordid, prodid, price, qty, summa)
values (612, 100062, 340, 2,680);
insert into sitem(ordid, prodid, price, qty, summa)
values (612, 100060, 230, 1,230);
insert into sitem (ordid, prodid, price, qty, summa)
values (620, 100003, 80, 20,1600);
insert into sitem (ordid, prodid, price, qty, summa)
values (620, 100004, 60, 20,1200);
insert into sitem (ordid, prodid, price, qty, summa)
values (620, 100012, 6, 100,600);
insert into sitem (ordid, prodid, price, qty, summa)
values (613, 100050, 60, 10,600);
insert into sitem (ordid, prodid, price, qty, summa)
values (613, 100042, 50, 10,500);
insert into sitem (ordid, prodid, price, qty, summa)
values (613, 100041, 60, 10,600);
insert into sitem (ordid, prodid, price, qty, summa)
values (619, 100067, 486, 2,972);
insert into sitem (ordid, prodid, price, qty, summa)
values (617, 100071, 890, 1,890);
insert into sitem (ordid, prodid, price, qty, summa)
values (617, 100070, 500, 1,500);
insert into sitem (ordid, prodid, price, qty, summa)
values (614, 100066, 330, 2,660);
insert into sitem (ordid, prodid, price, qty, summa)
values (616, 100007, 50, 10,500);
insert into sitem (ordid, prodid, price, qty, summa)
values (616, 100004, 60, 20,1200);
insert into sitem (ordid, prodid, price, qty, summa)
values (616, 100012, 6, 100,600);
insert into sitem (ordid, prodid, price, qty, summa)
values (616, 100013, 6, 100,600);
insert into sitem (ordid, prodid, price, qty, summa)
values (616, 100020, 400, 5,2000);
insert into sitem (ordid, prodid, price, qty, summa)
values (619, 100064, 300, 4,1200);
insert into sitem (ordid, prodid, price, qty, summa)
values (619, 100065, 350, 1,350);
insert into sitem (ordid, prodid, price, qty, summa)
values (615, 100030, 60, 4,240);
insert into sitem (ordid, prodid, price, qty, summa)
values (618, 100005, 100, 10,1000);
insert into sitem (ordid, prodid, price, qty, summa)
values (615, 100021, 300, 5,1500);
insert into sitem (ordid, prodid, price, qty, summa)
values (617, 100002, 160, 10,1600);
insert into sitem (ordid, prodid, price, qty, summa)
values (621, 100007, 50, 20,1000);
insert into sitem (ordid, prodid, price, qty, summa)
values (609, 100007, 50, 10,500);
insert into sitem (ordid, prodid, price, qty, summa)
values (609, 100012, 6, 100, 600);
insert into sitem (ordid, prodid, price, qty, summa)
values (622, 100041, 60, 10, 600);
insert into sitem (ordid, prodid, price, qty, summa)
values (622, 100050, 60, 10, 600);      


insert into sprod (prodid,  descrip, price,p_qty)
values (100001,'Теннисная ракетка SPALDING',120,1000);
insert into sprod (prodid,  descrip, price,p_qty)
values (100002,'Теннисная ракетка PRINCE',160,1000);
insert into sprod (prodid,  descrip, price,p_qty)
values (100003,'Теннисная ракетка MAJOR',80,1000);
insert into sprod (prodid,  descrip, price,p_qty)
values (100004,'Теннисная ракетка PANTERA',60,1000);
insert into sprod (prodid,  descrip, price,p_qty)
values (100005,'Теннисная ракетка SHIRMA',100,1000);
insert into sprod (prodid,  descrip, price,p_qty)
values (100006,'Теннисная ракетка VALMIERA',40,1000);
insert into sprod (prodid,  descrip, price,p_qty)
values (100007,'Теннисная ракетка IDOL',50,1000);
insert into sprod (prodid,  descrip, price,p_qty)
values (100010,'Набор теннисных мячей SPALDING 1',6,100);
insert into sprod (prodid,  descrip, price,p_qty)
values (100011,'Набор теннисных мячей SPALDING 2',7,100);
insert into sprod (prodid,  descrip, price,p_qty)
values (100012,'Набор теннисных мячей PRINCE 1',6,100);
insert into sprod (prodid,  descrip, price,p_qty)
values (100013,'Набор теннисных мячей PRINCE 2',6,0);
insert into sprod (prodid,  descrip, price,p_qty)
values (100014,'Набор теннисных мячей PENN',5,100);
insert into sprod (prodid,  descrip, price,p_qty)
values (100015,'Набор теннисных мячей NOVA',5,100);
insert into sprod (prodid,  descrip, price,p_qty)
values (100016,'Набор теннисных мячей LENINGRAD',2,100);
insert into sprod (prodid,  descrip, price,p_qty)
values (100017,'Набор теннисных мячей TIGER',6,100);
insert into sprod (prodid,  descrip, price,p_qty)
values (100020,'Чехол для тенниса REEBOK',400,100);
insert into sprod (prodid,  descrip, price,p_qty)
values (100021,'Чехол для тенниса TENNIS',300,100);
insert into sprod (prodid,  descrip, price,p_qty)
values (100030,'Сетка для тенниса',60,100);
insert into sprod (prodid,  descrip, price,p_qty)
values (100040,'Кроссовки REEBOK',80,10);
insert into sprod (prodid,  descrip, price,p_qty)
values (100041,'Кроссовки ADIDAS',60,100);
insert into sprod (prodid,  descrip, price,p_qty)
values (100042,'Кроссовки PUMA',50,100);
insert into sprod (prodid,  descrip, price,p_qty)
values (100043,'Кроссовки HEADE',70,100);
insert into sprod (prodid,  descrip, price,p_qty)
values (100050,'Костюм спортивный PUMA',60,10);
insert into sprod (prodid,  descrip, price,p_qty)
values (100051,'Костюм спортивный ADIDAS',50,100);
insert into sprod (prodid,  descrip, price,p_qty)
values (100052,'Костюм спортивный HEADE',60,100);
insert into sprod (prodid,  descrip, price,p_qty)
values (100053,'Костюм спортивный HAWAI',40,100);
insert into sprod (prodid,  descrip, price,p_qty)
values (100060,'Телевизор DAEWOO 37',230,1000);
insert into sprod (prodid,  descrip, price,p_qty)
values (100061,'Телевизор DAEWOO 51',295,1000);
insert into sprod (prodid,  descrip, price,p_qty)
values (100062,'Телевизор DAEWOO 54',340,1000);
insert into sprod (prodid,  descrip, price,p_qty)
values (100063,'Телевизор ColdStar 37',240,1000);
insert into sprod (prodid,  descrip, price,p_qty)
values (100064,'Телевизор GoldStar 51',300,1000);
insert into sprod (prodid,  descrip, price,p_qty)
values (100065,'Телевизор GoldStar 54',350,1000);
insert into sprod (prodid,  descrip, price,p_qty)
values (100066,'Телевизор SONY 37',330,1000);
insert into sprod (prodid,  descrip, price,p_qty)
values (100067,'Телевизор SONY 54',486,1000);
insert into sprod (prodid,  descrip, price,p_qty)
values (100068,'Телевизор SONY 63',650,1000);
insert into sprod (prodid,  descrip, price,p_qty)
values (100069,'Телевизор Panasonic 37',335,5);
insert into sprod (prodid,  descrip, price,p_qty)
values (100070,'Телевизор Panasonic 54',500,5);
insert into sprod (prodid,  descrip, price,p_qty)
values (100071,'Телевизор Panasonic 63',890,5);

INSERT INTO SALS VALUES ('CLERK',700,1400);
INSERT INTO SALS VALUES ('SALESMAN',1200,1500);
INSERT INTO SALS VALUES ('ANALYST',1500,3000);
INSERT INTO SALS VALUES ('MANAGER',2000,4000);
INSERT INTO SALS VALUES ('PRESIDENT',5000,9999);

insert into sklad values(nextval('seq_sklad'), 5469, 500);
insert into sklad values(nextval('seq_sklad'), 7243, 450);
insert into sklad values(nextval('seq_sklad'), 5469, 500);
insert into sklad values(nextval('seq_sklad'), 5469, 500);
insert into sklad values(nextval('seq_sklad'), 6085, 415);
insert into sklad values(nextval('seq_sklad'), 5469, 500);
insert into sklad values(nextval('seq_sklad'), 8159, 619);

insert into cr_scust values(nextval('seq_cr_scust'), 3000, 20);
insert into cr_scust values(nextval('seq_cr_scust'), 3500, 20);
insert into cr_scust values(nextval('seq_cr_scust'), 5000, 20);
insert into cr_scust values(nextval('seq_cr_scust'), 4000, 20);
