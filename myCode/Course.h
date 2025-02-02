#ifndef COURSE_H
#define COURSE_H

#include <map>
#include <string>
#include <stdexcept>

class Course
{

protected:

	static std::map<unsigned char, std::string> majorById;
	unsigned int courseKey;
	std::string title;
	unsigned char major;
	float creditPoints;

public:

	Course(unsigned int courseKey, std::string title, std::string major, float creditPoints);
	virtual ~Course() = 0;

	virtual void write(std::ostream& out) const; //write base attributes to os stream
	virtual void read(std::istream& in);

	unsigned int getCourseKey() const;
	float getCreditPoints() const;
	const std::string& getMajor() const;
	const std::string& getTitle() const;

	//getter to use in simpleui class valdiation for major
	static const std::map<unsigned char, std::string>& getMajorById();
	
};


#endif
