#ifndef COMPONENTS_GAMEOBJECT_H
#define COMPONENTS_GAMEOBJECT_H

struct SObjectID;
struct SGameObjectInitContext;
struct SGameObjectUpdateContext;
struct SGameObjectRenderContext;
struct SGameObjectSetPropertiesContext;
class CAABox;
class CAnimatedModel;
class CSaveContext;
class CSaveInfo;
class static_string;
namespace NModelSystem {
    class CModelInstance;
}
namespace NCharacterSystem {
    class CContextAction;
}

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Types/Rtti.h"
#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/UpdateQueue.h"
#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Types/ObjectID.h"
#include "build/Win64/Final/engine/AvaCore/main/AvaCore/FileHandling/Parsing/PropertyContainerAllocators.h"
#include "build/Win64/Final/engine/AvaCore/main/AvaCore/FileHandling/Parsing/Variant.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/SaveSystem/SaveInfo.h"

class CGameObject : public CRtti {
    public:
    enum EUpdateType : int32_t {
        UpdateTypeNone = 0x0000,
        UpdateTypePreSim = 0x0001,
        UpdateTypePostSim = 0x0002,
        UpdateTypeRender = 0x0004,
        UpdateTypePreSimAndPostSim = 0x0003,
        UpdateTypePreSimAndRender = 0x0005,
        UpdateTypePostSimAndRender = 0x0006,
        UpdateTypeAll = 0x0007,
    };

    private: 
    uint32_t* m_Tags;
    uint8_t m_TagCount;
    SObjectID m_ObjectID;
    CHashString m_AliasID;
    CHashString m_NameHash;

    protected: 
    uint8_t m_Inited : 1; /* BitPos=0 */
    uint8_t m_PostInited : 1; /* BitPos=1 */

    public: 
    SUpdateQueueHandles m_UpdateHandles;
    uint8_t m_RemoveFromUpdate : 1; /* BitPos=0 */
    std::vector<std::shared_ptr<CGameObject>,std::allocator<std::shared_ptr<CGameObject> > > m_Children; // BOOST PTR
    std::weak_ptr<CGameObject> m_Parent; // BOOST PTR
    std::weak_ptr<CGameObject> m_WeakThis; // BOOST PTR

    private: 
    static int32_t m_ClassID;

    protected: 
    static bool s_LiveEditEnabled;

    public: 
    static const uint32_t s_MaxNumChildren;
    static const uint32_t s_MaxLengthChildName;
    
    public:
    virtual const CRttiTypeId& GetTypeId() const;
    virtual bool IsType(const CRttiTypeId&) const;
    CGameObject(const CGameObject&);
    CGameObject();
    virtual ~CGameObject();
    virtual void Init(SGameObjectInitContext*);

    protected: 
    virtual void PostInit();

