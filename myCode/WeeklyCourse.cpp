#include "WeeklyCourse.h"


WeeklyCourse::WeeklyCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints)
: Course(courseKey,title,major,creditPoints) {}

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
