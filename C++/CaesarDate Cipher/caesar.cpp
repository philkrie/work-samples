//
//  caesar.cpp
//  
//
//  Created by Phillip Kriegel on 2/10/15.
//
//

#include <iostream>
#include <locale>
#include "cipher.hpp"
#include "caesar.hpp"

// Single-argument constructor
CaesarCipher::CaesarCipher(int rotation) : Cipher() {
    rotation = ((( rotation % 27 ) + 27 ) % 27 );
    this->rotation = rotation;
    
    // Nothing else to do in the constructor
}

// Destructor
CaesarCipher::~CaesarCipher() {
}

// Overloaded encrypt method
std::string CaesarCipher::encrypt( std::string &inputText ) {
    std::string lowercase = "abcdefghijklmnopqrstuvwxyz ";
    std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string text = inputText;
    std::string::size_type len = text.length();
    for (int i = 0; i != len; ++i) {
        if (text[i] == ' '){
            if (rotation - 1 == -1){
                text[i] = ' ';
            }
            else {
                text[i] = lowercase[rotation-1];
            }
        }
        else if (islower(text[i])){
            int shiftedpos = (text[i] - 97 + rotation) % 27;
            text[i] = lowercase[shiftedpos];
        }
        else if (isupper(text[i])){
            int shiftedpos = (text[i] - 65 + rotation) % 26;
            text[i] = uppercase[shiftedpos];
        }
    }
    return text;
}

std::string CaesarCipher::decrypt( std::string &inputText ) {
    std::string lowercase = "abcdefghijklmnopqrstuvwxyz ";
    std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string text = inputText;
    std::string::size_type len = text.length();
    for (int i = 0; i != len; ++i) {
        if (text[i] == ' '){
            text[i] = lowercase[26-rotation];
        }
        
        else if (islower(text[i])){
            int shiftedpos = (text[i] - 97 + (27 - rotation)) % 27;
            text[i] = lowercase[shiftedpos];
        }
        else if (isupper(text[i])){
            int shiftedpos = (text[i] - 65 + (26 - rotation)) % 26;
            text[i] = uppercase[shiftedpos];
        }
    }
    return text;
    }
