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
	string dayOfWeekStr;
	string startTimeStr, endTimeStr, startDateStr, endDateStr;
	string hourStr, minuteStr, secondStr, yearStr, monthStr, dayStr;
	size_t courseCount, studentCount, enrollmentCount;

	courses.clear();
	for(auto& student: students)
	{
		student.second.clearEnrollments();
	}
	students.clear();

	in >> courseCount;
	in.ignore();
	string line;
	for(size_t i = 0; i < courseCount; i++)
	{
		char courseType;
		unsigned int courseKey;
		string title, major;
		float creditPoints;
		Poco::Data::Time startTime;
		Poco::Data::Time endTime;
		Poco::Data::Date startDate;
		Poco::Data::Date endDate;

		string courseLine;
		getline(in, line);  // Read full line
		istringstream courseSs(line);  // Create stringstream

		getline(courseSs, courseLine, ';');
		courseType = courseLine[0];  // Extract first character safely

		getline(courseSs, courseLine, ';');
		courseKey = static_cast<unsigned int>(stoi(courseLine));  // Convert string to unsigned int
		getline(courseSs, title, ';');
		getline(courseSs, major, ';');
		getline(courseSs, courseLine, ';');
		creditPoints = stof(courseLine);  // Convert string to float

		if(courseType == 'W')
		{
			unique_ptr<WeeklyCourse> weeklyCourse = std::make_unique<WeeklyCourse>(courseKey, title, major, creditPoints);

			Poco::DateTime::DaysOfWeek dayOfWeek;
			getline(courseSs, dayOfWeekStr, ';');
			dayOfWeek = static_cast<Poco::DateTime::DaysOfWeek>(stoi(dayOfWeekStr));

			getline(courseSs, startTimeStr, ';');
			istringstream startTimeSs(startTimeStr);
			getline(startTimeSs, hourStr, '.');
			getline(startTimeSs, minuteStr, '.');
			getline(startTimeSs, secondStr, '.');
			startTime = {stoi(hourStr),stoi(minuteStr),stoi(secondStr)};

			getline(courseSs, endTimeStr, ';');
			istringstream endTimeSs(endTimeStr);
			getline(endTimeSs, hourStr, '.');
			getline(endTimeSs, minuteStr, '.');
			getline(endTimeSs, secondStr, '.');
			endTime = {stoi(hourStr),stoi(minuteStr),stoi(secondStr)};

			weeklyCourse->setDayOfWeek(dayOfWeek);
			weeklyCourse->setStartTime(startTime);
			weeklyCourse->setEndTime(endTime);

			setCourse(std::move(weeklyCourse));
		}
		else if(courseType == 'B')
		{
			std::unique_ptr<BlockCourse> blockCourse = std::make_unique<BlockCourse>(courseKey, title, major, creditPoints);

			getline(courseSs, startDateStr, ';');
			istringstream startDateSs(startDateStr);
			getline(startDateSs, dayStr, '.');
			getline(startDateSs, monthStr, '.');
			getline(startDateSs, yearStr, '.');
			startDate = {stoi(yearStr), stoi(monthStr), stoi(dayStr)};

			getline(courseSs, endDateStr, ';');
			istringstream endDateSs(endDateStr);
			getline(endDateSs, dayStr, '.');
			getline(endDateSs, monthStr, '.');
			getline(endDateSs, yearStr, '.');
			endDate = {stoi(yearStr), stoi(monthStr), stoi(dayStr)};

			getline(courseSs, startTimeStr, ';');
			istringstream startTimeSs(startTimeStr);
			getline(startTimeSs, hourStr, '.');
			getline(startTimeSs, minuteStr, '.');
			getline(startTimeSs, secondStr, '.');
			startTime = {stoi(hourStr), stoi(minuteStr), stoi(secondStr)};

			getline(courseSs, endTimeStr, ';');
			istringstream endTimeSs(endTimeStr);
			getline(endTimeSs, hourStr, '.');
			getline(endTimeSs, minuteStr, '.');
			getline(endTimeSs, secondStr, '.');
			endTime = {stoi(hourStr), stoi(minuteStr), stoi(secondStr)};

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
		unsigned int matrikelNumber;
		string firstNameStr, lastNameStr, dateOfBirthStr;
		Poco::Data::Date dateOfBirth;
		string streetStr, cityNameStr, additionalInfoStr;
		unsigned short postalCode;

		string studentLine;
		getline(in, line);  // Read full line
		istringstream studentSs(line);  // Create stringstream

		getline(studentSs, studentLine, ';');
		matrikelNumber = static_cast<unsigned int>(stoi(studentLine));  // Convert string to unsigned int
		getline(studentSs, lastNameStr, ';');
		getline(studentSs, firstNameStr, ';');

		getline(studentSs, dateOfBirthStr, ';');
		istringstream dateOfBirthSs(dateOfBirthStr);
		getline(dateOfBirthSs, dayStr, '.');
		getline(dateOfBirthSs, monthStr, '.');
		getline(dateOfBirthSs, yearStr, '.');
		dateOfBirth = {stoi(yearStr), stoi(monthStr), stoi(dayStr)};

		getline(studentSs, streetStr, ';');
		getline(studentSs, studentLine, ';');
		postalCode = static_cast<unsigned short>(stoi(studentLine));  // Convert string to unsigned short
		getline(studentSs, cityNameStr, ';');
		getline(studentSs, additionalInfoStr, ';');

		Student student(firstNameStr, lastNameStr, dateOfBirth, streetStr, postalCode, cityNameStr, additionalInfoStr);
		setStudent(student);
	}

	in >> enrollmentCount;
	in.ignore();
	for(size_t i = 0; i < enrollmentCount; i++)
	{
		unsigned int matrikelNumber, courseKey;
		string semesterStr;
		float grade;

		string EnrollmentLine;
		getline(in, line);  // Read full line
		istringstream studentSs(line);  // Create stringstream

		getline(studentSs, EnrollmentLine, ';');
		matrikelNumber = static_cast<unsigned int>(stoi(EnrollmentLine));  // Convert string to unsigned int
		getline(studentSs, EnrollmentLine, ';');
		courseKey = static_cast<unsigned int>(stoi(EnrollmentLine));  // Convert string to unsigned int
		getline(studentSs, semesterStr, ';');
		getline(studentSs, EnrollmentLine, ';');
		grade = static_cast<unsigned int>(stof(EnrollmentLine));  // Convert string to unsigned int

		Course* course = const_cast<Course*>(courses.at(courseKey).get()); // Get the raw Course pointer of the corresponding course
		students.at(matrikelNumber).setEnrollment(grade, semesterStr, course); //add enrollment to enrollment vector of student with given matriklenumber
	}
}
