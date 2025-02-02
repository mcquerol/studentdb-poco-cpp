#include "Enrollment.h"
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

using namespace std;

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

void Enrollment::setGrade(float grade)
{
	this->grade = grade;
}

const std::string& Enrollment::getSemester() const
{
	return semester;
}

const Course& Enrollment::getCourse() const
{
	return *course;
}

void Enrollment::write(std::ostream &out) const
{
	out << course->getCourseKey() << ';' << semester << ';' << grade << "\n";
}

void Enrollment::read(std::istream &in)
{
	string line, temp;

	getline(in, line);  // Read full line
	istringstream iss(line);  // Create stringstream
	getline(iss, semester, ';');
	getline(iss, temp, ';');
	grade = (stof(temp));  // Convert string to unsigned int

}
