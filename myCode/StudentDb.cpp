#include "StudentDb.h"


StudentDb::StudentDb()
{
}

StudentDb::~StudentDb()
{
}

const std::map<int, std::unique_ptr<const Course> >& StudentDb::getCourses() const
{
	return courses;
}

const std::map<int, Student>& StudentDb::getStudents() const
{
	return students;
}
