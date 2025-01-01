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

	void setDayofWeek(Poco::DateTime::DaysOfWeek dayofWeek);
	void setStartTime(Poco::Data::Time startTime);
	void setEndTime(Poco::Data::Time EndTime);
	
	void getDayOfWeek() const;
	void getStartTime() const;
	void getEndTime() const;


};

#endif WEEKLYCOURSE_H
