#include "HelperFunctions.h"
#include "Request.h"
#include <string>
using namespace std;

int webserver_cnt = 0;
extern int total_clock_cycles;

string generateRandomIP() {
    string random_IP = "192.168.1.";
    int digit = rand() % 1000;
    random_IP += to_string(digit);
    return random_IP;
}

string generateWebserverIP() {
    return "192.168.1." + to_string(webserver_cnt++);
}

Request* generateRequest(char type) {
    return new Request(generateRandomIP(), generateRandomIP(), 20 + rand() % 40, rand() % total_clock_cycles, type, false);
}