/**********************************************
 * File: Requester.cpp
 * -------------------------------------------------------------------------
 * Revision History:
 * - 2024-07-16: Initial version created by Jovin Dosanjh
 * - 2024-07-31: Version 2 by Jovin Dosanjh
 *      - Changed while loop in query requesters
 *      - Switched createRequester to return a boolean value
 *      - Added getLastRequester
 *      - Removed seekFromBeg
 * -------------------------------------------------------------------------
 * Purpose:
 * The implementation of the Requester module shows the composition of each function listed in the header file.
 * The requesters will be stored in the file Requester.dat, for which the file path must be pasted into the function
 * initRequester(). Requesters will be appended onto the end of the file and will be searched for using a linear search.
 **********************************************/

#include "requester.h"
#include <string>
using namespace std;

//================================
// Module scope variable
//================================
static std::fstream rfio;
/* Module scope variable of the file where requesters are stored. Must be static in order to make it usable by all functions.
Opened in initRequester(). */

//================================
// Function implementations
//================================

/**********************************************
 * Function: initRequester
 * Description:
 * Initializes the static variable that holds the file where the requesters are stored. 
 * The file is opened, and the put pointer is initialized to the end of the file, while the get pointer is initialized to the start of the file.
 * Parameters: None
 * Returns: bool: True if the file was opened successfully, otherwise false.
 **********************************************/
bool Requester::initRequester() {
    rfio.open("req.txt", ios::out | ios::in | ios::app | ios::binary);

    if(!rfio.good()){
        cout << "File not opened... Please try again" << endl;
        return false;
    }

    rfio.seekg(0);
    rfio.seekp(0, ios::end);
    return true;
}

/**********************************************
 * Function: Requester
 * Description:
 * The constructor for creating a new Requester object and writing it to the file.
 * The details are copied into the private variables and written to the file.
 * Parameters: 
 * - n: The name of the requester
 * - num: The phone number of the requester
 * - mail: The email of the requester
 * - dept: The department of the requester
 **********************************************/
Requester::Requester(
    const char* n,          
    const char* num,   
    const char* mail,         
    const char* dept   
) {
    strcpy(name, n);
    strcpy(phoneNumber, num);
    strcpy(email, mail);
    strcpy(department, dept);
    rfio.seekp(0, ios::end);
    rfio.write(reinterpret_cast<char *>(this), 81);
    rfio.flush();

    cout << "Requester added!" << endl;
}

/**********************************************
 * Function: Requester
 * Description:
 * The constructor for creating a new Requester object
 * Parameters: None
 **********************************************/
Requester::Requester(){}

/**********************************************
 * Function: createRequester
 * Description:
 * This function will create a new employee or customer requester and add them to the file holding the requesters.
 * Prompts the user for details like name, phone number, email, and department.
 * Parameters: None
 * Returns: true if the requester is successfully added or false if the requester already exists or if input length too long.
 **********************************************/
bool Requester::createRequester() {   
    string name;
    string num;
    string mail;
    string dept;
    cout << "New Requester: " << endl;
    // get email first and check for matching a matching email already in the file
    cout << "Email (24 char or less): ";
    cin >> mail;
    if(mail.length() > 24){
        cout << "Enter an email 24 char or less" << endl;
        return false;
    }
    char buffer[25];
    rfio.seekg(43, ios::beg);
    // the loop goes through the file and checks the product against each word already in the file
    // one by one and if a match is found the error is reported to the user and false is returned,
    // if no match is found the loop stops at the end of the file 
    while(rfio.read(reinterpret_cast<char *>(buffer), 25)){
        if(strcmp(mail.c_str(), buffer) == 0){
            cout << "==ERROR==" << endl;
            cout << "The item you have entered already exists" << endl;
            rfio.clear();
            return false;
        }
        rfio.seekg(56, ios::cur);
    }
    rfio.clear();
    cout << "Name (30 char max): ";
    cin.ignore();
    getline(cin, name);
    if(name.length() > 30){
        cout << "Enter a name 30 char or less" << endl;
        return false;
    }
    cout <<  "Phone Number (11 digits max, no dashes): ";
    cin >> num;
    if(num.length() > 11){
        cout << "Enter a number 11 char or less" << endl;
        return false;
    }
    cout << "Department (12 char or less): ";
    cin.ignore();
    getline(cin, dept);
    if(dept.length() > 12){
        cout << "Enter a department name 12 char or less" << endl;
        return false;
    }
    new Requester(name.c_str(), num.c_str(), mail.c_str(), dept.c_str());
    return true;
}

