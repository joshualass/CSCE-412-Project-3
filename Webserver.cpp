#include "Webserver.h"
#include "Request.h"
#include <assert.h>
#include <iostream>
#include "HelperFunctions.h"

using namespace std;

Webserver::Webserver(string IP_address, char preferred_job_type) : 
    active(false),
    current_request(nullptr),
    time_left(0),
    preferred_job_type(preferred_job_type),
    IP_address(IP_address)
{}

void Webserver::processRequest(Request* request) {
    assert(current_request == nullptr); //we cannot process a request when we already have a request
    current_request = request;
    time_left = request->time_to_complete;
}

void Webserver::simulateClockCycle() {
    if(current_request != nullptr) {
        time_left -= 1;
        if(time_left <= 0) {
            //job is complete
            cout << GREEN << "Webserver " << IP_address << " has completed this request: " << *current_request << RESET << endl;
            this->current_request->completeRequest();
            this->current_request = nullptr;
        }
    }
}

void Webserver::activate() {
    assert(active == false);
    active = true;
}

void Webserver::deactivate() {
    assert(active == true);
    active = false;
}