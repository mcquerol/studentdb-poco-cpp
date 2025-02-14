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
//
//
//	std::cout << "Debug: [" << __FILE__ << ":" << __LINE__ << "] Attempting to convert to int: '" << line << "'" << std::endl;
//	this->courseKey = static_cast<unsigned int>(stoi(line));  // Convert string to unsigned int
//	getline(in, this->title, ';');
//	string majorStr;
//	getline(in, majorStr, ';');  // Read as a string
//	this->major = majorStr[0];//access first character
//	getline(in, line, ';');
//	creditPoints = stof(line);  // Convert string to float

    std::cout << "Debug: Reading Course line..." << std::endl;
    getline(in, line);  // Read full line
    std::cout << "Debug: Read line: '" << line << "'" << std::endl;

    std::istringstream iss(line);

    std::cout << "Debug: Reading Course Key..." << std::endl;
    getline(iss, temp, ';');
    std::cout << "Debug: Extracted Course Key: '" << temp << "'" << std::endl;
    courseKey = static_cast<unsigned int>(stoi(temp));

    std::cout << "Debug: Reading Title..." << std::endl;
    getline(iss, title, ';');
    std::cout << "Debug: Extracted Title: '" << title << "'" << std::endl;

    std::cout << "Debug: Reading Major..." << std::endl;
    getline(iss, majorStr, ';');
    std::cout << "Debug: Extracted Major: '" << majorStr << "'" << std::endl;
    if (!majorStr.empty()) {
        this->major = majorStr[0];
    } else {
        std::cerr << "Warning: Major string is empty!" << std::endl;
    }

    std::cout << "Debug: Reading Credit Points..." << std::endl;
    getline(iss, temp, ';');
    std::cout << "Debug: Extracted Credit Points: '" << temp << "'" << std::endl;
    creditPoints = stof(temp);
}
