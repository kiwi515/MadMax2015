#ifndef COMPONENT_DATA_SAVE_HANDLER_H
#define COMPONENT_DATA_SAVE_HANDLER_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class CDataSaveHandler {
    struct SDataSave {
        public:
        uint64_t m_Size;
        uint32_t m_Data[1];
    };

    private: 
    std::map<uint64_t, CDataSaveHandler::SDataSave*> m_DataSave;
    unsigned char* m_MemoryAllocation[8];
    uint64_t m_CurrentMemoryPool;
    uint64_t m_CurrentMemoryPoolOffset;
    static const int32_t MEMORY_POOL_SIZE;
    static const int32_t MAX_MEMORY_POOLS;
};

#endif