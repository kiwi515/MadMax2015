#ifndef PROJECT_GAME_INTERACTION_COMPONENT_SET_MODIFIER_H
#define PROJECT_GAME_INTERACTION_COMPONENT_SET_MODIFIER_H

#include "project/Game/Interaction/InteractionComponents/InteractionComponent.h"

class CInteractionComponentSetModifier : public CInteractionComponent {
    private: 
    CHashString m_ModifierId;
    
    public: 
    virtual const CRttiTypeId& GetTypeId() const;
    virtual bool IsType(const CRttiTypeId&) const;
    CInteractionComponentSetModifier(const CInteractionComponentSetModifier&);
    CInteractionComponentSetModifier();
    virtual ~CInteractionComponentSetModifier();
    virtual void SetProperties(CInteractionContext*, const CRuntimeContainer&);
    virtual void Execute(CInteractionUserProxy*);
    CInteractionComponentSetModifier& operator=(const CInteractionComponentSetModifier&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
    
    public: 
    static CInteractionComponent* Create();
    static void Register();
    static void Unregister();
    static const CRttiTypeId& TYPE_ID();
};

#endif