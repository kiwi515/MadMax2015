#ifndef PROJECT_GAME_MISSION_TYPES_H
#define PROJECT_GAME_MISSION_TYPES_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct SMissionObjective {
    public: 
    uint32_t m_EventHash[6];
    const char* m_IDString;
    uint32_t m_ID;
    uint32_t m_LocalizationKey;
    unsigned char m_ObjectiveIndex;
    unsigned char m_Activated;
    unsigned char m_Completed;
    unsigned char m_GameProgression;
    
    public: 
    void SetDefaultValues();
};

struct SMissionData {
    struct ArrayDependencies {
        public: 
        uint32_t* m_Data;
        uint32_t m_Count;
        
        public: 
        uint64_t GetDataSize() const;
        const uint32_t& operator[](uint32_t) const;
        uint32_t& operator[](uint32_t);
        uint32_t GetSize() const;
    };

    struct ArrayMissionLocationEvents {
        public: 
        uint32_t* m_Data;
        uint32_t m_Count;
        
        public: 
        uint64_t GetDataSize() const;
        const uint32_t& operator[](uint32_t) const;
        uint32_t& operator[](uint32_t);
        uint32_t GetSize() const;
    };

    struct ArrayObjectives {
        public: 
        SMissionObjective* m_Data;
        uint32_t m_Count;
        
        public: 
        uint64_t GetDataSize() const;
        const SMissionObjective& operator[](uint32_t) const;
        SMissionObjective& operator[](uint32_t);
        uint32_t GetSize() const;
    };

    public: 
    SMissionData::ArrayObjectives m_Objectives;
    SMissionData::ArrayMissionLocationEvents m_MissionLocationEvents;
    uint32_t m_MissionEvents[10];
    SMissionData::ArrayDependencies m_Dependencies;
    const char* m_IDString;
    const char* m_LoadingTag;
    uint32_t m_ID;
    uint32_t m_LocalizationKey;
    uint32_t m_ParentEvent;
    unsigned char m_MissionType;
    unsigned char m_ResourceStatusFlags;
    unsigned char m_Locked;
    unsigned char m_Activated;
    unsigned char m_Completed;
    unsigned char m_LockedAtStart;
    unsigned char m_ParentEventReceived;
    uint32_t m_RestartPointNameID;
    unsigned char m_Abandonable;

    public: 
    void SetDefaultValues();
};

struct ArrayMissions {
    public: 
    SMissionData* m_Data;
    uint32_t m_Count;
    
    public: 
    uint64_t GetDataSize() const;
    const SMissionData& operator[](uint32_t) const;
    SMissionData& operator[](uint32_t);
    uint32_t GetSize() const;
};

struct SMissionCollection {
    struct ArrayMissions {
        public: 
        SMissionData* m_Data;
        uint32_t m_Count;
        
        public: 
        uint64_t GetDataSize() const;
        const SMissionData& operator[](uint32_t) const;
        SMissionData& operator[](uint32_t);
        uint32_t GetSize() const;
    };
    
    public: 
    SMissionCollection::ArrayMissions m_Missions;
    const char* m_MissionScript;
    const char* m_LocationName;
    uint32_t m_MissionScriptHash;
    
    public: 
    void SetDefaultValues();
};

#endif