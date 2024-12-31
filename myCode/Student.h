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
	Poco::Data::Date dateofBirth;
	std::vector<Enrollment> enrollments;

public:



};

#endif STUDENT_H
