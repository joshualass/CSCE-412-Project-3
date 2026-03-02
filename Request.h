/**
 * @file Request.h
 * @brief Defines the Request struct representing a network job.
 */

#ifndef _REQUEST_H_
#define _REQUEST_H_

#include <string>
using namespace std;

/**
 * @struct Request
 * @brief Represents a single network request to be processed by a Webserver.
 * * Contains metadata about the request including its origin IP, destination IP,
 * required processing time, arrival time, and completion status.
 */
struct Request {

    /** @brief The origin IP address of the request. */
    string IP_in;
    /** @brief The destination IP address of the request. */
    string IP_out;
    /** @brief Number of clock cycles required to process this request. */
    int time_to_complete;
    /** @brief The clock cycle during which this request was generated. */
    int time_received;
    /** @brief Character representing the request type ('P', 'S', etc.). */
    char type;
    /** @brief Boolean flag indicating if the request has finished processing. */
    bool complete;

    /**
     * @brief Constructs a new Request object.
     * @param IP_in Origin IP address.
     * @param IP_out Destination IP address.
     * @param time_to_complete Clock cycles needed to finish the job.
     * @param time_received The cycle when this request enters the simulation.
     * @param type The classification type of the request.
     * @param complete Initial completion status (usually false).
     */
    Request(string IP_in, string IP_out, int time_to_complete, int time_received, char type, bool complete);
    
    /**
     * @brief Marks the request as fully processed.
     */
    void completeRequest();

    /**
     * @brief Overloads the stream insertion operator for easy printing.
     * @param os The output stream.
     * @param req The Request to format and print.
     * @return ostream& The modified output stream.
     */
    friend ostream& operator<<(ostream& os, const Request& req);
};

#endif