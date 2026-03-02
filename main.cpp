#include "LoadBalancer.h"
#include "Request.h"
#include "Webserver.h"
#include "HelperFunctions.h"
#include "Switch.h"

using namespace std;

const int num_servers = 10;
int total_clock_cycles, num_requests;
int n;

int main(int argc, char **argv) {

    int total_clock_cycles, num_requests;

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
    vector<vector<Request*>> requests_at_time(10000);
    for(int i = 0; i < server_types.size(); i++) {
        for(int j = 0; j < num_requests; j++) {
            auto request = generateRequest(server_types[i]);
            requests_at_time[request->time_received].push_back(request);
        }
    }

    for(int time = 0; time <= total_clock_cycles; time++) {
        for(auto request : requests_at_time[time]) {
            s.queueRequest(request);
        }
    }

    return 0;

};  