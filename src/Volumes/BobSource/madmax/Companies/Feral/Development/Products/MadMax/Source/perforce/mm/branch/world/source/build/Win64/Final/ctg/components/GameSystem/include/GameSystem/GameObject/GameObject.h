#ifndef COMPONENTS_GAMEOBJECT_H
#define COMPONENTS_GAMEOBJECT_H

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
    
    public:
    virtual unsigned long long GetObjectID() const;
    virtual void PostInit();
    bool IsTagged(const uint32_t hashed_tag);

    CGameObject();
    virtual ~CGameObject();
};

#endif