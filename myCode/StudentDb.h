#ifndef STUDENTDB_H
#define STUDENTDB_H

#include <map>
#include <memory>

#include "Student.h"


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
	std::map<int, Student>& getStudents(); // non const getter for addenrollment

	void setCourse(std::unique_ptr<Course> course);
	void setStudent(Student student);

	void write(std::ostream& out) const; //write attributes to ostream
	void read(std::istream& in) const; //read data to instream
};

#endif
