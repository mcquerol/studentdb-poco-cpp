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

	while(1)
	{
		cout << endl;
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
			case 1 : addNewCourse(); break;
			case 2 : listCourses(); break;
			case 3 : addNewStudent(); break;
			case 4 : addEnrollment(); break;
			case 5 : printStudent(); break;
			case 6 : searchStudent(); break;
			case 7 : updateStudent(); break;
			case 0 : cerr << "Program Terminated" << endl; return;
			default: cerr << "Invalid choice. Please try again." << endl;
		}
	}
}

void SimpleUI::addNewCourse()
{
	unsigned int courseKey;
	string title;
	string major;
	float creditPoints;

	int startHour, startMinute, startSecond;
	int endHour, endMinute, endSecond;
	int startYear, startMonth, startDay;
	int endYear, endMonth, endDay;

	int dayOfWeek;

	char courseChoice;

	cout << "-------------------------" << endl;
	cout << "1. Add new course" << endl;
	cout << "-------------------------" << endl;
	cout << endl;

	cout << "Enter W for Weeklycourse or B for Blockcourse" << endl;
	do
	{
		cin >> courseChoice;
	}
	while(courseChoice != 'W' && courseChoice != 'w' && courseChoice != 'B' && courseChoice != 'b');

	/* Course class parameters */
	cout << "Enter Course key: ";
	cin >> courseKey;
	cout << "Enter Module title: ";
	cin.ignore();
	getline(cin, title);
	cout << "Enter Major: ";
	cin.ignore();
	getline(cin, major);
	cout << "Enter Credit points: ";
	cin >> creditPoints;
	cout << "Enter start time (HH MM SS): ";
	cin >> startHour >> startMinute >> startSecond;
	Poco::Data::Time startTime(startHour, startMinute, startSecond);
	cout << "Enter end time (HH MM SS): ";
	cin >> endHour >> endMinute >> endSecond;
	Poco::Data::Time endTime(endHour, endMinute, endSecond););

	//TODO error handlinf for poco?


	if(courseChoice == 'B' || courseChoice == 'b')
	{
		cout << "Enter start date (DD MM YYYY): ";
		cin >> startDay >> startMonth >> startYear;
		cout << "Enter end date (DD MM YYYY): ";
		cin >> endDay >> endMonth >> endYear;

		Poco::Data::Date startDate(startYear, startMonth, startDay);
		Poco::Data::Date endDate(endYear, endMonth, endDay);

		std::unique_ptr<BlockCourse> blockCourse = std::make_unique<BlockCourse>(courseKey, title, major, creditPoints);

		blockCourse->setStartDate(startDate);
		blockCourse->setEndDate(endDate);
		blockCourse->setStartTime(startTime);
		blockCourse->setEndTime(endTime);

		db->setCourse(std::move(blockCourse));
		cout << "Block course added" << endl;
	}
	else if(courseChoice == 'W' || courseChoice == 'w')
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
	cout << endl;
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
		cout << "Title: " << coursePtr.second->getTitle() << endl;
		cout << "Major: " << coursePtr.second->getMajor() << endl;
		cout << "Credit Points: " << coursePtr.second->getCreditPoints() << endl;

		auto* blockCourse = dynamic_cast<BlockCourse*>(const_cast<Course*>(coursePtr.second.get()));
		auto* weeklyCourse = dynamic_cast<WeeklyCourse*>(const_cast<Course*>(coursePtr.second.get()));

		if(blockCourse)
		{
			cout << "Start Date: " << blockCourse->getStartDate().day() << "." << blockCourse->getStartDate().month() << "." << blockCourse->getStartDate().year() << endl;
			cout << "End Date: " << blockCourse->getEndDate().day() << "." << blockCourse->getEndDate().month() << "." << blockCourse->getEndDate().year() << endl;
			cout << "Start Time: " << blockCourse->getStartTime().hour() << "." << blockCourse->getStartTime().minute() << "." << blockCourse->getStartTime().second() << endl;
			cout << "End Time: " << blockCourse->getEndTime().hour() << "." << blockCourse->getEndTime().minute() << "." << blockCourse->getEndTime().second() << endl;
		}
		else if(weeklyCourse)
		{
			cout << "Day of the week: " << weeklyCourse->getDayOfWeek() << endl;
			cout << "Start Time: " << weeklyCourse->getStartTime().hour() << "." << weeklyCourse->getStartTime().minute() << "." << weeklyCourse->getStartTime().second() << endl;
			cout << "End Time: " << weeklyCourse->getEndTime().hour() << "." << weeklyCourse->getEndTime().minute() << "." << weeklyCourse->getEndTime().second() << endl;
		}
		cout << endl;
	}
}

