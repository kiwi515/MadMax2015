#ifndef COMPONENT_EVENT_STRUCTS_GEN_H
#define COMPONENT_EVENT_STRUCTS_GEN_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/Online/EventStructs.h"
#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Types/HashString.h"

class GlobalDifficultySetting : public SEventBaseData {
    public:
    int32_t difficulty;

    public: 
    virtual CHashString InstanceClassId() const;
    virtual bool IsInstanceOf(CHashString) const;
    virtual SEventBaseData* Clone() const;
    virtual const char* EventType() const;
    virtual const char* EventName() const;
    virtual float GetNumericalField(CHashString) const;
    virtual uint32_t GetIntegerField(CHashString, bool&) const;
    virtual int32_t GetSignedIntegerField(CHashString, bool&) const;
    GlobalDifficultySetting(const GlobalDifficultySetting&);
    GlobalDifficultySetting();
    virtual ~GlobalDifficultySetting();
    GlobalDifficultySetting& operator=(const GlobalDifficultySetting&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
    static CHashString ClassId();
};

#endif