#include "BlockCourse.h"
#include <iostream>
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
	string line;
	string startTimeStr, endTimeStr, startDateStr, endDateStr;
	int day, month, year;
	int startHour, startMinute, startSecond, endHour, endMinute, endSecond;

	Course::read(in);

	getline(in, startDateStr, ';');
	istringstream dateStreamStart(startDateStr);
	getline(dateStreamStart, line, '.');

	day = stoi(line);
	getline(dateStreamStart, line, '.');

	month = stoi(line);
	getline(dateStreamStart, line, '.');

	year = stoi(line);
	startDate = Poco::Data::Date(year, month, day);

	getline(in, endDateStr, ';');
	istringstream dateStreamEnd(endDateStr);
	getline(dateStreamEnd, line, '.');

	day = stoi(line);
	getline(dateStreamEnd, line, '.');

	month = stoi(line);
	getline(dateStreamEnd, line, '.');

	year = stoi(line);
	endDate = Poco::Data::Date(year, month, day);

	getline(in, startTimeStr, ';');
	istringstream timeStreamStart(startTimeStr);
	getline(timeStreamStart, line, '.');

	startHour = stoi(line);
	getline(timeStreamStart, line, '.');

	startMinute = stoi(line);
	getline(timeStreamStart, line, '.');

	startSecond = stoi(line);
	startTime = Poco::Data::Time(startHour, startMinute, startSecond);

	getline(in, endTimeStr, ';');
	istringstream timeStreamEnd(endTimeStr);
	getline(timeStreamEnd, line, '.');

	endHour = stoi(line);
	getline(timeStreamEnd, line, '.');

	endMinute = stoi(line);
	getline(timeStreamEnd, line, '.');

	endSecond = stoi(line);
	endTime = Poco::Data::Time(endHour, endMinute, endSecond);

}
