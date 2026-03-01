#include <Request.h>

using namespace std;

#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

struct Webserver {

    bool active;
    Request* current_request;
    int time_left; 
    char preferred_job_type;
    bool processRequest(Request* request);
    bool simulateClockCycle();
    void activate();
    void deactivate();

};

#endif