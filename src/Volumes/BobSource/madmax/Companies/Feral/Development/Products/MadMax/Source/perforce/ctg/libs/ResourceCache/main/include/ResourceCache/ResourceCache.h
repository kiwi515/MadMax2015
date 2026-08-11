#ifndef LIB_RESOURCE_CACHE_H
#define LIB_RESOURCE_CACHE_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct SResourceHandle {
    public:
    uint16_t m_Index;
    uint16_t m_Timestamp;
    SResourceCache* m_ResourceCache;
    void* m_UserCtx;
};

struct SResourceCache {
    public:
    char temp_padding[0xe8];
};

#endif