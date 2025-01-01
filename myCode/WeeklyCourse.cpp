#include "WeeklyCourse.h"


WeeklyCourse::WeeklyCourse(Poco::DateTime::DaysOfWeek dayOfWeek, Poco::Data::Time startTime, Poco::Data::Time endTime)
{
	this->dayOfWeek = dayOfWeek;
	this->startTime = startTime;
	this->endTime = endTime;
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