/**********************************************
 * Function: getNextRequester
 * Description:
 * This function will get the next requester name to be read from the file.
 * Reads the next 31 bytes of data from the file into the provided char array.
 * Parameters: 
 * - name: The char array to store the requester name
 * Returns: const char*: The requester name
 **********************************************/
const char* Requester::getNextRequester(char* name) {
    rfio.read(reinterpret_cast<char *>(name), 31);
    rfio.seekg(50, ios::cur);

    return name;
}

/**********************************************
 * Function: getLastRequester
 * Description:
 * This function will get the last requester name to added to the file.
 * Should be used after using createRequester when the programmer needs the
 * requesters name to add to the changeRequest.
 * Parameters: 
 * - name: The char array to store the requester name
 * Returns: const char*: The requester name
 **********************************************/
const char* Requester::getLastRequester(char* name) {
    rfio.seekg(-81, ios::end);
    rfio.read(reinterpret_cast<char *>(name), 31);
    rfio.seekg(0);

    return name;
}

/**********************************************
 * Function: getRequester
 * Description:
 * Seeks to the position given with the function and reads that data into a char array.
 * The char array is then returned.
 * Parameters: 
 * - name: The char array to store the requester name
 * - n: The position of the requester name in the file
 * Returns: const char*: The requester name
 **********************************************/
const char* Requester::getRequester(char* name, int n) {
    rfio.seekg(n * 81, ios::beg);
    rfio.read(reinterpret_cast<char *>(name), 31);

    return name;
}

/**********************************************
 * Function: queryRequesters
 * Description:
 * This function will find a specific requester based on their unique email associated with them.
 * Prompts the user to select a requester from the list.
 * Lists the requesters in batches of 5 and waits for user input to load more or make a selection.
 * Parameters: None
 * Returns: int: The position of the selected requester
 **********************************************/
int Requester::queryRequesters() {
    rfio.seekg(0);
    char buffer[31];
    int count = 0;
    cout << "Please select the requester name: " << endl << endl;
    string input = "N";
    // Loops through reading 5 product names (55 bytes) at a time and
    // asks the user for input if they want to see the next 5 products
    // or select a product already listed.
    // Will break out of loop when customer selects a number or when
    // the end of the file is reached
    rfio.clear();
    while(input == "N"){
        // if the read pointer cannot read anymore its reached the EOF and there are
        // no names left
        if(!rfio.read(reinterpret_cast<char *>(buffer), 31)){
            cout << "No more names" << endl;
            cout << "Enter selection: ";
            cin >> input;
            break;
        }
        count++;
        cout << count << ") " << buffer << endl;
        // every 5 names the user is prompted for input
        if(count%5 == 0){
            // if 0 returned user will be exited to previous menu
            cout << "0) Exit" << endl;
            cout << "To load next 5 names enter 'N'" << endl;
            cout << "Enter selection: ";
            cin >> input;
        }
        // set get pointer to the next name
        rfio.seekg(50, ios::cur);
    }
    // return position of the product user wants and reset file from EOF state
    rfio.clear();
    return stoi(input) - 1;
}

/**********************************************
 * Function: closeRequester
 * Description:
 * The file is closed.
 * Parameters: None
 * Returns: void
 **********************************************/
void Requester::closeRequester() {
    rfio.close();
}