#ifndef COMPONENT_GLOBAL_DICTIONARY_H
#define COMPONENT_GLOBAL_DICTIONARY_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace NGlobalDictionary {
    enum EGlobalDictionaryError : int32_t {
        EGLOBALDICTIONARY_OK = 0x0000,
        EGLOBALDICTIONARY_ALREADY_EXISTS = 0x0001,
        EGLBOALDICTIONARY_NOT_FOUND = 0x0002,
        EGLOBALDICTIONARY_TYPE_MISMATCH = 0x0003,
    };

    bool Exists(const uint32_t name_hash);

    template <typename T>
    NGlobalDictionary::EGlobalDictionaryError Get(const uint32_t name_hash, T& out_value);

    template <typename T>
    NGlobalDictionary::EGlobalDictionaryError Update(const uint32_t name_hash, const T& out_value);

    template <typename T>
    NGlobalDictionary::EGlobalDictionaryError Put(const uint32_t name_hash, const T& out_value);
};

#endif