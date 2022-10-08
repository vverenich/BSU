CREATE TABLE speciality (
	code_spes INT NOT NULL,
    title VARCHAR(255),
    PRIMARY KEY (code_spes)
);

CREATE TABLE doctor (
	ID_doctor INT NOT NULL,
    doctor_surname VARCHAR(255),
    doctor_name VARCHAR(255),
    doctor_middle_name VARCHAR(255),
    doctor_speciality_ID INT,
    PRIMARY KEY (ID_doctor),
    FOREIGN KEY (doctor_speciality_ID) REFERENCES speciality(code_spes)
);

CREATE TABLE patient (
	N_card INT NOT NULL,
    patient_surname VARCHAR(255),
    patient_name VARCHAR(255),
    patient_middle_name VARCHAR(255),
    patient_address VARCHAR(255),
    patient_phone VARCHAR(255),
    PRIMARY KEY (N_card)
);

CREATE TABLE services (
	code_srv INT NOT NULL,
    title VARCHAR(255),
    price INT,
    PRIMARY KEY (code_srv)
);


CREATE TABLE visit (
	N_visit INT NOT NULL,
    ID_doctor INT,
    ID_patient INT,
    date_visit DATE,
    ID_service INT,
    PRIMARY KEY (N_visit),
    FOREIGN KEY (ID_doctor) REFERENCES doctor(ID_doctor),
	FOREIGN KEY (ID_patient) REFERENCES patient(N_card),
    FOREIGN KEY (ID_service) REFERENCES services(code_srv)
);

