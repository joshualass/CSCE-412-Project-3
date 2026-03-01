#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include <string>
using namespace std;

struct Request;

struct Webserver {

    bool active;
    Request* current_request;
    int time_left; 
    char preferred_job_type;
    string IP_address;

    Webserver(string IP_address, char preferred_job_type);
    bool processRequest(Request* request);
    void simulateClockCycle();
    void activate();
    void deactivate();

};

#endif