#include "Student.h"

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

std::vector<Enrollment>& Student::getEnrollments()
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

void Student::write(std::ostream &out) const
{
	out << matrikelNumber << ';' << firstName << ';';
	out << dateOfBirth.day() << '.' << dateOfBirth.month() << '.' << dateOfBirth.year() << ';';
	out << address.write(out);
}
