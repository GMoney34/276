/**********************************************
 * ChangeItem Implementation File
 * Revision History:
 * - 2024-07-30: Initial version created.
 *--------------------------------
 * Purpose: 
 * This module implements the ChangeItem class, providing functionality for creating,
 * initializing, querying, and managing change items. It includes file operations 
 * to store and retrieve change item data, ensuring data integrity and proper handling 
 * of change item.
 **********************************************/
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#include "ChangeItem.h"
#include "ObjectNotFoundException.h"

static std::fstream file;

int ChangeItem::currentChangeIdCount = 0;

// Default Constructor: Will create an instance of a ChangeItem.
ChangeItem::ChangeItem() {}

/**********************************************
 * Constructor: ChangeItem
 * Description:
 * The constructor for creating a new ChangeItem object and writing it to the file.
 * The details are copied into the private variables and written to the file.
 * Parameters: 
 * - n: The name of the requester
 * - num: The phone number of the requester
 * - mail: The email of the requester
 * - dept: The department of the requester
 **********************************************/
ChangeItem::ChangeItem(Product product, const char* n, State theState, int newPriority, const char* reportedDate) {
    changeId = currentChangeIdCount++;
    priority = newPriority;
    productName = product;
    strncpy(description, n, 149);
    description[149] = '\0';
    changeItemState = theState;
    strncpy(date, reportedDate, 10);
    date[11] = '\0';
}


// Was used for testing can delete later
void ChangeItem::printState() {
    switch(changeItemState) {
            case ASSESSED:
                std::cout << "ASSESSED" << std::endl;
                break;
            case INPROGRESS:
                std::cout << "IN-PROGRESS" << std::endl;
                break;            
            case DONE:
                std::cout << "Done" << std::endl;
                break;

            case CANCELLED:
                std::cout << "CANCELLED" << std::endl;
                break;
    }
}


/**********************************************
 * Function: initChangeItem
 * Description:
 * Initializes the static variable that holds the file where the ChangeItems are stored. 
 * The file is opened, and the put pointer is initialized to the end of the file, while the get pointer is initialized to the start of the file.
 * Parameters: None
 * Returns: bool: True if the file was opened successfully, otherwise false.
 **********************************************/
bool ChangeItem::initChangeItem() {
    file.open("ChangeItem.txt", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return false;
    }

    // Find the last changeId from the file
    std::ifstream infile("ChangeItem.txt", std::ios::binary | std::ios::ate);
    if (!infile.is_open()) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return false;
    }

    std::streampos fileSize = infile.tellg();
    if (fileSize < sizeof(ChangeItem)) {
        currentChangeIdCount = 0; // No items in file
    } else {
        infile.seekg(-sizeof(ChangeItem), std::ios::end);
        ChangeItem lastChangeItem;
        infile.read(reinterpret_cast<char*>(&lastChangeItem), sizeof(ChangeItem));
        currentChangeIdCount = lastChangeItem.changeId + 1;
    }

    infile.close();
    file.close();
    return true;
}

/**********************************************
 * Function: createChangeItem
 * Description:
 * Writes a new ChangeItem object to the file.
 * Parameters:
 * - changeItem: The ChangeItem object to be written to the file
 **********************************************/
 void ChangeItem::createChangeItem(const ChangeItem& changeItem) {
    file.open("ChangeItem.txt", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
    }

    file.write(reinterpret_cast<const char*>(&changeItem), sizeof(ChangeItem));
    closeChangeItem();
}

/**********************************************
 * Function: getChangeItem
 * Description:
 * Retrieves a ChangeItem object from the file based on the change ID.
 * Parameters:
 * - findChangeId: The change ID of the ChangeItem to retrieve
 * Returns: ChangeItem object if found, otherwise throws an exception
 **********************************************/
ChangeItem ChangeItem::getChangeItem(int findChangeId) {
    file.open("ChangeItem.txt", std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
    }

    file.seekg(0, std::ios::beg); // Reset file pointer to beginning
    ChangeItem changeItem;
    bool found = false;
    while (!found && file.read(reinterpret_cast<char*>(&changeItem), sizeof(ChangeItem))) {
        if (changeItem.changeId == findChangeId) {
            found = true;
        }
    }

    closeChangeItem();
    if (found)
        return changeItem;
    else throw ObjectNotFoundException("Object with this changeID was not found in file");

    return changeItem;
}

/**********************************************
 * Function: queryChangeItem
 * Description:
 * Interacts with the user to create a new ChangeItem or select an existing one based on the product name.
 * Parameters:
 * - product: The name of the product for which to query change items
 * Returns: ChangeItem object created or selected by the user
 **********************************************/
