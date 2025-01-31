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
	courses.clear();
	for(auto& student: students)
	{
		student.second.clearEnrollments();
	}
	students.clear();

	size_t courseCount, studentCount, enrollmentCount;
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
			string DayOfWeekStr;
			string startTimeStr, endTimeStr;
			string hour, minute, second;
			getline(iss, DayOfWeekStr, ';');
			dayOfWeek = static_cast<Poco::DateTime::DaysOfWeek>(stoi(DayOfWeekStr));

			getline(iss, startTimeStr, ';');
			istringstream startTimess(startTimeStr);
			getline(startTimess, hour, '.');
			getline(startTimess, minute, '.');
			getline(startTimess, second, '.');
			startTime = {stoi(hour),stoi(minute),stoi(second)};

			getline(iss, endTimeStr, ';');
			istringstream endTimess(endTimeStr);
			getline(endTimess, hour, '.');
			getline(endTimess, minute, '.');
			getline(endTimess, second, '.');
			endTime = {stoi(hour),stoi(minute),stoi(second)};

			weeklyCourse->setDayOfWeek(dayOfWeek);
			weeklyCourse->setStartTime(startTime);
			weeklyCourse->setEndTime(endTime);

			setCourse(std::move(weeklyCourse));
		}
		else if(courseType == 'B')
		{

		}
	}
}
