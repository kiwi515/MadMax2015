#ifndef COMPONENT_SAVE_CONTEXT_H
#define COMPONENT_SAVE_CONTEXT_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/SaveSystem/DataSaveHandler.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/SaveSystem/SaveBitStorage.h"

class CSaveContext {
    CDataSaveHandler m_DataHandler;
    CSaveBitStorage m_BitStorage;
    uint32_t m_Version;
};

#endif