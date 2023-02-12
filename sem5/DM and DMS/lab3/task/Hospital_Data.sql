-- Добавление данных Специальности
insert into H_Speciality (CODE_SPEC, Title) values(nextval('seq_spec'), 'Терапевт');
insert into H_Speciality (CODE_SPEC, Title) values(nextval('seq_spec'), 'Хирург');
insert into H_Speciality (CODE_SPEC, Title) values(nextval('seq_spec'), 'Невролог');
insert into H_Speciality (CODE_SPEC, Title) values(nextval('seq_spec'), 'Офтальмолог');
insert into H_Speciality (CODE_SPEC, Title) values(nextval('seq_spec'), 'Травмвматолог');
insert into H_Speciality (CODE_SPEC, Title) values(nextval('seq_spec'), 'Дерматовенеролог');
INSERT INTO H_SPECIALITY (CODE_SPEC, Title) VALUES(nextval('seq_spec'), 'Медсестра');
INSERT INTO H_SPECIALITY (CODE_SPEC, Title) VALUES(nextval('seq_spec'), 'Интерн');
insert into H_Speciality (CODE_SPEC, Title) values(nextval('seq_spec'), 'Кардиолог');

-- Добавление данных Врачи
INSERT INTO H_DOCTOR (ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec) VALUES(nextval('seq_doc'), 'Быков', 'Андрей', 'Евгеньевич', 1401);
INSERT INTO H_DOCTOR (ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec) VALUES(nextval('seq_doc'), 'Кисегач', 'Анастасия', 'Константиновна', 1401);
INSERT INTO H_DOCTOR (ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec) VALUES(nextval('seq_doc'), 'Купитман', 'Иван', 'Натанович', 1406);
INSERT INTO H_DOCTOR (ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec) VALUES(nextval('seq_doc'), 'Скрябина', 'Любовь', 'Михайловна', 1407);
INSERT INTO H_DOCTOR (ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec) VALUES(nextval('seq_doc'), 'Королева', 'Маргарита', 'Павловна', 1407);
INSERT INTO H_DOCTOR (ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec) VALUES(nextval('seq_doc'), 'Левин', 'Борис', 'Аркадьевич', 1404);
INSERT INTO H_DOCTOR (ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec) VALUES(nextval('seq_doc'), 'Черноус', 'Варвара', 'Николаевна', 1408);
INSERT INTO H_DOCTOR (ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec) VALUES(nextval('seq_doc'), 'Романенко', 'Глеб', 'Викторович', 1401);
INSERT INTO H_DOCTOR (ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec) VALUES(nextval('seq_doc'), 'Лобанов', 'Семен', 'Семенович', 1408);
INSERT INTO H_DOCTOR (ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec) VALUES(nextval('seq_doc'), 'Ричардс', 'Фил', NULL, 1406);
INSERT INTO H_DOCTOR (ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec) VALUES(nextval('seq_doc'), 'Ульянова', 'Полина', 'Сергеевна', 1408);
INSERT INTO H_DOCTOR (ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec) VALUES(nextval('seq_doc'), 'Корнеев', 'Максим', 'Леонидович', 1402);
INSERT INTO H_DOCTOR (ID_DOCTOR, SURNAME, FIRSTNAME, MIDDLE_NAME, code_spec) VALUES(nextval('seq_doc'), 'Калинина', 'Софья', 'Яковлевна ', 1405);

