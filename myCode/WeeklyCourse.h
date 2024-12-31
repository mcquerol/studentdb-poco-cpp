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


};

#endif WEEKLYCOURSE_H
