#include "Switch.h"
#include <vector>
using namespace std;

Switch::Switch(vector<char> types, int servers_per_loadbalancer) {
    for(char t : types) {
        loadBalancers.push_back(LoadBalancer(servers_per_loadbalancer, t));
    }
}

void Switch::queueRequest(Request* request) {
    for(int i = 0; i < loadBalancerTypes.size(); i++) {
        if(request->type == loadBalancerTypes[i]) {
            loadBalancers[i].addRequest(request);
        }
    }
}

void Switch::simulateClockCycle() {
    for(auto &loadBalancer : loadBalancers) loadBalancer.simulateClockCycle();
}