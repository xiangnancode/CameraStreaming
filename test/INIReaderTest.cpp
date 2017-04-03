// Example that shows simple usage of the INIReader class

#include <iostream>
#include <string>
#include "INIReader.h"

using namespace std;

int main()
{
    INIReader reader("config_user.ini");

    if (reader.ParseError() < 0) {
        std::cout << "Can't load 'config_user.ini'\n";
        return 1;
    }
    /*std::cout << "Config loaded from 'test.ini': version="
              << reader.GetInteger("protocol", "version", -1) << ", name="
              << reader.Get("user", "name", "UNKNOWN") << ", email="
              << reader.Get("user", "email", "UNKNOWN") << ", pi="
              << reader.GetReal("user", "pi", -1) << ", active="
              << reader.GetBoolean("user", "active", true) << "\n";*/

    int ID = 0;
    cout << "user"+to_string(ID++) << endl;
    cout << reader.Get("user0", "username", "UNKNOWN") << endl;
    return 0;
}
