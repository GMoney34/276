/**********************************************
 * Requester Header File
 * Revision History:
 * - 2024-07-02: Initial version created by Sandeep Dhillon
 * - 2024-07-16: Edits by Jovin Dosanjh
 *--------------------------------
 * Purpose:
 * This header file defines the Requester class, which manages the initialization, creation, querying, and closing of requesters 
 * in the system. The class provides methods to initialize the requester arrays, create new requesters (either employees or customers), 
 * query existing requesters by their unique email, and close (remove) requesters from the system. The abstraction ensures that internal 
 * details like requester storage and uniqueness constraints are hidden, while providing a cohesive interface for requester management. 
 * The functions work together to maintain data integrity and support efficient operations involving requesters.
 **********************************************/

#ifndef REQUESTER_H
#define REQUESTER_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstring>

//================================
// Class Declaration
//================================

class Requester {
public:
    //================================
    // Function Declarations
    //================================
    
    //---------------------------------------------------------- 
    static bool initRequester();
    // Description: This function will initialize the file holding the requesters.

    //---------------------------------------------------------- 
    static bool createRequester();
    // Description: This function will create a new employee or customer requester and add them to the file holding the requesters.
    // Exceptions: 
    // A KeyUniquenessException will be thrown if there is already a requester with the same email.
    // An UninitializedException will be thrown if this function is called before initProduct().

    //---------------------------------------------------------- 
    Requester(
        const char* name,          // in - This will be used as the name of the requester
        const char* number,        // in - Every requester must have their phone on file
        const char* email,         // in - Every requester will have a unique email associated with them
        const char* department     // in - If the requester is an employee then their department is recorded
    );
    // Description: The constructor for creating a new Requester object and writing it to the file.

    //----------------------------------------------------------
    Requester();
    // Description: Default constructor for creating a requester object.

    //----------------------------------------------------------  
    static const char* getNextRequester(char* name); 
    // Description: This function will get the next requester name to be read from the file.

    //----------------------------------------------------------
    static const char* getLastRequester(char* name); 
    // Description: This function will get the next requester name to be read from the file.

    //----------------------------------------------------------
    static const char* getRequester(char* name, int n); 
    // Description: This function will get a specific requester name from the file given the place of the requester name which can be prompted from the user using queryRequesters().

    //----------------------------------------------------------
    static int queryRequesters();        
    // Description: This function will find a specific requester based on their unique email associated with them.
    // Exceptions: 
    // A RequesterNotFoundException will be thrown if no requester with the associated email.
    // An UninitializedException will be thrown if this function is called before initProduct().

    //---------------------------------------------------------- 
    static void closeRequester();
    // Description: This function will close the file that contains all requesters.

private:
    char name[31];
    char phoneNumber[12];
    char email[25];
    char department[13];
};

#endif // REQUESTER_H
