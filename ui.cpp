/**********************************************
 * File: ui.cpp
 * -------------------------------------------------------------------------
 * Revision History:
 * - 2024-07-02: Initial version created.
 * - 2024-07-16: Added runUserInterface under each case selection for every switch statement
 * other than the first one, this way the sub-menus return to the main menu when their finished.
 * - 2024-07-31: Fixed the menus to fix up certain input errors.
 * -------------------------------------------------------------------------
 * Purpose:
 * This file implements the user interface module. It contains functions 
 * for running the user interface, displaying menus, and handling user 
 * actions. The functions here facilitate navigation through the menu and 
 * interaction with the user for various operations related to change 
 * requests, products, and releases.
 **********************************************/

#include "ui.h"
#include "scenarioControl.h"
#include "systemControl.h"
#include <iostream>
#include <string>

//================================
// Function implementations
//================================

/**********************************************
 * Function: runUserInterface
 * Description: Main loop for user interface
 * Displays the main menu and handles user selections
 * Parameters: None
 * Returns: void
 **********************************************/
void runUserInterface() {
    char choice;
    do {
        std::cout << "\nMain Menu:\n"
                  << "1) Create\n"
                  << "2) Update\n"
                  << "3) View\n"
                  << "0) Exit\n"
                  << "Enter selection: ";
        std::cin >> choice;
        switch (choice) {
            case '1':
                createMenu();
                break;
            case '2':
                updateMenu();
                break;
            case '3':
                viewMenu();
                break;
            case '0':
                systemShutdown();
                return;
            default:
                std::cout << "Invalid option, please try again.\n";
        }
    } while (choice != '0');
}

/**********************************************
 * Function: createMenu
 * Description: 
 * Displays the create menu and handles user input for creating new items.
 * Parameters: None
 * Returns: void
 **********************************************/
void createMenu() {
    char createChoice;
        std::cout << "\nCreate Menu:\n"
                  << "1) New Change Request\n"
                  << "2) New Product\n"
                  << "3) New Product Release\n"
                  << "0) Exit\n"
                  << "Enter selection: ";
        std::cin >> createChoice;
        switch (createChoice) {
            case '1':
                control_createRequest();
                break;
            case '2':
                control_createProduct();
                break;
            case '3':
                control_createRelease();
                break;
            case '0':
                return;
            default:
                std::cout << "Invalid option, please try again.\n";
        }
}

/**********************************************
 * Function: updateMenu
 * Description: 
 * Displays the update menu and handles user input for updating existing items.
 * Parameters: None
 * Returns: void
 **********************************************/
void updateMenu() {
    char updateChoice;
    std::string changeID;
    int newPriority;
        std::cout << "\nUpdate Menu:\n"
                  << "1) Update ChangeItem State\n"
                  << "2) Update ChangeItem Priority\n"
                  << "0) Exit\n"
                  << "Enter selection: ";
        std::cin >> updateChoice;
        switch (updateChoice) {
            case '1':
                control_updateItemState();
                break;
            case '2':
                control_updateItemPriority();
                break;
            case '0':
                return;
            default:
                std::cout << "Invalid selection. Try again.\n";
        } 
}

/**********************************************
 * Function: viewMenu
 * Description: 
 * Displays the view menu and handles user input for viewing items.
 * Parameters: None
 * Returns: void
 **********************************************/
void viewMenu() {
    char viewChoice;
        std::cout << "\nView Menu:\n"
                  << "1) View Specific ChangeItem\n"
                  << "2) View Reports\n"
                  << "0) Exit\n"
                  << "Enter selection: ";
        std::cin >> viewChoice;
        switch (viewChoice) {
            case '1':
                control_viewItem();
                break;
            case '2':
                control_viewReport();
                break;
            case '0':
                return;
            default:
                std::cout << "Invalid option, please try again.\n";
        }
}
