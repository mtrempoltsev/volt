#include "stdafx.h"

#include "../../shared/crypto/dsa.h"

int main(int argc, char* argv[])
{
    bool success = false;

    auto dsa = crypto::Dsa::createNew(2048, success);
    YAL_INFO << success;

    crypto::Dsa::createWithPublicKey(dsa.publicKey(), success);
    YAL_INFO << success;

    crypto::Dsa::createWithPrivateKey(dsa.privateKey(), success);
    YAL_INFO << success;

    return 0;
}
