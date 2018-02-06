#include "../../utils/locale.h"

int main(int argc, char* argv[])
{
    volt::utils::setDefaultLocale();

    YAL_INFO << "hello!";

    return 0;
}
