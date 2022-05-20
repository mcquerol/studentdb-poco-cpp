#include "CCourse.h"

using namespace std;
/*
 * course class constructor
 */
CCourse::CCourse(unsigned int courseKey, std::string title, unsigned char major, float creditPoints)
{
	this->courseKey = courseKey;
	this->title = title;
	this->major = major;
	this->creditPoints = creditPoints;

//	this->majorById.insert({'A', "Automation"});
//	this->majorById.insert({'C', "Communications"});
//	this->majorById.insert({'E', "Embedded"});
//	this->majorById.insert({'P', "Power"});

}

CCourse::~CCourse()
{

}

unsigned int CCourse::getCourseKey() const
{
	return this->courseKey;
}

const std::string& CCourse::getTitle() const
{
	return this->title;
}

unsigned char CCourse::getMajor() const
{
	return this->major;
}

float CCourse::getCreditPoints() const
{
	return this->creditPoints;
}


