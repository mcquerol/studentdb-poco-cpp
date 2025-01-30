#include "Course.h"
#include <ostream>


std::map<unsigned char, std::string> Course::majorById =
{
	{'A', "Automation"},
	{'C', "Communications"},
	{'E', "Embedded"},
	{'P', "Power"},
};

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
    auto it = majorById.find(major);
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
