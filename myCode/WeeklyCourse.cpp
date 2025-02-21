#include "WeeklyCourse.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

WeeklyCourse::WeeklyCourse()
{
}

WeeklyCourse::WeeklyCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints)
: Course(courseKey,title,major,creditPoints)
{

	this->dayOfWeek = 0; // default day is sunday
	this->startTime = -1; // default startTime
	this->endTime = -1; // default endTime

}

WeeklyCourse::~WeeklyCourse()
{
}

int WeeklyCourse::getDayOfWeek() const
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

void WeeklyCourse::setDayOfWeek(int dayOfWeek)
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
	string line;
	string dayOfWeekStr;
	string startTimeStr, endTimeStr;
	int startHour, startMinute, startSecond, endHour, endMinute, endSecond;

	std::cout << "Debug: Entering WeeklyCourse::read()" << std::endl;
	Course::read(in);

	std::getline(in, line, ';');
	std::cout << "Debug: Extracted DayOfWeek: '" << line << "'" << std::endl;
	if (line.empty()) {
	    std::cerr << "ERROR: DayOfWeek is EMPTY! CHECK INPUT FILE OR GETLINE ORDER." << std::endl;
	} else {
	    dayOfWeek = stoi(line);
	}


	getline(in, startTimeStr, ';');
	istringstream timeStreamStart(startTimeStr);
	getline(timeStreamStart, line, '.');
	std::cout << "Debug: [" << __FILE__ << ":" << __LINE__ << "] Attempting to convert to int: '" << line << "'" << std::endl;
	startHour = stoi(line);
	getline(timeStreamStart, line, '.');
	std::cout << "Debug: [" << __FILE__ << ":" << __LINE__ << "] Attempting to convert to int: '" << line << "'" << std::endl;
	startMinute = stoi(line);
	getline(timeStreamStart, line, '.');
	std::cout << "Debug: [" << __FILE__ << ":" << __LINE__ << "] Attempting to convert to int: '" << line << "'" << std::endl;
	startSecond = stoi(line);
	startTime = Poco::Data::Time(startHour, startMinute, startSecond);

	getline(in, endTimeStr, ';');
	istringstream timeStreamEnd(endTimeStr);
	getline(timeStreamEnd, line, '.');
	std::cout << "Debug: [" << __FILE__ << ":" << __LINE__ << "] Attempting to convert to int: '" << line << "'" << std::endl;
	endHour = stoi(line);
	getline(timeStreamEnd, line, '.');
	std::cout << "Debug: [" << __FILE__ << ":" << __LINE__ << "] Attempting to convert to int: '" << line << "'" << std::endl;
	endMinute = stoi(line);
	getline(timeStreamEnd, line, '.');
	std::cout << "Debug: [" << __FILE__ << ":" << __LINE__ << "] Attempting to convert to int: '" << line << "'" << std::endl;
	endSecond = stoi(line);
	endTime = Poco::Data::Time(endHour, endMinute, endSecond);
}
