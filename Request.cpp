#include "Request.h"
#include <iostream>
using namespace std;

Request::Request(string IP_in, string IP_out, int time_to_complete, int time_received, char type, bool complete) : 
    IP_in(IP_in),
    IP_out(IP_out),
    time_to_complete(time_to_complete),
    time_received(time_received),
    type(type),
    complete(complete)
{}

void Request::completeRequest() {
    complete = true;
}

ostream& operator<<(ostream& os, const Request& req) {
    os << "Request [IP In: " << req.IP_in 
       << " | IP Out: " << req.IP_out 
       << " | Type: " << req.type 
       << " | Request Time: " << req.time_to_complete 
       << " | Status: " << (req.complete ? "Complete" : "Pending") << "]";
    return os;
}