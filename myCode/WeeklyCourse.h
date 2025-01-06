#ifndef WEEKLYCOURSE_H
#define WEEKLYCOURSE_H

#include <Poco/DateTime.h>
#include <Poco/Data/Time.h>

#include "Course.h"

class WeeklyCourse : public Course
{

private:

	Poco::DateTime::DaysOfWeek dayOfWeek;
	Poco::Data::Time startTime;
	Poco::Data::Time endTime;

public:

	WeeklyCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints);
	~WeeklyCourse();

	Poco::DateTime::DaysOfWeek getDayOfWeek() const;
	const Poco::Data::Time& getEndTime() const;
	const Poco::Data::Time& getStartTime() const;

	void setDayOfWeek(Poco::DateTime::DaysOfWeek dayOfWeek);
	void setEndTime(const Poco::Data::Time &endTime);
	void setStartTime(const Poco::Data::Time &startTime);

};

#endif
