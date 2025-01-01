#ifndef WEEKLYCOURSE_H
#define WEEKLYCOURSE_H

#include <Poco/DateTime.h>
#include <Poco/Data/Time.h>

class WeeklyCourse
{

private:

	Poco::DateTime::DaysOfWeek dayOfWeek;
	Poco::Data::Time startTime;
	Poco::Data::Time endTime;

public:

	WeeklyCourse(Poco::DateTime::DaysOfWeek dayOfWeek, Poco::Data::Time startTime, Poco::Data::Time endTime);
	~WeeklyCourse();

	Poco::DateTime::DaysOfWeek getDayOfWeek() const;
	const Poco::Data::Time& getEndTime() const;
	const Poco::Data::Time& getStartTime() const;
};

#endif
