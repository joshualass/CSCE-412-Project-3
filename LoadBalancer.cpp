#include "LoadBalancer.h"
#include "Webserver.h"
#include "Request.h"
#include "HelperFunctions.h"
#include <vector>
#include <iostream> 

using namespace std;
extern int n, firewall_lower_range, firewall_upper_range;

LoadBalancer::LoadBalancer(int num_webservers, char web_server_type) : 
    check_countdown(0),
    active_server_count(0),
    web_server_type(web_server_type)
{
    for(int i = 0; i < n; i++) {
        webservers.push_back(Webserver(generateWebserverIP(), web_server_type));
    }
}

void LoadBalancer::addRequest(Request* request) {

    request_queue.push(request);
}

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
}