-- Добавление данных Пациенты
INSERT INTO H_PATIENT (N_CARD, SURNAME, FIRSTNAME, MIDDLE_NAME, ADDRESS, Phone) VALUES(nextval('seq_patient_1'),'Безенчук', 'Федор', 'Николаевич', 'г. Артемовск', '+375256788098');
INSERT INTO H_PATIENT (N_CARD, SURNAME, FIRSTNAME, MIDDLE_NAME, ADDRESS, Phone) VALUES(nextval('seq_patient_2'),'Берлага', 'Михаил', 'Александрович','г. Южногорск', '+375331234579');
INSERT INTO H_PATIENT (N_CARD, SURNAME, FIRSTNAME, MIDDLE_NAME, ADDRESS, Phone) VALUES(nextval('seq_patient_1'),'Грицацуева', 'Нина', 'Ивановна','г. Прокопьевск', '+375299089096');
INSERT INTO H_PATIENT (N_CARD, SURNAME, FIRSTNAME, MIDDLE_NAME, ADDRESS, Phone) VALUES(nextval('seq_patient_1'),'Паниковский', 'Самюэль','Михайлович', 'г. Криворуков', '+375244777881');
INSERT INTO H_PATIENT (N_CARD, SURNAME, FIRSTNAME, MIDDLE_NAME, ADDRESS, Phone) VALUES(nextval('seq_patient_1'),'Христофоров', 'Эрнест', 'Ричардович','г. Бердянск', '+375991456682');
INSERT INTO H_PATIENT (N_CARD, SURNAME, FIRSTNAME, MIDDLE_NAME, ADDRESS, Phone) VALUES(nextval('seq_patient_2'),'Щукина', 'Элла', 'Аркадьевна','г. Урюпинск', '+375113451173');
INSERT INTO H_PATIENT (N_CARD, SURNAME, FIRSTNAME, MIDDLE_NAME, ADDRESS, Phone) VALUES(nextval('seq_patient_1'),'Бендер', 'Остап', 'Ибрагимович','г. Черноморск', '+375000000000');
INSERT INTO H_PATIENT (N_CARD, SURNAME, FIRSTNAME, MIDDLE_NAME, ADDRESS, Phone) VALUES(nextval('seq_patient_1'),'Балаганов', 'Александр', 'Николаевич', 'г. Черноморск', '+375444567799');
INSERT INTO H_PATIENT (N_CARD, SURNAME, FIRSTNAME, MIDDLE_NAME, ADDRESS, Phone) VALUES(nextval('seq_patient_1'),'Корейко', 'Александр', 'Иванович','г. Урюпинск', '+375337777777');
INSERT INTO H_PATIENT (N_CARD, SURNAME, FIRSTNAME, MIDDLE_NAME, ADDRESS, Phone) VALUES(nextval('seq_patient_1'),'Козлевич','Адам', 'Казимирович', 'г. Верхнехолмск', '+375172061544');
INSERT INTO H_PATIENT (N_CARD, SURNAME, FIRSTNAME, MIDDLE_NAME, ADDRESS, Phone) VALUES(nextval('seq_patient_2'),'Растопыркин ', 'Григорий', 'Феликсович','г. Урюпинск', '+375173076553');
INSERT INTO H_PATIENT (N_CARD, SURNAME, FIRSTNAME, MIDDLE_NAME, ADDRESS, Phone) VALUES(nextval('seq_patient_2'),'Рукоблудов', 'Леонид', 'Ильич', 'г. Криворуков', '+375172061544' );
INSERT INTO H_PATIENT (N_CARD, SURNAME, FIRSTNAME, MIDDLE_NAME, ADDRESS, Phone) VALUES(nextval('seq_patient_2'),'Филинов', 'Василий', 'Денисович', 'г. Артемовск', '+375552347890');
INSERT INTO H_PATIENT (N_CARD, SURNAME, FIRSTNAME, MIDDLE_NAME, ADDRESS, Phone) VALUES(nextval('seq_patient_2'),'Тугодумов', 'Василий', 'Федорович', 'г. Верхнехолмск', '+375297777777');
INSERT INTO H_PATIENT (N_CARD, SURNAME, FIRSTNAME, MIDDLE_NAME, ADDRESS, Phone) VALUES(nextval('seq_patient_2'),'Заныкин', 'Андрей', 'Данилович', 'г. Артемовск', '+375172124689');

