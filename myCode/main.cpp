#include <Poco/LocalDateTime.h>
#include <Poco/DateTimeFormatter.h>
#include <iostream>

int main() {
    // Get the current local date and time
    Poco::LocalDateTime localNow;

    // Format the current local date and time as a string
    std::string formattedLocalDateTime = Poco::DateTimeFormatter::format(localNow, "%Y-%m-%d %H:%M:%S");
    std::cout << "Local DateTime: " << formattedLocalDateTime << std::endl;

    return 0;
}
