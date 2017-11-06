#pragma once

#include "../../include/structs/server_info.h"

namespace volt
{
    namespace core
    {
        bool loadFromStream(std::istream& source, ServerList& result);
    }
}
