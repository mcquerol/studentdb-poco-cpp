#include "CEnrollment.h"

CEnrollment::CEnrollment(std::string semester, CCourse *course) : course{course}
{
	this->grade = -1; //can be changed later
	this->semester = semester;
}

float CEnrollment::getGrade() const
{
	return this->grade;
}

std::string CEnrollment::getSemester() const
{
	return this->semester;
}

const CCourse* CEnrollment::getCourse() const
{
	return this->course;
}

void CEnrollment::setGrade(float grade)
{
	this->grade = grade;
}
