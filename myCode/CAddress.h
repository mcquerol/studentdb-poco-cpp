#ifndef CADRESS_H
#define CADRESS_H

#include <string>

class CAddress {
private:

	/*
	 * street string
	 */
    std::string street;

    /*
     * postal code unsigned short
     */
    unsigned short postalCode;

    /*
     * city name string
     */
    std::string cityName;

    /*
     * additional info string
     */
    std::string additionalInfo;

public:

    /*
     * this is the constructor for the CAddress class
     */
    CAddress(std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo);

    /*
     * virtual destructor
     */
    virtual ~CAddress();

    /*
     * getter functions for the class members
     */
	const std::string& getAdditionalInfo() const;
	const std::string& getCityName() const;
	unsigned short getPostalCode() const;
	const std::string& getStreet() const;
};
#endif /* CADRESS_H */
