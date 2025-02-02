#include "BlockCourse.h"
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

using namespace std;

BlockCourse::BlockCourse()
{
}

BlockCourse::BlockCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints)
: Course(courseKey,title,major,creditPoints) {}

BlockCourse::~BlockCourse()
{
}

const Poco::Data::Time& BlockCourse::getStartTime() const
{
	return startTime;
}

const Poco::Data::Time& BlockCourse::getEndTime() const
{
	return endTime;
}

const Poco::Data::Date& BlockCourse::getStartDate() const
{
	return startDate;
}

const Poco::Data::Date& BlockCourse::getEndDate() const
{
	return endDate;
}

void BlockCourse::setStartTime(const Poco::Data::Time &startTime)
{
	this->startTime = startTime;
}

void BlockCourse::setEndTime(const Poco::Data::Time &endTime)
{
	this->endTime = endTime;
}

void BlockCourse::setStartDate(const Poco::Data::Date &startDate)
{
	this->startDate = startDate;
}

void BlockCourse::setEndDate(const Poco::Data::Date &endDate)
{
	this->endDate = endDate;
}

void BlockCourse::write(std::ostream &out) const
{
	out << "B;";
	Course::write(out);
	out << startDate.day() << '.' << startDate.month() << '.' << startDate.year() << ';';
	out << endDate.day() << '.' << endDate.month() << '.' << endDate.year() << ';';
	out << startTime.hour() << '.' << startTime.minute() << '.' << startTime.second();
	out << endTime.hour() << '.' << endTime.minute() << '.' << endTime.second()<< "\n";
}

void BlockCourse::read(std::istream &in)
{
	string line, temp;
	string startTimeStr, endTimeStr, startDateStr, endDateStr;
	string year, month, day;

	Course::read(in);
	getline(in, line);  // Read full line
	istringstream iss(line);  // Create stringstream

	getline(iss, startDateStr, ';');
	istringstream dateStreamStart(startDateStr);
	getline(dateStreamStart, day, '.');
	getline(dateStreamStart, month, '.');
	getline(dateStreamStart, year, '.');
	startDate = Poco::Data::Date(stoi(year), stoi(month), stoi(day));

	getline(iss, endDateStr, ';');
	istringstream dateStreamEnd(endDateStr);
	getline(dateStreamEnd, day, '.');
	getline(dateStreamEnd, month, '.');
	getline(dateStreamEnd, year, '.');
	endDate = Poco::Data::Date(stoi(year), stoi(month), stoi(day));

	getline(iss, startTimeStr, ';');
	istringstream timeStreamStart(startTimeStr);
	getline(timeStreamStart, temp, '.');
	int startHour = stoi(temp);
	getline(timeStreamStart, temp, '.');
	int startMinute = stoi(temp);
	getline(timeStreamStart, temp, '.');
	int startSecond = stoi(temp);
	startTime = Poco::Data::Time(startHour, startMinute, startSecond);

	getline(iss, endTimeStr, ';');
	istringstream timeStreamEnd(endTimeStr);
	getline(timeStreamEnd, temp, '.');
	int endHour = stoi(temp);
	getline(timeStreamEnd, temp, '.');
	int endMinute = stoi(temp);
	getline(timeStreamEnd, temp, '.');
	int endSecond = stoi(temp);
	endTime = Poco::Data::Time(endHour, endMinute, endSecond);

}