ChangeItem ChangeItem::queryChangeItem(std::string product){
    std::string input;
    int intInput;
    std::cout << std::endl;

    file.open("ChangeItem.txt", std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
    }
    file.seekg(0, std::ios::beg); // Reset file pointer to beginning


    int multiple = 1;
    int counter = 1;
    int currentEntry;
    ChangeItem changeItem;
    std::vector<ChangeItem> changeItems;
    std::cout << "Please select a ChangeItem" << std::endl;
    while (!file.eof()){
        while (file.read(reinterpret_cast<char*>(&changeItem), sizeof(ChangeItem)) && counter < 21) {
            if (product == changeItem.productName.getProductName()){
                currentEntry = multiple * counter;
                changeItems.push_back(changeItem);
                std::cout << currentEntry << ") " << changeItem.description << std::endl;
                counter++;
            }
        }
        if (file.eof())
            std::cout << currentEntry + 1 << ") Add new ChangeItem\n";
        std::cout << "To load next 20 descriptions enter 'N'" << std::endl;
        std::cin >> input;
        if (input == "N"){
            if (file.eof()){
                while (input == "N"){
                    std::cout << "End of list must choose an option" << std::endl;
                    std::cin >> input;
                }
            }
            else {
                multiple++;
                continue;
            }   
        }
        else{
            while (std::stoi(input) < 1 || std::stoi(input) > currentEntry + 1){
                std::cout << "Not a valid option. Try again" << std::endl;
                std::cin >> input;
            }
        break;
        }
    }
    closeChangeItem();
    if (std::stoi(input) != currentEntry + 1)
        return changeItems[std::stoi(input) - 1];
    
    else if (std::stoi(input) == currentEntry + 1){
        std::string itemDescription;
        int itemPriority;
        std::cout << "Enter a description of the ChangeItem (max 40 char): ";
        std::cin >>  itemDescription;
        if (itemDescription.length() > 40)
            itemDescription.substr(0, 40);
        std::cout << std::endl;
        std::cout << "Enter a priority (number between 1-5): ";
        std::cin >> itemPriority;
        std::cout << std::endl;
        while (itemPriority < 1 || itemPriority > 5){
            std::cout << "Not a valid priority. Try again: ";
            std::cin >> itemPriority;
        }
        std::cout << "Enter a status of the ChangeItem: " << std::endl;
        std::cout << "1) Assessed " << std::endl;
        std::cout << "2) In-Progress " << std::endl;
        std::cout << "3) Done " << std::endl;
        std::cout << "4) Cancelled " << std::endl;
        std::cout << "Enter selection: " << std::endl;
        std::cin >> intInput;
        while (intInput < 0 || intInput > 4){
            std::cout << "Not a valid option. Try again: " << std::endl;
            std::cout << "1) Assessed " << std::endl;
            std::cout << "2) In-Progress " << std::endl;
            std::cout << "3) Done " << std::endl;
            std::cout << "4) Cancelled " << std::endl;
            std::cin >> intInput;
        }
        State itemState;
        if (intInput == 1)
            itemState = ChangeItem::ASSESSED;       
        if (intInput == 2)
            itemState = ChangeItem::INPROGRESS;
        if (intInput == 3)
            itemState = ChangeItem::DONE;
        if (intInput == 4)
            itemState = ChangeItem::CANCELLED;
        std::cout << "Enter the release ID (Format: X.X.X.X): ";
        std::string id;
        std::cin >> id;
        bool badId = true;
        while (badId == true){
            badId = false;
            if (id.length() > 7)
                badId = true;
            if (!std::isdigit(id[0]) || !std::isdigit(id[2]) || !std::isdigit(id[4]) || !std::isdigit(id[6]))
                badId = true;
            if (id[1] != '.' || id[3] != '.' || id[5] != '.')
                badId = true;
            if (badId == true){
                std::cout << "Not a valid release ID. Try again (Format: X.X.X.X): ";
            std::cin >> id;
            }
        }
        std::string idDate;
        std::cout << "Enter the date (Format: YYYY-MM-DD): ";
        std::cin >> idDate;
        bool badDate = true;
        while (badDate == true){
            badDate = false;
            if (idDate.length() > 10)
                badDate = true;
            if (!std::isdigit(idDate[0]) || !std::isdigit(idDate[1]) || !std::isdigit(idDate[2]) || !std::isdigit(idDate[3]) || !std::isdigit(idDate[5]) || !std::isdigit(idDate[6]) || !std::isdigit(idDate[8]) || !std::isdigit(idDate[9]))
                badDate = true;
            if (idDate[4] != '-' || idDate[7] != '-')
                badDate = true;
            if (badDate == true) {
                std::cout << "Not a valid date, Try Again (YYYY-MM-DD): ";
                std::cin >> idDate;
            }
        }

        Product changeItemProduct = Product();
        changeItemProduct.updateName(product.c_str());
        //Product changeItemProduct = Product(product.c_str());
        ProductRelease newRelease = ProductRelease (changeItemProduct, id.c_str(), idDate.c_str());
        ChangeItem newChangeItem = ChangeItem(changeItemProduct, itemDescription.c_str(), itemState, itemPriority, idDate.c_str());
        createChangeItem(newChangeItem);
        std::cout << "ChangeItem Created!\n";
        return newChangeItem;
    }
}

