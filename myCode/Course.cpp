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

    std::cout << "Debug: Reading Course Key..." << std::endl;
    getline(in, temp, ';');
    std::cout << "Debug: Extracted Course Key: '" << temp << "'" << std::endl;
    courseKey = static_cast<unsigned int>(stoi(temp));

    std::cout << "Debug: Reading Title..." << std::endl;
    getline(in, title, ';');
    std::cout << "Debug: Extracted Title: '" << title << "'" << std::endl;

    std::cout << "Debug: Reading Major..." << std::endl;
    getline(in, majorStr, ';');
    std::cout << "Debug: Extracted Major: '" << majorStr << "'" << std::endl;
    if (!majorStr.empty()) {
        this->major = majorStr[0];
    } else {
        std::cerr << "Warning: Major string is empty!" << std::endl;
    }

    std::cout << "Debug: Reading Credit Points..." << std::endl;
    getline(in, temp, ';');
    std::cout << "Debug: Extracted Credit Points: '" << temp << "'" << std::endl;
    creditPoints = stof(temp);
    std::cout << "Debug: Leaving Course::read(), next char in stream: '" << in.peek() << "' (ASCII: " << int(in.peek()) << ")" << std::endl;

    if (in.peek() == '\n') {
        std::cout << "Debug: Newline detected, ignoring it..." << std::endl;
        in.ignore();
    }


}
