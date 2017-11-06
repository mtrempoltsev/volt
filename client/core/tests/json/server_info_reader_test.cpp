#include "../src/json/server_info_reader.h"

const char config[] =
R"(
{
    "servers" :
    [
        {
            "name" : "Main Server",
            "publicKey" : "-----BEGIN PUBLIC KEY-----\nMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAskwLtEKKNBfKv66WKKYP\n6zCnmT70O8Ehl7W2DFzjqFKLzQrFySaG6OmxMOhxj7dMlX7whIiAQGWt1cUAqQV6\naPAO0fH74khx9DRZfN7V4XtGhxncWplJWwXvGfNoP+6mkeeaOlbJy7vfyG3KIFHY\nl5VKJvshfczv7Tr6SyTnRSL0d+kwozEu9dYMkQAPQifcc/xLgkwwCZEFa73qJT5r\nmSk+fHei9J9u17vrYBKmcnlJcLHN8mFbNDAv1wFB4ulVddGWr8klIulwK5AeigtY\n5/jRZuEhCVgOjuduqRyKHKZ9z4lI/ZWKc1ybKdRlf8T8lIhHck3ZuwO+iXWBWt/a\nvwIDAQAB\n-----END PUBLIC KEY-----",
            "address" : "volt.trempoltsev.ru",
            "port" : 2017
        }
    ]
}
)";

TEST(serverInfoReader, common)
{
    volt::core::ServerList servers;
    const bool result = volt::core::loadFromStream(std::stringstream(config), servers);

    ASSERT_TRUE(result);

    ASSERT_EQ(servers.servers.size(), 1);
}
