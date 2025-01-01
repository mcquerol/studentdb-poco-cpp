#include "Address.h"

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
