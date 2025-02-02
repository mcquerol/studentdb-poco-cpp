#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <Poco/Data/Date.h>

#include "Enrollment.h"
#include "Address.h"

class Student
{

private:

	static unsigned int nextMatrikelNumber;
	unsigned int matrikelNumber;
	std::string firstName;
	std::string lastName;
	Poco::Data::Date dateOfBirth;
	std::vector<Enrollment> enrollments;

public:

	Student();
	Student(std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth, std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo);
	~Student();

	Address address;

	const Poco::Data::Date& getDateOfBirth() const;
	const std::string& getFirstName() const;
	const std::string& getLastName() const;
	unsigned int getMatrikelNumber() const;

	const std::vector<Enrollment>& getEnrollments() const;

	void setEnrollment(float grade, std::string semester, Course *course);
	void removeEnrollment(size_t index);
	void clearEnrollments();

	void setAddress(const Address &address);
	void setDateOfBirth(const Poco::Data::Date &dateOfBirth);
	void setFirstName(const std::string &firstName);
	void setLastName(const std::string &lastName);

	void write(std::ostream& out) const; //write attributes to os stream
	void read(std::istream& in);

	static void setNextMatrikelNumber(unsigned int newMatrikelNumber);
};

#endif
