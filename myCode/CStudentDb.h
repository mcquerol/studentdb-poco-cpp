#ifndef CSTUDENTDB_H
#define CSTUDENTDB_H

#include <map>
#include <memory>

#include "CStudent.h"
#include "CCourse.h"

class CStudentDb {

private:
	/*
	 * both of these maps represent the students and courses
	 */
    std::map<int,CStudent> students;
    std::map<int,std::unique_ptr<const CCourse>> courses;

public:

    /*
     * empty constructor
     */
    CStudentDb();

    /*
     * map setters and getters
     * they return the entire maps as well as allow to add values to the maps
     * by pointer and reference respectively
     */
	const std::map<int, std::unique_ptr<const CCourse>>& getCourses() const;
	const std::map<int, CStudent>& getStudents() const;

	//void setCourse(CCourse *course);
	//void setStudent(CStudent &student);

    void addCourse(unsigned int courseKey, std::unique_ptr <const CCourse> course);
    void addStudent(CStudent student);

    void setCourses(std::map<int, std::unique_ptr<const CCourse>>& courses);
    void setStudents(std::map<int,CStudent> students);



};
#endif /* CSTUDENTDB_H */
