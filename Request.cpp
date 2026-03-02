/**
 * @file Request.cpp
 * @brief Implements the Request struct lifecycle and stream formatting.
 */

#include "Request.h"
#include <iostream>
using namespace std;

/**
 * @brief Initializes a Request with the given parameters.
 */
Request::Request(string IP_in, string IP_out, int time_to_complete, int time_received, char type, bool complete) : 
    IP_in(IP_in),
    IP_out(IP_out),
    time_to_complete(time_to_complete),
    time_received(time_received),
    type(type),
    complete(complete)
{}

/**
 * @brief Updates the internal state of the request to indicate completion.
 */
void Request::completeRequest() {
    complete = true;
}

/**
 * @brief Formats the Request object into a readable string for logging.
 */
ostream& operator<<(ostream& os, const Request& req) {
    os << "Request [IP In: " << req.IP_in 
       << " | IP Out: " << req.IP_out 
       << " | Type: " << req.type 
       << " | Request Time: " << req.time_to_complete 
       << " | Status: " << (req.complete ? "Complete" : "Pending") << "]";
    return os;
}