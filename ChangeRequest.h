/**********************************************
 * ChangeRequest Header File
 * Revision History:
 * - 2024-07-30: Initial version created.
 *--------------------------------
 * Purpose: 
 * This module provides a cohesive interface for managing change requests, including initialization, 
 * creation, querying, and closing operations. It abstracts the internal implementation details, 
 * such as the storage of change requests in a file, ensuring data integrity and proper initialization.
 **********************************************/
#ifndef CHANGEREQUEST_H
#define CHANGEREQUEST_H


#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "Product.h"
#include "Requester.h"
#include "ProductRelease.h"

//=============================
// Class Declaration
//=============================

class ChangeRequest {
public:

    //=============================
    // Constructor Declarations
    //=============================
    //----------------------------------------------------------
    ChangeRequest();
    // Description: Default constructor for the ChangeRequest class.

    //----------------------------------------------------------
    ChangeRequest(const char* requester, Product product, const char* theDate);
    // Description: Parameterized constructor for creating a new ChangeRequest object.
    // Parameters: 
    // - const char* requester: The name of the requester.
    // - Product product: The product associated with the change request.
    // - const char* theDate: The date the change request was submitted.

    //=============================
    // Function Declarations
    //=============================

    //----------------------------------------------------------
    void printId();
    // Description: Prints the change request ID.

    //----------------------------------------------------------
    static bool initChangeRequest();
    // Description: Initializes the static variable that holds the file where the ChangeRequests are stored. 
    //              The file is opened, and the put pointer is initialized to the end of the file, 
    //              while the get pointer is initialized to the start of the file.
    // Returns: bool - True if the file is successfully opened and initialized, false otherwise.

    //----------------------------------------------------------
    static void createChangeRequest(const ChangeRequest& product);
    // Description: Writes a new ChangeRequest object to the file.
    // Parameters: 
    // - const ChangeRequest& product: The ChangeRequest object to be written to the file.

    //----------------------------------------------------------
    static ChangeRequest getChangeRequest(int findChangeId);
    // Description: Retrieves a ChangeRequest object from the file based on the change ID.
    // Parameters: 
    // - int findChangeId: The change ID of the ChangeRequest to retrieve.
    // Returns: ChangeRequest object if found, otherwise throws an exception.

    //----------------------------------------------------------
    static void closeChangeRequest();
    // Description: Closes the file if it is open.

private:
    //=============================
    // Private Member Variables
    //=============================

    static int currentChangeIdCount; // Holds the current change request ID count
    int changeId;                    // The change request ID
    char requestedBy[30];            // The name of the requester
    Product productName;             // The product associated with the change request
    ProductRelease release;          // The product release associated with the change request
    char date[11];                   // The date the change request was submitted
};

#endif // CHANGEREQUEST_H
