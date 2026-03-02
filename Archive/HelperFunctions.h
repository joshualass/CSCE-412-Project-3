/**
 * @file HelperFunctions.h
 * @brief Declares utility functions and global color constants for terminal output.
 */

#ifndef _HELPER_FUNCTIONS_H_
#define _HELPER_FUNCTIONS_H_

#include <string>
using namespace std;

/** @brief ANSI color code to reset terminal output to default. */
const string RESET = "\033[0m";
/** @brief ANSI color code for red text (used for blocking/scaling down). */
const string RED = "\033[31m";
/** @brief ANSI color code for green text (used for successful completions). */
const string GREEN = "\033[32m";
/** @brief ANSI color code for yellow text (used for scaling up). */
const string YELLOW = "\033[33m";
/** @brief ANSI color code for blue text (used for assigning requests). */
const string BLUE = "\033[34m";
/** @brief ANSI color code for cyan text (used for switch routing). */
const string CYAN = "\033[36m";
/** @brief ANSI color code for magenta text (used for clock cycle headers). */
const string MAGENTA = "\033[35m";

struct Request;

/**
 * @brief Generates a random IPv4 address in the 192.168.1.x subnet.
 * @return string A randomly generated IP address.
 */
string generateRandomIP();

/**
 * @brief Generates sequential IPv4 addresses for Webservers.
 * @return string A sequentially generated IP address.
 */
string generateWebserverIP();

/**
 * @brief Generates a new random network Request.
 * @param type The type of web server requested (e.g., 'P' or 'S').
 * @return Request* A pointer to the newly allocated Request object.
 */
Request* generateRequest(char type);

#endif