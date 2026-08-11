#ifndef COMPONENT_SAVE_BIT_STORAGE_H
#define COMPONENT_SAVE_BIT_STORAGE_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class CSaveBitStorage {
    uint64_t* m_Hashes;
    uint64_t* m_Bits;
    uint32_t m_Size;
    uint32_t m_AmountStoredHash;
};

#endif