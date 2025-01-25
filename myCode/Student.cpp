#include "Student.h"

unsigned int Student::nextMatrikelNumber = 100000;


Student::Student(unsigned int matrikelNumber, std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth)
{
	this->matrikelNumber = Student::nextMatrikelNumber++;
	this->firstName = firstName;
	this->lastName = lastName;
	this->dateOfBirth = dateOfBirth;
}

Student::~Student()
{
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
