#include "../configs/servers.h"

TEST(clientConfigsServers, common)
{
    const volt::core::ServerList expected = 
    {
        {
            { "fist", "key1", "addr1", 8000 },
            { "second", "key2", "addr2", 8001 }
        }
    };

    pods::ResizeableWriteOnlyMemoryStorage out;
    pods::JsonSerializer<pods::ResizeableWriteOnlyMemoryStorage> serializer(out);

    ASSERT_EQ(serializer.save(expected), pods::Error::NoError);

    pods::ReadOnlyMemoryStorage in(out.data(), out.size());
    pods::JsonDeserializer<pods::ReadOnlyMemoryStorage> deserializer(in);

    volt::core::ServerList actual;

    ASSERT_EQ(deserializer.load(actual), pods::Error::NoError);

    ASSERT_EQ(expected.servers.size(), actual.servers.size());

    EXPECT_EQ(expected.servers[0].name, actual.servers[0].name);
    EXPECT_EQ(expected.servers[0].publicKey, actual.servers[0].publicKey);
    EXPECT_EQ(expected.servers[0].address, actual.servers[0].address);
    EXPECT_EQ(expected.servers[0].port, actual.servers[0].port);

    EXPECT_EQ(expected.servers[1].name, actual.servers[1].name);
    EXPECT_EQ(expected.servers[1].publicKey, actual.servers[1].publicKey);
    EXPECT_EQ(expected.servers[1].address, actual.servers[1].address);
    EXPECT_EQ(expected.servers[1].port, actual.servers[1].port);
}
