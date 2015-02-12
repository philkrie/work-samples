//
//  date.h
//  
//
//  Created by Phillip Kriegel on 2/11/15.
//
//

#ifndef ____date__
#define ____date__

#include "cipher.hpp"

class DateCipher : public Cipher {
public:
    DateCipher(std::string date);
    virtual ~DateCipher();
    virtual std::string encrypt( std::string &text );
    virtual std::string decrypt( std::string &text );
private:
    std::string datecode;
    int datelength;
    int* intarray;
};

#endif /* defined(____date__) */
