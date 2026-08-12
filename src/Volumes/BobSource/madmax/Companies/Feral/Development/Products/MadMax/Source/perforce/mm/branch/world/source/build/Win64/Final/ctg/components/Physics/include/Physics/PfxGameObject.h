#ifndef COMPONENT_PFX_GAME_OBJECT_H
#define COMPONENT_PFX_GAME_OBJECT_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class IPfxGameObject {
    public:
    struct SHitReactInfo {

    };

    enum E_BREAKRESULT : int32_t {
        ONBREAK_CB_BREAK = 0x0000,
        ONBREAK_CB_DONT_BREAK = 0x0001,
    };

    public: 
    virtual ~IPfxGameObject();
    virtual IPfxInstance* GetIPfxInstance();
    virtual void DoReactToHit(const IPfxGameObject::SHitReactInfo&);
    //virtual IPfxGameObject::E_BREAKRESULT OnBreak(const hkpBreakOffPartsListener::ContactImpulseLimitBreachedEvent&, hkArray<unsigned int,hkContainerHeapAllocator>&, hkpPhysicsSystem&);
    virtual bool NotifyOutOfBroadphase() const;
    virtual void OnOutOfBroadphase();
    IPfxGameObject(const IPfxGameObject&);
    IPfxGameObject();
    IPfxGameObject& operator=(const IPfxGameObject&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
};

#endif