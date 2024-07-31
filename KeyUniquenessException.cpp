/**********************************************
 * KeyUniquenessException Implementation File
 * Revision History:
 * - 2024-07-30: Initial version created.
 *--------------------------------
 * Purpose: 
 * This module implements the KeyUniquenessException class, providing a custom exception
 * for handling cases where a key is not unique. It inherits from std::logic_error and
 * adds a custom message to the exception.
 **********************************************/ 
#include "KeyUniquenessException.h"
#include <string>  

/**********************************************
 * Constructor: KeyUniquenessException
 * Description: Constructs a KeyUniquenessException with a custom message.
 * Parameters: 
 * - const std::string& message: The custom message describing the exception.
 **********************************************/
KeyUniquenessException::KeyUniquenessException(const string& message): 
logic_error("Release ID is not unique: " + message) {}  
