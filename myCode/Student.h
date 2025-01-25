#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <Poco/Data/Date.h>

#include "Enrollment.h"
#include "Address.h"

class Student
{

private:

	static unsigned int nextMatrikelNumber;
	unsigned int matrikelNumber;
	std::string firstName;
	std::string lastName;
	Poco::Data::Date dateOfBirth;
	std::vector<Enrollment> enrollments;

public:

	Student(std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth);
	~Student();

	Address address;

	const Poco::Data::Date& getDateOfBirth() const;
	const std::string& getFirstName() const;
	const std::string& getLastName() const;
	unsigned int getMatrikelNumber() const;

	const std::vector<Enrollment>& getEnrollments() const;
};

#endif
