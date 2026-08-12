#ifndef COMPONENT_ANIMATION_RULE_SYSTEM_H
#define COMPONENT_ANIMATION_RULE_SYSTEM_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class CAnimationRuleSystem {
    public:
    enum EAnimationModifierType : int32_t {
        E_FRAME_BOUND = 0x0000,
        E_STATE_BOUND = 0x0001,
    };
};

#endif