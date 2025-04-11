#ifndef SIMPLEUI_H
#define SIMPLEUI_H

#include "StudentDb.h"

class SimpleUI
{

private:

	StudentDb* db;

public:

	SimpleUI(StudentDb& db);
	void run();

	/* Error handling and input validation help functions */
	Poco::Data::Date getValidatedDate(const std::string& prompt);
	Poco::Data::Time getValidatedTime(const std::string& prompt);
	Poco::DateTime::DaysOfWeek getValidatedDayOfWeek(const std::string& prompt);
	unsigned int getValidatedUnsignedInt(const std::string& prompt, unsigned int min = 0, unsigned int max = UINT_MAX);
	float getValidatedFloat(const std::string& prompt, float min = 1.0, float max = 5.0);
	std::string getValidatedString(const std::string& prompt, bool allowNumbers = true);
	std::string getValidatedMajor(const std::string& prompt);
	unsigned short getValidatedPostalCode(const std::string& prompt);

	/* Helper functions */
	void addNewCourse();
	void listCourses();
	void addNewStudent();
	void addEnrollment();
	void printStudent();
	void searchStudent();
	void updateStudent();

	void writeToCsv();
	void readFromCsv();

	void obtainingTestData();
};

#endif
