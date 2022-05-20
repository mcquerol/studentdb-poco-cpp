#include "CSimpleUI.h"

int main (void)
{
	CStudentDb db;
	CSimpleUI ui(db);

	ui.run();

	return 0;
}
