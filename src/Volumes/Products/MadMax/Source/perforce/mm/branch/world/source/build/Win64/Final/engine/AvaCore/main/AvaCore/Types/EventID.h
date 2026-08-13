#ifndef ENGINE_EVENT_ID_H
#define ENGINE_EVENT_ID_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct SEventID {
    public: 
    uint32_t m_Hash;
    uint32_t m_NameSpace;
  
    public: 
    SEventID(uint32_t, uint32_t);
    SEventID(uint64_t);
    SEventID();
    bool operator==(const SEventID&);
    operator uint64_t() const;
};

#endif