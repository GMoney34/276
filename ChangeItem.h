/**********************************************
 * ChangeItem Header File
 * Revision History:
 * - 2024-07-30: Initial version created.
 *--------------------------------
 * Purpose: 
 * This module provides a cohesive interface for managing change items, including initialization, 
 * creation, querying, updating status and priority, and displaying operations. It abstracts the 
 * internal implementation details, such as the storage of change items in a file, ensuring data 
 * integrity and proper initialization.
 **********************************************/
#ifndef CHANGEITEM_H
#define CHANGEITEM_H


#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "Product.h"
#include "ProductRelease.h"

//=============================
// Class Declaration
//=============================

class ChangeItem {
public:
    //=============================
    // Enum Declarations
    //=============================
    enum State {
        ASSESSED,
        INPROGRESS,
        DONE,
        CANCELLED
    };

    //=============================
    // Constructor Declarations
    //=============================
    //----------------------------------------------------------
    ChangeItem();
    // Description: Default constructor for the ChangeItem class.

    //----------------------------------------------------------
    ChangeItem(Product product, const char* n, State theState, int priority, const char* reportedDate);
    // Description: Parameterized constructor for creating a new ChangeItem object.
    // Parameters: 
    // - Product product: The product associated with the change item.
    // - const char* n: The description of the change item.
    // - State theState: The state of the change item.
    // - int priority: The priority of the change item.
    // - const char* reportedDate: The date the change was reported.

    //=============================
    // Function Declarations
    //=============================

    //----------------------------------------------------------
    void printState();
    // Description: Prints the current state of the change item.

    //----------------------------------------------------------
    static bool initChangeItem();
    // Description: Initializes the static variable that holds the file where the ChangeItems are stored. 
    //              The file is opened, and the put pointer is initialized to the end of the file, 
    //              while the get pointer is initialized to the start of the file.
    // Returns: bool - True if the file is successfully opened and initialized, false otherwise.

    //----------------------------------------------------------
    static void createChangeItem(const ChangeItem& product);
    // Description: Writes a new ChangeItem object to the file.
    // Parameters: 
    // - const ChangeItem& product: The ChangeItem object to be written to the file.

    //----------------------------------------------------------
    static ChangeItem getChangeItem(int findChangeId);
    // Description: Retrieves a ChangeItem object from the file based on the change ID.
    // Parameters: 
    // - int findChangeId: The change ID of the ChangeItem to retrieve.
    // Returns: ChangeItem object if found, otherwise throws an exception.

    //----------------------------------------------------------
    static ChangeItem queryChangeItem(std::string product);
    // Description: Interacts with the user to create a new ChangeItem or select an existing one based on the product name.
    // Parameters: 
    // - std::string product: The name of the product for which to query change items.
    // Returns: ChangeItem object created or selected by the user.

    //----------------------------------------------------------
    static void updateStatus(State newState, int theChangeId);
    // Description: Updates the status of a ChangeItem in the file based on the change ID.
    // Parameters: 
    // - State newState: The new state to set.
    // - int theChangeId: The change ID of the ChangeItem to update.

    //----------------------------------------------------------
    static void updatePriority(int newPriority, int theChangeId);
    // Description: Updates the priority of a ChangeItem in the file based on the change ID.
    // Parameters: 
    // - int newPriority: The new priority to set.
    // - int theChangeId: The change ID of the ChangeItem to update.

    //----------------------------------------------------------
    static ChangeItem displayChangeItems(std::string product);
    // Description: Displays a list of ChangeItems for a given product and allows the user to select one.
    // Parameters: 
    // - std::string product: The name of the product for which to query change items.
    // Returns: The selected ChangeItem object.

    //----------------------------------------------------------
    static void closeChangeItem();
    // Description: Closes the file if it is open.

private:
    static int currentChangeIdCount;
    int changeId;
    char description[150];
    Product productName;
    char date[11];
    ProductRelease anticipatedRelease;
    int priority;

    State changeItemState;


};
#endif // CHANGE_ITEM_H
