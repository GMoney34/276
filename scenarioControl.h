/**********************************************
 * Scenario Control Header File
 * Revision History:
 * - 2024-07-02: Initial version created.
 *--------------------------------
 * Purpose: This module contains the declarations for the scenario control functions.
 *          It provides functionalities to manage different scenarios in the system.
 **********************************************/

#ifndef SCENARIOCONTROL_H
#define SCENARIOCONTROL_H

 //=============================
 // Function Declarations
 //=============================


//----------------------------------------------------
void control_createRelease();
// Description: Controls the creation of a new product release.

//----------------------------------------------------
void control_createRequest();
// Description: Controls the creation of a new change request.

//----------------------------------------------------
void control_viewItem();
// Description: Controls the viewing of a specific change item.

//----------------------------------------------------
void control_viewReport();
// Description: Controls the viewing of reports.

//----------------------------------------------------
void control_updateItemState();
// Description: Controls the updating of a change item's state.

//----------------------------------------------------
void control_updateItemPriority();
// Description: Controls the updating of a change item's priority.

//----------------------------------------------------
void control_createProduct();
// Description: Controls the creation of a new product.

//----------------------------------------------------
void queryProducts();
// Description: Queries and lists all products.

//----------------------------------------------------
void createItem();
// Description: Creates a new change item.

//----------------------------------------------------
void queryItems();
// Description: Queries and lists all change items.

//----------------------------------------------------
void initRequest();
// Description: Initializes the request subsystem.

//----------------------------------------------------
void initItem();
// Description: Initializes the item subsystem.

//----------------------------------------------------
void initRelease();
// Description: Initializes the release subsystem.

//----------------------------------------------------
void initRequester();
// Description: Initializes the requester subsystem.

//----------------------------------------------------
void initProduct();
// Description: Initializes the product subsystem.

//----------------------------------------------------
void closeRequest();
// Description: Closes the request subsystem.

//----------------------------------------------------
void closeItem();
// Description: Closes the item subsystem.

//----------------------------------------------------
void closeRelease();
// Description: Closes the release subsystem.

//----------------------------------------------------
void closeRequester();
// Description: Closes the requester subsystem.

//----------------------------------------------------
void closeProduct();
// Description: Closes the product subsystem.


#endif // SCENARIOCONTROL_H