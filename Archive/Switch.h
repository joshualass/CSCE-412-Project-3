/**
 * @file Switch.h
 * @brief Defines the Switch struct used to route traffic to LoadBalancers.
 */

#ifndef _SWITCH_H_
#define _SWITCH_H_

#include <vector>
#include "LoadBalancer.h"
using namespace std;

/**
 * @struct Switch
 * @brief Acts as a router directing incoming requests to the appropriate LoadBalancer.
 * * The Switch holds multiple LoadBalancers, each dedicated to a specific 
 * type of network request. It inspects incoming requests and forwards them 
 * to the LoadBalancer matching the request's type.
 */
struct Switch {

    /** @brief Collection of LoadBalancers managed by the switch. */
    vector<LoadBalancer> loadBalancers;
    
    /** @brief The types of requests each corresponding LoadBalancer handles. */
    vector<char> loadBalancerTypes;

    /**
     * @brief Constructs a new Switch object.
     * @param types A vector of characters representing the types of LoadBalancers to create.
     * @param servers_per_loadbalancer The number of Webservers to initialize per LoadBalancer.
     */
    Switch(vector<char> types, int servers_per_loadbalancer);

    /**
     * @brief Routes a request to the correct LoadBalancer based on its type.
     * @param request A pointer to the Request object to be routed.
     */
    void queueRequest(Request *request);

    /**
     * @brief Simulates a single clock cycle for all managed LoadBalancers.
     */
    void simulateClockCycle();

};

#endif