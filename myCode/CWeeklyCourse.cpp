#include "CWeeklyCourse.h"

CWeeklyCourse::CWeeklyCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints)
{
	this->dayOfWeek=0;
	this->startTime={0,0,0};
	this->endTime={0,0,0};
}

CWeeklyCourse::~CWeeklyCourse()
{

}

Poco::DateTime::DaysOfWeek CWeeklyCourse::getDayOfWeek() const
{
	return this->dayOfWeek;
}

const Poco::Data::Time& CWeeklyCourse::getStartTime() const
{
	return this->startTime;
}

const Poco::Data::Time& CWeeklyCourse::getEndTime() const
{
	return this->endTime;
}

void CWeeklyCourse::setDayOfWeek(Poco::DateTime::DaysOfWeek dayOfWeek)
{
	this->dayOfWeek = dayOfWeek;
}

void CWeeklyCourse::setStartTime(const Poco::Data::Time &startTime)
{
	this->startTime = startTime;
}

void CWeeklyCourse::setEndTime(const Poco::Data::Time &endTime)
{
	this->endTime = endTime;
}
