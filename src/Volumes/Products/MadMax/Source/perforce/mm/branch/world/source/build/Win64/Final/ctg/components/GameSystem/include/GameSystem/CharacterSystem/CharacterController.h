#ifndef COMPONENT_CHARACTER_CONTROLLER_H
#define COMPONENT_CHARACTER_CONTROLLER_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace NCharacterSystem {

class CCharacterController {
    private:
    int32_t m_CameraId;
    int32_t m_AimCameraId;
};

}

#endif