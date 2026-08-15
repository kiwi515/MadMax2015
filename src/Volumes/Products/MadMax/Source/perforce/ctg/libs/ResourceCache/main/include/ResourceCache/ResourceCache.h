#ifndef LIB_RESOURCE_CACHE_H
#define LIB_RESOURCE_CACHE_H

class SResourceCache;

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

struct SResourceAllocator {
    // public: 
    // SPlatformAllocator* m_AllocStruct;
    // SResourceAllocatorWrapper m_Wrapper;
    
    // public: 
    // SResourceAllocator(SPlatformAllocator*);
    // SResourceAllocator(void* (*)(void*, uint64_t, uint32_t), void (*)(void*, void*), uint32_t, void*);
    // SResourceAllocator& operator=(const SResourceAllocator&);
    // void* Alloc(uint64_t) const;
    // void Dealloc(void*) const;
};

#endif