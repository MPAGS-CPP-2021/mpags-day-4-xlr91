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


    //store coord of each letter
    //map is letter : x,y coordinate
    //pair of 2 numbers make up the coordinate from the looks of it

    
    
    
    /*
    using CoordPair = std::pair<int, int>;

    CoordPair c0{1, 3};

    using Let2CoordMap = std::map<char, std::pair<int, int>>;

    letcoordmap.insert(std::make_pair('a', c0));

    for (const auto& origChar : inputText)

    std::string::iterator it=str.begin(); it!=str.end(); ++it

    */

    

    std::string::iterator its=key_.begin();
    
    for(int yc =0 ; yc < 5; yc++){
        for(int xc = 0; xc< 5; xc++){
            std::cout << yc << xc << std::endl;
            letcoordmap_.insert(std::make_pair(*its, std::make_pair(xc, yc)));
            coordletmap_.insert(std::make_pair(std::make_pair(xc, yc), *its));
            its++;
        }
    }

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