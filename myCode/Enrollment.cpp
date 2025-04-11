#include "Enrollment.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Enrollment::Enrollment() : grade(0), course(nullptr) {}

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
    std::string temp;

    // Read semester (string)
    getline(in, semester, ';');
    // Read grade (float)
    getline(in, temp, '\n');

    grade = std::stof(temp);
}

