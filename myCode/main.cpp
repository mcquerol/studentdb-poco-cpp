#include "SimpleUI.h"

int main (void)
{
	StudentDb db;
	SimpleUI ui(db);

	ui.run();

	return 0;
}
