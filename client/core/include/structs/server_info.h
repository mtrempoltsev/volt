#pragma once

namespace volt
{
    namespace core
    {
        struct ServerInfo
        {
            std::string name_;
            std::string publicKey_;
            std::string address_;
            uint16_t port_;
        };

        struct ServerList
        {
            std::vector<ServerInfo> servers;
        };
    }
}
