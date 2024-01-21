create database football;
use football;

create table Clubs
(
	id int primary key auto_increment,
    title varchar(100) not null,
    star int not null,
    budget int not null
); 

insert into Clubs (title, star, budget)
values ('Man City', 5, 75000), ('Chelsea', 5, 40000), ('Dinamo', 2, 1000), 
('Arsenal', 5, 35000), ('Barcelona', 5, 55000), ('Real', 5, 50000), 
('Man Un', 5, 23400), ('Roma', 4, 10000), ('Atletico', 5, 17000),  
('Valencia', 4, 25000), ('Burnley', 3, 30000), ('PSG', 5, 80000), 
('Bayern', 5, 45000), ('Inter', 5, 44000), ('Milan', 5, 60000), 
('Napoli', 5, 28000), ('Juventus', 4, 60000), ('Bate', 2, 2000), 
('Energetic', 1, 25000), ('Sevilla', 4, 29000), ('Ajax', 4, 21000); 

create table Scouts
(
	id int primary key auto_increment,
    name varchar(50) not null,
    salary int not null
); 

insert into Scouts (name, salary)
values ('Alex', 20), ('Nikita', 90), ('Kirill', 25), 
('Vlad', 70), ('Vova', 30), ('Ahmed', 80), 
('Maks', 100),  ('Leon', 53), ('Artem', 13),  
('Eugen', 66), ('Sergey', 150);


create table Players
(
	id int primary key auto_increment,
    name varchar(100) not null,
    cost int not null,
    age  int not null,
    level  int not null,
    `date` date,
    club_id int not null,
    scout_id int not null,
	FOREIGN KEY (club_id)  REFERENCES Clubs (id),
    FOREIGN KEY (scout_id)  REFERENCES Scouts (id)
); 

