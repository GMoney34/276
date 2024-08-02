/**********************************************
 * File: scenarioControl.cpp
 * -------------------------------------------------------------------------
 * Revision History:
 * - 2024-07-02: Initial version created.
 * - 2024-07-16: Added the logic to each function except control_createRequest, control_updateItemPriority, 
 * control_viewReport, control_updateItemState, initRequest, closeRequest.
 * - 2024-07-31: ADded the logic for all the functions that werent implemented in previous releases.
 * -------------------------------------------------------------------------
 * Purpose:
 * This file implements the scenario control module. It contains functions 
 * for controlling different scenarios in the system. The functions here 
 * facilitate the creation of change requests, products, and releases, as 
 * well as viewing specific change items.
 **********************************************/

#include "scenarioControl.h"
#include "Product.h"
#include "ProductRelease.h"
#include "Requester.h"
#include "ChangeItem.h"
#include "requester.h"
#include "ChangeRequest.h"
#include <iostream>
#include <string>

using namespace std;
//================================
// Function implementations
//================================

/**********************************************
 * Function: control_createRelease
 * Description:
 * Controls the creation of a new product release. Prompts the user to add 
 * another product release until they choose not to.
 * Parameters: None
 * Returns: void
 **********************************************/
void control_createRelease() {
    // Logic for creating a release
    char anotherRelease = 'Y';
    ProductRelease pr;
    Product p1 = Product();
    char buffer[11];
    char okay[40];
    char date[11];
    do {
        int n = Product::queryProducts();
        if(n == -1){
            return;
        }
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
                std::cout << "Not a valid release ID. Try again (X.X.X.X): ";
            std::cin >> id;
            }
        }
        std::strcopy(okay, id);
        std::string idDate;
        std::cout << "Enter the date of the release (YYYY-MM-DD): ";
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
        std::strcopy(date, idDate);
        //cout<< "Enter the releaseID: \n";
        //cin >> okay;
        //cout << "Enter the date of the release (YYYY-MM-DD): \n";
        //cin >> date;
        const char* charry = Product::getProduct(buffer,n);
        p1.updateName(charry);
        ProductRelease pr(p1, okay, date);
        ProductRelease::createProductRelease(pr);
        std::cout << "Would you like to add another product release?(Y/N): ";
        std::cin >> anotherRelease;
    } while (anotherRelease == 'Y');
}

/**********************************************
 * Function: control_createRequest
 * Description: Handles the logic for creating a new change request. 
 *              It interacts with the user to input the necessary details, such as requester information, product, and date.
 *              It also allows the user to create multiple change requests in a loop.
 **********************************************/
void control_createRequest() {
    // Logic for creating a change request FIX THIS
    char anotherRequest = 'Y';
    //ChangeItem cc = ChangeItem();
    char buffer[11];
    std::string idDate;
    char name[30];
    Product pr = Product();
    do {
        std::cout << "Create New Change Request:\n";
        std::cout << "Existing Requester? (Y/N)\n";
        char req;
        cin >> req;

        if(req == 'N') {
            req = 'Y';
                while((req == 'Y') && (!Requester::createRequester())) {
                cout << "Try again? (Y//N) \n";
                cin >> req;
            }
            if(req == 'N'){
                return;
            }
        } 
        int i = Requester::queryRequesters();
        if(i == -1){
            return;
        }
        const char* requester = Requester::getRequester(name, i);
        int v = Product::queryProducts();
        if(v == -1){
            return;
        }
        cout << "Please input the date(YYYY-MM-DD): ";
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
        const char* date = idDate.c_str();
        const char* products = Product::getProduct(buffer, v);
        pr.updateName(products);
        string str(products);
        ChangeItem::queryChangeItem(str);
        ChangeRequest ChangeRequest(requester, pr, date);
        ChangeRequest::createChangeRequest(ChangeRequest);
        std::cout << "Would you like to add another change request?(Y/N): ";
        std::cin >> anotherRequest;
    } while(anotherRequest == 'Y');
}

/**********************************************
 * Function: control_viewItem
 * Description:
 * Controls the viewing of a specific change item. Prompts the user to view 
 * another item until they choose not to.
 * Parameters: None
 * Returns: void
 **********************************************/
void control_viewItem() {
    // Logic for viewing a change item
    char anotherViewItem = 'Y';
    char buffer[11];
    do {
        int i;
        i = Product::queryProducts();
        if(i == -1){
            return;
        }
        const char* charry = Product::getProduct(buffer,i);
        string str(charry);
        ChangeItem::displayChangeItems(str);
        std::cout << "Would you like to view another ChangeItem(Y/N): ";
        std::cin >> anotherViewItem;
    } while (anotherViewItem == 'Y');
}

/**********************************************
 * Function: control_updateItemState
 * Description: Handles the logic for updating the state of a change item.
 *              It prompts the user for the ChangeId and the new state, then updates the state of the change item.
 *              Allows the user to update multiple items in a loop.
 **********************************************/
