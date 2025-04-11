#include "SimpleUI.h"

#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <iostream>

#include <thread>

using boost::asio::ip::tcp;
namespace json = boost::json;

using namespace std;

int main (void)
{
	StudentDb db;
	SimpleUI ui(db);

	ui.run();
	return 0;
}
