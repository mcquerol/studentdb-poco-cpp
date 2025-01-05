#ifndef SIMPLEUI_H
#define SIMPLEUI_H

#include "StudentDb.h"

class SimpleUI
{

private:



public:

	SimpleUI(StudentDb& db);
	void run();

	/* Helper functions */
	void addNewCourse();
	void listCourses();
	void addNewStudent();
	void addEnrollment();
	void printStudent();
	void searchStudent();
	void updateStudent();

};

#endif