void SimpleUI::addNewStudent()
{
	string firstName;
	string lastName;
	int year, month, day;

	string street;
	unsigned short postalCode;
	string cityName;
	string additionalInfo;

	cout << "-------------------------" << endl;
	cout << "3. Add new student" << endl;
	cout << "-------------------------" << endl;
	cout << endl;

	cout << "Enter first name: " << endl;
	cin.ignore();
	getline(cin, firstName);
	cout << "Enter last name: " << endl;
	cin.ignore();
	getline(cin, lastName);
	cout << "Enter date of birth (DD MM YYYY): " << endl;
	cin >> day >> month >> year;
	Poco::Data::Date dateOfBirth(year, month, day); //construct poco date object
	cout << "Enter street" << endl;
	cin.ignore();
	getline(cin, street);
	cout << "Enter postal code" << endl;
	cin >> postalCode;
	cout << "Enter City name: " << endl;
	cin.ignore();
	getline(cin, cityName);
	cout << "Enter any additional info: " << endl;
	cin.ignore();
	getline(cin, additionalInfo);

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
	cin.ignore();
	getline(cin, semester);
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
	    	auto& enrollments = db->getStudents().at(matrikelNumber).getEnrollments();

	    	auto it = std::find_if(enrollments.begin(), enrollments.end(), [&](const Enrollment& e) {
	    	    return e.getGrade() == grade &&
	    	           e.getSemester() == semester &&
	    	           e.getCourse().getCourseKey() == courseKey;
	    	});

	    	if(it != enrollments.end())
	    	{
	    		cerr << "Enrollment already exsits" << endl;
	    	}
	    	else
	    	{
	    		db->getStudents().at(matrikelNumber).setEnrollment(grade, semester, course);
	    	}
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

	cout << endl;
    cout << "Info for: " << matrikelNumber << endl;
    cout << "-------------------------" << endl;

	if (db->getStudents().find(matrikelNumber) != db->getStudents().end())
	{
	    auto it = db->getStudents().find(matrikelNumber);

		cout << "\tfirst name: "<< it->second.getFirstName() << endl;
		cout << "\tlast name: "<< it->second.getLastName() << endl;
		cout << "\tdate of birth: "<< it->second.getDateOfBirth().day() << "." << it->second.getDateOfBirth().month() << "." << it->second.getDateOfBirth().year() << endl;
		cout << "\tstreet: "<< it->second.address.getStreet() << endl;
		cout << "\tpostal code: "<< it->second.address.getPostalCode() << endl;
		cout << "\tcity name: " << it->second.address.getCityName() << endl;
		cout << "\tadditional info" << it->second.address.getAdditionalInfo() << endl;

		cout << endl;

		cout << "\tEnrollment info" << endl;

		for(const auto& enrollment : it->second.getEnrollments())
		{
			cout << "\t\tSemester: " << enrollment.getSemester() << endl;
			cout << "\t\tGrade: " << enrollment.getGrade() << endl;
			cout << "\tCourse info for: " << enrollment.getCourse().getCourseKey() << endl;
			cout << "\t\tTitle: " << enrollment.getCourse().getTitle() << endl;
			cout << "\t\tMajor: " << enrollment.getCourse().getMajor() << endl;
			cout << "\t\tCreditPoints: " << enrollment.getCourse().getCreditPoints() << endl;
		}
		cout << endl;
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
	cin.ignore();
	getline(cin, stringToSearch);

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

/*TODO change the add and remove enrollment methods
 *
 * Use references where necessary to avoid unnecessary copies.
 * Break down repetitive logic into helper functions for readability.
 * Add validation for user inputs to prevent runtime errors or bad data.
 *
 */
void SimpleUI::updateStudent()
{
	unsigned int matrikelNumber;
	int choice;

	string firstName;
	string lastName;
	int year, month, day;

	string street;
	unsigned short postalCode;
	string cityName;
	string additionalInfo;

	float grade;

	cout << "-------------------------" << endl;
	cout << "7. Update student" << endl;
	cout << "-------------------------" << endl;
	cout << endl;

	cout << "Enter matrikel number: " << endl;
	cin >> matrikelNumber;

	if (db->getStudents().find(matrikelNumber) != db->getStudents().end())
	{
		cout << "What would you like to update?: " << endl;
		cout << "-------------------------" << endl;
		cout << "1. First name" << endl;
		cout << "2. Last name" << endl;
		cout << "3. Date of birth" << endl;
		cout << "4. Address" << endl;

		auto& enrollments = db->getStudents().at(matrikelNumber).getEnrollments();
		for (size_t i = 0; i < enrollments.size(); i++)
		{
		    const auto& enrollment = enrollments[i];
		    cout << (i + 5) << ". [Enrollment #" << (i + 1) << " Semester: " << enrollment.getSemester() << ", Grade: " << enrollment.getGrade() << "]" <<endl;
		}

		cout << "0. Exit" << endl;
		cout << "Enter your choice: " << endl;

		while(1)
		{
			cin >> choice;
			switch(choice)
			{
			case 1:
				cout << "Enter first name: " << endl;
				cin.ignore();
				getline(cin, firstName);
				db->getStudents().at(matrikelNumber).setFirstName(firstName);
			break;
			case 2:
				cout << "Enter last name: " << endl;
				cin.ignore();
				getline(cin, lastName);
				db->getStudents().at(matrikelNumber).setLastName(lastName);
			break;
			case 3:
				cout << "Enter date of birth (DD MM YYYY): " << endl;
				cin >> year >> month >> day;
				Poco::Data::Date dateOfBirth(year, month, day);
				db->getStudents().at(matrikelNumber).setDateOfBirth(dateOfBirth);
			break;
			case 4:
				cout << "Enter street: " << endl;
				cin >> street;
				cin.ignore();
				getline(cin, street);
				cout << "Enter postal code:" << endl;
				cin >> postalCode;
				cout << "Enter City name: " << endl;
				cin.ignore();
				getline(cin, cityName);
				cout << "Enter any additional info: " << endl;
				cin.ignore();
				getline(cin, additionalInfo);

				db->getStudents().at(matrikelNumber).setAddress(Address(street, postalCode, cityName, additionalInfo));
			break;
			case 0: return;
			default:
				size_t enrollmentIndex = choice - 5; // Calculate index for vector
				if (enrollmentIndex < enrollments.size())
				{
					auto& selectedEnrollment = enrollments[enrollmentIndex];

					do
					{
						cout << "What would you like to do with the enrollment?" << endl;
						cout << "1. Remove enrollment" << endl;
						cout << "2. Add grade" << endl;
						cin >> choice;

						if(choice == 1)
						{
							db->getStudents().find(matrikelNumber)->second.removeEnrollment(enrollmentIndex);
						}
						else if (choice == 2)
						{
							cout << "Enter grade: " << endl;
							cin >> grade;
							selectedEnrollment.setGrade(grade);
						}
					    else
					    {
					        cerr << "Invalid choice. Please select 1 or 2." << endl;
					    }

					}while(choice != 1 && choice != 2);
				}
				else
				{
					cerr << "Invalid choice! Please select a valid enrollment." << endl;
				}
			break;
			}
		}
	}
	else
	{
		cerr << "Student with matrikel number " << matrikelNumber << " not found!" << endl;
	}
}
