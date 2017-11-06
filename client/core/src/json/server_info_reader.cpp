#include "server_info_reader.h"

namespace
{
    struct ServerHandler
    {
        bool Null()
        {
            return false;
        }

        bool Bool(bool b)
        {
            return false;
        }

        bool Int64(int64_t i)
        {
            return false;
        }

        bool Uint64(uint64_t u)
        {
            return false;
        }

        bool Double(double d)
        {
            return false;
        }

        bool RawNumber(const char* str, rapidjson::SizeType length, bool copy)
        {
            return false;
        }

        bool Int(int i)
        {
            return false;
        }

        bool Uint(unsigned u)
        {
            return true;
        }

        bool String(const char* str, rapidjson::SizeType length, bool copy)
        {
            return true;
        }

        bool Key(const char* str, rapidjson::SizeType length, bool copy)
        {
            switch (*str++)
            {
            case 's':
                if (length == 7 && *str++ == 'e' && *str++ == 'r' && *str++ == 'v' && *str++ == 'e' && *str++ == 'r' && *str++ == 's')
                {
                    state_ = State::Servers;
                    return true;
                }
                break;
            case 'n':
                if (length == 4 && *str++ == 'a' && *str++ == 'm' && *str++ == 'e')
                {
                    state_ = State::Name;
                    return true;
                }
                break;
            case 'p':
                switch (*str++)
                {
                case 'o':
                    if (length == 4 && *str++ == 'r' && *str++ == 't')
                    {
                        state_ = State::Port;
                        return true;
                    }
                    break;
                case 'u':
                    if (length == 9 && *str++ == 'b' && *str++ == 'l' && *str++ == 'i' && *str++ == 'c' && *str++ == 'K' && *str++ == 'e' && *str++ == 'y')
                    {
                        state_ = State::PublicKey;
                        return true;
                    }
                    break;
                }
                break;
            case 'a':
                if (length == 7 && *str++ == 'd' && *str++ == 'd' && *str++ == 'r' && *str++ == 'e' && *str++ == 's' && *str++ == 's')
                {
                    state_ = State::Address;
                    return true;
                }
                break;
            }

            return false;
        }

        bool StartObject()
        {
            return state_ == State::Begin;
        }

        bool EndObject(rapidjson::SizeType memberCount)
        {
            return true;
        }

        bool StartArray()
        {
            if (state_ != State::Servers)
                return false;

            state_ = State::Begin;

            servers_.servers.push_back({});
            return true;
        }

        bool EndArray(rapidjson::SizeType /*elementCount*/) { return true; }

        explicit ServerHandler(volt::core::ServerList& servers)
            : servers_(servers)
            , state_(State::Begin)
        {
        }

        volt::core::ServerList& servers_;

    private:
        enum class State
        {
            Begin,

            Servers,
            Name,
            PublicKey,
            Address,
            Port,

            End
        };

        State state_;
    };
}

bool volt::core::loadFromStream(std::istream& source, ServerList& result)
{
    if (!source)
        return false;

    rapidjson::Reader reader;
    rapidjson::IStreamWrapper stream(source);
    reader.Parse(stream, ServerHandler(result));
    if (reader.HasParseError())
        return false;

    return true;
}
