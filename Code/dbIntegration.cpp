// +---------------------------+--------+
// |         Mnexacore         | ef1500 |
// +---------------------------+--------+
// |     Database Integration Code      |
// +---------------------------+--------+

#include <cstdio>
#include <sqlite3.h>

//This file is supposed to act as a "middle man" between the GUI and the SVM.
//It transports data to and from the SVM, and to any other files that may require
//The database.
