/**********************************************
 * ProductRelease Header File
 * Revision History:
 * - 2024-07-30: Initial version created.
 *--------------------------------
 * Purpose: 
 * This module provides a cohesive interface for managing product releases, including initialization, 
 * creation, querying, and closing operations. It abstracts the internal implementation details, 
 * such as the storage of product releases in a file, ensuring data integrity and proper initialization.
 **********************************************/

#ifndef PRODUCTRELEASE_H
#define PRODUCTRELEASE_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "Product.h"

//=============================
// Class Declaration
//=============================

class ProductRelease {
public:
    //=============================
    // Constructor Declarations
    //=============================

    //----------------------------------------------------------
    ProductRelease();
    // Description: Default constructor for the ProductRelease class.

    //----------------------------------------------------------
    ProductRelease(Product theProduct, const char* theReleaseId, const char* theDate);
    // Description: Parameterized constructor for creating a new ProductRelease object.
    // Parameters: 
    // - Product theProduct: The product associated with the release.
    // - const char* theReleaseId: The release ID.
    // - const char* theDate: The release date.

    //=============================
    // Function Declarations
    //=============================

    //----------------------------------------------------------
    void print();
    // Description: Prints the product release details.

    //----------------------------------------------------------
    static bool initProductRelease();
    // Description: Initializes the static variable that holds the file where the ProductReleases are stored. 
    //              The file is opened, and the put pointer is initialized to the end of the file, 
    //              while the get pointer is initialized to the start of the file.
    // Returns: bool - True if the file is successfully opened and initialized, false otherwise.

    //----------------------------------------------------------
    static void createProductRelease(const ProductRelease& product);
    // Description: Writes a new ProductRelease object to the file.
    // Parameters: 
    // - const ProductRelease& product: The ProductRelease object to be written to the file.

    //----------------------------------------------------------
    static ProductRelease getProductRelease(const char* findChangeId);
    // Description: Retrieves a ProductRelease object from the file based on the release ID.
    // Parameters: 
    // - const char* findChangeId: The release ID of the ProductRelease to retrieve.
    // Returns: ProductRelease object if found, otherwise throws an exception.

    //----------------------------------------------------------
    std::string releaseIdToString();
    // Description: Converts the release ID to a string.
    // Returns: std::string - The release ID as a string.

    //----------------------------------------------------------
    static void closeProductRelease();
    // Description: Closes the file if it is open.

private:
    //=============================
    // Private Member Variables
    //=============================

    Product productName;         // The product associated with the release
    char releaseId[8];           // The release ID
    char date[11];               // The release date
};

#endif // PRODUCTRELEASE_H
