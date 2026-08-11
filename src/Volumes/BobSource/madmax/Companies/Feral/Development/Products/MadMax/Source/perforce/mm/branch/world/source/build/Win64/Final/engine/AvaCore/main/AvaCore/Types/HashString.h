#ifndef ENGINE_HASHSTRING_H
#define ENGINE_HASHSTRING_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class CHashString {
    public:
    uint32_t m_Hash;

    public: 
    CHashString(const std::basic_string<char,std::char_traits<char>,std::allocator<char> >&);
    CHashString(uint32_t, const std::basic_string<char,std::char_traits<char>,std::allocator<char> >&);
    CHashString(const char*);
    CHashString(uint32_t, const char*);
    CHashString(CHashString&&);
    CHashString(const CHashString&);
    CHashString(uint32_t);
    CHashString();
    CHashString& operator=(const std::basic_string<char,std::char_traits<char>,std::allocator<char> >&);
    CHashString& operator=(const char*);
    CHashString& operator=(CHashString&&);
    CHashString& operator=(const CHashString&);
    void reset(uint32_t);
    void reset(const std::basic_string<char,std::char_traits<char>,std::allocator<char> >&);
    void reset(const char*);
    bool operator==(uint32_t) const;
    bool operator==(const CHashString&) const;
    bool operator!=(uint32_t) const;
    bool operator!=(const CHashString&) const;
    bool operator<(const CHashString& other) const {
        return this->m_Hash < other.m_Hash;
    };
    uint32_t get() const;
    
    static uint32_t Hash(const char*);
};

#endif