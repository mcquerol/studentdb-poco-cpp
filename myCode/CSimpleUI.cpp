#include <iostream>
#include <fstream>

#include "CSimpleUI.h"
#include "CBlockCourse.h"
#include "CWeeklyCourse.h"

#include <string>
#include <thread>
#include <mutex>
#include <Poco/DateTime.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/SocketStream.h>

using namespace std;

/*
 * constructor for the simple UI
 * takes in a studentDB object and is passed by reference
 */
CSimpleUI::CSimpleUI(CStudentDb& db) : db{db}
{
	this->course = 0;
	//this->student = 0;
}

/*
 * this is the main method that contains everything
 * the user chooses an option out of the menu then
 * a switch statement is called, each option has a certain functionality
 *
 * after the swtich statement, the data is added into a csv file which
 * when the program is executed can be generated in the project directory
 *
 * finally, test data is obtained from mnl.de:4242 and parsed into a json file
 * format
 */
void CSimpleUI::run()
{
	int choice;

	cout << "Select an option:" << endl;
	cout << "1. Add new course" << endl;
	cout << "2. List courses" << endl;
	cout << "3. Add new student" << endl;
	cout << "4. Add enrollment" << endl;
	cout << "5. Print students" << endl;
	cout << "6. Search student" << endl;
	cout << "7. Update student" << endl;
	cout << "or type 0 to terminate" << endl;

	while(1)
	{
		cin >> choice;
		if(choice == 0)
		{
			return;
		}
		else
		{
			switch(choice)
			{
				case 1:
					cout << "1. Add new course" << endl;

					unsigned int courseKey;
					//string title;
					unsigned char major;
					float creditPoints;
					int dayOfWeek;
					int startHour, startMinute, startSecond;
					int endHour, endMinute, endSecond;

					cout << "Enter Course key: ";
					cin >> courseKey;
//					cout << "Enter Module title: ";
//					cin >> title;
					cout << "Enter Major (char): ";
					cin >> major;
					cout << "Enter Credit points: ";
					cin >> creditPoints;
					cout << "Enter day of the week (0-6): ";
					cin >> dayOfWeek;
					cout << "Enter start time (h:m:s:): ";
					cin >> startHour >> startMinute >> startSecond;
					cout << "Enter end time (h:m:s:): ";
					cin >> endHour >> endMinute >> endSecond;


					this->course = new CWeeklyCourse(courseKey,"",major,creditPoints);
					this->course->setDayOfWeek((Poco::DateTime::DaysOfWeek)dayOfWeek);
					this->course->setStartTime({startHour, startMinute, startSecond});
					this->course->setEndTime({endHour, endMinute, endSecond});
					db.setCourse(this->course);

					cout << "course added!" << endl;

				break;
			case 2:
				cout << "2. List courses" << endl;

				////for (int it = 0; it <=db.getCourses().size(); it++)
				//{
					cout << "Course key: "<< this->course->getCourseKey() << endl;
					cout << "Module title: "<< this->course->getTitle() << endl;
					cout << "Major: "<< this->course->getMajor() << endl;
					cout << "Credit points: "<< this->course->getCreditPoints() << endl;
					cout << "Day of the week: "<< this->course->getDayOfWeek() << endl;
					cout << "Start time: "<< this->course->getStartTime().hour() << "." <<this->course->getStartTime().minute() << "." <<this->course->getStartTime().second() <<endl;
					cout << "End time: "<< this->course->getEndTime().hour() << "." <<this->course->getEndTime().minute() << "." <<this->course->getEndTime().second() << endl;
				//}

				break;
//			case 3:
//				cout << "3. Add new student" << endl;
//
//				string firstname;
//				string lastname;
//				int year,month,day;
//				string street;
//				int postalcode;
//				string cityname;
//				string additionalinfo;
//
//				cout << "Enter first name: ";
//				cin >> firstname;
//				cout << "Enter last name: ";
//				cin >> lastname;
//				cout << "Enter date of birth (y:m:d): ";
//				cin >> year >> month >> day;
//				cout << "Enter street: ";
//				cin >> street;
//				cout << "Enter postal code: ";
//				cin >> postalcode;
//				cout << "Enter city name: ";
//				cin >> cityname;
//				cout << "Enter additional info: ";
//				cin >> additionalinfo;
//
//				this->student = new CStudent(firstname, lastname, {year,month,day}, street, postalcode, cityname, additionalinfo);
//				db.setStudent(this->student);
//				break;
//			case 4:
//				cout << "4. Add enrollment" << endl;
//				break;
//			case 5:
//				cout << "5. Print student" << endl;
//				break;
//			case 6:
//				cout << "6. Search student" << endl;
//
//				int matrikelnumber;
//				cin >> matrikelnumber;
//				cout << "enter matrikel number:" << endl;
//
//
//				cout << "Matrikel number: "<< this->student.getMatrikelNumber() << endl;
//				cout << "first name: "<< this->student.getFirstName() << endl;
//				cout << "last name: "<< this->student.getLastName() << endl;
//				cout << "date of birth: "<< this->student.getDateOfBirth().day() << "." << this->student.getDateOfBirth().month() << "." <<this->student.getDateOfBirth().year() << endl;
//				cout << "street: "<< this->student.address.getStreet() << endl;
//				cout << "postal code: "<< this->student.address.getPostalCode() << endl;
//				cout << "additional info" << this->student.address.getAdditionalInfo() << endl;
//
//				break;
//			case 7:
//				cout << "7. Update student" << endl;
//				break;
			}
		}
	}

	/* 3.2 - persisting the database*/
	/*
	 * the following lines of code write data to data.csv
	 * with the course, student and enrollment data.
	 * This file is located in the project directory
	 */

    std::ofstream csvFile;
    try
    {
    	csvFile.open("data.csv");
    }
    catch(std::exception const& e){
        cout << "There was an error: " << e.what() << endl;
    }

    csvFile << db.getCourses().size() << "\n";
	//for (int it = 0; it <=db.getCourses().size(); it++)
	//{
		csvFile << this->course->getCourseKey() << ";";
		csvFile << this->course->getTitle() << ";";
		csvFile << this->course->getMajor() << ";";
		csvFile << this->course->getCreditPoints() << ";";
		csvFile << this->course->getDayOfWeek() << ";";
		csvFile << this->course->getStartTime().hour() << "." <<this->course->getStartTime().minute() << "." <<this->course->getStartTime().second() <<";";
		csvFile << this->course->getEndTime().hour() << "." <<this->course->getEndTime().minute() << "." <<this->course->getEndTime().second() << ";";
		csvFile << "\n";
	//}

	csvFile << db.getStudents().size() << "\n";
//	for (int it = 0; it <=db.getCourses().size(); it++)
//	{
//		csvFile << this->student.getMatrikelNumber() << ";";
//		csvFile << this->student.getFirstName() << ";";
//		csvFile << this->student.getLastName() << ";";
//		csvFile << this->student.getDateOfBirth().day() << "." << this->student.getDateOfBirth().month() << "." <<this->student.getDateOfBirth().year() << ";";
//		csvFile << this->student.address.getStreet() << ";";
//		csvFile << this->student.address.getPostalCode() << ";";
//		csvFile << this->student.address.getAdditionalInfo() << ";";
//		csvFile << "\n";
//	}

    csvFile.close();

    cout << "write to csv file successful!";


    /* 3.3 - obtaining test data */
	/*
	 * the following lines of code connect to the server and gather data
	 * to put it into a json file format
	 */

	//	mutex consoleLock;
	//
	//		while (true) {
	//			Poco::Net::SocketStream streamToClient(connectionToClient);// does not work
	//
	//			streamToClient << "Hello!\r\n";
	//			streamToClient.flush();
	//
	//			string command;
	//			std::getline(streamToClient, command);
	//		}
}
