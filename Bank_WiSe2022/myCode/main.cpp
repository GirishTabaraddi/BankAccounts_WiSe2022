// Standard (system) header files
#include <iostream>
#include <stdlib.h>

using namespace std;

// Main program
int main (void)
{
    cout << "<last name>, <first name>, <matr.nb.>" << endl << endl;
    
    extern void allTests();
    allTests();
    return 0;
}
