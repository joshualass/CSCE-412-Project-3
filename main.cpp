#include "LoadBalancer.h"
#include "Request.h"
#include "Webserver.h"
#include "HelperFunctions.h"

using namespace std;

const int num_servers = 10;
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
        num_requests = 6000;
    }
    
    total_clock_cycles = atoi(argv[1]);
    num_requests = atoi(argv[2]);
    n = atoi(argv[3]);

    //generate all the classes. 
    vector<char> 

    return 0;

};  