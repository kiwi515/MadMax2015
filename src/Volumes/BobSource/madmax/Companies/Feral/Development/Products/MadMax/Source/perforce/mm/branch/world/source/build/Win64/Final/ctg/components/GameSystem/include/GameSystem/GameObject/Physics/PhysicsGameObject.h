#ifndef COMPONENT_PHYSICS_GAME_OBJECT_H
#define COMPONENT_PHYSICS_GAME_OBJECT_H

#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/GameObject/GameObject.h"
#include "build/Win64/Final/ctg/components/Physics/include/Physics/PfxGameObject.h"

class CPhysicsGameObjectListenerContainer {

};

class CPhysicsGameObject : public IPfxGameObject, public CGameObject {
    public:
    struct SHitByExplosionData {

    };

    struct SHitByBulletData {

    };

    struct SHitByFireData {

    };
};

class IPhysicsGameObjectListenable {

};

#endif