#include <iostream>
#include <string>
#include "INIReader.h"

using namespace std;


int main (int argc, char * const argv[]) 
{
	INIReader reader("../Data/config_user.ini");

    if (reader.ParseError() < 0) {
        std::cout << "Can't load 'config_user.ini'\n";
        return 1;
    }
    int ID = 0;
    cout << "user"+to_string(ID++) << endl;
    cout << reader.Get("user0", "username", "UNKNOWN") << endl;
    //str.replace(str.end()-1, str.end(), '1');
    return 0;
}