#ifndef CCOURSE_H
#define CCOURSE_H

#include <iostream>
#include <string>
#include <map>

class CCourse {
protected:

	/*
	 * static map to keep track of major by char/string
	 * as well as course info
	 */
    //static std::map<unsigned char, std::string> majorById;
    unsigned int courseKey;
    std::string title;
    unsigned char major;
    float creditPoints;

public:
    /*
     * course class contains default constructor and constructor with parameters
     * and virtual destructor because it is the parent class
     */
    CCourse();
    CCourse(unsigned int courseKey, std::string title, unsigned char major, float creditPoints);
    virtual ~CCourse() = 0;

	unsigned int getCourseKey() const;
	const std::string& getTitle() const;
	unsigned char getMajor() const;
	float getCreditPoints() const;


};

#endif /* CCOURSE_H */
