#ifndef COMPONENT_INPUT_ACTION_MAP_H
#define COMPONENT_INPUT_ACTION_MAP_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Input {
    static CHashString HASH_player;

class CInputActionMap {
    public:
    virtual float GetValue(uint32_t);
};

}

#endif