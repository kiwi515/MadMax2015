#ifndef LIB_XVM_ADF_H
#define LIB_XVM_ADF_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct SXvmFormatFunction {
    struct ArrayName {
        public: 
        unsigned char* m_Data;
        uint32_t m_Count;
        
        public: 
        uint64_t GetDataSize() const;
        const unsigned char& operator[](uint32_t) const;
        unsigned char& operator[](uint32_t);
        uint32_t GetSize() const;
    };

    struct ArrayInstructions {
        public: 
        uint16_t* m_Data;
        uint32_t m_Count;
        
        public: 
        uint64_t GetDataSize() const;
        const uint16_t& operator[](uint32_t) const;
        uint16_t& operator[](uint32_t);
        uint32_t GetSize() const;
    };

    public: 
    uint32_t m_NameHash;
    uint16_t m_LocalsCount;
    uint16_t m_ArgCount;
    SXvmFormatFunction::ArrayInstructions m_Instructions;
    uint16_t m_MaxStackDepth;
    uint64_t m_Module;
    uint64_t m_LinenoPtr;
    uint64_t m_ColnoPtr;
    SXvmFormatFunction::ArrayName m_Name;
    
    public: 
    void SetDefaultValues();
};

#endif