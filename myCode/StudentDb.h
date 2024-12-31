#ifndef STUDENTDB_H
#define STUDENTDB_H

#include <map>
#include <memory>

#include "Student.h"
#include "Course.h"

class StudentDb
{

private:

	std::map<int, Student> students;
	std::map<int, std::unique_ptr<const Course>> courses;

public:


};

#endif STUDENTDB_H
