#include "CBlockCourse.h"

/*
 * CBlockCourse constructor
 * inherits from the CCourse class
 */
CBlockCourse::CBlockCourse(unsigned int courseKey, std::string title, unsigned char major, float creditPoints)
: CCourse(courseKey,title,major,creditPoints)
{
	this->courseKey = courseKey;
	this->title = title;
	this->major = major;
	this->creditPoints = creditPoints;
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
