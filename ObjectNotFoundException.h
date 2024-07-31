
 
#ifndef OBJECTNOTFOUNDEXCEPTION_H
#define OBJECTNOTFOUNDEXCEPTION_H

#include <stdexcept>

using std::string;
using std::logic_error;

class ObjectNotFoundException : public logic_error {
 
   public:
      // Constructor
      ObjectNotFoundException(const string& message = "");
   
}; 
#endif
