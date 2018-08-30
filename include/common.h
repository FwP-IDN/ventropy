#ifndef COMMON
#define COMMON

#include <atomic>
#include <chrono>
#include <functional>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <sstream>
#include "fmt/fmt.h"

#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define VENT_NOEXCEPT throw()
#define VENT_CONSTEXPR
#else
#define VENT_NOEXCEPT noexcept
#define VENT_CONSTEXPR constexpr
#endif

const uint16_t MAX_HUE = 257;

namespace detail
{
    constexpr std::uint32_t fnv1a_32(char const* s, std::size_t count)
    {
        return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u;
    }
}

constexpr std::uint32_t fnhash(char const* s, std::size_t count)
{
    return detail::fnv1a_32(s, count);
}

enum class SampleBlock : uint16_t 
{ 
    b64=64, 
    b128=128, 
    b256=256
};

inline std::istream &operator>>(std::istream &in, SampleBlock &block) {
    int i;
    in >> i;
    block = static_cast<SampleBlock>(i);
    return in;
}

inline uint16_t &operator<<(uint16_t &in, const SampleBlock &block) {
    return in = static_cast<uint16_t>(block);
}

inline std::ostream &operator<<(std::ostream &in, const SampleBlock &block) { return in << static_cast<int>(block); }


enum class Block : uint8_t 
{ 
    b8=8, 
    b16=16, 
    b32=32 
};

inline std::istream &operator>>(std::istream &in, Block &block) {
    int i;
    in >> i;
    block = static_cast<Block>(i);
    return in;
}

inline uint16_t &operator<<(uint16_t &in, const Block &block) {
    return in = static_cast<uint16_t>(block);
}

inline std::ostream &operator<<(std::ostream &in, const Block &block) { return in << static_cast<int>(block); }

class vent_ex : public std::exception
{
public:
    explicit vent_ex(const std::string &msg)
        : _msg(msg)
    {
    }

    vent_ex(const std::string &msg, int last_errno)
    {
        fmt::memory_buffer outbuf;
        fmt::format_system_error(outbuf, last_errno, msg);
        _msg = fmt::to_string(outbuf);
    }

    const char *what() const VENT_NOEXCEPT   override
    {
        return _msg.c_str();
    }

private:
    std::string _msg;
};

#endif