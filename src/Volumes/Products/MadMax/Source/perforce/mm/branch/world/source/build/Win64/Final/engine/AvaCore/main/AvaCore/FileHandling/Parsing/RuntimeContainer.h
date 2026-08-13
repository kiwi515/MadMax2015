#ifndef ENGINE_RUNTIME_CONTAINER_H
#define ENGINE_RUNTIME_CONTAINER_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class SRuntimeContainerVariant {
    public: 
    uint32_t m_Key;
    uint32_t m_DataOffset;
    unsigned char m_Type;
};

struct SRuntimeContainer {
    public:
    uint32_t m_Key;
    uint32_t m_DataOffset;
    uint16_t m_NumVariants;
    uint16_t m_NumContainers;
};

class CRuntimeContainer {
    uint64_t m_Base;
    const SRuntimeContainer* m_Container;

    public:
    template <typename T>
    bool GetValue(uint32_t key, T& value) const;
};

#endif