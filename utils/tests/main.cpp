#include "../locale.h"

int main(int argc, char* argv[])
{
    volt::utils::setDefaultLocale();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
