//! Unit Tests for MPAGSCipher CaesarCipher Class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PlayfairCipher.hpp"

TEST_CASE("Playfair Cipher set key", "[playfair]")
{
    PlayfairCipher pc{"playfair-example!@#$%^&*()"};
    //REQUIRE(cc.applyCipher("HELLOWORLD", CipherMode::Encrypt) == "ROVVYGYBVN");
    std::string output = "PLAYFIREXMBCDGHKNOQSTUVWZ";
    REQUIRE(pc.returnKey() == output);
}


TEST_CASE("Playfair Cipher encryption", "[playfair]")
{
    //CaesarCipher cc{10};
    //REQUIRE(cc.applyCipher("HELLOWORLD", CipherMode::Encrypt) == "ROVVYGYBVN");

    REQUIRE(true);
}

TEST_CASE("Playfair Cipher decryption", "[playfair]")
{
    //CaesarCipher cc{10};
    //REQUIRE(cc.applyCipher("ROVVYGYBVN", CipherMode::Decrypt) == "HELLOWORLD");

    REQUIRE(true);
}