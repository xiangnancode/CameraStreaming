#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;


void testfunc (char *ptr1) {
    int size = sizeof(ptr1)/sizeof(char);
    char *pstr1 = new char[size];
    copy(ptr1, ptr1+size, pstr1);
    cout << pstr1 << endl;
    ptr1[0] = 'T';
    cout << pstr1 << endl;
}


int main (int argc, char * const argv[]) 
{
    char str1[] = "this is str1 bla bla bla";
    int size = sizeof(str1)/sizeof(char);
    char *pstr1 = new char[size];
    copy(str1, str1+size, pstr1);
    cout << pstr1 << endl;
    testfunc(pstr1);
    cout << pstr1 << endl;
    
    cout << "hello world" << endl;
    return 0;
}