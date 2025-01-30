#include "BlockCourse.h"

BlockCourse::BlockCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints)
: Course(courseKey,title,major,creditPoints) {}

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

void BlockCourse::setStartTime(const Poco::Data::Time &startTime)
{
	this->startTime = startTime;
}

void BlockCourse::setEndTime(const Poco::Data::Time &endTime)
{
	this->endTime = endTime;
}

void BlockCourse::setStartDate(const Poco::Data::Date &startDate)
{
	this->startDate = startDate;
}

void BlockCourse::setEndDate(const Poco::Data::Date &endDate)
{
	this->endDate = endDate;
}

void BlockCourse::write(std::ostream &out) const
{
	out << "B;";
	write(out);
	out << startDate << ';' << endDate << ';' << startTime << ';' << endTime << "\n";
}
