#ifndef COMPONENT_UPDATE_QUEUE_H
#define COMPONENT_UPDATE_QUEUE_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

enum EUpdateQueue : int32_t {
    QueuePreUpdate = 0x0000,
    QueuePostUpdate = 0x0001,
    QueueParallellToRender = 0x0002,
    QueueUpdateRender = 0x0003,
    NofQueues = 0x0004,
};

struct SUpdateQueueHandle { /* Size=0x8 */
    public: 
    EUpdateQueue m_Queue;
    uint16_t m_Handle;
    
    public: 
    SUpdateQueueHandle(EUpdateQueue, uint16_t);
    SUpdateQueueHandle();
};

struct SUpdateQueueHandles { /* Size=0x64 */
    public: 
    SUpdateQueueHandle m_Handles[12];
    unsigned char m_Count;

    public: 
    static const int32_t MAX_UPDATE_HANDLES;
    
    public: 
    SUpdateQueueHandles();
    SUpdateQueueHandle& operator[](int32_t);
};

#endif