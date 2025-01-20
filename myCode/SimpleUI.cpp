#include "SimpleUI.h"
#include "Course.h"
#include "WeeklyCourse.h"
#include "BlockCourse.h"

#include <iostream>

using namespace std;

SimpleUI::SimpleUI(StudentDb &db)
{
	this->db = &db;
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

	cin >> choice;

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
	cout << "-------------------------" << endl;
	cout << "1. Add new course" << endl;
	cout << "-------------------------" << endl;
	cout << "Enter W for Weeklycourse or B for Blockcourse" << endl;
	char courseChoice;
	cin >> courseChoice;


	unsigned int courseKey;
	string title;
	string major;
	float creditPoints;
	int dayOfWeek;
	int startHour, startMinute, startSecond;
	int endHour, endMinute, endSecond;

	cout << "Enter Course key: ";
	cin >> courseKey;
	cout << "Enter Module title: ";
	cin >> title;
	cout << "Enter Major (char): ";
	cin >> major;
	cout << "Enter Credit points: ";
	cin >> creditPoints;
	cout << "Enter day of the week (0-6): ";
	cin >> dayOfWeek;
	cout << "Enter start time (h m s): ";
	cin >> startHour >> startMinute >> startSecond;
	cout << "Enter end time (h m s): ";
	cin >> endHour >> endMinute >> endSecond;

	Poco::Data::Time startTime = {startHour, startMinute, startSecond};
	Poco::Data::Time endTime = {endHour, endMinute, endSecond};

	Poco::Data::Date startDate = {startYear, startMonth, startDay};
	Poco::Data::Date endDate = {endYear, endMonth, endDay};


	if(courseChoice == 'B')
	{
		std::unique_ptr<BlockCourse> blockCourse = std::make_unique<BlockCourse>(courseKey, "", major, creditPoints);
		blockCourse->setStartTime(startTime);
		blockCourse->setEndTime({endHour, endMinute, endSecond});
		blockCourse->setStartDate({startDate})
		db->setCourse(std::move(blockCourse));
	}
	else if(courseChoice == 'W')
	{
		std::unique_ptr<WeeklyCourse> weeklyCourse = std::make_unique<WeeklyCourse>(courseKey, "", major, creditPoints);
		weeklyCourse->setDayOfWeek((Poco::DateTime::DaysOfWeek)dayOfWeek);
		weeklyCourse->setStartTime({startHour, startMinute, startSecond});
		weeklyCourse->setEndTime({endHour, endMinute, endSecond});
		db->setCourse(std::move(weeklyCourse));
	}

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
