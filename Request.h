#include <string>

using namespace std;

#ifndef _REQUEST_H_
#define _REQUEST_H_

struct Request {
    
    string IP_In, IP_out;
    int num_cycles;
    char type;
    bool complete;

};

#endif