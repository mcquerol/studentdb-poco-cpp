#include "Address.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Address::Address()
{
}

Address::Address(std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo)
{
	this->street = street;
	this->postalCode = postalCode;
	this->cityName = cityName;
	this->additionalInfo = additionalInfo;
}

Address::~Address()
{
}

const std::string& Address::getAdditionalInfo() const
{
	return additionalInfo;
}

const std::string& Address::getCityName() const
{
	return cityName;
}

unsigned short Address::getPostalCode() const
{
	return postalCode;
}

const std::string& Address::getStreet() const
{
	return street;
}

void Address::write(std::ostream &out) const
{
	out << street << ';' << postalCode << ';' << cityName << ';' << additionalInfo << "\n";
}

void Address::read(std::istream &in)
{
	string line;

	getline(in, street, ';');
	getline(in, line, ';');
	std::cout << "Debug: [" << __FILE__ << ":" << __LINE__ << "] Attempting to convert to int: '" << line << "'" << std::endl;
	postalCode = static_cast<unsigned short>(stoi(line));  // Convert string to unsigned short
	getline(in, cityName, ';');
	getline(in, additionalInfo, ';');
}
