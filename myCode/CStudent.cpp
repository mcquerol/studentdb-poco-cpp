#include "CStudent.h"

using namespace std;

unsigned int CStudent::nextMatrikelNumber = 100000;

CStudent::CStudent(std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth, std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo)
: address{street, postalCode, cityName, additionalInfo}
{
	this->firstName = firstName;
	this->lastName = lastName;
	this->dateOfBirth = dateOfBirth;
	this->maktrikelNumber = CStudent::nextMatrikelNumber++; //TODO check syntax here maybe remove the CStudent::
}

const unsigned int CStudent::getMatrikelNumber() const
{
	return this->maktrikelNumber;
}

const std::string& CStudent::getFirstName() const
{
	return this->firstName;
}

const std::string& CStudent::getLastName() const
{
	return this->lastName;
}
