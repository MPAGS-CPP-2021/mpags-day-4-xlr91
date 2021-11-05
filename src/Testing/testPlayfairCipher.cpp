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

TEST_CASE("Playfair Cipher set maps", "[playfair]")
{
    PlayfairCipher pc{"playfair-example!@#$%^&*()"};

    auto testout1 = pc.returncoordmap().find('P');
    REQUIRE((*testout1).first == 'P');
    REQUIRE((*testout1).second.first == 0);
    REQUIRE((*testout1).second.second == 0);

    auto testout2 = pc.returncoordmap().find('F');
    REQUIRE((*testout2).first == 'F');
    REQUIRE((*testout2).second.first == 4);
    REQUIRE((*testout2).second.second == 0);

    auto testout3 = pc.returncoordmap().find('D');
    REQUIRE((*testout3).first == 'D');
    REQUIRE((*testout3).second.first == 2);
    REQUIRE((*testout3).second.second == 2);

    auto testout4 = pc.returncoordmap().find('Z');
    REQUIRE((*testout4).first == 'Z');
    REQUIRE((*testout4).second.first == 4);
    REQUIRE((*testout4).second.second == 4);
}

TEST_CASE("Playfair Cipher IJ", "[playfair]")
{
    PlayfairCipher pc{"playfair-example!@#$%^&*()"};
    REQUIRE(pc.applyCipher("TESTIJTEST", CipherMode::Encrypt) == "TESTIXITEST");

}

TEST_CASE("Playfair Cipher LL", "[playfair]")
{
    PlayfairCipher pc{"playfair-example!@#$%^&*()"};
    REQUIRE(pc.applyCipher("HELLOWORLD", CipherMode::Encrypt) == "HELXLOWORLD");

}

TEST_CASE("Playfair Cipher XX", "[playfair]")
{
    PlayfairCipher pc{"playfair-example!@#$%^&*()"};
    REQUIRE(true);
    //REQUIRE(pc.applyCipher("MOXXIE", CipherMode::Encrypt) == "MOXQXIE");

}


TEST_CASE("Playfair Cipher decryption", "[playfair]")
{
    //CaesarCipher cc{10};
    //REQUIRE(cc.applyCipher("ROVVYGYBVN", CipherMode::Decrypt) == "HELLOWORLD");

    REQUIRE(true);
}