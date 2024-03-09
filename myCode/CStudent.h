#ifndef CSTUDENT_H
#define CSTUDENT_H

#include <string>
#include <vector>
#include <Poco/Data/Date.h>

#include "CAddress.h"
#include "CEnrollment.h"

class CStudent {
private:
    static unsigned int nextMatrikelNumber;
    unsigned int maktrikelNumber;
    std::string firstName;
    std::string lastName;
    Poco::Data::Date dateOfBirth;


    std::vector<CEnrollment> enrollments; //TODO check the implementation of this..must add an enrollment


public:
    CStudent(std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth, std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo);

    CAddress address;

    const unsigned int getMatrikelNumber() const;
	const std::string& getFirstName() const;
	const std::string& getLastName() const;
	const Poco::Data::Date& getDateOfBirth() const;

	void setFirstName(const std::string &firstName);
	void setLastName(const std::string &lastName);
	void setDateOfBirth(const Poco::Data::Date &dateOfBirth);

};
#endif /* CSTUDENT_H */
