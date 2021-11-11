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



//remnants of the test cases used before the encryption actally works, testing out 
//individual IJ, LL, XX, etc
//unsure on how to access those individual blocks of code to properly implement this
/*

    TEST_CASE("Playfair Cipher IJ", "[playfair]")
    {
        PlayfairCipher pc{"playfair-example!@#$%^&*()"};
        REQUIRE(pc.applyCipher("TESTITESTJ", CipherMode::Encrypt) == "TESTITESTI");

    }

    TEST_CASE("Playfair Cipher LL", "[playfair]")
    {
        PlayfairCipher pc{"playfair-example!@#$%^&*()"};
        REQUIRE(pc.applyCipher("HELLOWORLDS", CipherMode::Encrypt) == "HELXLOWORLDS");

    }

    TEST_CASE("Playfair Cipher XX", "[playfair]")
    {
        PlayfairCipher pc{"playfair-example!@#$%^&*()"};
        REQUIRE(pc.applyCipher("MOXXIES", CipherMode::Encrypt) == "MOXQXIES");

    }

    TEST_CASE("Playfair Cipher Oddness", "[playfair]")
    {
        PlayfairCipher pc{""};
        REQUIRE(pc.applyCipher("HELLOWORLD", CipherMode::Encrypt) == "HELXLOWORLDZ");
    }

    TEST_CASE("Playfair Cipher Wikipedia", "[playfair]")
    {
        PlayfairCipher pc{"playfair example"};
        //REQUIRE(pc.applyCipher("hide the gold in the tree stump", CipherMode::Encrypt) == "BMODZBXDNABEKUDMUIXMMOUVIF");
        REQUIRE(true);
    }

*/

TEST_CASE("Playfair Cipher Wikipedia Encryption", "[playfair]")
{
    PlayfairCipher pc{"playfair example"};
    REQUIRE(pc.applyCipher("HIDETHEGOLDINTHETREESTUMP", CipherMode::Encrypt) == "BMODZBXDNABEKUDMUIXMMOUVIF");
    //REQUIRE(true);
}

TEST_CASE("Playfair Cipher Wikipedia decryption", "[playfair]")
{
    PlayfairCipher pc{"playfair example"};
    REQUIRE(pc.applyCipher("BMODZBXDNABEKUDMUIXMMOUVIF", CipherMode::Decrypt) == "HIDETHEGOLDINTHETREXESTUMP");                                                                            

    REQUIRE(true);
}

TEST_CASE("Playfair Cipher GeeksforGeeks Encryption", "[playfair]")
{
    PlayfairCipher pc{"MONARCHY"};
    //REQUIRE(true);
    REQUIRE(pc.applyCipher("INSTRUMENTS", CipherMode::Encrypt) == "GATLMZCLRQTX");
}

TEST_CASE("Playfair Cipher GeeksforGeeks Decryption", "[playfair]")
{
    PlayfairCipher pc{"MONARCHY"};
    REQUIRE(pc.applyCipher("GATLMZCLRQTX", CipherMode::Decrypt) == "INSTRUMENTSZ");

    REQUIRE(true);
}