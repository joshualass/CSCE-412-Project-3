#ifndef _REQUEST_H_
#define _REQUEST_H_

#include <string>
using namespace std;

struct Webserver;

struct Request {

    string IP_in, IP_out;
    int time_to_complete, time_received;
    char type;
    bool complete;

    Request(string IP_in, string IP_out, int time_to_complete, int time_received, char type, bool complete);
    void completeRequest(Webserver& webserver);

};

#endif
