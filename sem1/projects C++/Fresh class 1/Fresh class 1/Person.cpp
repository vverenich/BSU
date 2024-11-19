#include "Person.h"
#include<iostream>
#include<string.h>

#pragma warning (disable: 4996)
int Person::nextID = 0;

void Person::Clone(const Person& other)
{
	gender = other.gender;
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
}

Person::Person(const Person& p) :ID(++nextID)
{
	Clone(p);
}

Person::Person(const char* aname, const Gender& gen, Person* moth, Person* fath) : ID(++nextID)
{
	if (aname == NULL) {
		throw std::invalid_argument("Wrong parameter");
	}
	if (aname[0] == '\0') {
		throw std::invalid_argument("Wrong parameter(empty)");
	}
	name = new char[strlen(aname) + 1];
	strcpy(name, aname);

	if (gen == Gender::female || gen == Gender::male) {
		gender = gen;
	}
	else {
		throw std::invalid_argument("Wrong parameter");
	}

	if (ID > 2 && moth == nullptr) {
		throw std::invalid_argument("Wrong parameter(Person must have a mother)");
	}
	else if (ID > 2 && moth->gender != Gender::female) {
		throw std::invalid_argument("Wrong parameter(Gender of person's mother is female)");
	}
	else if ((ID == 1 || ID == 2) && moth != nullptr) {
		throw std::invalid_argument("Adam and Eve have not got parents");
	}
	else {
		mother = moth;
	}

	if (ID > 2 && fath->gender != Gender::male) {
		throw std::invalid_argument("Wrong parameter(Gender of person's father is male)");
	}
	else if ((ID == 1 || ID == 2) && fath != nullptr) {
		throw std::invalid_argument("Adam and Eve have not got parents");
	}
	else {
		father = fath;
	}
}

const char* Person::GetName() const
{
	return name;
}

int Person::GetID() const
{
	return ID;
}

Gender Person::GetGender() const
{
	return gender;
}

int Person::GetFatherID() const
{
	if (father != nullptr) {
		return father->ID;
	}
	else {
		throw std::runtime_error("You do not have such an opportunity");
	}
}

int Person::GetMotherID() const
{
	if (mother != nullptr) {
		return mother->ID;
	}
	else {
		throw std::runtime_error("You do not have such an opportunity");
	}
}

Person Person::giveBirth(const char* aname, const Gender& gen, Person* fath)
{
	return Person(aname, gen, this, fath);
}

void Person::Erase()
{
	delete[] name;
}

Person& Person::operator=(const Person& object)
{
	if (&object == this) {
		return *this;
	}
	Erase();
	name = new char[strlen(object.name) + 1];
	strcpy(name, object.name);

	gender = object.gender;
	mother = object.mother;
	father = object.father;

	return *this;
}

Person::~Person()
{
	Erase();
}
