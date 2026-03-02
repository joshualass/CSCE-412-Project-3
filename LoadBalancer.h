#ifndef _LOADBALANCER_H_
#define _LOADBALANCER_H_

#include <queue>
#include <vector>
#include "Request.h"
#include "Webserver.h"
using namespace std;

struct LoadBalancer {

    size_t check_countdown, active_server_count; 
    char web_server_type;
    queue<Request*> request_queue;
    vector<Webserver> webservers;

    LoadBalancer(int num_webservers, char web_server_type);
    void addRequest(Request* request);
    void simulateClockCycle();

};

#endif