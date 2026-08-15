#ifndef PROJECT_GAME_RESTARTPOINT_TYPES_H
#define PROJECT_GAME_RESTARTPOINT_TYPES_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct SRestartPoint {
    struct ArrayOnLoadEvent {
        public: 
        uint64_t* m_Data;
        uint32_t m_Count;
        
        public: 
        uint64_t GetDataSize() const;
        const uint64_t& operator[](uint32_t) const;
        uint64_t& operator[](uint32_t);
        uint32_t GetSize() const;
    };

    struct ArrayGlobalEnableEvent {
        public: 
        uint64_t* m_Data;
        public: uint32_t m_Count;
        
        public: 
        uint64_t GetDataSize() const;
        const uint64_t& operator[](uint32_t) const;
        uint64_t& operator[](uint32_t);
        uint32_t GetSize() const;
    };

    struct ArrayGlobalDisableEvent {
        public: 
        uint64_t* m_Data;
        uint32_t m_Count;
        
        public: 
        uint64_t GetDataSize() const;
        const uint64_t& operator[](uint32_t) const;
        uint64_t& operator[](uint32_t);
        uint32_t GetSize() const;
    };

    public: 
    SRestartPoint::ArrayOnLoadEvent m_OnLoadEvent;
    SRestartPoint::ArrayGlobalEnableEvent m_GlobalEnableEvent;
    SRestartPoint::ArrayGlobalDisableEvent m_GlobalDisableEvent;
    const char* m_Name;
    uint64_t m_ID;
    uint32_t m_NameId;
    float m_Transform[12];
    uint32_t m_Mission;
    uint32_t m_Objective;
    unsigned char m_IconType;
    unsigned char m_OverridePlacement;
    unsigned char m_Enabled;
    unsigned char m_EnabledAtStart;
    unsigned char m_RestartMissionPoint;
    unsigned char m_UseClosestFastTravelPosition;
    unsigned char m_FastTravelOnly;
    unsigned char m_UseAsLatestCheckpoint;
  
    public: void SetDefaultValues();
};

struct SRestartPointCollection {
    struct ArrayRestartPoints {
        public: 
        SRestartPoint* m_Data;
        uint32_t m_Count;
        
        public: 
        uint64_t GetDataSize() const;
        const SRestartPoint& operator[](uint32_t) const;
        SRestartPoint& operator[](uint32_t);
        uint32_t GetSize() const;
    };

    public: 
    SRestartPointCollection::ArrayRestartPoints m_RestartPoints;
    uint32_t m_FastTravelCount;
    uint32_t m_FreeRoamCount;
    uint32_t m_GlobalEventCount;
    
    public: 
    void SetDefaultValues();
};

#endif