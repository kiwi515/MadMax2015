#ifndef PROJECT_GAME_BONE_INDICES_H
#define PROJECT_GAME_BONE_INDICES_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace NBone {
    enum ESafeBoneIndex : int32_t { // this is a guess as to where this is defined
        REFERENCE = -1900872324,
        TARGET = 0x69a93d50,
        HIPS = 0x68c6a89f,
        LEFT_FOOT = 0x661134ac,
        RIGHT_FOOT = -12713909,
        LEFT_HAND = 0x57c83f95,
        RIGHT_HAND = 0x69e77fa6,
        HEAD = -1468540468,
        NECK = -1580637864,
        SPINE = 0x0e28c84b,
        SPINE1 = -455351441,
        SPINE2 = 0x6fe84908,
        LEFT_SHOULDER = -2026561411,
        RIGHT_SHOULDER = 0x302eee80,
        ATTACH_HAND_RIGHT = -714879458,
        ATTACH_HAND_LEFT = 0x5ea086b8,
        RIGHT_HAND_IK = -1123982540,
        LEFT_HAND_IK = -1702916962,
        RIGHT_FOOT_IK = 0x42294e4a,
        LEFT_FOOT_IK = 0x620737e1,
        RIGHT_LEG = -1466269347,
        LEFT_LEG = 0x782bf8f9,
        RIGHT_UP_LEG = -1893520619,
        LEFT_UP_LEG = 0x26392bc2,
        RIGHT_ARM = 0x19d4b6cf,
        LEFT_ARM = 0x4df0a2b1,
        CAMERA = -1246908626,
        CAMERA_REF = 0x27413152,
        BONE_NULL = 0x0000,
    };
};

#endif