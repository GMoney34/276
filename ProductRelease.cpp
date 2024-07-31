/**********************************************
 * File: Product.cpp
 * -------------------------------------------------------------------------
 * Revision History:
 * - 2024-07-15: Initial version created
 * - 2024-07-31: Version 2 created
 *      - Created releaseIdToString
 * -------------------------------------------------------------------------
 * Purpose:
 * This file contains the implementation of the Release module, showing the 
 * composition of each function listed in the header file. Releases will be 
 * stored in the file ProductRelease.txt. Releases will be appended onto the end 
 * of the file and will be searched for using a linear search.
 **********************************************/
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#include "ProductRelease.h"
#include "Product.h"
#include "KeyUniquenessException.h"
#include "ObjectNotFoundException.h"

//================================
// Static Variables
//================================
static std::fstream file;

//================================
// Function Implementations
//================================

/**********************************************
 * Constructor: Default ProductRelease Constructor
 * Description:
 * Creates a product object.
 * Parameters: none.
 * ********************************************/
//--------------------------------------------------------------------
ProductRelease::ProductRelease() {

}

/**********************************************
 * Constructor: ProductRelease Constructor
 * Description:
 * Creates a ProductRelease object.
 * Parameters: const char* n - The name of the product.
 **********************************************/
//--------------------------------------------------------------------
ProductRelease::ProductRelease(Product theProduct, const char* theReleaseId, const char* theDate) {
    productName = theProduct;
    strcpy(releaseId, theReleaseId);
    strcpy(date, theDate);
    date[10] = '\0';
}

/**********************************************
 * Function: initProductRelease
 * Description:
 * Initializes the static variable that holds the file where the product names go. 
 * It also initializes the file to be read and written to right away.
 * Parameters: None
 * Returns: bool - True if the file is successfully opened and initialized, false otherwise.
 **********************************************/
//--------------------------------------------------------------------
bool ProductRelease::initProductRelease() {
    file.open("ProductRelease.txt", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return false;
    }
    file.close();
    return true;
}

/**********************************************
 * Function: createProductRelease
 * Description:
 * Creates a product and stores it in the file holding all the ProductReleases.
 * Parameters: A ProductRelease to store
 **********************************************/
//--------------------------------------------------------------------
void ProductRelease::createProductRelease(const ProductRelease& productRelease) {
    file.open("ProductRelease.txt", std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
    }

    file.seekg(0, std::ios::beg); // Reset file pointer to beginning
    ProductRelease tempProductRelease;
    while (file.read(reinterpret_cast<char*>(&tempProductRelease), sizeof(ProductRelease))) {
        if (tempProductRelease.productName == productRelease.productName &&  strcmp(tempProductRelease.releaseId, productRelease.releaseId) == 0)
            throw KeyUniquenessException("Product: " + tempProductRelease.productName.getProductName() + " with the ProductRelease: " + std::string(productRelease.releaseId) + " already exists");

    }
    closeProductRelease();
    
    file.open("ProductRelease.txt", std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
    }

    file.write(reinterpret_cast<const char*>(&productRelease), sizeof(ProductRelease));
    cout << "Product Release created!" << std::endl;
    closeProductRelease();
}

/**********************************************
 * Function: getProductRelease
 * Description:
 * Finds a ProductRelease in the file based of a target ReleaseID.
 * Parameters: A ProductReleaseID to find
 * Returns: The ProductRelease object if it is found in the file otherwise an exception is thrown.
 **********************************************/
//--------------------------------------------------------------------
ProductRelease ProductRelease::getProductRelease(const char* findReleaseId) {
    file.open("ProductRelease.txt", std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
    }

    file.seekg(0, std::ios::beg); // Reset file pointer to beginning
    ProductRelease productRelease;
    bool found = false;
    while (!found && file.read(reinterpret_cast<char*>(&productRelease), sizeof(productRelease))) {
        if (strcmp(productRelease.releaseId, findReleaseId) == 0) {
            found = true;
        }
    }

    closeProductRelease();
    if (found)
        return productRelease;
    else throw ObjectNotFoundException("Object with this changeID was not found in file");

    return productRelease;
}

/**********************************************
 * Function: releaseIdToString
 * Description:
 * Converts the const char * holding the release ID into a string.
 * Parameters: A ProductReleaseID to find
 * Returns: A string
 **********************************************/
//--------------------------------------------------------------------
std::string ProductRelease::releaseIdToString(){
    return std::string(releaseId);
}

/**********************************************
 * Function: closeProductRelease
 * Description:
 * Ensures that the file of the ProductReleases is closed
 **********************************************/
//--------------------------------------------------------------------
void ProductRelease::closeProductRelease() {
    if (file.is_open()) {
        file.close();
    }
}