    public: 
    virtual CGameObject::EUpdateType GetRequiredUpdates();
    virtual int32_t GetParallelizedUpdates() const;
    void InitHierarchy(SGameObjectInitContext*);
    void PostInitHierarchy();
    virtual void SetProperties(const CRuntimeContainer&, SGameObjectSetPropertiesContext*);
    virtual void ExtendedSetProperties(const CRuntimeContainer&, const CRuntimeContainer*, SGameObjectSetPropertiesContext*);
    virtual void UpdateProperty(uint32_t, const TVariant<CPCBlockAllocator<uint32_t> >&);
    virtual void ReadProperty(uint32_t, TVariant<CPCBlockAllocator<uint32_t> >&);
    virtual void UpdatePreSim(SGameObjectUpdateContext*);
    virtual void UpdatePostSim(SGameObjectUpdateContext*);
    virtual void UpdateRender(SGameObjectRenderContext*);
    std::weak_ptr<CGameObject> GetTopRootObject(); // BOOST PTR
    virtual int32_t GetUpdateOrder() const;
    virtual bool NeedsUpdate();
    virtual bool StayInUpdate();
    virtual bool StayInUpdatePreSim();
    virtual bool StayInUpdatePostSim();
    virtual bool StayInUpdateRender();
    void SetWeakThis(std::weak_ptr<CGameObject>); // BOOST PTR
    virtual void InitTransform(const CMatrix4f&);
    virtual void SetTransform(const CMatrix4f&);
    virtual bool GetTransform(CMatrix4f*);
    virtual const CMatrix4f& GetLocalTransform();
    virtual void SetLocalTransform(const CMatrix4f&);
    virtual bool HasLocalTransform();
    void InitTransformRecursivly(const CMatrix4f&);
    void SetTransformRecursivly(const CMatrix4f&);
    void SetChildTransformsRecursivly();
    virtual const bool GetRenderTransform(CMatrix4f*, const float);
    virtual NModelSystem::CModelInstance* GetModel(uint64_t) const;
    virtual NModelSystem::CModelInstance* GetModel() const;
    virtual uint64_t GetNumModels() const;
    virtual bool GetModelAABB(CAABox&) const;
    virtual bool GetModelSpaceAABB(CAABox&) const;
    virtual CAnimatedModel* GetAnimatedModel();
    virtual void* GetInterface(uint32_t, uint32_t);
    virtual void SetOpacity(float);
    uint64_t GetObjectID() const;
    uint32_t GetObjectIDLow() const;
    uint32_t GetObjectIDHigh() const;
    uint32_t GetAliasID() const;
    uint32_t GetNameHash() const;
    const char* GetName() const;
    void AddChildObject(std::shared_ptr<CGameObject>); // BOOST PTR
    void AddChildObjectSimple(std::shared_ptr<CGameObject>); // BOOST PTR
    void RemoveChildObject(std::shared_ptr<CGameObject>); // BOOST PTR
    virtual void CreateHierarchy(const CRuntimeContainer&, SGameObjectSetPropertiesContext*);
    void ConnectObjects(const CRuntimeContainer&, SGameObjectSetPropertiesContext*);
    uint32_t GetHierarchyDepth();
    void SetObjectIDAndAlias(const CRuntimeContainer&);
    virtual static_string GetKlassName() const;
    // virtual void AddContextAction(const std::shared_ptr<NCharacterSystem::CContextAction>&, int32_t); // BOOST PTR // CContextAction does not appear in any debug info i have found
    virtual void Enable(bool);
    virtual void AddToUpdate();
    void RemoveFromUpdate();
    virtual void OnParentDamageLevelChanged();
    virtual void Save(CSaveContext&);
    virtual void Load(const CSaveContext&);
    virtual CSaveInfo* GetSaveInfo();
    bool IsAncestor(CGameObject*) const;

    protected: 
    virtual void RegisterUpdatePreSim(bool);
    virtual void RegisterUpdatePostSim(bool);
    virtual void RegisterUpdateRender(bool);
    bool GetParentTransform(CMatrix4f*);

    public: 
    const bool GetParentRenderTransform(CMatrix4f*, const float);

    private: 
    void __RemoveFromUpdate();

    public: 
    bool IsTagged(const uint32_t) const;
    void GetTags(const uint32_t*&, unsigned char&) const;

    private: 
    void SetupTags(const CRuntimeContainer&);

    public: 
    bool FindChildByNameHashOptional(const uint32_t, std::shared_ptr<CGameObject>&, const bool); // BOOST PTR
    bool FindChildByNameHashCritical(const uint32_t, std::shared_ptr<CGameObject>&, const bool); // BOOST PTR
    bool Inited() const;
    CGameObject& operator=(const CGameObject&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
    
    public: 
    static const CRttiTypeId& TYPE_ID();
    static bool ResolveTagCache(const uint32_t, const std::list<CGameObject *,std::allocator<CGameObject *> >*&);
    static bool FindOptional(uint64_t, std::shared_ptr<CGameObject>&); // BOOST PTR
    static bool FindCritical(uint64_t, std::shared_ptr<CGameObject>&); // BOOST PTR
    static bool FindByAliasOptional(uint32_t, std::shared_ptr<CGameObject>&); // BOOST PTR
    static bool FindByAliasCritical(uint32_t, std::shared_ptr<CGameObject>&); // BOOST PTR
    static const std::map<uint64_t,std::weak_ptr<CGameObject>,std::less<uint64_t>,std::allocator<std::pair<uint64_t const ,std::weak_ptr<CGameObject> > > >& GetGameObjectList(); // BOOST PTR
    static void PatchIDs(CRuntimeContainer&, uint32_t);
    static void PatchLocalEvents(CRuntimeContainer&, uint32_t);
    static void PatchIDsAndLocalEvents(CRuntimeContainer&, uint32_t);
    static void SetLiveEdit(bool);
    static bool GetLiveEdit();

    private: 
    static void AddToTagCacheMap(const uint32_t, CGameObject*);
    static void RemoveFromTagCacheMap(const uint32_t, CGameObject*);
    static bool RemoveAliasRef(CHashString, uint64_t);
    static void AddAliasRef(CHashString, uint64_t);
    static bool FindAnyByAlias(CHashString, uint64_t&);
};

#endif