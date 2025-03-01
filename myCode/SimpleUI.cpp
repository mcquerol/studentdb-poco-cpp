#include "SimpleUI.h"
#include "Course.h"
#include "WeeklyCourse.h"
#include "BlockCourse.h"
#include "Student.h"

#include <fstream>
#include <iostream>

using namespace std;

/* Error handling and input validation help functions
 *
 */
Poco::Data::Date SimpleUI::getValidatedDate(const std::string& prompt)
{
    Poco::Data::Date date; // Placeholder for the valid date

    while (true)
    {
        try
        {
            int day, month, year;
            cout << prompt; // Show the prompt to the user
            cin >> day >> month >> year;

            date = Poco::Data::Date(year, month, day); // Attempt to construct a valid date
            return date; // Return the valid date if no exception is thrown
        }
        catch (const Poco::InvalidArgumentException& ex)
        {
            cerr << "Invalid date. Please try again in the format DD MM YYYY." << endl;

            cin.clear(); // Clear input errors
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
    }
}

Poco::Data::Time SimpleUI::getValidatedTime(const std::string& prompt)
{
    Poco::Data::Time time; // Placeholder for the valid time

    while (true)
    {
        try
        {
            int hour, minute, second;
            cout << prompt; // Show the prompt to the user
            cin >> hour >> minute >> second;

            // Optional manual validation for ranges
            if (hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59)
            {
                throw Poco::InvalidArgumentException("Time values out of range.");
            }

            time = Poco::Data::Time(hour, minute, second); // Construct the valid time
            return time; // Return the valid time if no exception is thrown
        }
        catch (const Poco::InvalidArgumentException& ex)
        {
            cerr << "Invalid time. Please try again in the format HH MM SS." << endl;

            cin.clear(); // Clear input errors
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
    }
}

Poco::DateTime::DaysOfWeek SimpleUI::getValidatedDayOfWeek(const std::string& prompt)
{
	int dayOfWeek;

	while(true)
	{
		cout << prompt;
		cin >> dayOfWeek;

		if(cin.fail() || dayOfWeek < 0 || dayOfWeek > 6)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cerr << "Invalid input. Please enter a number between 0 and 6." << endl;
		}
		else
		{
			return static_cast<Poco::DateTime::DaysOfWeek>(dayOfWeek);
		}
	}
}

unsigned int SimpleUI::getValidatedUnsignedInt(const std::string& prompt, unsigned int min, unsigned int max)
{
    unsigned int value; // Variable to store the input
    while (true)
    {
        cout << prompt;
        cin >> value;

        // Check if the input was invalid or out of range
        if (cin.fail() || value < min || value > max)
        {
            cin.clear(); // Clear the error flag
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            cerr << "Invalid input. Please enter a number between " << min << " and " << max << "." << endl;
        }
        else
        {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear any trailing characters
            return value; // Valid input
        }
    }
}


float SimpleUI::getValidatedFloat(const std::string& prompt, float min, float max)
{
    float value;
    while (true)
    {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value < min || value > max)
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cerr << "Invalid input. Please enter a number between " << min << " and " << max << "." << endl;
        }
        else
        {
            return value;
        }
    }
}

std::string SimpleUI::getValidatedString(const std::string& prompt, bool allowNumbers)
{
    std::string input;

    while (true)
    {
        cout << prompt;

        // If previous input was `cin >>`, clear the buffer once
        if (cin.peek() == '\n')
        {
            cin.ignore();
        }

        std::getline(cin, input);

        if (input.empty())
        {
            cerr << "Input cannot be empty. Please try again." << endl;
            continue;
        }

        if (!allowNumbers && input.find_first_of("0123456789") != std::string::npos) {
            cerr << "Invalid input. Numbers are not allowed." << endl;
            continue;
        }

        return input;
    }
}

std::string SimpleUI::getValidatedMajor(const std::string& prompt)
{
    const auto& majorMap = Course::getMajorById(); // Access the static map
    string majorInput;
    while (true)
    {
        cout << prompt;
        getline(cin, majorInput);
        // Check user input against map values
        for (const auto& pair : majorMap)
        {
        	if(majorInput == pair.second)
        	{
        		return majorInput;
        	}
        }
        // If no match was found, print error and continue loop
    	cerr << "Invalid major. Please enter Automation, Communications, Embedded, or Power." << endl;
    }
}

