#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;


int main (int argc, char * const argv[]) 
{
	const char a[] = "80";
	long b = stoul(a);
	unsigned short c = atoi(a);
	cout << b << endl;

	cout << "hello world" << endl;

    return 0;
}