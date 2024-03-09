#include "CCourse.h"

using namespace std;


std::map<unsigned char, std::string> CCourse::majorById = {
    {'A', "Automation"},
    {'C', "Communications"},
    {'E', "Embedded"},
    {'P', "Power"}
};

CCourse::CCourse(unsigned int courseKey, std::string title, unsigned char major, float creditPoints)
: courseKey{courseKey}, title{title}, major{major}, creditPoints{creditPoints}
{
//TODO check about making the major attribute equal to the string (input being a char)
}

CCourse::~CCourse()
{

}

unsigned int CCourse::getCourseKey() const
{
	return courseKey;
}

const std::string& CCourse::getTitle() const
{
	return title;
}

std::string CCourse::getMajor() const
{
	return majorById[major];
}

float CCourse::getCreditPoints() const
{
	return creditPoints;
}


