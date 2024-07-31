/**********************************************
 * File: Product.cpp
 * -------------------------------------------------------------------------
 * Revision History:
 * - 2024-07-15: Initial version created
 * - 2024-07-31: Version 2 created
 *      - Changed while loop in queryProducts
 *      - Removed seekFromBeg
 *      - Overloaded comparison operator to compare products
 * -------------------------------------------------------------------------
 * Purpose:
 * This file contains the implementation of the Product module, showing the 
 * composition of each function listed in the header file. Products will be 
 * stored in the file Product.dat. Products will be appended onto the end 
 * of the file and will be searched for using a linear search.
 **********************************************/

#include "product.h"
#include <string>
using namespace std;

//================================
// Static Variables
//================================
static std::fstream pfio;
/* Module scope variable of the file where products are stored. Must be static in order to make it usable by all functions.
Opened in initProduct(). */

//================================
// Function Implementations
//================================

/**********************************************
 * Function: initProduct
 * Description:
 * Initializes the static variable that holds the file where the product names go. 
 * It also initializes the file to be read and written to right away.
 * Parameters: None
 * Returns: bool - True if the file is successfully opened and initialized, false otherwise.
 **********************************************/
bool Product::initProduct() {
    pfio.open("/Users/gurta/Downloads/NEWCMPT276/prod.txt", ios::out | ios::in | ios::app | ios::binary);

    if(!pfio.good()){
        cout << "File not opened... Please try again" << endl;
        return false;
    }

    pfio.seekp(0, ios::end);
    pfio.seekg(0);
    return true;
}

/**********************************************
 * Function: Product (Constructor)
 * Description:
 * Creates a product and stores it in the file holding all the products.
 * Parameters: const char* n - The name of the product.
 **********************************************/
Product::Product(const char* n) {   
        strcpy(name, n);
        pfio.write(reinterpret_cast<char *>(name), 11);
        pfio.flush();

        cout << "Product created!" << endl;
}

/**********************************************
 * Function: Product (Constructor)
 * Description:
 * Creates a product object.
 * Parameters: none.
 **********************************************/
Product::Product() {}

/**********************************************
 * Function: getNextProduct
 * Description:
 * Gets the next product to be read from the file.
 * Parameters: char* product - A buffer to store the product name read from the file.
 * Returns: const char* - The product name read from the file.
 **********************************************/
const char* Product::getNextProduct(char* product) {   
    if (!pfio.read(reinterpret_cast<char*>(product), 11)) {
        return nullptr;  // End of file reached or read error
    }
    return product;
}

/**********************************************
 * Function: getProduct
 * Description:
 * Gets a specific product name from the file given the place of the product name.
 * Parameters: char* product - A buffer to store the product name read from the file.
 *             int n - The position of the product in the file.
 * Returns: const char* - The product name read from the file.
 **********************************************/
const char* Product::getProduct(char* product, int n) {
    pfio.seekp(n*11);
    pfio.read(reinterpret_cast<char *>(product), 11);

    return product;
}

/**********************************************
 * Function: queryProducts
 * Description:
 * Finds a specific product in the array holding all the products using its productID.
 * Parameters: None
 * Returns: int - The product ID if found, otherwise an exception is thrown or returns -1 if user wants to exit.
 **********************************************/
int Product::queryProducts() {
    pfio.seekg(0);
    char buffer[11];
    int count = 0;
    cout << "Please select the product: " << endl << endl;
    string input = "N";
    // Loops through reading 5 product names (55 bytes) at a time and
    // asks the user for input if they want to see the next 5 products
    // or select a product already listed.
    // Will break out of loop when customer selects a number or when
    // the end of the file is reached
    while(input == "N"){
        if(!pfio.read(reinterpret_cast<char *>(buffer), 11)){
            cout << "No more products" << endl;
            cout << "Enter selection: ";
            cin >> input;
            break;
        }
        count++;
        cout << count << ") " << buffer << endl;
        if(count%5 == 0){
            // if 0 returned user will be exited to previous menu
            cout << "0) Exit" << endl;
            cout << "To load next 5 items enter 'N'" << endl;
            cout << "Enter selection: ";
            cin >> input;
        }
    }
    pfio.clear();
    return stoi(input) - 1;
}

/**********************************************
 * Function: createProduct
 * Description:
 * Creates a product and stores it in the array holding all the products.
 * Parameters: None
 * Returns: true if the product created successfully and false if an existing product with that name exists
 **********************************************/
bool Product::createProduct() {
    string prod;
    cout << "Enter product name (max 10 char): ";
    cin >> prod;
    if(prod.length() > 10){
        cout << "Enter a name 10 char or less" << endl;
        return false;
    }
    char buffer[11];
    // the loop goes through the file and checks the product against each word already in the file
    // one by one and if a match is found the error is reported to the user and false is returned,
    // if no match is found the loop stops at the end of the file 
    pfio.seekg(0);
    while(pfio.read(reinterpret_cast<char *>(buffer), 11)){
        if(strcmp(prod.c_str(), buffer) == 0){
            cout << "==ERROR==" << endl;
            cout << "The item you have entered already exists" << endl;
            pfio.clear();
            return false;
        }
    }
    pfio.clear();
    new Product(prod.c_str());
    return true;
}

/**********************************************
 * Function: closeProduct
 * Description:
 * Closes the products file the system is using.
 * Parameters: None
 * Returns: void
 **********************************************/
void Product::closeProduct() {
    pfio.close();
}

/**********************************************
 * Function: operator==
 * Description:
 * Compares a product with another product
 * Parameters: Product&
 * Returns: bool
 **********************************************/
bool Product::operator==(const Product &otherProduct){
    return strcmp(this->name, otherProduct.name) == 0;
}

/**********************************************
 * Function: print
 * Description: Prints the name of the product to the standard output.
 **********************************************/
void Product::print() {
    std::cout << "Product Name: " << this->name  << std::endl;
}

/**********************************************
 * Function: getProductName
 * Description: Retrieves the name of the product.
 * Returns: std::string - The name of the product.
 **********************************************/
std::string Product::getProductName() const {
    return std::string(name);
}

/**********************************************
 * Function: updateName
 * Description: Updates the name of the product.
 * Parameters: 
 * - const char* newName: The new name to assign to the product.
 **********************************************/
void Product::updateName(const char* newName) {
    strcpy(name, newName);
}