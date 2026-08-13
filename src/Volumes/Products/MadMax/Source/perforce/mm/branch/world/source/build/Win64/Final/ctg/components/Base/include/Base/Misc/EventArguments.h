#ifndef COMPONENT_EVENT_ARGUMENTS_H
#define COMPONENT_EVENT_ARGUMENTS_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace NEvent {
    class CEventData {
        uint64_t m_Type;
        const void* m_Pointers[5];

        public:
        CEventData(uint64_t type, const void* p1, const void* p2, const void* p3, const void* p4, const void* p5) 
            : m_Type(type), m_Pointers{p1, p2, p3, p4, p5} {};

        ~CEventData() {};

        void Push(uint32_t, void*);
        void __dflt_ctor_closure();
        void* __vecDelDtor(uint32_t);
    };
}

#endif