#ifndef CSIMPLEUI_H
#define CSIMPLEUI_H

#include "CStudentDb.h"
#include "CWeeklyCourse.h"
#include "CStudent.h"

class CSimpleUI {
private:

	CStudentDb &db;

public:
	/*
	 * constructor takes in a studentDB object by reference
	 */
    CSimpleUI(CStudentDb& db);

    /*
     * the run method executes the UI, generates the csv file
     * and obtains test data from mnl.de:4242
     */
    void run();
};

#endif /* CSIMPLEUI_H */
