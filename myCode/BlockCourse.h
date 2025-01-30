#ifndef BLOCKCOURSE_H
#define BLOCKCOURSE_H

#include <Poco/Data/Date.h>
#include <Poco/Data/Time.h>

#include "Course.h"

class BlockCourse : public Course
{

private:

	Poco::Data::Date startDate;
	Poco::Data::Date endDate;
	Poco::Data::Time startTime;
	Poco::Data::Time endTime;

public:

	BlockCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints);
	~BlockCourse();

	const Poco::Data::Time& getStartTime() const;
	const Poco::Data::Time& getEndTime() const;
	const Poco::Data::Date& getStartDate() const;
	const Poco::Data::Date& getEndDate() const;

	void setStartTime(const Poco::Data::Time &startTime);
	void setEndTime(const Poco::Data::Time &endTime);
	void setStartDate(const Poco::Data::Date &startDate);
	void setEndDate(const Poco::Data::Date &endDate);

	void write(std::ostream& out) const; //write attributes to os stream
};

#endif
