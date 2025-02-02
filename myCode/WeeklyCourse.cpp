#include "WeeklyCourse.h"
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

using namespace std;

WeeklyCourse::WeeklyCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints)
: Course(courseKey,title,major,creditPoints)
{

	this->dayOfWeek = Poco::DateTime::DaysOfWeek::SUNDAY; // default day is sunday
	this->startTime = -1; // default startTime
	this->endTime = -1; // default endTime

}

WeeklyCourse::~WeeklyCourse()
{
}

Poco::DateTime::DaysOfWeek WeeklyCourse::getDayOfWeek() const
{
	return dayOfWeek;
}

const Poco::Data::Time& WeeklyCourse::getStartTime() const
{
	return startTime;
}

const Poco::Data::Time& WeeklyCourse::getEndTime() const
{
	return endTime;
}

void WeeklyCourse::setDayOfWeek(Poco::DateTime::DaysOfWeek dayOfWeek)
{
	this->dayOfWeek = dayOfWeek;
}

void WeeklyCourse::setEndTime(const Poco::Data::Time &endTime)
{
	this->endTime = endTime;
}

void WeeklyCourse::setStartTime(const Poco::Data::Time &startTime)
{
	this->startTime = startTime;
}

void WeeklyCourse::write(std::ostream &out) const
{
	out << "W;";
	Course::write(out);
	out << dayOfWeek << ';';
	out << startTime.hour() << '.' << startTime.minute() << '.' << startTime.second() << ';';
	out << endTime.hour() << '.' << endTime.minute() << '.' << endTime.second() << "\n";
}

void WeeklyCourse::read(std::istream &in)
{
	string line, temp;
	string dayOfWeekStr;
	string startTimeStr, endTimeStr;
	string hour, minute, second;

	Course::read(in);

	getline(in, line);  // Read full line
	istringstream iss(line);  // Create stringstream
	getline(iss, dayOfWeekStr, ';');
	dayOfWeek = static_cast<Poco::DateTime::DaysOfWeek>(stoi(dayOfWeekStr));

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
