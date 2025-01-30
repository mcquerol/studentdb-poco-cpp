#include "WeeklyCourse.h"


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
	write(out);
	out << dayOfWeek << ';' << startTime << ';' << endTime << "\n";
}
