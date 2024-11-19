#include<string.h>
 
#pragma once

enum class Gender {
	male,
	female,
};

class Person
{
private:
	const int ID;
	static int nextID;
	char* name;
	Gender gender;
	Person* father;
	Person* mother;
	void Erase();
public:
	Person(const Person& p);
	Person(const char* aname, const Gender& gen, Person* moth, Person* fath);

	const char* GetName() const;
	int GetID()const;
	Gender GetGender() const;
	int GetFatherID()const;
	int GetMotherID() const;

	Person giveBirth(const char* aname, const Gender& gen, Person* fath);
    
	void Clone(const Person& other);
	
	Person& operator = (const Person&);
	virtual ~Person();
};

