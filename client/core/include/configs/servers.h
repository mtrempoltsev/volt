#pragma once

namespace volt
{
    namespace core
    {
        struct ServerInfo
        {
            std::string name;
            std::string publicKey;
            std::string address;
            uint16_t port;

            PODS_SERIALIZABLE(
                1,
                PODS_MDR(name),
                PODS_MDR(publicKey),
                PODS_MDR(address),
                PODS_MDR(port))
        };

        struct ServerList
        {
            std::vector<ServerInfo> servers;

            PODS_SERIALIZABLE(
                1,
                PODS_MDR(servers))
        };
    }
}
