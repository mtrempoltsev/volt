#pragma once

#include "../memory/view.h"

namespace volt
{
    namespace network
    {
        struct TransportPacket final
        {
            uint16_t size;
            opensslpp::Aes256Gcm::Iv iv;
            opensslpp::Aes256Gcm::Tag tag;
            std::vector<uint8_t> payload;
            opensslpp::Sha256::Digest hash;

            PODS_SERIALIZABLE(
                1,
                PODS_MDR(size),
                PODS_MDR(iv),
                PODS_MDR(tag),
                PODS_MDR(payload),
                PODS_MDR(hash)
            )

            static bool make(memory::View view);
        };
    }
}
