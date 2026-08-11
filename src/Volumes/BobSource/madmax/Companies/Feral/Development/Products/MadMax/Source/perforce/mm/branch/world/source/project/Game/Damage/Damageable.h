#ifndef PROJECT_GAME_DAMAGEABLE_H
#define PROJECT_GAME_DAMAGEABLE_H

#include "build/Win64/Final/ctg/components/Base/include/Base/Misc/Event.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/GameObject/Physics/PhysicsGameObject.h"
#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Types/HashString.h"
#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Math/Matrix.h"
#include "project/Game/GameObject/Healthbar.h"

class CDamageable : public CPhysicsGameObject, public NEvent::CEventHandler {
    friend class CPlayer;

    struct SExtraHitEvents {
        public:
        NEvent::CSendEvent<void,void,void,void,void> m_OnHitByPlayer;
        NEvent::CSendEvent<void,void,void,void,void> m_OnHitByEnemy;
    };

    struct SPerDamageTypeEvents {
        public:
        CHashString m_Type;
        NEvent::CSendEvent<void,void,void,void,void> m_OnHit;
        NEvent::CSendEvent<float,void,void,void,void> m_OnHitDamaged;
        NEvent::CSendEvent<void,void,void,void,void> m_OnHitNotDamaged;
        NEvent::CSendEvent<CMatrix4f,void,void,void,void> m_OnDestroy;
        NEvent::CReceiveEvent<void,void,void,void,void> m_ForceDestroy;
    };

    protected:
    bool m_Destroyed;
    bool m_Invulnerable;
    bool m_InvulnerableE3;
    NEvent::CReceiveEvent<void,void,void,void,void> m_RestoreHealth;
    NEvent::CReceiveEvent<void,void,void,void,void> m_ForceDestroy;
    NEvent::CReceiveEvent<void,void,void,void,void> m_MakeInvulnerable;
    NEvent::CReceiveEvent<void,void,void,void,void> m_MakeVulnerable;
    NEvent::CReceiveEvent<void,void,void,void,void> m_MakeInvulnerableE3;
    NEvent::CSendEvent<void,void,void,void,void> m_OnHit;
    NEvent::CSendEvent<float,void,void,void,void> m_OnHitDamaged;
    NEvent::CSendEvent<void,void,void,void,void> m_OnHitNotDamaged;
    NEvent::CSendEvent<CMatrix4f,void,void,void,void> m_OnDestroy;
    NEvent::CSendEvent<void,void,void,void,void> m_OnRemoved;
    NEvent::CSendEvent<void,void,void,void,void> m_OnHealthIncreased;
    NEvent::CSendEvent<void,void,void,void,void> m_OnHealthDecreased;
    CDamageable::SExtraHitEvents* m_ExtraHitEvents;
    std::vector<CDamageable::SPerDamageTypeEvents *,std::allocator<CDamageable::SPerDamageTypeEvents *> >* m_PerDamageTypeEvents;
    std::vector<std::pair<float,NEvent::CSendEvent<void,void,void,void,void> >,std::allocator<std::pair<float,NEvent::CSendEvent<void,void,void,void,void> > > > m_OnHealthDecreas;
    float m_MaxHealth;
    float m_CurHealth;
    float m_LastHealth;
    float m_Armor[8];
    CHashString m_OnlyAcceptDamageFromType;
    uint32_t m_DamageFromPlayerTimeStamp;
    CHealthbar* m_HealthbarPtr;

    public:
    static const float s_MagicInvunerableHealth;

    public:
    bool IsDestroyed() const;
};

#endif