#include "../../../utils/memory/buffer.h"

TEST(testBuffer, common)
{
    volt::memory::Buffer buf(64);

    EXPECT_EQ(buf.capacity(), 64);
    EXPECT_EQ(buf.size(), 64);

    auto ptr = buf.data();
    EXPECT_NE(ptr, nullptr);

    buf.resize(32);

    const auto constBuf = std::move(buf);

    EXPECT_EQ(buf.data(), nullptr);

    EXPECT_EQ(constBuf.data(), ptr);
    EXPECT_EQ(constBuf.capacity(), 64);
    EXPECT_EQ(constBuf.size(), 32);

    const auto view = constBuf.view();

    EXPECT_EQ(view.data, ptr);
    EXPECT_EQ(view.size, 32);
}
