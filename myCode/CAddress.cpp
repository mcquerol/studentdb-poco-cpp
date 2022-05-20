/*
 * CAddress.cpp
 *
 *  Created on: 20 Jan 2022
 *      Author: Mateo C. Querol
 */

#include "CAddress.h"

/*
 * CAddress constructor
 */
CAddress::CAddress(std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo)
{
	this->street = street;
	this->postalCode = postalCode;
	this->cityName = cityName;
	this->additionalInfo = additionalInfo;
}

/*
 * CAddress destructor
 */
CAddress::~CAddress()
{

}

/*
 * returns additional info
 */
const std::string& CAddress::getAdditionalInfo() const
{
	return this->additionalInfo;
}

/*
 * returns city name
 */
const std::string& CAddress::getCityName() const
{
	return this->cityName;
}

/*
 * returns postal code
 */
unsigned short CAddress::getPostalCode() const
{
	return this->postalCode;
}

/*
 * returns street
 */
const std::string& CAddress::getStreet() const
{
	return this->street;
}
