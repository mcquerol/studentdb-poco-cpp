#ifndef ADRESS_H
#define ADRESS_H

#include <string>

class Address
{

private:

	std::string street;
	unsigned short postalCode;
	std::string cityName;
	std::string additionalInfo;

public:

	Address(std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo);
	~Address();

	const std::string& getAdditionalInfo() const;
	const std::string& getCityName() const;
	unsigned short getPostalCode() const;
	const std::string& getStreet() const;

	void write(std::ostream& out) const; //write attributes to os stream
	void read(std::istream& in);


};

#endif
