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
	//Given that this->db=db cannot be written, the individual elements/parameters of the passed db are assign to the db parameter.
	std::map<int, std::unique_ptr<const CCourse>> courses  = std::move(db.getCourses());
	std::map<int,CStudent> students = db.getStudents();

	this->db.setCourses(courses);
	this->db.setStudents(students);
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
	int choice; // user input
	char courseType; // create weeklycourse or blockcourse

	/* student info */
	std::string firstname;
	std::string lastname;
	int year,month,day;
	std::string street;
	int postalcode;
	std::string cityname;
	std::string additionalinfo;

	/* course info */
	unsigned int courseKey;
	std::string title;
	std::string major;
	float creditPoints;

	/* weeklyCourse info*/
	int dayOfWeek;
	int startHour, startMinute, startSecond;
	int endHour, endMinute, endSecond;

//	/* blockCourse info*/
	int startYear, startMonth, startDay;
	int endYear, endMonth, endDay;



	/* for case 6 */
	int matrikelnumber;

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

					cout << "Enter Course key: ";
					cin >> courseKey;
					cout << endl;
					cout << "Enter Module title: ";
					cin >> title;
					cout << endl;
					cout << "Enter Major (char): ";
					cin >> major;
					cout << endl;
					cout << "Enter Credit points: ";
					cin >> creditPoints;
					cout << endl;

					cout << "Create weekly course or block course (Type 'W' or 'B')? ";
					cin >> courseType;


					//TODO make a helper function which returns the character and maybe use that in the if ?

					if (courseType == 'W') {
						// Create a unique_ptr to a CWeeklyCourse instance
						std::unique_ptr<const CCourse> weeklyCourse(new CWeeklyCourse(courseKey, title, major, creditPoints));
						// Set other attributes of weeklyCourse
						weeklyCourse->setDayOfWeek((Poco::DateTime::DaysOfWeek)dayOfWeek);
						weeklyCourse->setStartTime({startHour, startMinute, startSecond});
						weeklyCourse->setEndTime({endHour, endMinute, 0});

						// Add the course to the database using std::move
						db.addCourse(courseKey, std::move(weeklyCourse));
					} else {
						// Create a unique_ptr to a CBlockCourse instance
						std::unique_ptr<const CCourse> blockCourse(new CBlockCourse(courseKey, title, major, creditPoints,
							Poco::Data::Date(startYear, startMonth, startDay), Poco::Data::Date(endYear, endMonth, endDay),
							Poco::Data::Time(startHour, startMinute, 0), Poco::Data::Time(endHour, endMinute, 0)));

						// Add the course to the database using std::move
						db.addCourse(courseKey, std::move(blockCourse));
					}

					// After adding a course to the map
					std::cout << "Map size after adding course: " << db.getCourses().size() << std::endl;
					for (const auto& pair : db.getCourses()) {
						std::cout << "Course key: " << pair.second->getCourseKey() << std::endl;
						// Print other course details
					}

					cout << "course added!" << endl;

				break;
			case 2:
				cout << "2. List courses" << endl;

				// Iterate over all courses in the database
				for (auto it = db.getCourses().begin(); it != db.getCourses().end(); ++it) {
				    const CCourse& course = *(it->second); // Dereference the unique_ptr to get the CCourse reference

				    // Print course information
				    cout << "Course key: " << course.getCourseKey() << endl;
				    cout << "Module title: " << course.getTitle() << endl;
				    cout << "Major: " << course.getMajor() << endl;
				    cout << "Credit points: " << course.getCreditPoints() << endl;
				}
//				    cout << "Day of the week: " << course.getDayOfWeek() << endl;
//				    cout << "Start time: " << course.getStartTime().hour() << "." << course.getStartTime().minute() << "." << course.getStartTime().second() << endl;
//				    cout << "End time: " << course.getEndTime().hour() << "." << course.getEndTime().minute() << "." << course.getEndTime().second() << endl;
//

			break;
			case 3:
				cout << "3. Add new student" << endl;


				cout << "Enter first name: ";
				cin >> firstname;
				cout << "Enter last name: ";
				cin >> lastname;
				cout << "Enter date of birth (y:m:d): ";
				cin >> year >> month >> day;
				cout << "Enter street: ";
				cin >> street;
				cout << "Enter postal code: ";
				cin >> postalcode;
				cout << "Enter city name: ";
				cin >> cityname;
				cout << "Enter additional info: ";
				cin >> additionalinfo;

				//CStudent student(firstname, lastname, {year,month,day}, street, postalcode, cityname, additionalinfo);

				//db.setStudent(student);

				break;
			case 4:
				cout << "4. Add enrollment" << endl;
				break;
			case 5:
				cout << "5. Print student" << endl;
				break;
			case 6:
				cout << "6. Search student" << endl;


				cout << "enter matrikel number:" << endl;
				cin >> matrikelnumber;

				//cout << "Matrikel number: "<< db.getStudents()[matrikelnumber].getMatrikelNumber() << endl;
//				cout << "first name: "<< this->student.getFirstName() << endl;
//				cout << "last name: "<< this->student.getLastName() << endl;
//				cout << "date of birth: "<< this->student.getDateOfBirth().day() << "." << this->student.getDateOfBirth().month() << "." <<this->student.getDateOfBirth().year() << endl;
//				cout << "street: "<< this->student.address.getStreet() << endl;
//				cout << "postal code: "<< this->student.address.getPostalCode() << endl;
//				cout << "additional info" << this->student.address.getAdditionalInfo() << endl;

				break;
			case 7:
				cout << "7. Update student" << endl;
				break;
			}
		}
	}

	/* 3.2 - persisting the database*/
	/*
	 * the following lines of code write data to data.csv
	 * with the course, student and enrollment data.
	 * This file is located in the project directory
	 */

//    std::ofstream csvFile;
//    try
//    {
//    	csvFile.open("data.csv");
//    }
//    catch(std::exception const& e){
//        cout << "There was an error: " << e.what() << endl;
//    }
//
//    csvFile << db.getCourses().size() << "\n";
//	for (std::map<int, std::unique_ptr<const CCourse>>::size_type it = 0; it <=db.getCourses().size(); it++)
//	{
//		csvFile << this->course->getCourseKey() << ";";
//		csvFile << this->course->getTitle() << ";";
//		csvFile << this->course->getMajor() << ";";
//		csvFile << this->course->getCreditPoints() << ";";
//		csvFile << this->course->getDayOfWeek() << ";";
//		csvFile << this->course->getStartTime().hour() << "." <<this->course->getStartTime().minute() << "." <<this->course->getStartTime().second() <<";";
//		csvFile << this->course->getEndTime().hour() << "." <<this->course->getEndTime().minute() << "." <<this->course->getEndTime().second() << ";";
//		csvFile << "\n";
//	}
//
//	csvFile << db.getStudents().size() << "\n";
//	for (std::map<int, std::unique_ptr<const CCourse>>::size_type it = 0; it <=db.getCourses().size(); it++)
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
//
//    csvFile.close();
//
//    cout << "write to csv file successful!";


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
