/*
 * An abstract class defining the encryption and decryption
 * interface that is implemented by different concrete
 * encryption strategies.
 */

#ifndef CIPHER_HPP_
#define CIPHER_HPP_

#include <string>

class Cipher {
public:

	Cipher() {}
	~Cipher() {}

	// Encrypt the text argument and return the encrypted text
	virtual std::string encrypt( std::string &text ) = 0;

	// Decrypt the text argument and return the decrypted text
	virtual std::string decrypt( std::string &text ) = 0;
};

// A pure virtual destructor is different from other
// pure virtual function in that it must be defined
// (i.e., you have to provide an implementation).


#endif
