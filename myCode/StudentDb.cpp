#include "StudentDb.h"
#include <iostream>
#include <string>
#include <sstream>
#include "WeeklyCourse.h"
#include "BlockCourse.h"

using namespace std;

StudentDb::StudentDb()
{
}

StudentDb::~StudentDb()
{
}

const std::map<int, std::unique_ptr<const Course> >& StudentDb::getCourses() const
{
	return courses;
}

const std::map<int, Student>& StudentDb::getStudents() const
{
	return students;
}

std::map<int, Student>& StudentDb::getStudents()
{
	return students;
}

void StudentDb::setCourse(std::unique_ptr<Course> course)
{
    // Move the unique pointer into the courses map using the course id as the key
    courses.emplace(course->getCourseKey(), std::move(course));
}

void StudentDb::setStudent(Student student)
{
	// add an entry to the students map: matrtikelnumber and the student object
	students.emplace(student.getMatrikelNumber(), student);
}

void StudentDb::write(std::ostream &out) const
{
	//used for running count of enrollment vector size
	size_t enrollmentsSize;
	for(const auto& student: students)
	{
		enrollmentsSize+= student.second.getEnrollments().size();
	}
	//output the course count and courses info
	out << courses.size() << "\n";
	for(const auto& course: courses)
	{
		course.second->write(out);
	}
	//output the student count and student info
	out << students.size() << "\n";
	for(const auto& student: students)
	{
		student.second.write(out);
	}
	//output the enrollment count and enrollment info
	out << enrollmentsSize << "\n";
	for(const auto& student: students)
	{
		unsigned int matrikelNumber = student.second.getMatrikelNumber();
		auto& enrollments = student.second.getEnrollments();
		for(const auto& enrollment: enrollments)
		{
			out << matrikelNumber << ';';
			enrollment.write(out);
		}
	}
}

