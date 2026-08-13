#ifndef LIB_XVM_H
#define LIB_XVM_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct HXvmObject {
    public: 
    uint64_t m_Flags;
    uint64_t m_Value;
    
    public: 
    HXvmObject(const HXvmObject&);
    HXvmObject(uint64_t, uint64_t);
    HXvmObject();
    const HXvmObject& operator=(const HXvmObject&);
    bool operator==(const HXvmObject&) const;
    bool operator!=(const HXvmObject&) const;
};

#endif