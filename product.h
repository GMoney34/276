/**********************************************
 * Product Header File
 * Revision History:
 * - 2024-07-02: Initial version created.
 * - 2024-07-31: Version 2 created
 *--------------------------------
 * Purpose: 
 * This module provides a cohesive interface for managing products, including initialization, 
 * creation, querying, and closing operations. It abstracts the internal implementation details, 
 * such as the storage of products in a file, ensuring data integrity and proper initialization.
 **********************************************/

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

//=============================
// Class Declaration
//=============================

class Product {
    public:
        //=============================
        // Static Function Declarations
        //=============================
        
        //----------------------------------------------------------
        static bool initProduct();
        // Description: Initializes the static variable that holds the file where the product names go. 
        //              It also initializes the file to be read and written to right away.
        // Returns: bool - True if the file is successfully opened and initialized, false otherwise.

        //----------------------------------------------------------
        Product(const char* n);
        // Description: Creates a product and stores it in the file holding all the products.
        // Parameters: const char* n - The name of the product.
        // Exceptions: KeyUniquenessException - Thrown if there is already a product with the same name.
        //             UninitializedException - Thrown if this function is called before initProduct().

        //----------------------------------------------------------
        Product();
        // This function will create a product object

        //---------------------------------------------------------- 
        static const char* getNextProduct(char* product);
        // Description: Gets the next product to be read from the file.
        // Parameters: char* product - A buffer to store the product name read from the file.
        // Returns: const char* - The product name read from the file.

        //----------------------------------------------------------
        static const char* getProduct(char* product, int n);
        // Description: Gets a specific product name from the file given the place of the product name.
        // Parameters: char* product - A buffer to store the product name read from the file.
        //             int n - The position of the product in the file.
        // Returns: const char* - The product name read from the file.

        //----------------------------------------------------------
        static int queryProducts();
        // Description: Finds a specific product in the array holding all the products using its productID.
        // Exceptions: IdNotFoundException - Thrown if no product with the associated ID is found in the array.
        //             UninitializedException - Thrown if this function is called before initProduct().
        // Returns: int - The product ID if found, otherwise an exception is thrown.

        //----------------------------------------------------------
        static bool createProduct();
        // Description: Creates a product and stores it in the array holding all the products.
        // Exceptions: KeyUniquenessException - Thrown if there is already a product with the same name.
        //             UninitializedException - Thrown if this function is called before initProduct().

        //----------------------------------------------------------
        static void closeProduct();
        // Description: Closes the products file the system is using.

        void print();
        //----------------------------------------------------------
        bool operator==(const Product &otherProduct);
        // Description: Overloads the == operator to compare products

        std::string getProductName() const;

        void updateName(const char* newName);

    private:
        char name[11];
};
#endif