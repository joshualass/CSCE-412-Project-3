#ifndef _LOADBALANCER_H_
#define _LOADBALANCER_H_

#include <queue>
#include <vector>
#include <Request.h>
using namespace std;

struct LoadBalancer {

    queue<Request*> request_queue;
    int check_countdown, active_server_count; 
    vector<Webserver> webservers;

    LoadBalancer(int num_webservers, char web_server_type);
    void addRequest(Request* request);
    void simulateClockCycle();

};

#endif