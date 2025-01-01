#include "BlockCourse.h"

BlockCourse::BlockCourse(Poco::Data::Date startDate, Poco::Data::Date endDate, Poco::Data::Time startTime, Poco::Data::Time endTime)
{
	this->startDate = startDate;
	this->endDate = endDate;
	this->startTime = startTime;
	this->endTime = endTime;
}

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
