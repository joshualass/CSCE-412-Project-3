/**
 * @file Webserver.h
 * @brief Defines the Webserver struct that handles processing network requests.
 */

#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include <string>
using namespace std;

struct Request;

/**
 * @struct Webserver
 * @brief Simulates a physical server executing network requests over time.
 * * A Webserver can be toggled on or off (active/inactive) by a LoadBalancer. 
 * When active and assigned a Request, it counts down the required clock cycles 
 * until the job is fully processed.
 */
struct Webserver {

    /** @brief True if the server is powered on and capable of accepting requests. */
    bool active;
    /** @brief Pointer to the Request currently being processed (nullptr if idle). */
    Request* current_request;
    /** @brief Number of clock cycles remaining until the current request is complete. */
    int time_left; 
    /** @brief The type of traffic this server is optimized for. */
    char preferred_job_type;
    /** @brief The unique IPv4 address assigned to this server. */
    string IP_address;

    /**
     * @brief Constructs a new Webserver object.
     * @param IP_address The unique IP address for this server.
     * @param preferred_job_type The request type this server handles.
     */
    Webserver(string IP_address, char preferred_job_type);
    
    /**
     * @brief Assigns a new request to this server for processing.
     * @param request Pointer to the Request to be executed.
     */
    void processRequest(Request* request);
    
    /**
     * @brief Advances the processing time by one clock cycle.
     */
    void simulateClockCycle();
    
    /**
     * @brief Powers on the server, making it eligible for new requests.
     */
    void activate();
    
    /**
     * @brief Powers off the server, saving resources.
     */
    void deactivate();

};

#endif