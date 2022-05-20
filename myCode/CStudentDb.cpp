#include "CStudentDb.h"

CStudentDb::CStudentDb()
{

}


/*
 * map setters and getters
 * they return the entire maps as well as allow to add values to the maps
 * by pointer and reference respectively
 */

const std::map<int, std::unique_ptr<const CCourse> >& CStudentDb::getCourses() const
{
	return courses;
}

const std::map<int, CStudent>& CStudentDb::getStudents() const
{
	return students;
}

/*
 * the index of the course map is the course key and using the std::move function
 * the pointer can be assigned to the course key
 */
void CStudentDb::setCourse(CCourse *course)
{
	this->courses[course->getCourseKey()] = std::move(std::unique_ptr<CCourse>(course));

}

/*
 * in this map, the student matrikel number serves as the "index"
 * and is mapped to the student object. unlike the above map this is passed by reference
 */
void CStudentDb::setStudent(CStudent &student)
{
	this->students.insert({student.getMatrikelNumber(),student});
}
