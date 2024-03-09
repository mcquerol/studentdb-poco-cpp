#include "CBlockCourse.h"

/*
 * CBlockCourse constructor
 * inherits from the CCourse class
 */
CBlockCourse::CBlockCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints,Poco::Data::Date startDate,
		Poco::Data::Date endDate,Poco::Data::Time startTime, Poco::Data::Time endTime)
{
	this->startDate=startDate;
	this->endDate=endDate;
	this->startTime=startTime;
	this->endTime=endTime;
}

/*
 * Empty destructor
 */
CBlockCourse::~CBlockCourse()
{

}

/*
 * CBlockCourse constructor
 * inherits from the CCourse class
 */

const Poco::Data::Time& CBlockCourse::getStartTime() const
{
	return startTime;
}

const Poco::Data::Time& CBlockCourse::getEndTime() const
{
	return endTime;
}

const Poco::Data::Date& CBlockCourse::getStartDate() const
{
	return startDate;
}

const Poco::Data::Date& CBlockCourse::getEndDate() const
{
	return endDate;
}

void CBlockCourse::setStartTime(const Poco::Data::Time &startTime)
{
	this->startTime = startTime;
}

void CBlockCourse::setEndTime(const Poco::Data::Time &endTime)
{
	this->endTime = endTime;
}

void CBlockCourse::setStartDate(const Poco::Data::Date &startDate)
{
	this->startDate = startDate;
}

void CBlockCourse::setEndDate(const Poco::Data::Date &endDate)
{
	this->endDate = endDate;
}
