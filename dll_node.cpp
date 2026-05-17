/**
*
* @author - Hugh Hui, Nabiha Khalid Sheikh
* @file dll_node.cpp -  This file contains the constructor.

12/30/2024 - initial creation
05/17/2026 - added statusLevel field for milestone 6

*/

#include <string>
#include "dll_node.h"
#include"milestone5.h"

// Constructor to initialize a node with a specific value
DllNode::DllNode(int value) : key(value), prev(nullptr), next(nullptr) {}

DllNode::DllNode(int myValue, std::string myStatusLevel, std::string myFullName, std::string myAddress, std::string myCity, std::string myState, std::string myZip) : key(myValue), statusLevel(myStatusLevel), fullName(myFullName), address(myAddress), city(myCity), state(myState), zip(myZip), prev(nullptr), next(nullptr) {}

void DllNode::printNode() {
    bool verbose = false;
    if (verbose) {
        logToFileAndConsole("FIFO info from cacheManager.  Node key: " + std::to_string(key) + "; statusLevel: " + statusLevel + "; name: " + fullName + ";address: " + address + "; city: " + city + "; state: " + state + "; zip: " + zip);
    }
    else {
        logToFileAndConsole("FIFO info from cacheManager:  Node key: " + std::to_string(key));
    }
}
