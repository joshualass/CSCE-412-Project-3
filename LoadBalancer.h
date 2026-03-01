#ifndef _LOADBALANCER_H_
#define _LOADBALANCER_H_

#include <queue>
#include <vector>
#include <Request.h>
using namespace std;

struct LoadBalancer {

    int n;
    queue<Request*> request_queue;
    int check_countdown, active_server_count; 
    vector<Webserver> webservers;

    LoadBalancer(vector<Webserver> webservers, int n);
    void addRequest(Request* request);
    void simulateClockCycle();

};

#endif