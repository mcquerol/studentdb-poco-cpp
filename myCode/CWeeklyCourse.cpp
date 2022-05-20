#include "CWeeklyCourse.h"

CWeeklyCourse::CWeeklyCourse(unsigned int courseKey, std::string title, unsigned char major, float creditPoints)
: CCourse(courseKey,title,major,creditPoints){

	this->courseKey = courseKey;
	this->title = title;
	this->major = major;
	this->creditPoints = creditPoints;

	// the following paramters will be changed through setters
	this->dayOfWeek = Poco::DateTime::DaysOfWeek::SUNDAY; // default day is sunday
	this->startTime = -1; // default startTime
	this->endTime = -1; // default endTime
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
