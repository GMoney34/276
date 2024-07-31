/**********************************************
 * File: main.cpp
 * -------------------------------------------------------------------------
 * Revision History:
 * - 2024-07-02: Initial version created.
 * -------------------------------------------------------------------------
 * Purpose:
 * This file contains the main entry point for the Issue Tracking System. It 
 * initializes the system, runs the main user interface loop, and handles 
 * system shutdown. The main function serves as the central control for the 
 * application, coordinating startup, user interaction, and shutdown.
 **********************************************/

#include "ui.h"
#include "systemControl.h"  // Contains startup and shutdown logic
#include <iostream>

//================================
// Function implementations
//================================

/**********************************************
 * Function: main
 * Description:
 * The entry point of the program. It calls the systemStartup function, runs the user interface, and then calls the systemShutdown function.
 * Parameters: None
 * Returns: int: Exit status of the program.
 **********************************************/
int main() {
    // Start-up operations for the system.
    systemStartup();

    // Running the user interface loop.
    runUserInterface();

    return 0;
}

/* Coding Conventions:
 *- Functions are prefixed with their purpose (e.g., control_, query_, etc.).
 *- Constants and macros are written in uppercase.
 *- Use of descriptive variable names.
 *- Indentation is 4 spaces per level.
 *- Each function begins with a comment block describing its purpose, parameters, and return value (if any).
 **********************************************/