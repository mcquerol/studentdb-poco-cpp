#include "Student.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

unsigned int Student::nextMatrikelNumber = 100000;

Student::Student(std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth, std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo)
: address(street, postalCode, cityName, additionalInfo)
{
	this->matrikelNumber = Student::nextMatrikelNumber++;
	this->firstName = firstName;
	this->lastName = lastName;
	this->dateOfBirth = dateOfBirth;
}

Student::~Student()
{
}

void Student::setAddress(const Address &address)
{
	this->address = address;
}

void Student::setDateOfBirth(const Poco::Data::Date &dateOfBirth)
{
	this->dateOfBirth = dateOfBirth;
}

void Student::setFirstName(const std::string &firstName)
{
	this->firstName = firstName;
}

void Student::setLastName(const std::string &lastName)
{
	this->lastName = lastName;
}

const Poco::Data::Date& Student::getDateOfBirth() const
{
	return dateOfBirth;
}

const std::string& Student::getFirstName() const
{
	return firstName;
}

const std::string& Student::getLastName() const
{
	return lastName;
}

unsigned int Student::getMatrikelNumber() const
{
	return matrikelNumber;
}

const std::vector<Enrollment>& Student::getEnrollments() const
{
	return enrollments;
}

void Student::setEnrollment(float grade, std::string semester, Course *course)
{
	enrollments.emplace_back(grade, semester, course);
}

void Student::removeEnrollment(size_t index) {
    enrollments.erase(enrollments.begin() + index);
}

void Student::clearEnrollments()
{
	enrollments.clear();
}

void Student::write(std::ostream &out) const
{
	out << matrikelNumber << ';' << lastName << ';' << firstName << ';';
	out << dateOfBirth.day() << '.' << dateOfBirth.month() << '.' << dateOfBirth.year() << ';';
	address.write(out);
}

Student::Student()
{
}

void Student::setNextMatrikelNumber(unsigned int newMatrikelNumber)
{
    Student::nextMatrikelNumber = newMatrikelNumber;
}

void Student::read(std::istream &in)
{
	string line;
	string dateOfBirthStr;
	int day, month, year;

	getline(in, line, ';');
	matrikelNumber = static_cast<unsigned int>(stoi(line));  // Convert string to unsigned int
	getline(in, line, ';');
	lastName = line;
	getline(in, line, ';');
	firstName = line;

	getline(in, dateOfBirthStr, ';');
	istringstream dateStreamStart(dateOfBirthStr);
	getline(dateStreamStart, line, '.');
	day = stoi(line);
	getline(dateStreamStart, line, '.');
	month = stoi(line);
	getline(dateStreamStart, line, '.');
	year = stoi(line);
	dateOfBirth = Poco::Data::Date(year, month, day);

	address.read(in);

}
