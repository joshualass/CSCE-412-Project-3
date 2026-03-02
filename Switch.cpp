#include "Switch.h"
#include <vector>
using namespace std;

Switch::Switch(vector<char> types, int servers_per_loadbalancer) {
    for(char t : types) {
        loadBalancers.push_back(LoadBalancer(servers_per_loadbalancer, t));
    }
}

