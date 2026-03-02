/**
 * @file Switch.cpp
 * @brief Implements the Switch routing and simulation logic.
 */

#include "Switch.h"
#include "Request.h"
#include "LoadBalancer.h"
#include "HelperFunctions.h"
#include <vector>
#include <iostream>
using namespace std;

/**
 * @brief Initializes the Switch and creates its associated LoadBalancers.
 * * Iterates through the provided types and creates a LoadBalancer for each,
 * passing along the specified number of initial servers.
 * * @param types Vector of request types (e.g., 'P', 'S').
 * @param servers_per_loadbalancer Initial server count for each LoadBalancer.
 */
Switch::Switch(vector<char> types, int servers_per_loadbalancer) : loadBalancerTypes(types) {
    for(char t : types) {
        loadBalancers.push_back(LoadBalancer(servers_per_loadbalancer, t));
    }
}

/**
 * @brief Matches an incoming request to its designated LoadBalancer.
 * * Checks the type of the given request and pushes it to the LoadBalancer
 * that processes that specific type. Logs the routing event to the terminal.
 * * @param request Pointer to the incoming Request.
 */
void Switch::queueRequest(Request* request) {
    for(size_t i = 0; i < loadBalancerTypes.size(); i++) {
        if(request->type == loadBalancerTypes[i]) {
            cout << CYAN << *request << " sent to Load Balancer of Type: " << loadBalancerTypes[i] << endl;
            loadBalancers[i].addRequest(request);
        }
    }
}

/**
 * @brief Advances the simulation by one cycle for all LoadBalancers.
 * * Iterates through all LoadBalancers held by the Switch and calls their
 * simulateClockCycle() functions.
 */
void Switch::simulateClockCycle() {
    for(auto &loadBalancer : loadBalancers) loadBalancer.simulateClockCycle();
}