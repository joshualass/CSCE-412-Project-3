/**
 * @file HelperFunctions.cpp
 * @brief Implements utility functions for generating IPs and network Requests.
 */

#include "HelperFunctions.h"
#include "Request.h"
#include <string>
#include <iostream>
using namespace std;

/** @brief Global counter to ensure every web server gets a unique IP. */
int webserver_cnt = 0;

/** @brief Global reference to the total number of simulated clock cycles. */
extern int total_clock_cycles;

/**
 * @brief Creates a random IP address for incoming/outgoing network requests.
 * * Uses a standard 192.168.1.x prefix and generates a random final octet 
 * between 0 and 999 to simulate diverse network traffic.
 * * @return string The formatted IP address string.
 */
string generateRandomIP() {
    string random_IP = "192.168.1.";
    int digit = rand() % 1000;
    random_IP += to_string(digit);
    return random_IP;
}

/**
 * @brief Creates a unique, sequential IP address for internal Webservers.
 * * Automatically increments a global counter so no two webservers share an IP.
 * * @return string The formatted sequential IP address string.
 */
string generateWebserverIP() {
    cout << "gwbip" << endl;
    return "192.168.1." + to_string(webserver_cnt++);
}

/**
 * @brief Allocates and initializes a new Request object with random parameters.
 * * @param type The required server type for this request.
 * @return Request* Pointer to the dynamically allocated Request.
 */
Request* generateRequest(char type) {
    return new Request(generateRandomIP(), generateRandomIP(), 10 + rand() % 20, rand() % total_clock_cycles, type, false);
}