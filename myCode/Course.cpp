#include "Course.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


std::map<unsigned char, std::string> Course::majorById =
{
	{'A', "Automation"},
	{'C', "Communications"},
	{'E', "Embedded"},
	{'P', "Power"},
};

Course::Course()
{
}

Course::Course(unsigned int courseKey, std::string title, std::string major, float creditPoints)
{
	this->courseKey = courseKey;
	this->title = title;
	this->creditPoints = creditPoints;

    // Find the char representation for the provided string
    for (const auto& pair : majorById)
    {
        if (pair.second == major)
        {
            this->major = pair.first; // Store the char internally
            return;
        }
    }
    throw std::invalid_argument("Invalid major: " + major);

}

Course::~Course()
{

}

unsigned int Course::getCourseKey() const
{
	return courseKey;
}

float Course::getCreditPoints() const
{
	return creditPoints;
}

const std::string& Course::getMajor() const
{
    auto it = majorById.find(this->major);
    if (it != majorById.end())
    {
        return it->second; // Return the string representation
    }
    throw std::runtime_error("Major not found in mapping");

}

const std::string& Course::getTitle() const
{
	return title;
}

void Course::write(std::ostream &out) const
{
	out << courseKey << ";" << title << ";" << majorById.at(major) << ";" << creditPoints << ";";
}

const std::map<unsigned char, std::string>& Course::getMajorById()
{
    return Course::majorById; // Explicitly qualify the static member
}

void Course::read(std::istream &in)
{
	string line, temp, majorStr;

    getline(in, temp, ';');
    courseKey = static_cast<unsigned int>(stoi(temp));

    getline(in, title, ';');

    getline(in, majorStr, ';');
    if (!majorStr.empty())
    {
        this->major = majorStr[0];
    }
    else
    {
        std::cerr << "Warning: Major string is empty!" << std::endl;
    }

    getline(in, temp, ';');
    creditPoints = stof(temp);

    if (in.peek() == '\n')
    {
        in.ignore();
    }

}
