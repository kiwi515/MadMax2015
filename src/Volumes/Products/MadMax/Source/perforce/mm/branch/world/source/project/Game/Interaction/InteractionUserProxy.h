#ifndef PROJECT_GAME_INTERACTION_USER_PROXY_H
#define PROJECT_GAME_INTERACTION_USER_PROXY_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "libs/CoreLibs/main/include/ALib/Array.h"
#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Math/Matrix.h"
#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Math/Vector.h"
#include "project/Game/Interaction/InteractionGraphData/InteractionGraphUserEdge.h"
#include "project/Game/Interaction/InteractionGraphData/InteractionGraphExit.h"
#include "project/Game/Interaction/InteractionGraphEntry.h"
#include "project/Game/Interaction/InteractionGraphData/InteractionGraphTransition.h"
#include "project/Game/Interaction/InteractionGraphData/InteractionGraphNode.h"
#include "project/Game/Interaction/InteractionGraph.h"
#include "project/Game/Interaction/InteractionTrigger.h"
#include "project/Game/Interaction/InteractionContext.h"
#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Types/HashString.h"
#include "project/Game/Character/Character.h"



class CInteractionUserProxy {
    public:
    struct SInteractionGraphMovementToActMapping {
        public:
        TArray<int> m_MovementIdentifiers;
        TArray<int> m_ActEvents;
    };

    enum EIGraphUserState : int32_t {
        IGUS_INACTIVE = 0x0000,
        IGUS_ACTIVE_NODE = 0x0001,
        IGUS_ACTIVE_ENTRY = 0x0002,
        IGUS_ACTIVE_EXIT = 0x0003,
        IGUS_ACTIVE_TRANSITION = 0x0004,
    };

    public: 
    CCharacter* m_Character;
    CInteractionGraph* m_Graph;
    CInteractionGraphNode* m_CurrentNode;
    CInteractionGraphNode* m_TransitionFromNode;
    CInteractionGraphTransition* m_CurrentTransition;
    CInteractionGraphEntry* m_CurrentEntry;
    CInteractionGraphExit* m_CurrentExit;
    CInteractionGraphUserEdge* m_CurrentUserEdge;
    CInteractionGraphUserEdge* m_IntermediateUserEdge;
    CInteractionGraphUserEdge* m_ActiveUserEdge;
    CMatrix4f m_LocalMatrix;
    CMatrix4f m_MoveStartLS;
    CMatrix4f m_MoveEndLS;
    CVector3f m_ScaledAnimationTranslation;
    CMatrix4f m_ScaledAnimationRotationOffset;
    CMatrix4f m_ScaledAnimationRotationCurrentOffset;
    float m_LineNodeFraction;
    float m_MoveFraction;
    CVector2f m_EdgeRelativeInput;
    bool m_MotionStateEnabled;
    bool m_PhysicsUpdateEnable;
    bool m_UseInitFrame;
    TArray<CInteractionGraphEntry *> m_PotentialEntries;
    CHashString m_NamedFailEntry;

    private: 
    CInteractionUserProxy::SInteractionGraphMovementToActMapping m_MovementIdentifierToActMapping;
    std::vector<CInteractionTrigger *,std::allocator<CInteractionTrigger *> > m_InteractionTriggers;
    TArray<CInteractionGraphEntry *> m_ValidEntries;
    TArray<CInteractionGraphEntry *> m_PreviousValidEntries;
    CInteractionUserProxy::EIGraphUserState m_GraphUserState;
    bool m_IsValidatingEntry;
    bool m_ReEnterStateFlag;

    public: 
    static const uint32_t POTENTIAL_ENTRIES_CAPACITY;

    private: 
    static const uint32_t VALID_ENTRIES_CAPACITY;

    public:
    CInteractionContext* GetContext() const;
};

#endif