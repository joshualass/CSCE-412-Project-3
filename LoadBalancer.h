#include <queue>
#include <vector>
#include <Request.h>

#ifndef _LOADBALANCER_H_
#define _LOADBALANCER_H_

using namespace std;

struct LoadBalancer {

    int n;
    queue<Request*> request_queue;
    int current_time, check_countdown, active_server_count; 
    vector<Webserver> webservers;

    LoadBalancer(int current_time, vector<Webserver> webservers, int n);
    void addRequest(Request* request);
    void simulateClockCycle();

};

#endif