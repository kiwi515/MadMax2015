#ifndef COMPONENT_CLOCK_H
#define COMPONENT_CLOCK_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Misc/Singleton.h"

namespace Base {
    class CClock : public CAvaSingle<Base::CClock> {
        public: 
        uint32_t GetGameTime(bool) const;
    };
};

#endif