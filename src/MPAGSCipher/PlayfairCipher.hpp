#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include "CipherMode.hpp"
#include <string>
#include <map>


/**
 * \file PlayfairCipher.hpp
 * \brief Contains the declaration of the PlayfairCipher class
 */

/**
 * \class PlayfairCipher
 * \brief Encrypt or decrypt text using the Playfair cipher with the given key
 */




class PlayfairCipher {
  public:
      /**
     * \brief Create a new PlayfairCipher with the given key
     *
     * \param key the key to use in the cipher
     */
    explicit PlayfairCipher(const std::string& key);

      /**
     * \brief Sets the key
     *
     * \param key the key to use in the cipher
     */
    void setKey(const std::string& key);

        /**
     * \brief Apply the cipher to the provided text
     *
     * \param inputText the text to encrypt or decrypt
     * \param cipherMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
     */
    std::string applyCipher(const std::string& inputText, const CipherMode cipherMode) const;

          /**
     * \brief Returns the key
     */
    std::string returnKey() const;
    std::map<char, std::pair<int, int>> returncoordmap() const;
    

    

  private:
    std::string key_{0};
    std::map<std::pair<int, int>, char> coordletmap_;
    std::map<char, std::pair<int, int>> letcoordmap_;

};

#endif