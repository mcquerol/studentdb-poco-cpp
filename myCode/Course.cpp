#include "Course.h"

std::map<unsigned char, std::string> Course::majorById =
{
	{'A', "Automation"},
	{'C', "Communications"},
	{'E', "Embedded"},
	{'P', "Power"},
};

Course::Course(unsigned int courseKey, std::string title, unsigned char major, float creditPoints)
{
	this->courseKey = courseKey;
	this->title = title;
	this->major = major;
	this->creditPoints = creditPoints;
}

unsigned int Course::getCourseKey() const
{
	return courseKey;
}

float Course::getCreditPoints() const
{
	return creditPoints;
}

unsigned char Course::getMajor() const
{
	return majorById[major];
}

const std::string& Course::getTitle() const
{
	return title;
}
