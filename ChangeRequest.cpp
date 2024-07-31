/**********************************************
 * ChangeRequest Implementation File
 * Revision History:
 * - 2024-07-30: Initial version created.
 *--------------------------------
 * Purpose: 
 * This module implements the ChangeRequest class, providing functionality for creating,
 * initializing, querying, and managing change requests. It includes file operations 
 * to store and retrieve change request data, ensuring data integrity and proper handling 
 * of change requests.
 **********************************************/
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#include "ChangeRequest.h"
#include "ObjectNotFoundException.h"

static std::fstream file;

int ChangeRequest::currentChangeIdCount = 0;

/**********************************************
 * Constructor: ChangeRequest
 * Description: Default constructor for the ChangeRequest class.
 **********************************************/
ChangeRequest::ChangeRequest() {}

/**********************************************
 * Constructor: ChangeRequest
 * Description: Parameterized constructor for creating a new ChangeRequest object.
 * Parameters: 
 * - const char* requester: The name of the requester.
 * - Product product: The product associated with the change request.
 * - const char* theDate: The date the change request was submitted.
 **********************************************/
ChangeRequest::ChangeRequest(const char* requester, Product product, const char * theDate){
    changeId = currentChangeIdCount++;
    productName = product;
    strncpy(requestedBy, requester, 29);
    strncpy(date, theDate, 10);
    date[10] = '\0';
    requestedBy[29] = '\0';

    cout << "Change request submitted!" << endl;
}

/**********************************************
 * Function: printId
 * Description: Prints the change request ID.
 **********************************************/
void ChangeRequest::printId() {
    std::cout << "ChangeRequest ID: " << changeId << " " << std::endl;
}

/**********************************************
 * Function: initChangeRequest
 * Description: Initializes the static variable that holds the file where the ChangeRequests are stored. 
 *              The file is opened, and the put pointer is initialized to the end of the file, 
 *              while the get pointer is initialized to the start of the file.
 * Returns: bool - True if the file is successfully opened and initialized, false otherwise.
 **********************************************/
bool ChangeRequest::initChangeRequest() {
    file.open("ChangeRequest.txt", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return false;
    }

    // Find the last changeId from the file
    std::ifstream infile("ChangeRequest.txt", std::ios::binary | std::ios::ate);
    if (!infile.is_open()) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return false;
    }

    std::streampos fileSize = infile.tellg();
    if (fileSize < sizeof(ChangeRequest)) {
        currentChangeIdCount = 0; // No items in file
    } else {
        infile.seekg(-sizeof(ChangeRequest), std::ios::end);
        ChangeRequest lastChangeRequest;
        infile.read(reinterpret_cast<char*>(&lastChangeRequest), sizeof(ChangeRequest));
        currentChangeIdCount = lastChangeRequest.changeId + 1;
    }

    infile.close();
    file.close();
    return true;
}

/**********************************************
 * Function: createChangeRequest
 * Description: Writes a new ChangeRequest object to the file.
 * Parameters: 
 * - const ChangeRequest& changeRequest: The ChangeRequest object to be written to the file.
 **********************************************/
 void ChangeRequest::createChangeRequest(const ChangeRequest& changeRequest) {
    file.open("ChangeRequest.txt", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
    }

    file.write(reinterpret_cast<const char*>(&changeRequest), sizeof(ChangeRequest));
    closeChangeRequest();
}

/**********************************************
 * Function: getChangeRequest
 * Description: Retrieves a ChangeRequest object from the file based on the change ID.
 * Parameters: 
 * - int findChangeId: The change ID of the ChangeRequest to retrieve.
 * Returns: ChangeRequest object if found, otherwise throws an exception.
 **********************************************/
ChangeRequest ChangeRequest::getChangeRequest(int findChangeId) {
    file.open("ChangeRequest.txt", std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
    }

    file.seekg(0, std::ios::beg); // Reset file pointer to beginning
    ChangeRequest changeRequest;
    bool found = false;
    while (!found && file.read(reinterpret_cast<char*>(&changeRequest), sizeof(ChangeRequest))) {
        if (changeRequest.changeId == findChangeId) {
            found = true;
        }
    }

    closeChangeRequest();
    if (found)
        return changeRequest;
    else throw ObjectNotFoundException("Object with this changeID was not found in file");

    return changeRequest;
}

/**********************************************
 * Function: closeChangeRequest
 * Description: Closes the file if it is open.
 **********************************************/
void ChangeRequest::closeChangeRequest() {
    if (file.is_open()) {
        file.close();
    }
}