/**********************************************
 * Function: updateStatus
 * Description:
 * Updates the status of a ChangeItem in the file based on the change ID.
 * Parameters:
 * - newState: The new state to set
 * - theChangeId: The change ID of the ChangeItem to update
 **********************************************/
void ChangeItem::updateStatus(State newState, int theChangeId){
    file.open("ChangeItem.txt", std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    ChangeItem changeItem;
    bool found = false;
    std::streampos pos;

    while (!found && file.read(reinterpret_cast<char*>(&changeItem), sizeof(ChangeItem))) {
        if (changeItem.changeId == theChangeId) {
            found = true;
            pos = file.tellg(); // Get current position
            pos -= sizeof(ChangeItem); // Adjust position to the start of the current ChangeItem
        }
    }

    if (found) {
        changeItem.changeItemState = newState; // Update the state

        file.seekp(pos); // Move write pointer to the correct position
        file.write(reinterpret_cast<const char*>(&changeItem), sizeof(ChangeItem)); // Write the updated ChangeItem
        std::cout << "ChangeItem with ID " << theChangeId << " has been updated." << std::endl;
    } else {
        std::cerr << "ChangeItem with ID " << theChangeId << " not found." << std::endl;
    }

    closeChangeItem();
}

/**********************************************
 * Function: updatePriority
 * Description:
 * Updates the priority of a ChangeItem in the file based on the change ID.
 * Parameters:
 * - newPriority: The new priority to set
 * - theChangeId: The change ID of the ChangeItem to update
 **********************************************/
void ChangeItem::updatePriority(int newPriority, int theChangeId){ 
        file.open("ChangeItem.txt", std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    ChangeItem changeItem;
    bool found = false;
    std::streampos pos;

    while (!found && file.read(reinterpret_cast<char*>(&changeItem), sizeof(ChangeItem))) {
        if (changeItem.changeId == theChangeId) {
            found = true;
            pos = file.tellg(); // Get current position
            pos -= sizeof(ChangeItem); // Adjust position to the start of the current ChangeItem
        }
    }

    if (found) {
        changeItem.priority = newPriority; // Update the state

        file.seekp(pos); // Move write pointer to the correct position
        file.write(reinterpret_cast<const char*>(&changeItem), sizeof(ChangeItem)); // Write the updated ChangeItem
        std::cout << "ChangeItem with ID " << theChangeId << " has been updated." << std::endl;
    } else {
        std::cerr << "ChangeItem with ID " << theChangeId << " not found." << std::endl;
    }

    closeChangeItem();
}

/**********************************************
 * Function: displayChangeItems
 * Description:
 * Displays a list of ChangeItems for a given product and allows the user to select one.
 * Parameters:
 * - product: The name of the product for which to query change items
 * Returns: The selected ChangeItem object
 **********************************************/
ChangeItem ChangeItem::displayChangeItems(std::string product){
    file.open("ChangeItem.txt", std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
    }
    file.seekg(0, std::ios::beg); // Reset file pointer to beginning

    int multiple = 1;
    int currentEntry;
    std::string input;
    ChangeItem changeItem;
    std::vector<ChangeItem> changeItems;
    bool done = false;
    std::cout << "Please select a ChangeItem" << std::endl;
    while (!done && !file.eof()){
        int counter = 1;
        while (file.read(reinterpret_cast<char*>(&changeItem), sizeof(ChangeItem)) && counter < 21) {
            if (product == changeItem.productName.getProductName()){
                currentEntry = multiple * counter;
                changeItems.push_back(changeItem);
                std::cout << currentEntry << ") " << changeItem.description << std::endl;
                counter++;
            }
        }
        std::cout << "To load next 20 descriptions enter 'N'" << std::endl;
        std::cin >> input;
        if (input == "N"){
            if (file.eof()){
                while (std::stoi(input) < 1 || std::stoi(input) > currentEntry){
                    std::cout << "End of list must choose an option" << std::endl;
                    std::cin >> input;
                }
                done = true;
            }
            else {
                multiple++;
                continue;
            }   
        }
        while (std::stoi(input) < 1 || std::stoi(input) > currentEntry){
            std::cout << "Not a valid option. Try again" << std::endl;
            std::cin >> input;
        }
        break;
    }
    std::cout << "Name: " << changeItems[currentEntry - 1].productName.getProductName() << std::endl;
    std::cout << "Description: " << changeItems[currentEntry - 1].description << std::endl;
    std::cout << "ChangeID: " << changeItems[currentEntry - 1].changeId << std::endl;
    std::cout << "First Reported: " << changeItems[currentEntry - 1].date << std::endl;
    std::cout << "Priority: " << changeItems[currentEntry - 1].priority << std::endl;
    std::cout << "State: ";
    changeItem.printState();
    std::cout << "Anticipated Release: " << changeItems[currentEntry - 1].anticipatedRelease.releaseIdToString() << std::endl;
    closeChangeItem();
}

/**********************************************
 * Function: closeChangeItem
 * Description:
 * Closes the file if it is open.
 **********************************************/
void ChangeItem::closeChangeItem() {
    if (file.is_open()) {
        file.close();
    }
}
