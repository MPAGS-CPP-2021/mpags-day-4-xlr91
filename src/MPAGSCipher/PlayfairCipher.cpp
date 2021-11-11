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
    std::string TESTOUTPUT{""};    //FOR TESTING ONLY, DELETE THIS
    auto ijfunc = [](char x) {
        if (x == 'J') {
            return 'I';
        } else {
            return x;
        }
    };

    switch (cipherMode) {
        case CipherMode::Encrypt:

            std::transform(outputText.begin(), outputText.end(),
                           outputText.begin(), ijfunc);

            //if repeated chars in a digraph add an x or q if xx

            interstring += outputText.at(0);

            //switch to using a string iterator

            //use back insert thing
            //std::transform(key_.begin(), key_.end(), key_.begin(), ijfunc); but with back insert and ijfunc is something that switches it in the for loop like thing
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
            outputText =
                interstring;    //can replace this somehow so we dont need to deal with interstring

            //if size of input is odd, add trailing z

            if (outputText.length() % 2 != 0) {
                outputText += "Z";
            }

            break;

        case CipherMode::Decrypt:
            break;
    }

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

        std::cout << x0 << y0 << x1 << y1 << std::endl;
        std::cout << x0f << y0f << x1f << y1f << std::endl;

        std::cout << (*coordsToCharIter0).second << (*coordsToCharIter1).second
                  << std::endl;

        interstring += (*coordsToCharIter0).second;
        interstring += (*coordsToCharIter1).second;

        //(*charToCoordsIter).second.first and (*charToCoordsIter).second.second are the useful things

        //TESTOUTPUT += std::to_string((*charToCoordsIter).second.first);
        //TESTOUTPUT += (*charToCoordsIter).first;
        //charToCoordsIter = letcoordmap_.find(outputText.at(i+1));
        //TESTOUTPUT += (*charToCoordsIter).first;
        //TESTOUTPUT += std::to_string((*charToCoordsIter).second.first);
    }
    outputText = interstring;

    //  find the corods in grid of each digraph

    // appl rules to get new corod

    //find letter associated

    //return text

    /*
    switch (cipherMode) {
        case CipherMode::Encrypt:
            break;
        case CipherMode::Decrypt:
            break;
    }

    */

    return outputText;
}