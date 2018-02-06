#include "locale.h"

void volt::utils::setDefaultLocale()
{
#if defined(_WIN32)
    std::locale::global(boost::locale::generator().generate("en_US.UTF-8"));
    boost::filesystem::path::imbue(std::locale());
#endif
}
