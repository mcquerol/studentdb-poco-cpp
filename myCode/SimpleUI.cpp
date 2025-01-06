#include "SimpleUI.h"
#include <iostream>

using namespace std;

SimpleUI::SimpleUI(StudentDb &db)
{
	this->db = db;
}

void SimpleUI::run()
{

	int choice;

	cout << "Select an option:" << endl;
	cout << "1. Add new course" << endl;
	cout << "2. List courses" << endl;
	cout << "3. Add new student" << endl;
	cout << "4. Add enrollment" << endl;
	cout << "5. Print student" << endl;
	cout << "6. Search student" << endl;
	cout << "7. Update student" << endl;
	cout << "or type 0 to terminate" << endl;

	cin << choice;

	switch(choice)
	{
		case 1 :
			addNewCourse();
			break;
		case 2 :
			listCourses();
			break;
		case 3 :
			addNewStudent();
			break;
		case 4 :
			addEnrollment();
			break;
		case 5 :
			printStudent();
			break;
		case 6 :
			searchStudent();
			break;
		case 7 :
			updateStudent();
			break;
		case 0 :
			return;
	}

}

void SimpleUI::addNewCourse()
{
}

void SimpleUI::listCourses()
{
}

void SimpleUI::addNewStudent()
{
}

void SimpleUI::addEnrollment()
{
}

void SimpleUI::printStudent()
{
}

void SimpleUI::searchStudent()
{
}

void SimpleUI::updateStudent()
{
}
