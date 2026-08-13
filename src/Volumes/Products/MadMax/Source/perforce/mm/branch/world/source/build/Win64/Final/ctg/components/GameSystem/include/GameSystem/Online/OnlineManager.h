#ifndef COMPONENT_ONLINE_MANAGER_H
#define COMPONENT_ONLINE_MANAGER_H

#include "build/Win64/Final/ctg/components/Base/include/Base/Misc/Event.h"
#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Misc/Singleton.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/Online/IEventData.h"

namespace NNetwork {
    class COnlineManager : public CAvaSingle<NNetwork::COnlineManager>, public NEvent::CEventHandler {
        public:
        void AddMetricData(NMetricsEvent::IEventData*);
    };
};

#endif