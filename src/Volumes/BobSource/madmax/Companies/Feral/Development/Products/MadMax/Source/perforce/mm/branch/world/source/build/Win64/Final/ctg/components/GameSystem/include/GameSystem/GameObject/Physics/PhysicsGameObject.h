#ifndef COMPONENT_PHYSICS_GAME_OBJECT_H
#define COMPONENT_PHYSICS_GAME_OBJECT_H

#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/GameObject/GameObject.h"
#include "build/Win64/Final/ctg/components/Physics/include/Physics/PfxGameObject.h"

class CPhysicsGameObjectListenerContainer {

};

class CPhysicsGameObject : public IPfxGameObject, public CGameObject {
    public:
    struct SHitByExplosionData { /* Size=0x60 */
        public: 
        CVector3f m_Position;
        CVector3f m_Direction;
        float m_Damage;
        float m_Impulse;
        int32_t m_Faction;
        int32_t m_Level;
        float m_ExecuteDelay;
        float m_Radius;
        float m_DamageScale;
        float m_DamageRadius;
        float m_FireDamageRadius;
        CHashString m_AnimationEvent;
        CVector3f m_HitPosition;
        float m_Distance;
        float m_ForcePower;
        float m_PhysicsImpulse;
        CHashString m_DamageType;
        CHashString m_ExplosionTypeName;
        
        public: 
        SHitByExplosionData(const CPhysicsGameObject::SHitByExplosionData&);
        SHitByExplosionData();
        CPhysicsGameObject::SHitByExplosionData& operator=(const CPhysicsGameObject::SHitByExplosionData&);
    };

    struct SHitByBulletData {

    };

    struct SHitByFireData {

    };
};

class IPhysicsGameObjectListenable {

};

#endif