#include "HelperFunctions.h"
#include <string>
using namespace std;

int webserver_cnt = 0;

string generateRandomIP() {
    string random_IP = "192.168.1.";
    int digit = rand() % 1000;
    random_IP += to_string(digit);
    return random_IP;
}

string generateWebserverIP() {
    return "192.168.1." + to_string(webserver_cnt++);
}