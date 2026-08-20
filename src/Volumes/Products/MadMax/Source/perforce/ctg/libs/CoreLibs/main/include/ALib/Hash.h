#ifndef CORELIBS_ALIB_HASH_H
#define CORELIBS_ALIB_HASH_H

#include "Platform/Types.h"

uint32_t HashBuffer(const void* key, size_t length, uint32_t initval);
uint32_t HashString(const char* str);
uint32_t GetFastHash(const char* str);

uint64_t HashBuffer64(const void* data, size_t length, unsigned int seed);
uint64_t HashString64(const char* str);

#endif
