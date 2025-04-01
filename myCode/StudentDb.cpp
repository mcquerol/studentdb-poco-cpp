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
	size_t enrollmentsSize = 0;
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
		getline(in, line);  // Read the next line before extracting first character
		courseType = line[0];  // Extract first character safely (either W or B)
		std::istringstream lineStream(line.substr(2)); // Start reading after "W;
		if (courseType == 'W')
		{
			unique_ptr<WeeklyCourse> weeklyCourse = std::make_unique<WeeklyCourse>();
			weeklyCourse->read(lineStream);
			setCourse(move(weeklyCourse)); // add to courses map
		}
		else if (courseType == 'B')
		{
			unique_ptr<BlockCourse> blockCourse = std::make_unique<BlockCourse>();
			blockCourse->read(lineStream);
			setCourse(move(blockCourse)); // add to courses map
		}
	}

	in >> studentCount;
	in.ignore();
	for(size_t i = 0; i < studentCount; i++)
	{
        Student s;
        s.read(in);
        setStudent(s); // add to students map
	}

	in >> enrollmentCount;
	in.ignore();

	for(size_t i = 0; i < enrollmentCount; i++)
	{
	    std::string line, temp;
	    unsigned int matrikelNumber, courseKey;

	    getline(in, line);                      // Read the whole line
	    std::istringstream iss(line);          // Create stream from line

	    // Extract matrikel number
	    getline(iss, temp, ';');
	    matrikelNumber = static_cast<unsigned int>(std::stoi(temp));
	    // Extract course key
	    getline(iss, temp, ';');
	    courseKey = static_cast<unsigned int>(std::stoi(temp));

	    // Extract remaining enrollment data (semester and grade)
	    Enrollment e;
	    e.read(iss);  // Pass the stream! DO NOT call getline again here.

		if (courses.find(courseKey) == courses.end())
		{
		    cerr << "Error: Course with key " << courseKey << " not found." << endl;
		    continue; // Skip this enrollment
		}
		else
		{
			Course* course = const_cast<Course*>(courses.at(courseKey).get());
			students.at(matrikelNumber).setEnrollment(e.getGrade(), e.getSemester(), course); //add enrollment to enrollment vector of student with given matrikelnumber
		}
	}
	//check last matrikel number and add one to it
	auto lastStudent = students.rbegin(); // Reverse iterator, points to last element
	if (lastStudent != students.rend()) // Ensure map is not empty
	{
	    unsigned int highestMatrikel = lastStudent->first; // Extract the key
	    Student::setNextMatrikelNumber(highestMatrikel + 1); // Update static variable
	}
	else
	{
	    Student::setNextMatrikelNumber(100000); // Default starting value if empty
	}
}
