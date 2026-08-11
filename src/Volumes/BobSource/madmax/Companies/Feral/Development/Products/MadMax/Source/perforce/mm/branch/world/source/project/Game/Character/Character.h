#ifndef PROJECT_GAME_CHARACTER_H
#define PROJECT_GAME_CHARACTER_H

#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/CharacterSystem/CharacterBase.h"
#include "project/Game/Interaction/InteractionUserProxy.h"
#include "project/Game/Health/HealthWrapper.h"

class CCharacter : public CDamageable, public NCharacterSystem::CCharacterBase, public IPhysicsGameObjectListenable {
    public:
    CInteractionUserProxy m_InteractionUserProxy;
    
    public:
    static bool IsDead(float for_how_long);
    static float GetFloatRegister(int32_t index);
    int32_t GetFaction() const;
    virtual void SetTransform(const CMatrix4f& new_world_matrix);
    virtual CHealthWrapper* GetHealthWrapper() const; 
    void Revive();
    virtual void Enable(bool enable);
};

#endif