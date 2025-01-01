#ifndef BLOCKCOURSE_H
#define BLOCKCOURSE_H

#include <Poco/Data/Date.h>
#include <Poco/Data/Time.h>


class BlockCourse
{

private:

	Poco::Data::Date startDate;
	Poco::Data::Date endDate;
	Poco::Data::Time startTime;
	Poco::Data::Time endTime;

public:

	BlockCourse(Poco::Data::Date startDate, Poco::Data::Date endDate, Poco::Data::Time startTime, Poco::Data::Time endTime);
	~BlockCourse();

	const Poco::Data::Time& getStartTime() const;
	const Poco::Data::Time& getEndTime() const;
	const Poco::Data::Date& getStartDate() const;
	const Poco::Data::Date& getEndDate() const;

};

#ifndef BLOCKCOURSE_H
