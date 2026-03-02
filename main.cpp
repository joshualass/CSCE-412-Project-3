/**
 * @file main.cpp
 * @brief The entry point for the load balancer simulation.
 * * This file handles command-line argument parsing, initializes the simulation
 * parameters, generates the simulated network traffic, and runs the main 
 * clock cycle loop to process requests through the Switch and LoadBalancers.
 * It also tracks performance metrics and outputs simulation summaries.
 */

#include "LoadBalancer.h"
#include "Request.h"
#include "Webserver.h"
#include "HelperFunctions.h"
#include "Switch.h"
#include <iostream>
using namespace std;

/** @brief The default number of servers allocated to each LoadBalancer. */
const int num_servers = 10;

/** @brief Total number of clock cycles the simulation will run. */
int total_clock_cycles;

/** @brief Number of requests to generate per server type. */
int num_requests;

/** @brief Lower bound of the IP range blocked by the firewall. */
int firewall_lower_range;

/** @brief Upper bound of the IP range blocked by the firewall. */
int firewall_upper_range;

/** @brief Number of clock cycles to wait before checking if scaling is needed. */
int n;

/** @brief Tracks the total number of malicious requests dropped by the firewall. */
int total_blocked_requests = 0;

/** @brief Tracks the total number of requests successfully completely by all webservers. */
int total_completed_requests = 0;

/** @brief Global reference to the current clock cycle, used for timestamping requests. */
int current_time = 0;

/** @brief Accumulates the total clock cycles all completed requests spent waiting in the queue. */
long long total_queue_time = 0;

/** @brief Accumulates the total turnaround time (wait time + processing time) for all completed requests. */
long long total_turnaround_time = 0;

/** @brief The minimum number of clock cycles a task requires to complete. */
int min_task_time;

/** @brief The maximum number of clock cycles a task requires to complete. */
int max_task_time;

/**
 * @brief Main execution function for the simulation.
 * * Takes in simulation parameters via command line, sets up the Switch with 
 * designated server types ('P' and 'S'), generates requests, and runs the 
 * simulated clock cycles.
 * * @param argc The number of command-line arguments.
 * @param argv The command-line arguments (total_clock_cycles, num_requests, n, firewall_lower_range, firewall_upper_range) (min_task_time) (max_task_time).
 * @return int Exit status of the program (0 for success).
 */
int main(int argc, char **argv) {

    if(argc < 8) {
        cout << "Usage : ./loadbalancer (total_clock_cycles) (num_requests) (n) (firewall_lower_range) (firewall_upper_range) (min_task_time) (max_task_time)" << endl;
        return 0;
    }
    
    total_clock_cycles = atoi(argv[1]);
    num_requests = atoi(argv[2]);
    n = atoi(argv[3]);
    firewall_lower_range = atoi(argv[4]);
    firewall_upper_range = atoi(argv[5]);
    
    // 2. Parse the new parameters
    min_task_time = atoi(argv[6]);
    max_task_time = atoi(argv[7]);

    //generate all the classes. 
    vector<char> server_types = {
        'P',
        'S'
    };

    //main switch class that 
    Switch s(server_types, num_servers);

    //generate the num_requests requests
    vector<vector<Request*>> requests_at_time(total_clock_cycles);
    for(size_t i = 0; i < server_types.size(); i++) {
        for(int j = 0; j < num_requests; j++) {
            auto request = generateRequest(server_types[i]);
            requests_at_time[request->time_received].push_back(request);
        }
    }

    cout << MAGENTA << string(60, '=') << RESET << endl;
    cout << "SIMULATION CONFIGURATION & START SUMMARY" << endl;
    cout << "Total Clock Cycles: " << total_clock_cycles << endl;
    cout << "Number of Servers: " << num_servers << " per Load Balancer" << endl;
    cout << "Task Time Range: " << min_task_time << " to " << max_task_time << " clock cycles" << endl;
    cout << "Starting Queue Size: 0 (Requests arrive dynamically)" << endl;
    cout << MAGENTA << string(60, '=') << RESET << endl << endl;

    for(int time = 0; time < total_clock_cycles; time++) {
        current_time = time;
        cout << MAGENTA << "Start of cycle " << time << RESET << endl;
        for(const auto& lb : s.loadBalancers) {
            cout << MAGENTA << "  -> [LB Type " << lb.web_server_type << "] Queue Size: " << lb.request_queue.size() << " | Active Servers: " << lb.active_server_count << RESET << endl;
        }
        for(auto request : requests_at_time[time]) {
            s.queueRequest(request);
        }
        s.simulateClockCycle();
    }

    int ending_queue_size = 0;
    int active_servers = 0;
    int inactive_servers = 0;
    
    for (const auto& lb : s.loadBalancers) {
        ending_queue_size += lb.request_queue.size();
        for (const auto& ws : lb.webservers) {
            if (ws.active) active_servers++;
            else inactive_servers++;
        }
    }
    
    cout << endl << MAGENTA << string(60, '=') << RESET << endl;
    cout << "SIMULATION END STATUS SUMMARY" << endl;
    cout << "Ending Queue Size: " << ending_queue_size << " requests remaining" << endl;
    cout << "Total Active Servers: " << active_servers << endl;
    cout << "Total Inactive Servers: " << inactive_servers << endl;
    cout << "Total Original Requests Generated: " << (num_requests * server_types.size()) << endl;
    cout << "Total Firewall Blocked/Discarded Requests: " << total_blocked_requests << endl;
    cout << "Total Successfully Completed Requests: " << total_completed_requests << endl;
    cout << "--- Server Activity Distribution ---" << endl;
    for (const auto& lb : s.loadBalancers) {
        cout << "[LB Type " << lb.web_server_type << "] Cycles spent with 'k' active servers:" << endl;
        for (size_t k = 0; k <= lb.webservers.size(); k++) {
            int cycles_at_k = lb.active_server_histogram.count(k) ? lb.active_server_histogram.at(k) : 0;
            cout << "   k = " << k << " : " << cycles_at_k << " cycles" << endl;
        }
    }

    double avg_queue_time = total_completed_requests > 0 ? (double)total_queue_time / total_completed_requests : 0.0;
    double avg_turnaround_time = total_completed_requests > 0 ? (double)total_turnaround_time / total_completed_requests : 0.0;

    cout << "Average Time Spent in Queue: " << avg_queue_time << " clock cycles" << endl;
    cout << "Average Total Turnaround Time: " << avg_turnaround_time << " clock cycles" << endl;

    cout << MAGENTA << string(60, '=') << RESET << endl;

    return 0;

};