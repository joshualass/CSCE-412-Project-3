#include <string>

using namespace std;

#ifndef _REQUEST_H_
#define _REQUEST_H_

struct Request {
    
    string IP_In, IP_out;
    int time_to_complete, time_received;
    char type;
    bool complete;

};

#endif