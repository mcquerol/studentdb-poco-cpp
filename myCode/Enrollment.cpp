#include "Enrollment.h"


Enrollment::Enrollment(float grade, std::string semester, Course *course)
{
	this->grade = grade;
	this->semester = semester;
	this->course = course;
}

Enrollment::~Enrollment()
{
}

float Enrollment::getGrade() const
{
	return grade;
}

const std::string& Enrollment::getSemester() const
{
	return semester;
}

const Course& Enrollment::getCourse() const
{
	return *course;
}
