#ifndef PROJECT_GAME_TURN_TAKER_GAME_OBJECT_H
#define PROJECT_GAME_TURN_TAKER_GAME_OBJECT_H

#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/GameObject/GameObject.h"

class CTurnTakerHelperStaticRaycastTracker {
    uint64_t m_TurnTakerId;
    bool m_LastTestVisible;
    bool m_RegisteredWithTurnTaker;
    CGameObject* m_wpTurnTaker;
};

#endif