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

void StudentDb::setCourse(std::unique_ptr<Course> course)
{
    // Move the unique pointer into the courses map using the course id as the key
    courses.emplace(course->getCourseKey(), std::move(course));
}

void StudentDb::setStudent(Student student)
{
	// add an entry to the students map: matrtikelnumber and the student object
	students.emplace(student.getMatrikelNumber(), student);

}
