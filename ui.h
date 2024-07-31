/**********************************************
 *  User Interface Header File
 *  Revision History:
 *  - 2024-07-02: Initial version created.
 * --------------------------------
 *  Purpose: This module contains the declarations for the user interface functions.
 *           It provides functionalities to navigate through the menu and perform
 *           various operations related to change requests, products, and releases.
 **********************************************/
#include <string>
#ifndef UI_H
#define UI_H

 //=============================
 // Function Declarations
 //=============================


//----------------------------------------------------
void runUserInterface();
//Description: Start the main user interface loop.

//----------------------------------------------------
void createMenu();
// Description: Display the create menu and handle user input.

//----------------------------------------------------
void updateMenu(); 
//Description: Display the update menu and handle user input.

//----------------------------------------------------
void viewMenu();
//Description: Display the view menu and handle user input.


#endif