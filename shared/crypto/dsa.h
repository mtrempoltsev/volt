#pragma once

namespace crypto
{
    class Dsa final
    {
    public:
        Dsa(const Dsa&) = delete;
        Dsa& operator=(const Dsa&) = delete;

        Dsa(Dsa&&) = default;
        Dsa& operator=(Dsa&&) = default;

        ~Dsa();

        static Dsa createNew(int bits, bool& success);
        static Dsa createWithPublicKey(std::string&& publicKey, bool& success);
        static Dsa createWithPrivateKey(std::string&& privateKey, bool& success);

        std::string publicKey() const;
        std::string privateKey() const;

    private:
        explicit Dsa(void* dsa = nullptr);

    private:
        void* dsa_;
    };
}
