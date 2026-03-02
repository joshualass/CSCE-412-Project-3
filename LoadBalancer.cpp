/**
 * @file LoadBalancer.cpp
 * @brief Implementation of the LoadBalancer routing, firewall, and auto-scaling logic.
 */

#include "LoadBalancer.h"
#include "Webserver.h"
#include "Request.h"
#include "HelperFunctions.h"
#include <vector>
#include <iostream> 
#include <map>

using namespace std;

/** @brief Global wait-time variable for scaling logic. */
extern int n;
/** @brief Global lower boundary for the firewall IP block list. */
extern int firewall_lower_range;
/** @brief Global upper boundary for the firewall IP block list. */
extern int firewall_upper_range;

extern int total_blocked_requests;

/**
 * @brief Initializes a LoadBalancer with a set number of Webservers.
 * * Generates initial Webservers with random IP addresses matching the 
 * balancer's designated web_server_type.
 * * @param num_webservers The initial number of webservers to provision (Note: uses global 'n' for generation loop).
 * @param web_server_type The type of traffic this load balancer will process.
 */
LoadBalancer::LoadBalancer(int num_webservers, char web_server_type) : 
    check_countdown(0),
    active_server_count(0),
    web_server_type(web_server_type)
{
    for(int i = 0; i < num_webservers; i++) {
        webservers.push_back(Webserver(generateWebserverIP(), web_server_type));
    }
}

/**
 * @brief Filters incoming requests through a firewall before queueing them.
 * * Parses the final octet of the incoming request's IP address. If the value 
 * falls within the global firewall range, the request is blocked, logged as 
 * malicious, and deleted from memory. Otherwise, it is pushed to the queue.
 * * @param request Pointer to the Request object to evaluate and queue.
 */
void LoadBalancer::addRequest(Request* request) {
    size_t last_dot_pos = request->IP_in.find_last_of('.');
    if (last_dot_pos != string::npos) {
        int ip_end_value = stoi(request->IP_in.substr(last_dot_pos + 1));
        if (ip_end_value >= firewall_lower_range && ip_end_value <= firewall_upper_range) {
            cout << RED << "[FIREWALL BLOCKED] Dropped malicious request from: " << request->IP_in << RESET << endl;
            total_blocked_requests++;
            delete request; 
            return; 
        }
    }
    request_queue.push(request);
}

/**
 * @brief Evaluates scaling thresholds, delegates requests, and advances time.
 * * Every clock cycle, the load balancer checks if the cooldown timer (check_countdown)
 * has reached zero. If so, it evaluates the ratio of queued requests to active 
 * servers. If traffic is too high, it activates an offline server. If traffic is 
 * low, it deactivates an online server to save resources. 
 * Finally, it delegates requests from the front of the queue to available active 
 * servers and calls simulateClockCycle() on every server.
 */
void LoadBalancer::simulateClockCycle() {
    // cout << "rqs : " << request_queue.size() << " asc : " << active_server_count << endl;
    if(check_countdown) {
        check_countdown--;
    } else {
        if(request_queue.size() + 49 < active_server_count * 50) {
            //when we reach this branch, we need to deactivate a server as we have too many
            for(auto &webserver : webservers) {
                if(webserver.active) {
                    cout << RED << "[LB Type " << web_server_type << "] [SCALE DOWN] " << "Webserver " << webserver.IP_address << " deactivated." << RESET << endl;
                    webserver.deactivate();
                    break;
                }
            }
            check_countdown = n;
            active_server_count--;
        } else if(request_queue.size() + 79 > active_server_count * 80) {
            //when we reach this branch, we need to activate a server as the queue is much larger than the active server count
            for(auto &webserver : webservers) {
                if(!webserver.active) {
                    cout << YELLOW << "[LB Type " << web_server_type << "] [SCALE UP] " << "Webserver " << webserver.IP_address << " activated." << RESET << endl;
                    webserver.activate();
                    break;
                }
            }
            check_countdown = n - 1;
            active_server_count++;
        }
    }

    //simulate a clock cycle for each of the web servers 
    for(auto &webserver : webservers) {
        //give this server a request if possible
        if(webserver.current_request == nullptr && webserver.active && !request_queue.empty()) {
            cout << BLUE << "Webserver " << webserver.IP_address << " has been assigned this request: " << *(request_queue.front()) << RESET << endl;
            webserver.processRequest(request_queue.front());
            request_queue.pop();
        }
        webserver.simulateClockCycle();
    }

    active_server_histogram[active_server_count]++;
}