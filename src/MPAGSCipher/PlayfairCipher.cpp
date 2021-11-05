#include "PlayfairCipher.hpp"

#include <algorithm>
#include <iostream>

PlayfairCipher::PlayfairCipher(const std::string& key){
    setKey(key);
}

std::string PlayfairCipher::returnKey() const{
    return key_;
}

std::map<char, std::pair<int, int>> PlayfairCipher::returncoordmap() const{
    return letcoordmap_;
}

void PlayfairCipher::setKey(const std::string& key){
    //store original key
    key_ = key;

    //append alphabet
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    key_ += alphabet;

    //make sure key is upper case
    std::transform(key_.begin(), key_.end(), key_.begin(), ::toupper);
     
    //remove non-alpha characters

    key_.erase(std::remove_if(key_.begin(), key_.end(), 
                [](char x) {return !std::isalpha(x);}), key_.end());

    //change j->i
    auto ijfunc = [](char x){
        if (x == 'J'){
            return 'I';
        } else {
            return x;
        }
    };
    std::transform(key_.begin(), key_.end(), key_.begin(), ijfunc);

    //remove duplicate letters
    std::string duplicate_letters = "";
    auto duplicate = [&](char x){
        int dlPos = duplicate_letters.find(x);
        if (dlPos != -1){ //found a match, delete me (set to true)
            return true;
        } else {
            duplicate_letters += x;
            return false;
        }
    };

    key_.erase(std::remove_if(key_.begin(), key_.end(), 
                duplicate), 
                key_.end());

    std::string::iterator its=key_.begin();
    
    for(int yc =0 ; yc < grid_size_; yc++){
        for(int xc = 0; xc< grid_size_; xc++){
            //std::cout << yc << xc << std::endl;
            letcoordmap_.insert(std::make_pair(*its, std::make_pair(xc, yc)));
            coordletmap_.insert(std::make_pair(std::make_pair(xc, yc), *its));
            its++;
        }
    }

    //store playfair cipher key map
}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode)const {
    //change j->i
    std::string outputText = inputText;
    auto ijfunc = [](char x){
            if (x == 'J'){
                return 'I';
            } else {
                return x;
            }
    };
    std::transform(outputText.begin(), outputText.end(), outputText.begin(), ijfunc);
    

    //if repeated chars in a digraph add an x or q if xx
    std::string interstring = "";

    interstring += outputText.at(0);
    for(std::string::size_type i = 1; i < outputText.length() ; i++){
        if(outputText.at(i-1) == outputText.at(i)){
            interstring += "X";
        }
        interstring += outputText.at(i);
    }
    outputText = interstring;
    //if size of input is odd, add trailing z

    //loop over inputs in digraphs

    //  find the corods in grid of each digraph

    // appl rules to get new corod

    //find letter associated

    //return text
    
    switch (cipherMode) {
        case CipherMode::Encrypt:
            break;
        case CipherMode::Decrypt:
            break;
    }
    return outputText;
}