insert into Players (name, cost, age, level, date, club_id, scout_id)
values ("Lionel Messi",2093,18,10,STR_TO_DATE("15-5-2019", '%d-%m-%Y'),15,2),
("Cristiano Ronaldo",7897,33,1,STR_TO_DATE("10-12-2022", '%d-%m-%Y'),16,8),
("Neymar",17215,33,7,STR_TO_DATE("13-2-2018", '%d-%m-%Y'),12,10),
("Luis Suarez",10353,26,1,STR_TO_DATE("8-11-2021", '%d-%m-%Y'),18,8),
("Robert Lewandowski",17198,32,5,STR_TO_DATE("18-9-2019", '%d-%m-%Y'),15,10),
("Kylian Mbappe",1920,24,5,STR_TO_DATE("18-9-2022", '%d-%m-%Y'),15,4),
("Mohamed Salah",12313,21,3,STR_TO_DATE("6-3-2018", '%d-%m-%Y'),11,7),
("Sergio Ramos",7160,28,9,STR_TO_DATE("27-1-2021", '%d-%m-%Y'),9,10),
("Luka Modric",14563,20,4,STR_TO_DATE("11-12-2022", '%d-%m-%Y'),21,4),
("Gareth Bale",11937,31,5,STR_TO_DATE("18-7-2019", '%d-%m-%Y'),13,10),
("Antoine Griezmann",13730,18,2,STR_TO_DATE("2-6-2022", '%d-%m-%Y'),7,9),
("Harry Kane",1005,29,3,STR_TO_DATE("15-5-2020", '%d-%m-%Y'),11,2),
("Paulo Dybala",9523,17,7,STR_TO_DATE("7-2-2022", '%d-%m-%Y'),2,1),
("Kevin De Bruyne",13649,17,3,STR_TO_DATE("27-7-2022", '%d-%m-%Y'),2,6),
("Virgil van Dijk",12557,29,2,STR_TO_DATE("20-9-2022", '%d-%m-%Y'),13,9),
("Andrea Pirlo",18232,30,6,STR_TO_DATE("7-2-2021", '%d-%m-%Y'),20,2),
("Sergio Aguero",19597,28,7,STR_TO_DATE("2-4-2020", '%d-%m-%Y'),3,8),
("David de Gea",12273,30,2,STR_TO_DATE("5-3-2022", '%d-%m-%Y'),14,9),
("Raphael Varane",1270,26,10,STR_TO_DATE("21-11-2018", '%d-%m-%Y'),20,9),
("Marco Reus",9364,29,3,STR_TO_DATE("12-7-2022", '%d-%m-%Y'),4,3),
("Paul Pogba",549,32,2,STR_TO_DATE("7-4-2020", '%d-%m-%Y'),4,8),
("Thiago Alcantara",8177,34,2,STR_TO_DATE("27-12-2018", '%d-%m-%Y'),12,7),
("Raheem Sterling",8894,35,5,STR_TO_DATE("9-4-2021", '%d-%m-%Y'),3,2),
("Toni Kroos",12145,25,5,STR_TO_DATE("2-10-2020", '%d-%m-%Y'),18,2),
("Son Heung-Min",7831,29,1,STR_TO_DATE("8-3-2019", '%d-%m-%Y'),3,6),
("Romelu Lukaku",17975,30,1,STR_TO_DATE("3-10-2020", '%d-%m-%Y'),6,7),
("Isco",1101,18,1,STR_TO_DATE("12-4-2020", '%d-%m-%Y'),14,10),
("Andres Iniesta",2561,35,1,STR_TO_DATE("25-10-2021", '%d-%m-%Y'),13,2),
("Luis Figo",2372,35,10,STR_TO_DATE("3-10-2019", '%d-%m-%Y'),20,8),
("Samuel Eto'o",8997,21,1,STR_TO_DATE("15-2-2018", '%d-%m-%Y'),21,10),
("Fernando Torres",11282,26,2,STR_TO_DATE("26-11-2019", '%d-%m-%Y'),18,7),
("Gerard Pique",4020,21,1,STR_TO_DATE("9-11-2019", '%d-%m-%Y'),13,10),
("Olivier Giroud",12820,23,2,STR_TO_DATE("17-7-2021", '%d-%m-%Y'),15,7),
("Josef Martinez",9259,19,4,STR_TO_DATE("20-6-2018", '%d-%m-%Y'),17,5),
("Lorenzo Insigne",11073,27,3,STR_TO_DATE("14-9-2020", '%d-%m-%Y'),20,11),
("Harry Maguire",3910,26,4,STR_TO_DATE("21-5-2022", '%d-%m-%Y'),9,5),
("Leroy Sane",4470,28,6,STR_TO_DATE("26-12-2019", '%d-%m-%Y'),4,7),
("N'Golo Kante",10754,25,9,STR_TO_DATE("22-8-2018", '%d-%m-%Y'),4,4),
("Timo Werner",6263,18,8,STR_TO_DATE("22-10-2022", '%d-%m-%Y'),4,7),
("Marcelo",5066,26,3,STR_TO_DATE("11-4-2018", '%d-%m-%Y'),15,5),
("Karim Benzema",11935,27,1,STR_TO_DATE("6-3-2020", '%d-%m-%Y'),9,4),
("Diego Maradona",1428,18,5,STR_TO_DATE("24-11-2019", '%d-%m-%Y'),19,2),
("Zlatan Ibrahimovic",6419,30,8,STR_TO_DATE("4-10-2020", '%d-%m-%Y'),15,2),
("Ronaldinho",7075,22,5,STR_TO_DATE("17-8-2020", '%d-%m-%Y'),17,2),
("Andriy Shevchenko",5673,18,8,STR_TO_DATE("28-2-2019", '%d-%m-%Y'),20,8),
("Diego Costa",11207,22,5,STR_TO_DATE("4-2-2019", '%d-%m-%Y'),18,6),
("James Rodriguez",10027,20,5,STR_TO_DATE("9-9-2022", '%d-%m-%Y'),20,1),
("Yerry Mina",4670,17,9,STR_TO_DATE("27-1-2021", '%d-%m-%Y'),19,11),
("Radamel Falcao",5962,27,5,STR_TO_DATE("26-12-2022", '%d-%m-%Y'),7,4),
("Alexey Orlovich",3962,20,5,STR_TO_DATE("04-06-2023", '%d-%m-%Y'),1,1);