void control_updateItemState() {
    // Logic for updating change item state
    char anotherUpdateItemState = 'Y';
    do{
        int changeID;
        std::cout << "Enter the associated ChangeId of the Change Request: \n";
        cin >> changeID;
        int selection;
        cout << "What status would you like to change this Change Request to: " << endl;
        cout << "1) Assessed" << endl;
        cout << "2) In-Progress" << endl;
        cout << "3) Done" << endl;
        cout << "4) Cancelled" << endl;
        cout << "0) Exit" << endl;
        cout << "Enter Selection: ";
        cin >> selection;
        
        if (selection == 0)
            return;
        else if (selection == 1)
            ChangeItem::updateStatus(ChangeItem::ASSESSED, changeID);
        else if (selection == 2)
            ChangeItem::updateStatus(ChangeItem::INPROGRESS, changeID);
        else if (selection == 3)
            ChangeItem::updateStatus(ChangeItem::DONE, changeID);
        else if (selection == 4)
            ChangeItem::updateStatus(ChangeItem::CANCELLED, changeID);
        else
            cout << "Invalid selection." << endl;

        std::cout << "Would you like to update another item state? (Y/N):  ";
        std::cin >> anotherUpdateItemState;
        } while (anotherUpdateItemState == 'Y');
}

/**********************************************
 * Function: control_updateItemPriority
 * Description: Handles the logic for updating the priority of a change item.
 *              It prompts the user for the ChangeId and the new priority, then updates the priority of the change item.
 *              Allows the user to update multiple items in a loop.
 **********************************************/
void control_updateItemPriority() {
    // Logic for updating change item priority
    char anotherUpdateItemPriority = 'Y';
    do {
        int changeID;
        cout << "Enter the associated ChangeId of the Change Item: ";
        cin >> changeID;
        int newPriority;
        cout << "Enter a new Priority(number between 1-5): ";
        cin >> newPriority;
        ChangeItem::updatePriority(newPriority, changeID);
        std::cout << "Would you like to update another item priority? (Y/N): ";
        std::cin >> anotherUpdateItemPriority;
    } while(anotherUpdateItemPriority == 'Y');
}

/**********************************************
 * Function: control_createProduct
 * Description:
 * Controls the creation of a new product. Prompts the user to add 
 * another product until they choose not to.
 * Parameters: None
 * Returns: void
 **********************************************/
void control_createProduct() {
    // Logic for creating a product
    char anotherProduct = 'Y';
    do {
        Product::createProduct();
        std::cout << "Would you like to add another product?(Y/N): ";
        std::cin >> anotherProduct;
    } while (anotherProduct == 'Y');
}

/**********************************************
 * Function: queryProducts
 * Description:
 * Queries the available products.
 * Parameters: None
 * Returns: void
 **********************************************/
void queryProducts() {
    // Logic for querying products
    Product::queryProducts();
}

/**********************************************
 * Function: createItem
 * Description:
 * Controls the creation of a new change item.
 * Parameters: None
 * Returns: void
 **********************************************/
void createItem() {
    // Logic for creating a change item
    ChangeItem cc = ChangeItem();
    ChangeItem::createChangeItem(cc);
}

/**********************************************
 * Function: viewReport
 * Description:
 * Controls the viewing of a report.
 * Parameters: None
 * Returns: void
 **********************************************/
void control_viewReport() {
    //Logic for viewing a report
}

/**********************************************
 * Function: queryItems
 * Description:
 * Queries the available change items.
 * Parameters: None
 * Returns: void
 **********************************************/
void queryItems() {
    // Logic for querying change items
    ChangeItem::queryChangeItem("");
}

void initRequest() {
    // Logic for initializing requests
    Requester::initRequester();
}

/**********************************************
 * Function: initItem
 * Description:
 * Initializes the change items.
 * Parameters: None
 * Returns: void
 **********************************************/
void initItem() {
    // Logic for initializing items
    ChangeItem::initChangeItem();
}

/**********************************************
 * Function: initRelease
 * Description:
 * Initializes the releases.
 * Parameters: None
 * Returns: void
 **********************************************/
void initRelease() {
    // Logic for initializing release
    ProductRelease::initProductRelease();
}

/**********************************************
 * Function: initRequester
 * Description:
 * Initializes the requesters.
 * Parameters: None
 * Returns: void
 **********************************************/
void initRequester() {
    // Logic for initializing requesters
    Requester::initRequester();
}

/**********************************************
 * Function: initProduct
 * Description:
 * Initializes the products.
 * Parameters: None
 * Returns: void
 **********************************************/
void initProduct() {
    // Logic for initializing products
    Product::initProduct();
}

void closeRequest() {
    // Logic for closing requests
    ChangeRequest::closeChangeRequest();
}

/**********************************************
 * Function: closeItem
 * Description:
 * Closes the change items.
 * Parameters: None
 * Returns: void
 **********************************************/
void closeItem() {
    // Logic for closing items
    ChangeItem::closeChangeItem();
}

/**********************************************
 * Function: closeRelease
 * Description:
 * Closes the releases.
 * Parameters: None
 * Returns: void
 **********************************************/
void closeRelease() {
    // Logic for closing releases
    ProductRelease::closeProductRelease();
}

/**********************************************
 * Function: closeRequester
 * Description:
 * Closes the requesters.
 * Parameters: None
 * Returns: void
 **********************************************/
void closeRequester() {
    // Logic for closing requesters
    Requester::closeRequester();
}

/**********************************************
 * Function: closeProduct
 * Description:
 * Closes the products.
 * Parameters: None
 * Returns: void
 **********************************************/
void closeProduct() {
    // Logic for closing products
    Product::closeProduct();
}
