#include "SimpleUI.h"

using namespace std;

int main (void)
{
	StudentDb db;
	SimpleUI ui(db);

	ui.run();

	return 0;
}
