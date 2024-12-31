#ifndef COURSE_H
#ifndef COURSE_H

#include <map>

#include <string>

class Course
{

private:

	static unsigned std::map<unsigned char, std::string> majorById;
	unsigned int courseKey;
	std::string title;
	unsigned char major;
	float creditPoints;


public:

	virtual ~Course() = 0;

};


#endif COURSE_H
