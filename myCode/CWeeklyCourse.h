#ifndef CWEEKLYCOURSE_H
#define CWEEKLYCOURSE_H

#include "CCourse.h"

#include <Poco/DateTime.h>
#include <Poco/Data/Time.h>

class CWeeklyCourse : public CCourse {
private:

    Poco::DateTime::DaysOfWeek dayOfWeek;
    Poco::Data::Time startTime;
    Poco::Data::Time endTime;

public:

    CWeeklyCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints);
    ~CWeeklyCourse();

    Poco::DateTime::DaysOfWeek getDayOfWeek() const;
	const Poco::Data::Time& getStartTime() const;
	const Poco::Data::Time& getEndTime() const;

	void setDayOfWeek(Poco::DateTime::DaysOfWeek dayOfWeek);
	void setStartTime(const Poco::Data::Time &startTime);
	void setEndTime(const Poco::Data::Time &endTime);

};
#endif /* CWEEKLYCOURSE_H */
