#include "Request.h"
using namespace std;

Request::Request(string IP_in, string IP_out, int time_to_complete, int time_received, char type, bool complete) : 
    IP_in(IP_in),
    IP_out(IP_out),
    time_to_complete(time_to_complete),
    time_received(time_received),
    type(type),
    complete(complete)
{}

void Request::completeRequest(Webserver& webserver) {
    complete = true;
    // TODO add logging to show that this request was complete. 
}