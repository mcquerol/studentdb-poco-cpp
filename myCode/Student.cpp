#include "Student.h"

Student::Student(unsigned int matrikelNumber, std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth, std::vector<Enrollment> enrollments)
{
	this->matrikelNumber = matrikelNumber;
	this->firstName = firstName;
	this->lastName = lastName;
	this->dateOfBirth = dateOfBirth;
	this->enrollments = enrollments;
}

Student::~Student()
{
}

const Poco::Data::Date& Student::getDateOfBirth() const
{
	return dateOfBirth;
}

const std::vector<Enrollment>& Student::getEnrollments() const
{
	return enrollments;
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
