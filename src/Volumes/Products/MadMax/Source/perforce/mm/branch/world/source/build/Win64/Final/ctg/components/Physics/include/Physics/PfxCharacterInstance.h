#ifndef COMPONENT_CHARACTER_INSTANCE_H
#define COMPONENT_CHARACTER_INSTANCE_H

#include "build/Win64/Final/ctg/components/Physics/include/Physics/PhysicsSystem.h"
#include "build/Win64/Final/ctg/components/Physics/include/Physics/PfxInstance.h"

class CPfxCharacterInstance : public IPfxInstance, public CPfxPreSimulationCallback {
    public:
    enum EProxyState : int32_t {
        STANDING = 0x0000,
        CROUCHING = 0x0001,
        SWIMMING = 0x0002,
        ROTATED_STANDING = 0x0003,
        SAFE_PERSONAL_SPACE_100 = 0x0004,
        SAFE_PERSONAL_SPACE_067 = 0x0005,
        STANDING_LARGE = 0x0006,
        STANDING_CLOSE_COMBAT = 0x0007,
        CREATURE = 0x0008,
        SLENDERMAN = 0x0009,
        NR_PROXY_GEOMS = 0x000a,
    };

    public:
    class CharacterInput {

    };
};

#endif