#include "SimpleUI.h"
#include <iostream>
#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <string>

using boost::asio::ip::tcp;
namespace json = boost::json;

using namespace std;

int main (void)
{
	StudentDb db;
	SimpleUI ui(db);

	ui.run();
//	tcp::iostream stream;
//	stream.connect("www.hhs.users.h-da.cloud", "4242");
//	if (!stream) {
//	    cerr << "Failed to connect to server!" << endl;
//	} else {
//	    cout << "Connected successfully!" << endl;
//	}
//
//	for(int i = 0; i < 10; i++)
//	{
//		stream << "generate\n";
//		stream.flush();
//		string generatingStr;
//		getline(stream, generatingStr);
//	    string jsonStr;
//	    getline(stream, jsonStr);
//	    json::value jv = json::parse(jsonStr);
//
//	    json::object dateOfBirth = jv.at("dateOfBirth").as_object();
//	    int day = dateOfBirth.at("day").as_int64();
//	    int month = dateOfBirth.at("month").as_int64();
//	    int year = dateOfBirth.at("year").as_int64();
//	    cout << day << '.' << month << '.' << 1900 + year << endl;
//	    cout << endl;
//
//	    json::object address = jv.at("location").as_object();
//	    string cityName = string((address.at("city").as_string()).c_str());
//	    string postalCode = string(((address.at("postCode").as_string())).c_str());
//	    string street = string((address.at("street").as_string()).c_str());
//	    cout << "city: " << cityName << endl;
//	    cout << "postal code: " << postalCode << endl;
//	    cout << "street: " << street << endl;
//	    cout << endl;
//
//	    json::object name = jv.at("name").as_object();
//	    string firstName = string((name.at("firstName").as_string()).c_str());
//	    string lastName = string((name.at("lastName").as_string()).c_str());
//	    cout << "first name: " << firstName << endl;
//	    cout << "last name: " << lastName << endl;
//	    cout << endl;
//	}
//	stream << "quit\n";
//	stream.flush();
//	stream.close();

	return 0;
}
