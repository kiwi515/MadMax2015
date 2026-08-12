#ifndef PROJECT_GAME_CHARACTER_IK_H
#define PROJECT_GAME_CHARACTER_IK_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class CCharacterIK {
    public:
    enum ETypes : int32_t {
        LEFT_ARM = 0x0000,
        RIGHT_ARM = 0x0001,
        LEFT_LEG = 0x0002,
        RIGHT_LEG = 0x0003,
        NOF_IK_CHAINS = 0x0004,
    };
};

#endif