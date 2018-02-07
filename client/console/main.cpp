#include "../../utils/localization/locale.h"

int main(int argc, char* argv[])
{
    volt::localization::setDefaultLocale();

    YAL_INFO << "hello!";

    return 0;
}
