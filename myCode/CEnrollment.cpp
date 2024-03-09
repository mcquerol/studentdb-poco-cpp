#include "CEnrollment.h"

CEnrollment::CEnrollment(std::string semester, CCourse *course) : semester{semester}, course{course}
{
	grade = 0.0; // initial grade is 0.0
}

float CEnrollment::getGrade() const
{
	return grade;
}

std::string CEnrollment::getSemester() const
{
	return semester;
}

const CCourse* CEnrollment::getCourse() const
{
	return course;
}

void CEnrollment::setGrade(float grade)
{
	this->grade = grade;
}

//TODO check why this was implemented ^^^^