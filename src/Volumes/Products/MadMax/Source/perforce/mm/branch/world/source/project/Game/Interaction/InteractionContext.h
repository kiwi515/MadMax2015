#ifndef PROJECT_GAME_INTERACTION_CONTEXT_H
#define PROJECT_GAME_INTERACTION_CONTEXT_H

class CInteraction;
class CAiInteractionContextEntity;
class CInteractionComponentKit;
class CInteractionConditionKit;

#include "project/Game/AI/AiEntitiesGame.h"
#include "project/Game/Interaction/InteractionComponents/InteractionComponentKit.h"
#include "project/Game/Interaction/InteractionConditionKit.h"

class CInteractionContext : public CGameObject, public NEvent::CEventHandler {
    protected: CMatrix4f m_LocalTransform;
    CSaveInfo m_SaveInfo;

    public: 
    std::shared_ptr<CInteractionGraph> m_InteractionGraphs[16]; // BOOST PTR
    CInteractionTrigger* m_InteractionTriggers[16];
    CInteraction* m_Interactions[16];

    private: 
    CHashString m_Name;
    CMatrix4f m_WorldMatrix;
    NEvent::CReceiveEvent<void,void,void,void,void> m_EnableEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_DisableEvent;
    CMatrix4f m_StartTransform;
    bool m_StartTransformHasBeenSet;
    bool m_KeepStartPosition;
    bool m_HasOccupants;
    bool m_Enabled;
    bool m_EnabledOverride : 1;

    public: 
    bool m_LocalDebugDrawGraphs : 1; /* BitPos=1 */
    uint16_t m_NofGraphs;
    CAiInteractionContextEntity m_AiEntity;

    public: 
    static const uint32_t INTERACTION_GRAPHS_CAPACITY;
    static bool s_GlobalDebugDrawGraphs;
    static bool s_GlobalDebugDrawGraphsName;
    static bool s_GlobalDebugDrawEntries;
    static bool s_GlobalDebugDrawEntriesName;
    static bool s_GlobalDebugTriggers;
    static const uint32_t INTERACTION_TRIGGERS_CAPACITY;
    static const uint32_t INTERACTIONS_CAPACITY;

    private: 
    static CInteractionComponentKit* m_ComponentKit;
    static CInteractionConditionKit* m_ConditionKit;
    
    public: 
    virtual static_string GetKlassName() const;
    virtual const CMatrix4f& GetLocalTransform();
    virtual void SetLocalTransform(const CMatrix4f&);
    virtual bool HasLocalTransform();

    protected: 
    virtual void Save(CSaveContext&);
    virtual void Load(const CSaveContext&);
    virtual CSaveInfo* GetSaveInfo();

    public: 
    virtual const CRttiTypeId& GetTypeId() const;
    virtual bool IsType(const CRttiTypeId&) const;
    CInteractionContext(const CInteractionContext&);
    CInteractionContext();
    virtual ~CInteractionContext();

    protected: 
    virtual void PostInit();
    virtual CGameObject::EUpdateType GetRequiredUpdates();

    public: 
    virtual void Clear();
    virtual void UpdatePostSim(SGameObjectUpdateContext*);
    virtual void UpdateRender(SGameObjectRenderContext*);
    virtual void HandleEvent(const NEvent::CEventImpl*, const NEvent::CEventData&);
    virtual void Enable(bool);
    bool IsEnabled() const;
    virtual void SetProperties(const CRuntimeContainer&, SGameObjectSetPropertiesContext*);
    virtual void SetTransform(const CMatrix4f&);
    virtual void InitTransform(const CMatrix4f&);
    virtual bool GetTransform(CMatrix4f*);
    virtual CMatrix4f& GetTransformRef();
    virtual void RenderEditorSpecifics(bool);
    const CHashString& GetName() const;
    const bool KeepStartPosition();
    uint32_t GetNofGraphs();
    CInteractionGraph* GetGraphByHash(uint32_t);
    CInteractionGraph* GetGraphByIndex(uint32_t);
    CInteraction* GetInteractionById(uint64_t);
    CInteraction* GetInteractionByNameHash(const uint32_t);
    bool GetReferenceFrameCollisionGroup(uint32_t*);
    void SetStartTransformForInteraction(CMatrix4f);
    CMatrix4f& GetStartTransformForInteraction(CMatrix4f&);
    CInteractionContext& operator=(CInteractionContext&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
    
    public: 
    static static_string GetClassNameStatic();
    static const CRttiTypeId& TYPE_ID();
    static CInteractionComponentKit* GetInteractionComponentKit();
    static void RegisterInteractionComponents();
    static void UnregisterInteractionComponents();
    static CInteractionConditionKit* GetInteractionConditionKit();
    static void RegisterInteractionConditions();
    static void UnregisterInteractionConditions();
};

#endif