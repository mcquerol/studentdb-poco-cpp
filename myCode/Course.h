#ifndef COURSE_H
#define COURSE_H

#include <map>
#include <string>

class Course
{

private:

	static std::map<unsigned char, std::string> majorById;
	unsigned int courseKey;
	std::string title;
	unsigned char major;
	float creditPoints;

public:

	Course(unsigned int courseKey, std::string title, std::string major, float creditPoints);
	virtual ~Course() = 0;

	unsigned int getCourseKey() const;
	float getCreditPoints() const;
	unsigned char getMajor() const;
	const std::string& getTitle() const;

};


#endif
