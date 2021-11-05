#include "PlayfairCipher.hpp"

#include <string>
#include <algorithm>
#include <iostream>

PlayfairCipher::PlayfairCipher(const std::string& key){
    setKey(key);
}

std::string PlayfairCipher::returnKey() const{
    return key_;
}

void PlayfairCipher::setKey(const std::string& key){
    //store original key
    key_ = key;

    //append alphabet
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    key_.append(alphabet);

    //make sure key is upper case
    std::transform(key_.begin(), key_.end(), key_.begin(), ::toupper);
     
    //remove non-alpha characters

    key_.erase(std::remove_if(key_.begin(), key_.end(), [](unsigned char x) {std::cout<<std::isalpha(x) << std::endl; return !std::isalpha(x);}), key_.end());

    //change j->i

    //remove duplicate letters

    //store coord of each letter

    //store playfair cipher key map
}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode)const {
    //change j->i

    //if repeated chars in a digraph add an x or q if xx

    //if size of input is odd, add trailing z

    //loop over inputs in digraphs

    //  find the corods in grid of each digraph

    // appl rules to get new corod

    //find letter associated

    //return text
    
    
    std::string outputtext = inputText;
    switch (cipherMode) {
        case CipherMode::Encrypt:
            break;
    case CipherMode::Decrypt:
            break;
    }
    return "Hello, World!";
}