-- Добавление данных Услуги
INSERT INTO H_SERVICES (CODE_SRV, TITLE, Price) VALUES(nextval('seq_srv'), 'Консультация', 50.00);
INSERT INTO H_SERVICES (CODE_SRV, TITLE, Price) VALUES(nextval('seq_srv'), 'Первичный осмотр', 15.30);
INSERT INTO H_SERVICES (CODE_SRV, TITLE, Price) VALUES(nextval('seq_srv'), 'Рефлексотерапия', 185.60);
INSERT INTO H_SERVICES (CODE_SRV, TITLE, Price) VALUES(nextval('seq_srv'), 'Физиолечение', 5.30);
INSERT INTO H_SERVICES (CODE_SRV, TITLE, Price) VALUES(nextval('seq_srv'), 'Курс терапевтического лечения', 47.75);
INSERT INTO H_SERVICES (CODE_SRV, TITLE, Price) VALUES(nextval('seq_srv'), 'Курс профилактического лечения', 300.00);
INSERT INTO H_SERVICES (CODE_SRV, TITLE, Price) VALUES(nextval('seq_srv'), 'Ренгеноскопия', 10.00);
INSERT INTO H_SERVICES (CODE_SRV, TITLE, Price) VALUES(nextval('seq_srv'), 'ЭКГ', 0.85);
INSERT INTO H_SERVICES (CODE_SRV, TITLE, Price) VALUES(nextval('seq_srv'), 'Компьютерная томография', 450.99);
INSERT INTO H_SERVICES (CODE_SRV, TITLE, Price) VALUES(nextval('seq_srv'), 'МРТ', 560.70);
INSERT INTO H_SERVICES (CODE_SRV, TITLE, Price) VALUES(nextval('seq_srv'), 'Анализ крови', 0.35);

-- Добавление данных Вмзиты
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'), 13, 116002, TO_DATE('12.09.22','DD.MM.RR'), 110);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'), 21, 116003, TO_DATE('12.09.22','DD.MM.RR'), 110);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'), 11, 216002, TO_DATE('12.09.22','DD.MM.RR'), 150);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'), 20, 116006, TO_DATE('13.09.22','DD.MM.RR'), 160);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'), 18, 216003, TO_DATE('13.09.22','DD.MM.RR'), 120);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'), 11, 116007, TO_DATE('14.09.22','DD.MM.RR'), 150);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'), 20, 216004, TO_DATE('15.09.22','DD.MM.RR'), 160);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'), 14, 116008, TO_DATE('19.09.22','DD.MM.RR'), 210);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'), 19, 216001, TO_DATE('19.09.22','DD.MM.RR'), 170);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'), 21, 116003, TO_DATE('19.09.22','DD.MM.RR'), 110);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'),NULL,216005, TO_DATE('20.09.22','DD.MM.RR'), 170);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'), 18, 216002, TO_DATE('21.09.22','DD.MM.RR'), 140);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'), 16, 116004, TO_DATE('21.09.22','DD.MM.RR'), 110);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'), 18, NULL,   TO_DATE('22.09.22','DD.MM.RR'), 120);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'),NULL,216001, TO_DATE('23.09.22','DD.MM.RR'), 210);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'), 22, 216007, TO_DATE('26.09.22','DD.MM.RR'), 130);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'), 21, 116003, TO_DATE('26.09.22','DD.MM.RR'), 110);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'),NULL,216001, TO_DATE('27.09.22','DD.MM.RR'), 170);
INSERT INTO H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) VALUES (nextval('SEQ_VISIT'), 22, 116008, TO_DATE('28.09.22','DD.MM.RR'), 130);
Insert into H_VISIT (N_VISIT,ID_DOCTOR,ID_PATIENT,DATE_VISIT,CODE_SRV) values (nextval('SEQ_VISIT'), 12, 116007, to_date('29.09.22','DD.MM.RR'), 200);