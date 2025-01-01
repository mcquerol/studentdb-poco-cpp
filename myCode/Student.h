#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <Poco/Data/Date.h>
#include <vector>

#include "Enrollment.h"

class Student
{

private:

	static unsigned int nextMatikelNumber = 100000;
	unsigned int matrikelNumber;
	std::string firstName;
	std::string lastName;
	Poco::Data::Date dateOfBirth;
	std::vector<Enrollment> enrollments;

public:

	Student(unsigned int matrikelNumber, std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth, std::vector<Enrollment> enrollments);
	~Student();

	const Poco::Data::Date& getDateOfBirth() const;
	const std::vector<Enrollment>& getEnrollments() const;
	const std::string& getFirstName() const;
	const std::string& getLastName() const;
	unsigned int getMatrikelNumber() const;
};

#endif STUDENT_H
