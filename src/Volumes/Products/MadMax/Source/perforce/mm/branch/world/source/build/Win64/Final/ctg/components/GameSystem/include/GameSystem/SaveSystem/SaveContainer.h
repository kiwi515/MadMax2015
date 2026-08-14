#ifndef COMPONENT_SAVE_CONTAINER_H
#define COMPONENT_SAVE_CONTAINER_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class CSaveContainer {
    enum EAccessMode : int32_t {
        E_NONE = 0x0000,
        E_WRITE = 0x0001,
        E_READ = 0x0002,
    };

    struct SContainerHeader {

    };

    struct SSlotInfo {

    };

    struct STOCEntry {

    };

    private: 
    unsigned char* m_Buffer;
    uint64_t m_BufferSize;
    uint64_t m_BufferOffset;
    CSaveContainer::SContainerHeader* m_Header;
    CSaveContainer::STOCEntry* m_CurrentTOCEntry;
    uint64_t m_CurrentSlotIndex;
    unsigned char m_Mode;
    bool m_OwnMemory;
    bool m_BrokenData;
    
    public: 
    CSaveContainer(uint64_t);
    CSaveContainer(void*, uint64_t);

    private: 
    CSaveContainer();

    public: 
    ~CSaveContainer();
    uint32_t GetVersion() const;
    bool BeginContainer(CSaveContainer::EAccessMode);
    uint64_t EndContainer(bool);
    void BeginSegment(uint64_t);
    void EndSegment();
    bool GetSegment(const uint64_t) const;
    void* AllocateRAWData(uint64_t, uint64_t);
    const void* GetAllocatedRAWDataPtr(uint64_t, uint64_t&) const;
    uint64_t SetContainerData(const unsigned char*);
    uint64_t GetContainerData(unsigned char*, uint64_t);
    uint64_t GetContainerDataSize() const;
    CSaveContainer::EAccessMode GetAccessMode() const;

    private: 
    void CreateSortedTOCArray();
    bool CheckSpace(uint64_t);
    void WriteSlotInfo(const CSaveContainer::SSlotInfo&);
    uint64_t ReadSlotInfo(CSaveContainer::SSlotInfo&) const;
    void WriteRAWData(uint64_t, const void*, uint64_t);
    bool ReadRAWData(uint64_t, void*, uint64_t) const;

    public: 
    void* __vecDelDtor(uint32_t);
    
    public: 
    static bool IsValidContainer(void*);    
};

#endif