void StudentDb::read(std::istream &in)
{

	size_t courseCount, studentCount, enrollmentCount;
	unsigned int matrikelNumber, courseKey;
	string year, month, day;

	string line, temp; //strings for line and temp data

	courses.clear();
	for(auto& student: students)
	{
		student.second.clearEnrollments();
	}
	students.clear();

	in >> courseCount;
	in.ignore();

	for(size_t i = 0; i < courseCount; i++)
	{
		char courseType;
		string title, major;
		float creditPoints;
		Poco::Data::Time startTime;
		Poco::Data::Time endTime;
		Poco::Data::Date startDate;
		Poco::Data::Date endDate;
		Poco::DateTime::DaysOfWeek dayOfWeek;
		string dayOfWeekStr;
		string startTimeStr, endTimeStr, startDateStr, endDateStr;
		string hour, minute, second;

		getline(in, line);  // Read full line
		istringstream iss(line);  // Create stringstream

		getline(iss, temp, ';');
		courseType = temp[0];  // Extract first character safely

		getline(iss, temp, ';');
		courseKey = static_cast<unsigned int>(stoi(temp));  // Convert string to unsigned int
		getline(iss, title, ';');
		getline(iss, major, ';');
		getline(iss, temp, ';');
		creditPoints = stof(temp);  // Convert string to float

		if(courseType == 'W')
		{
			unique_ptr<WeeklyCourse> weeklyCourse = std::make_unique<WeeklyCourse>(courseKey, title, major, creditPoints);

			getline(iss, dayOfWeekStr, ';');
			dayOfWeek = static_cast<Poco::DateTime::DaysOfWeek>(stoi(dayOfWeekStr));

			getline(iss, startTimeStr, ';');
			getline(iss, hour, '.');
			getline(iss, minute, '.');
			getline(iss, second, '.');
			startTime = Poco::Data::Time(stoi(hour), stoi(minute), stoi(second));

			getline(iss, endTimeStr, ';');
			getline(iss, hour, '.');
			getline(iss, minute, '.');
			getline(iss, second, '.');
			endTime = Poco::Data::Time(stoi(hour), stoi(minute), stoi(second));

			weeklyCourse->setDayOfWeek(dayOfWeek);
			weeklyCourse->setStartTime(startTime);
			weeklyCourse->setEndTime(endTime);

			setCourse(std::move(weeklyCourse));
		}
		else if(courseType == 'B')
		{
			std::unique_ptr<BlockCourse> blockCourse = std::make_unique<BlockCourse>(courseKey, title, major, creditPoints);

			getline(iss, startDateStr, ';');
			getline(iss, day, '.');
			getline(iss, month, '.');
			getline(iss, year, '.');
			startDate = Poco::Data::Date(stoi(year), stoi(month), stoi(day));

			getline(iss, endDateStr, ';');
			getline(iss, day, '.');
			getline(iss, month, '.');
			getline(iss, year, '.');
			endDate = Poco::Data::Date(stoi(year), stoi(month), stoi(day));

			getline(iss, startTimeStr, ';');
			getline(iss, hour, '.');
			getline(iss, minute, '.');
			getline(iss, second, '.');
			startTime = Poco::Data::Time(stoi(hour), stoi(minute), stoi(second));

			getline(iss, endTimeStr, ';');
			getline(iss, hour, '.');
			getline(iss, minute, '.');
			getline(iss, second, '.');
			endTime = Poco::Data::Time(stoi(hour), stoi(minute), stoi(second));

			blockCourse->setStartDate(startDate);
			blockCourse->setEndDate(endDate);
			blockCourse->setStartTime(startTime);
			blockCourse->setEndTime(endTime);

			setCourse(std::move(blockCourse));
		}
	}

	in >> studentCount;
	in.ignore();
	for(size_t i = 0; i < studentCount; i++)
	{
		string firstNameStr, lastNameStr, dateOfBirthStr;
		Poco::Data::Date dateOfBirth;
		string streetStr, cityNameStr, additionalInfoStr;
		unsigned short postalCode;

		getline(in, line);  // Read full line
		istringstream iss(line);  // Create stringstream

		getline(iss, temp, ';');
		matrikelNumber = static_cast<unsigned int>(stoi(temp));  // Convert string to unsigned int
		getline(iss, lastNameStr, ';');
		getline(iss, firstNameStr, ';');

		getline(iss, dateOfBirthStr, ';');
		getline(iss, day, '.');
		getline(iss, month, '.');
		getline(iss, year, '.');
		dateOfBirth = Poco::Data::Date(stoi(year), stoi(month), stoi(day));

		getline(iss, streetStr, ';');
		getline(iss, temp, ';');
		postalCode = static_cast<unsigned short>(stoi(temp));  // Convert string to unsigned short
		getline(iss, cityNameStr, ';');
		getline(iss, additionalInfoStr, ';');

		Student student(firstNameStr, lastNameStr, dateOfBirth, streetStr, postalCode, cityNameStr, additionalInfoStr);
		setStudent(student);
	}

	in >> enrollmentCount;
	in.ignore();
	for(size_t i = 0; i < enrollmentCount; i++)
	{
		string semesterStr;
		float grade;

		getline(in, line);  // Read full line
		istringstream iss(line);  // Create stringstream

		getline(iss, temp, ';');
		matrikelNumber = static_cast<unsigned int>(stoi(temp));  // Convert string to unsigned int
		getline(iss, temp, ';');
		courseKey = static_cast<unsigned int>(stoi(temp));  // Convert string to unsigned int
		getline(iss, semesterStr, ';');
		getline(iss, temp, ';');
		grade = (stof(temp));  // Convert string to unsigned int

		if (courses.find(courseKey) == courses.end())
		{
		    cerr << "Error: Course with key " << courseKey << " not found." << std::endl;
		    continue; // Skip this enrollment
		}
		else
		{
			Course* course = const_cast<Course*>(courses.at(courseKey).get());
			students.at(matrikelNumber).setEnrollment(grade, semesterStr, course); //add enrollment to enrollment vector of student with given matriklenumber
		}
	}
}
