//
//  date.cpp
//  
//
//  Created by Phillip Kriegel on 2/11/15.
//
//

#include <iostream>
#include <locale>


#include "date.hpp"
#include "cipher.hpp"

// Single-argument constructor
DateCipher::DateCipher(std::string date) : Cipher() {
    
    this -> datecode = date;
    this -> datelength = date.length();
    // Nothing else to do in the constructor
}

// Destructor
DateCipher::~DateCipher() {
}


// Overloaded encrypt method
std::string DateCipher::encrypt( std::string &inputText ){
    std::string text = inputText;
    int size = text.length();
    this -> intarray   = new int[size];
    
    int j = 0;
    
    for (int i = 0; i < size; i++){
        if (text[i] == ' '){
            intarray[i] = 0;
        }
        else if (datecode[j % datelength] != '/'){
                intarray[i] = datecode[j % datelength] - '0';
                j++;
        }
        else {
            j++;
            intarray[i] = datecode[j % datelength] - '0';
            j++;
        }
        
       
    }
    
    
    for (int i = 0; i < size; i++){
        if (islower(text[i])){
            if ((text[i] + intarray[i]) > 122){
                text[i] = text[i] + intarray[i] - 26;
            } else {
                text[i] = text[i] + intarray[i];
            }
        }
        else if (isupper(text[i])){
            if ((text[i] + intarray[i]) > 90){
                text[i] = text[i] + intarray[i] - 26;
            } else {
                text[i] = text[i] + intarray[i];
            }
        }
    }
    
    return text;
}

std::string DateCipher::decrypt( std::string &inputText ){
    std::string text = inputText;
    int size = text.length();
    for (int i = 0; i < size; i++){
        if (islower(text[i])){
            if ((text[i] - intarray[i]) < 97){
                text[i] = text[i] - intarray[i] + 26;
            } else {
                text[i] = text[i] - intarray[i];
            }
        }
        else if (isupper(text[i])){
            if ((text[i] - intarray[i]) < 65){
                text[i] = text[i] - intarray[i] + 26;
            } else {
                text[i] = text[i] - intarray[i];
            }
        }
    }
    
    return text;

}

