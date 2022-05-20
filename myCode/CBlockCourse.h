#ifndef CBLOCKCOURSE_H
#define CBLOCKCOURSE_H
#include "CCourse.h"

#include <Poco/DateTime.h>
#include <Poco/Data/Time.h>
#include <Poco/Data/Date.h>

class CBlockCourse : public CCourse {
private:

	/*
	 * start and end time/date for the CBlockCourse
	 * these are POCO time and date objects
	 */
    Poco::Data::Time startTime;
    Poco::Data::Time endTime;
    Poco::Data::Date startDate;
    Poco::Data::Date endDate;
public:

    /*
     * CBlockCourse constructor
     * inherits from the CCourse class
     */
    CBlockCourse(unsigned int courseKey, std::string title, unsigned char major, float creditPoints);

    /*
     * Empty destructor
     */
    ~CBlockCourse();

    /*
     * getter and setter functions for the class members
     */
	const Poco::Data::Time& getStartTime() const;
	const Poco::Data::Time& getEndTime() const;
	const Poco::Data::Date& getStartDate() const;
    const Poco::Data::Date& getEndDate() const;

	void setStartTime(const Poco::Data::Time &startTime);
	void setEndTime(const Poco::Data::Time &endTime);
 	void setStartDate(const Poco::Data::Date &startDate);
 	void setEndDate(const Poco::Data::Date &endDate);

};
#endif /* CBLOCKCOURSE_H */
