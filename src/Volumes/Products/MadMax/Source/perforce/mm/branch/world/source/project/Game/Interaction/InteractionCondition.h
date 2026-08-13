#ifndef PROJECT_GAME_INTERACTION_CONDITION_H
#define PROJECT_GAME_INTERACTION_CONDITION_H

class CInteractionUserProxy;

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "project/Game/Interaction/InteractionUserProxy.h"

class CInteractionCondition {
    public: 
    int32_t m_EvaluationPriority;
    
    public: 
    CInteractionCondition(const CInteractionCondition&);
    CInteractionCondition();
    virtual ~CInteractionCondition();
    virtual bool Evaluate(CInteractionUserProxy*);
    virtual void SetProperties(const CRuntimeContainer&);
    virtual void SetParentEntry(CInteractionGraphEntry*);
    virtual void SetParentExit(CInteractionGraphExit*);
    int32_t GetSortOrder();
    CInteractionCondition& operator=(const CInteractionCondition&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
};

#endif