#ifndef _SWITCH_H_
#define _SWITCH_H_

#include <vector>
#include "LoadBalancer.h"
using namespace std;

struct Switch {

    vector<LoadBalancer> loadBalancers;
    vector<char> loadBalancerTypes;

    Switch(vector<char> types, int servers_per_loadbalancer);

};

#endif