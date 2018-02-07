#include "../../../utils/localization/locale.h"

int main(int argc, char* argv[])
{
    volt::localization::setDefaultLocale();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
