#ifndef COMPONENTS_GAMEOBJECT_H
#define COMPONENTS_GAMEOBJECT_H

struct SObjectID;

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
    virtual unsigned long long GetObjectID() const;
    virtual void PostInit();
    bool IsTagged(const uint32_t hashed_tag);

    CGameObject();
    virtual ~CGameObject();
};

#endif