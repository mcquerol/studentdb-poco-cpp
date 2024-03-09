#ifndef CENROLLMENT_H
#define CENROLLMENT_H

#include "CCourse.h"
#include <string>

class CEnrollment {
private:
    float grade;
    std::string semester;

   const CCourse* course;
public:
    CEnrollment(std::string semester, CCourse* course);

    float getGrade() const;
    std::string getSemester()const ;
    const CCourse* getCourse() const;

	void setGrade(float grade);
};

#endif /* CENROLLMENT_H */
