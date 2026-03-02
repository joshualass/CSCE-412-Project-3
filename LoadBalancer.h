/**
 * @file LoadBalancer.h
 * @brief Defines the LoadBalancer struct responsible for queue management and auto-scaling.
 */

#ifndef _LOADBALANCER_H_
#define _LOADBALANCER_H_

#include <queue>
#include <vector>
#include <map>
#include "Request.h"
#include "Webserver.h"
using namespace std;

/**
 * @struct LoadBalancer
 * @brief Manages a queue of requests and scales Webservers dynamically based on load.
 * * The LoadBalancer acts as the middleman between the Switch and the individual 
 * Webservers. It contains a built-in firewall to drop malicious IPs, an internal 
 * queue to hold pending requests, and logic to activate or deactivate servers 
 * based on current traffic demands.
 */
struct LoadBalancer {

    /** @brief Cycles remaining until the load balancer can check if scaling is needed again. */
    size_t check_countdown;
    
    /** @brief The number of Webservers currently powered on and accepting requests. */
    size_t active_server_count; 
    
    /** @brief The specific type of request this load balancer handles (e.g., 'V' or 'S'). */
    char web_server_type;
    
    /** @brief Queue holding incoming requests waiting to be processed. */
    queue<Request*> request_queue;
    
    /** @brief Vector containing all allocated Webserver objects. */
    vector<Webserver> webservers;

    /** * @brief Histogram tracking the number of clock cycles spent with exactly 'k' active servers.
     * * The key represents the number of active servers ('k'), and the value represents 
     * the total number of clock cycles the load balancer spent in that state.
     */
    map<int, int> active_server_histogram;

    /**
     * @brief Constructs a new LoadBalancer object.
     * @param num_webservers The number of servers to allocate for this balancer.
     * @param web_server_type The character representing the type of server traffic handled.
     */
    LoadBalancer(int num_webservers, char web_server_type);
    
    /**
     * @brief Processes an incoming request through the firewall and adds it to the queue.
     * @param request Pointer to the incoming Request object.
     */
    void addRequest(Request* request);
    
    /**
     * @brief Simulates a single clock cycle for the LoadBalancer and its servers.
     * * Evaluates auto-scaling thresholds, assigns queued requests to idle active 
     * servers, and advances the clock cycle for all managed Webservers.
     */
    void simulateClockCycle();

};

#endif