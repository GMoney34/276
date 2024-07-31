
#ifndef KEY_UNIQUENESS_EXCEPTION_H
#define KEY_UNIQUENESS_EXCEPTION_H

#include <stdexcept>

using std::string;
using std::logic_error;

class KeyUniquenessException : public logic_error {
 
   public:
      // Constructor
      KeyUniquenessException(const string& message = "");
   
}; 
#endif
