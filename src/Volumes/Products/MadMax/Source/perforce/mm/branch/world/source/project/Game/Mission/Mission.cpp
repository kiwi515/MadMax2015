#define BATCH_GAME_826130353_18_50
#include "Mission.h"

#ifdef BATCH_GAME_826130353_18_50

void NMissionSystem::CMission::UnlockMsg() {
    SEventID eventId(this->m_Data->m_Objectives.m_Data->m_EventHash[0], 0);

    NEvent::CEventData eventData(0xffffffffff, nullptr, nullptr, nullptr, nullptr, nullptr);
    
    CAvaSingle<CEventSystem>::Instance->SendEvent(&eventId, 1, eventData);
}

#endif