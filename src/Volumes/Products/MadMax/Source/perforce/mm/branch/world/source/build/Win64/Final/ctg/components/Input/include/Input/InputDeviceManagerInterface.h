#ifndef COMPONENT_INPUT_DEVICE_MANAGER_INTERFACE_H
#define COMPONENT_INPUT_DEVICE_MANAGER_INTERFACE_H

#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Types/HashString.h"
#include "build/Win64/Final/ctg/components/Input/include/Input/InputActionMap.h"

namespace Input {

class IInputDeviceManager {
    public:
    static Input::CInputActionMap* GetActionMap(const CHashString& id);
};

}

#endif