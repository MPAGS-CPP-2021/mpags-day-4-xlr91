#include "PlayfairCipher.hpp"

#include <algorithm>
#include <iostream>

PlayfairCipher::PlayfairCipher(const std::string& key)
{
    setKey(key);
}

std::string PlayfairCipher::returnKey() const
{
    return key_;
}

std::map<char, std::pair<int, int>> PlayfairCipher::returncoordmap() const
{
    return letcoordmap_;
}

void PlayfairCipher::setKey(const std::string& key)
{
    //store original key
    key_ = key;

    //append alphabet
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    key_ += alphabet;

    //make sure key is upper case
    std::transform(key_.begin(), key_.end(), key_.begin(), ::toupper);

    //remove non-alpha characters

    key_.erase(std::remove_if(key_.begin(), key_.end(),
                              [](char x) { return !std::isalpha(x); }),
               key_.end());

    //change j->i
    auto ijfunc = [](char x) {
        if (x == 'J') {
            return 'I';
        } else {
            return x;
        }
    };
    std::transform(key_.begin(), key_.end(), key_.begin(), ijfunc);

    //remove duplicate letters
    std::string duplicate_letters = "";
    auto duplicate = [&](char x) {
        int dlPos = duplicate_letters.find(x);
        if (dlPos != -1) {    //found a match, delete me (set to true)
            return true;
        } else {
            duplicate_letters += x;
            return false;
        }
    };

    key_.erase(std::remove_if(key_.begin(), key_.end(), duplicate), key_.end());

    std::string::iterator its = key_.begin();

    for (int yc = 0; yc < grid_size_; yc++) {
        for (int xc = 0; xc < grid_size_; xc++) {
            //std::cout << yc << xc << std::endl;
            letcoordmap_.insert(std::make_pair(*its, std::make_pair(xc, yc)));
            coordletmap_.insert(std::make_pair(std::make_pair(xc, yc), *its));
            its++;
        }
    }

    //store playfair cipher key map
}

std::string PlayfairCipher::applyCipher(const std::string& inputText,
                                        const CipherMode cipherMode) const
{
    //change j->i

    //this part should only be done during encryption, as it is assuemd that the encrytped message is fully proper
    //when sticking it in the ciphertext

    std::string interstring = "";

    std::string outputText = inputText;
    auto ijfunc = [](char x) {
        if (x == 'J') {
            return 'I';
        } else {
            return x;
        }
    };


    //applying encryption cipher rules for the incoming encryption text
    switch (cipherMode) {
        case CipherMode::Encrypt:

            std::transform(outputText.begin(), outputText.end(),
                           outputText.begin(), ijfunc);

            //if repeated chars in a digraph add an x or q if xx
            
            //this bit of code could surely be done using an algorithm
            //thinking of using the adjacent_find alg to find any occurences of double chars
            //and then use something like the insert iterator to stick it in
            //unsure how to proceed with iterators so for now going use standard for loops etc
            //also time constraints
            interstring += outputText.at(0);
            for (std::string::size_type i = 1; i < outputText.length(); i++) {
                if (outputText.at(i - 1) == outputText.at(i)) {
                    if (outputText.at(i) == 'X') {
                        interstring += "Q";
                    } else {
                        interstring += "X";
                    }
                }
                interstring += outputText.at(i);
            }            
            outputText = interstring;    //can replace this somehow so we dont need to deal with interstring

            if (outputText.length() % 2 != 0) {
                outputText += "Z";
            }

            break;

        case CipherMode::Decrypt:
            break;
    }


    // use text to find coordinate, apply rules, and return the letter
    auto charToCoordsIter0 = letcoordmap_.find('A');
    auto charToCoordsIter1 = letcoordmap_.find('B');
    auto coordsToCharIter0 = coordletmap_.find(std::make_pair(0, 0));
    auto coordsToCharIter1 = coordletmap_.find(std::make_pair(0, 0));

    int x0{0};
    int y0{0};
    int x1{0};
    int y1{0};
    int x0f{0};
    int y0f{0};
    int x1f{0};
    int y1f{0};

    //loop over inputs in digraphs
    interstring = "";

    for (std::string::size_type i = 0; i < outputText.length(); i += 2) {
        charToCoordsIter0 = letcoordmap_.find(outputText.at(i));
        charToCoordsIter1 = letcoordmap_.find(outputText.at(i + 1));

        //find the coordinates in grid of each diagram
        x0 = (*charToCoordsIter0).second.first;
        y0 = (*charToCoordsIter0).second.second;
        x1 = (*charToCoordsIter1).second.first;
        y1 = (*charToCoordsIter1).second.second;

        x0f = x0;
        x1f = x1;
        y0f = y0;
        y1f = y1;

        //apply rules to get new coordinates
        switch (cipherMode) {
            case CipherMode::Encrypt:
                if (y0 == y1) {    //rule1
                    x0f = (x0 + 1) % grid_size_;
                    x1f = (x1 + 1) % grid_size_;
                } else if (x0 == x1) {    //rule 2
                    y0f = (y0 + 1) % grid_size_;
                    y1f = (y1 + 1) % grid_size_;
                } else {    //rule 3
                    x0f = x1;
                    x1f = x0;
                }
                break;
            case CipherMode::Decrypt:
                if (y0 == y1) {
                    //(b + (a%b)) % b to handle negative wrap arounds
                    x0f = (grid_size_ + (x0 - 1) % grid_size_) % grid_size_;
                    x1f = (grid_size_ + (x1 - 1) % grid_size_) % grid_size_;
                } else if (x0 == x1) {
                    y0f = (grid_size_ + (y0 - 1) % grid_size_) % grid_size_;
                    y1f = (grid_size_ + (y1 - 1) % grid_size_) % grid_size_;
                } else {
                    x0f = x1;
                    x1f = x0;
                }
                break;
        }

        coordsToCharIter0 = coordletmap_.find(std::make_pair(x0f, y0f));
        coordsToCharIter1 = coordletmap_.find(std::make_pair(x1f, y1f));
        
        //it might also be possible to use iterators/algs to transform the string
        //but this works, and time constraints
        interstring += (*coordsToCharIter0).second;
        interstring += (*coordsToCharIter1).second;
    }
    
    
    outputText = interstring;

    return outputText;
}