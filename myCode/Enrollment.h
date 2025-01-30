#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <string>

#include "Course.h"

class Enrollment
{

private:

	float grade;
	std::string semester;
	Course* course;

public:

	Enrollment(float grade, std::string semester, Course* course);
	~Enrollment();

	void setGrade(float grade);
	float getGrade() const;
	const std::string& getSemester() const;
	const Course& getCourse() const;

	void write(std::ostream& out) const; //write attributes to os stream
};

#endif
