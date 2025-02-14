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
//	string line;
//	getline(in, semester, ';');
//	getline(in, line, ';');
//	grade = (stof(line));  // Convert string to float

    std::string temp, line;

    std::cout << "Debug: Reading Enrollment line..." << std::endl;
    getline(in, line);
    std::cout << "Debug: Read line: '" << line << "'" << std::endl;

    std::istringstream iss(line);

    getline(iss, semester, ';');
    std::cout << "Debug: Semester: '" << semester << "'" << std::endl;

    getline(iss, temp, ';');
    std::cout << "Debug: Attempting to convert Grade: '" << temp << "'" << std::endl;
    grade = stof(temp);
}
