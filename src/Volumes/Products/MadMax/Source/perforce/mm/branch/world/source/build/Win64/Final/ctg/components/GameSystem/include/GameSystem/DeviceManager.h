#ifndef COMPONENT_DEVICE_MANAGER_H
#define COMPONENT_DEVICE_MANAGER_H

#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Misc/Singleton.h"
#include "build/Win64/Final/ctg/components/Input/include/Input/InputDeviceManagerInterface.h"

class CDeviceManager : public CAvaSingle<CDeviceManager> {
    public:
    static Input::IInputDeviceManager* GetInputManager();
};

#endif