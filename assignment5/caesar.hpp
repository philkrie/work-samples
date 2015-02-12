//
//  caesar.h
//  
//
//  Created by Phillip Kriegel on 2/10/15.
//
//

#ifndef ____caesar__
#define ____caesar__

#include "cipher.hpp"

class CaesarCipher : public Cipher {
public:
    CaesarCipher(int rotation);
    virtual ~CaesarCipher();
    virtual std::string encrypt( std::string &text );
    virtual std::string decrypt( std::string &text );
private:
    int rotation;
};

#endif /* defined(____caesar__) */
