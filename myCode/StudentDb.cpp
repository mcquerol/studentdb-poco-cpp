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

		string temp;
		std::getline(in, line);  // Read full line
		istringstream iss(line);  // Create stringstream

		std::getline(iss, temp, ';');
		courseType = temp[0];  // Extract first character safely

		getline(iss, temp, ';');
		courseKey = std::stoi(temp);  // Convert string to unsigned int
		getline(iss, title, ';');
		getline(iss, major, ';');
		getline(iss, temp, ';');
		creditPoints = std::stof(temp);  // Convert string to float

		if(courseType == 'W')
		{
			unique_ptr<WeeklyCourse> weeklyCourse = std::make_unique<WeeklyCourse>(courseKey, title, major, creditPoints);

			Poco::DateTime::DaysOfWeek dayOfWeek;
			getline(iss, dayOfWeekStr, ';');
			dayOfWeek = static_cast<Poco::DateTime::DaysOfWeek>(stoi(dayOfWeekStr));

			getline(iss, startTimeStr, ';');
			istringstream startTimeSs(startTimeStr);
			getline(startTimeSs, hourStr, '.');
			getline(startTimeSs, minuteStr, '.');
			getline(startTimeSs, secondStr, '.');
			startTime = {stoi(hourStr),stoi(minuteStr),stoi(secondStr)};

			getline(iss, endTimeStr, ';');
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

			getline(iss, startDateStr, ';');
			istringstream startDateSs(startDateStr);
			getline(startDateSs, dayStr, '.');
			getline(startDateSs, monthStr, '.');
			getline(startDateSs, yearStr, '.');
			startDate = {stoi(yearStr), stoi(monthStr), stoi(dayStr)};

			getline(iss, endDateStr, ';');
			istringstream endDateSs(endDateStr);
			getline(endDateSs, dayStr, '.');
			getline(endDateSs, monthStr, '.');
			getline(endDateSs, yearStr, '.');
			endDate = {stoi(yearStr), stoi(monthStr), stoi(dayStr)};

			getline(iss, startTimeStr, ';');
			istringstream startTimeSs(startTimeStr);
			getline(startTimeSs, hourStr, '.');
			getline(startTimeSs, minuteStr, '.');
			getline(startTimeSs, secondStr, '.');
			startTime = {stoi(hourStr), stoi(minuteStr), stoi(secondStr)};

			getline(iss, endTimeStr, ';');
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
}
