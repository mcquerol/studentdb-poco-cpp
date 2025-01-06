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

	StudentDb();
	~StudentDb();

	const std::map<int, std::unique_ptr<const Course>>& getCourses() const;
	const std::map<int, Student>& getStudents() const;

	void setCourse(Course* course);
	void setStudent(Student student);
};

#endif