unsigned short SimpleUI::getValidatedPostalCode(const std::string& prompt)
{
	unsigned short postalCode;

	while(true)
	{
        cout << prompt;
        cin >> postalCode;
		if(cin.fail() || postalCode < 0)
		{
			cin.clear();  // Clear the error flag
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
			cerr << "Invalid input. Please enter a number greater than 0 " << endl;
		}
		else
		{
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear any trailing input
			return postalCode;
		}
	}
}


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
		cout << "8. Write student db contents to csv file" << endl;
		cout << "9. Read csv contents to db" << endl;
		cout << "or type 0 to terminate" << endl;

		choice = getValidatedUnsignedInt("Enter choice: ", 0, 9);

		switch(choice)
		{
			case 1 : addNewCourse(); break;
			case 2 : listCourses(); break;
			case 3 : addNewStudent(); break;
			case 4 : addEnrollment(); break;
			case 5 : printStudent(); break;
			case 6 : searchStudent(); break;
			case 7 : updateStudent(); break;
			case 8 : writeToCsv(); break;
			case 9 : readFromCsv(); break;
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
	Poco::Data::Time startTime;
	Poco::Data::Time endTime;
	Poco::DateTime::DaysOfWeek dayOfWeek;

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

	courseKey = getValidatedUnsignedInt("Enter Course key: ", 1);
	while (db->getCourses().find(courseKey) != db->getCourses().end())
	{
	    cerr << "Course key already exists. Please enter a unique Course key." << endl;
	    courseKey = getValidatedUnsignedInt("Enter Course key: ", 1);
	}
    title = getValidatedString("Enter Module title: ");
    major = getValidatedMajor("Enter Major (Automation, Communications, Embedded, Power): ");
    creditPoints = getValidatedFloat("Enter Credit points: ", 0.0, 5.0);
	startTime = getValidatedTime("Enter start time (HH MM SS): ");
	endTime = getValidatedTime("Enter end time (HH MM SS): ");

	if(courseChoice == 'B' || courseChoice == 'b')
	{
		Poco::Data::Date startDate = getValidatedDate("Enter start date (DD MM YYYY): ");
		Poco::Data::Date endDate = getValidatedDate("Enter end date (DD MM YYYY): ");

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
		dayOfWeek = getValidatedDayOfWeek("Enter day of the week (0-6): ");

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
	string street;
	unsigned short postalCode;
	string cityName;
	string additionalInfo;

	cout << "-------------------------" << endl;
	cout << "3. Add new student" << endl;
	cout << "-------------------------" << endl;
	cout << endl;


	firstName = getValidatedString("Enter first name: ", true);
	lastName = getValidatedString("Enter last name: ", true);
	Poco::Data::Date dateOfBirth = getValidatedDate("Enter start date (DD MM YYYY): ");

	street = getValidatedString("Enter street: ");
	postalCode = getValidatedPostalCode("Enter postal code: ");
	cityName = getValidatedString("Enter City: ");
	additionalInfo = getValidatedString("Enter any additional info: ");

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

	matrikelNumber = getValidatedUnsignedInt("Enter matrikel number: ");
	courseKey = getValidatedUnsignedInt("Enter course key: ");
	grade = getValidatedFloat("Enter grade: ");
	semester = getValidatedString("Enter semester: ");


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
	    	    return e.getCourse().getCourseKey() == courseKey;
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

	matrikelNumber = getValidatedUnsignedInt("Enter matrikel number: ");

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
		cout << "\tadditional info: " << it->second.address.getAdditionalInfo() << endl;

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

	stringToSearch = getValidatedString("Enter a string to search for a student: ");

	for(const auto& students : db->getStudents())
	{
		if(students.second.getFirstName().find(stringToSearch) != string::npos || students.second.getLastName().find(stringToSearch) != string::npos)
		{
			cout << "Matrikel Number: " << students.second.getMatrikelNumber() << endl;
			cout << "\tfirst name: "<< students.second.getFirstName() << endl;
			cout << "\tlast name: "<< students.second.getLastName() << endl;
			cout << endl;
		}
		else
		{
			cerr << "No matching student containing : " << stringToSearch << endl;
		}
	}
}

void SimpleUI::updateStudent()
{
	unsigned int matrikelNumber;
	int choice;

	cout << "-------------------------" << endl;
	cout << "7. Update student" << endl;
	cout << "-------------------------" << endl;
	cout << endl;

	matrikelNumber = getValidatedUnsignedInt("Enter matrikel number: ");

	if (db->getStudents().find(matrikelNumber) != db->getStudents().end())
	{
		auto& student = db->getStudents().at(matrikelNumber);
		auto& enrollments = const_cast<vector<Enrollment>&>(db->getStudents().at(matrikelNumber).getEnrollments());

		do
		{
			cout << "What would you like to update?: " << endl;
			cout << "-------------------------" << endl;
			cout << "1. First name" << endl;
			cout << "2. Last name" << endl;
			cout << "3. Date of birth" << endl;
			cout << "4. Address" << endl;

			for (size_t i = 0; i < enrollments.size(); i++)
			{
				const auto& enrollment = enrollments[i];
				cout << (i + 5) << ". [Enrollment #" << (i + 1) << " Semester: " << enrollment.getSemester() << ", Grade: " << enrollment.getGrade() << "]" <<endl;
			}

			cout << "0. Exit" << endl;
			cout << "Enter your choice: " << endl;

			cin >> choice;
			switch(choice)
			{
			case 1:
				student.setFirstName(getValidatedString("Enter first name: "));
			break;
			case 2:
				student.setLastName(getValidatedString("Enter last name: "));
			break;
			case 3:
				student.setDateOfBirth(getValidatedDate("Enter start date (DD MM YYYY): "));
			break;
			case 4:
	            student.setAddress
				(
	                Address
					(
	                    getValidatedString("Enter street: "),
	                    getValidatedPostalCode("Enter postal code: "),
	                    getValidatedString("Enter City: "),
	                    getValidatedString("Enter any additional info: ")
	                )
	            );
	            break;
			case 0:
				cout << "Exiting update menu..." << endl;
				return; //exit
			default:
			break;
			}

		    // Dynamically handle enrollments (Choices 5 and beyond)
			if (choice >= 5 && choice < static_cast<int>(5 + enrollments.size()))
		    {
		    	size_t enrollmentIndex = choice - 5; // Calculate index for vector
				auto& selectedEnrollment = enrollments[enrollmentIndex];

				do
				{
					cout << "What would you like to do with the enrollment?" << endl;
					cout << "1. Remove enrollment" << endl;
					cout << "2. Add grade" << endl;
					cin >> choice;

					if(choice == 1)
					{
						student.removeEnrollment(enrollmentIndex);
					}
					else if (choice == 2)
					{
						selectedEnrollment.setGrade(getValidatedFloat("Enter grade: "));
					}
				    else
				    {
				        cerr << "Invalid choice. Please select 1 or 2." << endl;
				    }

				} while(choice != 1 && choice != 2);
			}
		} while (choice != 0);
	}
	else
	{
		cerr << "Student with matrikel number " << matrikelNumber << " not found!" << endl;
	}
}

void SimpleUI::writeToCsv()
{
	ofstream csvFile;
	string fileName = getValidatedString("Enter a file name: ", true);
	csvFile.open(fileName);

	if (!csvFile.is_open())
	{
	    cerr << "Error: Unable to open file '" << fileName << "'" << endl;
	    return;
	}

	db->write(csvFile);
	csvFile.close();  // Ensure file is closed properly
}

void SimpleUI::readFromCsv()
{
	ifstream csvFile;
	string fileName = getValidatedString("Enter a file name: ", true);
	csvFile.open(fileName);

	if (!csvFile.is_open())
	{
	    cerr << "Error: Unable to open file '" << fileName << "'" << endl;
	    return;
	}

	db->read(csvFile);
	csvFile.close();  // Ensure file is closed properly
}
