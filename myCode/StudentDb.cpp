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

void StudentDb::setCourse(Course *course)
{
	// move a unique pointer into the courses map using the courseid as the key of the par in thte map
	courses.insert({course->getCourseKey(), std::move(std::unique_ptr<Course>(course))});
}

void StudentDb::setStudent(Student student)
{
	// add an entry to the students map: matrtikelnumber and the student object
	students.insert({student.getMatrikelNumber(), student});
}
