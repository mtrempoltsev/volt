#include "dsa.h"

#include <openssl/bio.h>
#include <openssl/dsa.h>
#include <openssl/rand.h>
#include <openssl/pem.h>

namespace
{
    const int Ok = 1;

    using DsaPtr = std::unique_ptr<DSA, decltype(&DSA_free)>;
    using BioMemPtr = std::unique_ptr<BIO, decltype(&BIO_free)>;

    DSA* asDsa(void* ptr)
    {
        return static_cast<DSA*>(ptr);
    }
}

crypto::Dsa crypto::Dsa::createNew(int bits, bool& success)
{
    success = false;

    int bytes = 32;
    while (RAND_status() != Ok)
    {
        if (RAND_load_file("/dev/random", bytes) != bytes)
            return Dsa();

        bytes *= 2;
    }

    DsaPtr dsa(DSA_new(), DSA_free);
    if (!dsa)
        return Dsa();

    const int seedSize = 32;
    unsigned char seed[seedSize];

    if (RAND_bytes(seed, seedSize) != Ok)
        return Dsa();

    if (DSA_generate_parameters_ex(dsa.get(), bits, seed, seedSize, nullptr, nullptr, nullptr) != Ok)
        return Dsa();

    if (DSA_generate_key(dsa.get()) != Ok)
        return Dsa();

    success = true;

    return Dsa(dsa.release());
}

crypto::Dsa crypto::Dsa::createWithPublicKey(std::string&& publicKey, bool& success)
{
    success = false;

    BioMemPtr bio(BIO_new_mem_buf(publicKey.c_str(), publicKey.size()), &BIO_free);

    auto dsa = PEM_read_bio_DSA_PUBKEY(bio.get(), nullptr, nullptr, nullptr);
    if (!dsa)
        return Dsa();

    success = true;

    return Dsa(dsa);
}

crypto::Dsa crypto::Dsa::createWithPrivateKey(std::string&& privateKey, bool& success)
{
    success = false;

    BioMemPtr bio(BIO_new_mem_buf(privateKey.c_str(), privateKey.size()), &BIO_free);

    auto dsa = PEM_read_bio_DSAPrivateKey(bio.get(), nullptr, nullptr, nullptr);
    if (!dsa)
        return Dsa();

    success = true;

    return Dsa(dsa);
}

crypto::Dsa::Dsa(void* dsa)
    : dsa_(dsa)
{
}

crypto::Dsa::~Dsa()
{
    if (dsa_)
        DSA_free(asDsa(dsa_));
}

std::string crypto::Dsa::publicKey() const
{
    BioMemPtr bio(BIO_new(BIO_s_mem()), BIO_free);

    if (PEM_write_bio_DSA_PUBKEY(bio.get(), asDsa(dsa_)) != Ok)
        return std::string();

    BUF_MEM* buffer = nullptr;
    BIO_get_mem_ptr(bio.get(), &buffer);

    if (!buffer || !buffer->data || !buffer->length)
        return std::string();

    return std::string(buffer->data, buffer->length);
}

std::string crypto::Dsa::privateKey() const
{
    BioMemPtr bio(BIO_new(BIO_s_mem()), BIO_free);

    if (PEM_write_bio_DSAPrivateKey(bio.get(), asDsa(dsa_), nullptr, nullptr, 0, nullptr, nullptr) != Ok)
        return std::string();

    BUF_MEM* buffer = nullptr;
    BIO_get_mem_ptr(bio.get(), &buffer);

    if (!buffer || !buffer->data || !buffer->length)
        return std::string();

    return std::string(buffer->data, buffer->length);
}
