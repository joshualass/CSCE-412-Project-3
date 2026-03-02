#include "LoadBalancer.h"
#include "Request.h"
#include "Webserver.h"
#include "HelperFunctions.h"
#include "Switch.h"
#include <iostream>
using namespace std;

const int num_servers = 10;
int total_clock_cycles, num_requests;
int n;

int main(int argc, char **argv) {

    if(argc < 4) {
        cout << "Usage : ./loadbalancer (total_clock_cycles) (num_requests) (n)" << endl;
        return 0;
    }

    if(argc >= 2) {
        total_clock_cycles = atoi(argv[1]);
    } else {
        total_clock_cycles = 10000;
    }

    if(argc >= 3) {
        num_requests = atoi(argv[2]);
    } else {
        num_requests = 1000;
    }
    
    total_clock_cycles = atoi(argv[1]);
    num_requests = atoi(argv[2]);
    n = atoi(argv[3]);

    //generate all the classes. 
    vector<char> server_types = {
        'P',
        'S'
    };

    //main switch class that 
    Switch s(server_types, num_servers);

    //generate the num_requests requests
    vector<vector<Request*>> requests_at_time(total_clock_cycles);
    for(size_t i = 0; i < server_types.size(); i++) {
        for(int j = 0; j < num_requests; j++) {
            auto request = generateRequest(server_types[i]);
            requests_at_time[request->time_received].push_back(request);
        }
    }

    for(int time = 0; time < total_clock_cycles; time++) {
        cout << "start of cycle: " << time << endl;
        for(auto request : requests_at_time[time]) {
            cout << "queue request: " << (*request) << endl;
            s.queueRequest(request);
        }
        s.simulateClockCycle();
    }

    return 0;

};  