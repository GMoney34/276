/**********************************************
 * ObjectNotFoundException Implementation File
 * Revision History:
 * - 2024-07-30: Initial version created.
 *--------------------------------
 * Purpose: 
 * This module implements the ObjectNotFoundException class, providing a custom exception
 * for handling cases where an object is not found. It inherits from std::logic_error and
 * adds a custom message to the exception.
 **********************************************/
#include "ObjectNotFoundException.h" 
#include <string> 

/**********************************************
 * Constructor: ObjectNotFoundException
 * Description: Constructs an ObjectNotFoundException with a custom message.
 * Parameters: 
 * - const std::string& message: The custom message describing the exception.
 **********************************************/
ObjectNotFoundException::ObjectNotFoundException(const string& message): 
logic_error("ObjectNotFoundException: " + message) {}  
