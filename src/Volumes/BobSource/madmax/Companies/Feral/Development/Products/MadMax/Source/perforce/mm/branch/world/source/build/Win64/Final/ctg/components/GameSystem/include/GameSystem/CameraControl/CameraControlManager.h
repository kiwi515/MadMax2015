#ifndef COMPONENT_CAMERA_CONTROL_MANAGER_H
#define COMPONENT_CAMERA_CONTROL_MANAGER_H

#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Misc/Singleton.h"

class CCameraControlManager : public CAvaSingle<CCameraControlManager> {
    public:
    float GetPlayerOpacity();
};

#endif