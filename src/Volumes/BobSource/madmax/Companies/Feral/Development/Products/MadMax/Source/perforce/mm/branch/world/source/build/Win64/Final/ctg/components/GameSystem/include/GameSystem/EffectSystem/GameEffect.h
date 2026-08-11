#ifndef COMPONENT_GAME_EFFECT_H
#define COMPONENT_GAME_EFFECT_H

#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Types/HashString.h"
#include "libs/ResourceCache/main/include/ResourceCache/ResourceCache.h"

struct SGameEffectContainer {
    public:
    CHashString m_HashedEffectName;
    SResourceHandle* m_ResourceHandle;
};

#endif