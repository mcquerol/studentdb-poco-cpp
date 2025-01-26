#include "SimpleUI.h"
#include "Course.h"
#include "WeeklyCourse.h"
#include "BlockCourse.h"
#include "Student.h"

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
	cout << endl;

	cout << "Enter W for Weeklycourse or B for Blockcourse" << endl;

	char courseChoice;
	cin >> courseChoice;

	unsigned int courseKey;
	string title;
	string major;
	float creditPoints;

	int startHour, startMinute, startSecond;
	int endHour, endMinute, endSecond;
	int startYear, startMonth, startDay;
	int endYear, endMonth, endDay;

	int dayOfWeek;

	/* Course class parameters */
	cout << "Enter Course key: ";
	cin >> courseKey;
	cout << "Enter Module title: ";
	cin >> title;
	cout << "Enter Major (char): ";
	cin >> major;
	cout << "Enter Credit points: ";
	cin >> creditPoints;

	cout << "Enter start time (h m s): ";
	cin >> startHour >> startMinute >> startSecond;
	cout << "Enter end time (h m s): ";
	cin >> endHour >> endMinute >> endSecond;

	Poco::Data::Time startTime = {startHour, startMinute, startSecond};
	Poco::Data::Time endTime = {endHour, endMinute, endSecond};


	if(courseChoice == 'B')
	{
		cout << "Enter start date (Y M D): ";
		cin >> startYear >> startMonth >> startDay;
		cout << "Enter end date (Y M D): ";
		cin >> endYear >> endMonth >> endDay;

		Poco::Data::Date startDate = {startYear, startMonth, startDay};
		Poco::Data::Date endDate = {endYear, endMonth, endDay};

		std::unique_ptr<BlockCourse> blockCourse = std::make_unique<BlockCourse>(courseKey, title, major, creditPoints);

		blockCourse->setStartDate(startDate);
		blockCourse->setEndDate(endDate);
		blockCourse->setStartTime(startTime);
		blockCourse->setEndTime(endTime);

		db->setCourse(std::move(blockCourse));
		cout << "Block course added" << endl;
	}
	else if(courseChoice == 'W')
	{
		cout << "Enter day of the week (0-6): ";
		cin >> dayOfWeek;

		std::unique_ptr<WeeklyCourse> weeklyCourse = std::make_unique<WeeklyCourse>(courseKey, title, major, creditPoints);

		weeklyCourse->setDayOfWeek((Poco::DateTime::DaysOfWeek)dayOfWeek);
		weeklyCourse->setStartTime(startTime);
		weeklyCourse->setEndTime(endTime);

		db->setCourse(std::move(weeklyCourse));
		cout << "Weekly course added" << endl;
	}

}

void SimpleUI::listCourses()
{
	cout << "-------------------------" << endl;
	cout << "2. List courses" << endl;
	cout << "-------------------------" << endl;
	cout << endl;

	for(const auto& coursePtr : db->getCourses())
	{
		//data from base class
		cout << "Course key: " << coursePtr.first << endl; // use the first iterator instead of having to use .second
		cout << "Course Title: " << coursePtr.second->getTitle() << endl;
		cout << "Course Major: " << coursePtr.second->getMajor() << endl;
		cout << "Course Credit Points: " << coursePtr.second->getCreditPoints() << endl;

		auto* blockCourse = dynamic_cast<BlockCourse*>(const_cast<Course*>(coursePtr.second.get()));
		auto* weeklyCourse = dynamic_cast<WeeklyCourse*>(const_cast<Course*>(coursePtr.second.get()));

		if(blockCourse)
		{
			cout << "Start Date: " << blockCourse->getStartDate().day() << "." << blockCourse->getStartDate().month() << "." << blockCourse->getStartDate().year() << endl;
			cout << "End Date: " << blockCourse->getEndDate().day() << "." << blockCourse->getEndDate().month() << "." << blockCourse->getEndDate().year() << endl;
			cout << "Start Time: " << blockCourse->getStartTime().second() << "." << blockCourse->getStartTime().minute() << "." << blockCourse->getStartTime().hour() << endl;
			cout << "End Time: " << blockCourse->getEndTime().second() << "." << blockCourse->getEndTime().minute() << "." << blockCourse->getEndTime().hour() << endl;
		}
		else if(weeklyCourse)
		{
			cout << "Day of the week: " << weeklyCourse->getDayOfWeek() << endl;
			cout << "Start Time: " << weeklyCourse->getStartTime().second() << "." << weeklyCourse->getStartTime().minute() << "." << weeklyCourse->getStartTime().hour() << endl;
			cout << "End Time: " << weeklyCourse->getEndTime().second() << "." << weeklyCourse->getEndTime().minute() << "." << weeklyCourse->getEndTime().hour() << endl;
		}
		else
		{
			continue;
		}
	}
}

