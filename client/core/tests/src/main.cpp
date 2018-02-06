int main(int argc, char* argv[])
{
#if defined(_WIN32)
    std::locale::global(boost::locale::generator().generate(""));
    boost::filesystem::path::imbue(std::locale());
#endif

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
