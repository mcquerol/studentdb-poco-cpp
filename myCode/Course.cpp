#include "Course.h"
#include <ostream>
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
	string line, temp;
	getline(in, line);  // Read full line
	istringstream iss(line);  // Create stringstream
	getline(iss, temp, ';');
	this->courseKey = static_cast<unsigned int>(stoi(temp));  // Convert string to unsigned int
	getline(iss, this->title, ';');
	string majorStr;
	getline(iss, majorStr, ';');  // Read as a string
	this->major = majorStr[0];//access first character
	creditPoints = stof(temp);  // Convert string to float
}
