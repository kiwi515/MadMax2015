#ifndef PROJECT_GAME_AI_ENTITIES_GAME_H
#define PROJECT_GAME_AI_ENTITIES_GAME_H

class CCharacter;
class CInteractionContext;
class CInteractionGraph;
class CVehicle;
class CRuntimeContainer;
struct SAiEntityInstance;
struct SAiEntityProperty;

#include "project/fragments/ai/include/AiBehavior/AiLinAlg.h"
#include "project/fragments/ai/include/AiBehavior/AiEntities.h"
#include "project/Game/AI/GameObject/NamedPoint.h"
#include "project/Game/GameObject/SplineObjectGame.h"

class CAiObjectEntity {
    protected: 
    uint32_t m_Handle;
    uint32_t m_Hash;
    bool m_HashRegistered;
    
    public: 
    CAiObjectEntity(const CAiObjectEntity&);
    CAiObjectEntity();
    virtual ~CAiObjectEntity();
    uint32_t GetHandle() const;
    uint32_t GetHash() const;
    const SAiEntityInstance* GetInstance() const;
    SAiEntityInstance* GetInstance();
    const SAiEntityInstance* GetConstInstance() const;

    protected: 
    virtual void Reset(SAiEntityInstance*);

    public: 
    void Reset();
    void RegisterHash(uint32_t);
    void UnregisterHash();
    bool IsRegistered();
    SAiEntityInstance* CreateInstance();
    void ParseEntityProperties(const CRuntimeContainer&);
    void SetValid(bool);

    protected: 
    void ResetProperties(SAiEntityInstance*);

    public: 
    CAiObjectEntity& operator=(const CAiObjectEntity&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
    
    static void ParseEntityProperties(const CRuntimeContainer&, std::vector<SAiEntityProperty,std::allocator<SAiEntityProperty> >&);
};

class CAiCharacterEntity : public CAiObjectEntity {
    public: 
    SMatrix4f m_BoneMatrices[2];
    uint32_t m_BoneNames[2];
    static const int32_t MAX_BONE_COUNT;
    
    public: 
    virtual ~CAiCharacterEntity();
    bool Create(CCharacter*);
    void Init(CCharacter*);
    CAiCharacterEntity(const CAiCharacterEntity&);
    CAiCharacterEntity();
    CAiCharacterEntity& operator=(const CAiCharacterEntity&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
};

class CAiInteractionContextEntity : public CAiObjectEntity {
    public: 
    bool Create(CInteractionContext*);
    void Init(CInteractionContext*);

    protected: 
    virtual void Reset(SAiEntityInstance*);

    public: 
    CAiInteractionContextEntity(const CAiInteractionContextEntity&);
    CAiInteractionContextEntity();
    virtual ~CAiInteractionContextEntity();
    CAiInteractionContextEntity& operator=(const CAiInteractionContextEntity&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
};

class CAiInteractionGraphEntity : public CAiObjectEntity {
    public: 
    void SetLocalTransform(const CMatrix4f&);
    bool Create(CInteractionGraph*);
    void Init(CInteractionGraph*);
    CAiInteractionGraphEntity(const CAiInteractionGraphEntity&);
    CAiInteractionGraphEntity();
    virtual ~CAiInteractionGraphEntity();
    CAiInteractionGraphEntity& operator=(const CAiInteractionGraphEntity&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
};

class CAiNamedPointEntity : public CAiObjectEntity {
    public: 
    bool Create(CNamedPoint*);
    void Init(CNamedPoint*);
    CAiNamedPointEntity(const CAiNamedPointEntity&);
    CAiNamedPointEntity();
    virtual ~CAiNamedPointEntity();
    CAiNamedPointEntity& operator=(const CAiNamedPointEntity&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
};

class CAiSplineEntity : public CAiObjectEntity {
    public: 
    bool Create(CSplineObjectGame*);
    CAiSplineEntity(const CAiSplineEntity&);
    CAiSplineEntity();
    virtual ~CAiSplineEntity();
    CAiSplineEntity& operator=(const CAiSplineEntity&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
};

class CAiVehicleEntity : public CAiObjectEntity {
    public: 
    virtual ~CAiVehicleEntity();
    bool Create(CVehicle*);
    void Init(CVehicle*);

    protected: 
    virtual void Reset(SAiEntityInstance*);

    public: 
    CAiVehicleEntity(const CAiVehicleEntity&);
    CAiVehicleEntity();
    CAiVehicleEntity& operator=(const CAiVehicleEntity&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
};

#endif