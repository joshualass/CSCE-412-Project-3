#include <queue>
#include <vector>
#include <Request.h>

#ifndef _LOADBALANCER_H_
#define _LOADBALANCER_H_

using namespace std;

struct LoadBalancer {

    queue<Request> request_queue;
    int current_time; 
    vector<Webserver> webservers;
    void addRequest(Request request);
    void simulateClockCycle();

};

#endif