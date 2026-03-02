/**
 * @file Webserver.cpp
 * @brief Implements the Webserver lifecycle and clock cycle simulation logic.
 */

#include "Webserver.h"
#include "Request.h"
#include <assert.h>
#include <iostream>
#include "HelperFunctions.h"

using namespace std;

extern int total_completed_requests;

extern int current_time;

extern long long total_queue_time;

extern long long total_turnaround_time;

extern int total_completed_requests;

/**
 * @brief Initializes an inactive Webserver with no active requests.
 */
Webserver::Webserver(string IP_address, char preferred_job_type) : 
    active(false),
    current_request(nullptr),
    time_left(0),
    preferred_job_type(preferred_job_type),
    IP_address(IP_address)
{}

/**
 * @brief Begins processing a new Request.
 * * Asserts that the server is not already busy before taking on the new job.
 * Sets the internal countdown timer to the request's required time.
 * * @param request Pointer to the assigned Request.
 */
void Webserver::processRequest(Request* request) {
    assert(current_request == nullptr); //we cannot process a request when we already have a request
    current_request = request;
    time_left = request->time_to_complete;
}

/**
 * @brief Decrements the remaining time on the current request.
 * * If the timer reaches zero, the request is marked complete, logged to the 
 * terminal in green, and the server's current_request pointer is reset to 
 * nullptr so it can accept a new job.
 */
void Webserver::simulateClockCycle() {
    if(current_request != nullptr) {
        time_left -= 1;
        if(time_left <= 0) {
            total_queue_time += (current_request->time_started_processing - current_request->time_received);
            total_turnaround_time += (current_time - current_request->time_received);
            total_completed_requests++;
            cout << GREEN << "Webserver " << IP_address << " has completed this request: " << *current_request << RESET << endl;
            this->current_request->completeRequest();
            this->current_request = nullptr;
        }
    }
}

/**
 * @brief Activates the server.
 * * Asserts that the server is currently inactive before changing state.
 */
void Webserver::activate() {
    assert(active == false);
    active = true;
}

/**
 * @brief Deactivates the server.
 * * Asserts that the server is currently active before changing state.
 */
void Webserver::deactivate() {
    assert(active == true);
    active = false;
}