void SimpleUI::addNewStudent()
{
	string firstName;
	string lastName;
	int year, month, day;
	Poco::Data::Date dateOfBirth(year, month, day);

	string street;
	unsigned short postalCode;
	string cityName;
	string additionalInfo;

	cout << "-------------------------" << endl;
	cout << "3. Add new student" << endl;
	cout << "-------------------------" << endl;
	cout << endl;

	cout << "Enter first name: " << endl;
	cin >> firstName;
	cout << "Enter last name: " << endl;
	cin >> lastName;
	cout << "Enter date of birth (Y M D): " << endl;
	cin >> year >> month >> day;
	cout << "Enter street" << endl;
	cin >> street;
	cout << "Enter postal code" << endl;
	cin >> postalCode;
	cout << "Enter City name: " << endl;
	cin >> cityName;
	cout << "Enter any additional info: " << endl;
	cin >> additionalInfo;

	Student student(firstName, lastName, dateOfBirth, street, postalCode, cityName, additionalInfo);
	db->setStudent(student);
}

void SimpleUI::addEnrollment()
{
	unsigned int matrikelNumber;
	float grade;
	string semester;
	unsigned int courseKey;

	cout << "-------------------------" << endl;
	cout << "4. Add enrollment" << endl;
	cout << "-------------------------" << endl;
	cout << endl;

	cout << "Enter matrikel number: " << endl;
	cin >> matrikelNumber;
	cout << "Enter grade: " << endl;
	cin >> grade;
	cout << "Enter semester: " << endl;
	cin >> semester;
	cout << "Enter course key: " << endl;
	cin >> courseKey;

	//access the enrollments but might need to create a setter for the enrollments vector
	//check if the enrollment exists when trying to make it..so yea will need a settter
	//add the course to the enrollment vector that is associated with the coursekey that is provided here

	if (db->getStudents().find(matrikelNumber) != db->getStudents().end())
	{
	    // Access the course associated with the courseKey
	    auto it = db->getCourses().find(courseKey);

	    if (it != db->getCourses().end())
	    {
	    	// Get the raw Course pointer
	    	Course* course = const_cast<Course*>(it->second.get());
	        // Call setEnrollment on the Student object
	        db->getStudents().at(matrikelNumber).setEnrollment(grade, semester, course);
	    }
	    else
	    {
	        cerr << "Course with key " << courseKey << " not found!" << endl;
	    }
	}
	else
	{
	    cerr << "Student with matrikel number " << matrikelNumber << " not found!" << endl;
	}
}

void SimpleUI::printStudent()
{

	unsigned int matrikelNumber;

	cout << "-------------------------" << endl;
	cout << "5. Print Student" << endl;
	cout << "-------------------------" << endl;
	cout << endl;

	cout << "Enter matrikel number: " << endl;
	cin >> matrikelNumber;

    cout << "Info for: " << matrikelNumber << endl;
    cout << "-------------------------" << endl;

	if (db->getStudents().find(matrikelNumber) != db->getStudents().end())
	{
	    auto it = db->getStudents().find(matrikelNumber);

	    cout << "Info for: " << matrikelNumber << endl;
	    cout << "-------------------------" << endl;

		cout << "\tfirst name: "<< it->second.getFirstName() << endl;
		cout << "\tlast name: "<< it->second.getLastName() << endl;
		cout << "\tdate of birth: "<< it->second.getDateOfBirth().day() << "." << it->second.getDateOfBirth().month() << "." << it->second.getDateOfBirth().year() << endl;
		cout << "\tstreet: "<< it->second.address.getStreet() << endl;
		cout << "\tpostal code: "<< it->second.address.getPostalCode() << endl;
		cout << "\tadditional info" << it->second.address.getAdditionalInfo() << endl;

		cout << endl;

		cout << "Enrollment info" << endl;

		for(const auto& enrollment : it->second.getEnrollments())
		{
			cout << "\tSemester: " << enrollment.getSemester() << endl;
			cout << "\tGrade: " << enrollment.getGrade() << endl;
			if (enrollment.getCourse())
			{
				cout << "Course info for: " << enrollment.getCourse().getCourseKey() << endl;
				cout << "\tTitle: " << enrollment.getCourse().getTitle() << endl;
				cout << "\tMajor: " << enrollment.getCourse().getMajor() << endl;
				cout << "\tCreditPoints: " << enrollment.getCourse().getCreditPoints() << endl;
			}
			else
			{
			    cerr << "\tNo course information available for this enrollment." << endl;
			}

		}
	}
	else
	{
	    cerr << "Student with matrikel number " << matrikelNumber << " not found!" << endl;
	}
}

void SimpleUI::searchStudent()
{
	std::string stringToSearch;

	cout << "-------------------------" << endl;
	cout << "6. Search student" << endl;
	cout << "-------------------------" << endl;
	cout << endl;

	cout << "Enter a string to search for a student: " << endl;
	cin >> stringToSearch;

	for(const auto& students : db->getStudents())
	{
		if(students.second.getFirstName().find(stringToSearch) != string::npos || students.second.getLastName().find(stringToSearch) != string::npos)
		{
			cout << "Matrikel Number: " << students.second.getMatrikelNumber() << endl;
			cout << "\tfirst name: "<< students.second.getFirstName() << endl;
			cout << "\tlast name: "<< students.second.getLastName() << endl;
			cout << endl;
		}
	}
}

void SimpleUI::updateStudent()
{
	cout << "-------------------------" << endl;
	cout << "7. Update student" << endl;
	cout << "-------------------------" << endl;
	cout << endl;
}
