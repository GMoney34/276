/**********************************************
 * File: systemControl.cpp
 * -------------------------------------------------------------------------
 * Revision History:
 * - 2024-07-02: Initial version created.
 * - 2024-07-16: Added the initalize statements to systemStartup and systemShutdown
 * - 2024-07-31: Added init and close statements modules that werent there before.
 * -------------------------------------------------------------------------
 * Purpose:
 * This file implements the system control module. It contains functions 
 * for system startup and shutdown.
 **********************************************/

#include "systemControl.h"
#include "scenarioControl.h"
#include <iostream>
#include <fstream>

//================================
// Function implementations
//================================

/**********************************************
 * Function: systemStartup
 * Description: 
 * Initializes the system by loading necessary resources and setting up the environment.
 * Parameters: None
 * Returns: void
 **********************************************/
void systemStartup() {
    initRelease();
    initProduct();
    initRequester();
    initItem();
    initRequest();
}

/**********************************************
 * Function: systemShutdown
 * Description: 
 * Shuts down the system by releasing resources and performing cleanup tasks.
 * Parameters: None
 * Returns: void
 **********************************************/
void systemShutdown() {
    closeRelease();
    closeProduct();
    closeRequester();
    closeItem();
    closeRequest();
    exit(0);
}