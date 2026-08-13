#ifndef LIB_XVM_H
#define LIB_XVM_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "libs/Xvm2/main/build/Win64/Final/common/adftypes/xvm_adf.h"
#include "libs/Xvm2/main/source/common/xvm_vm.h"

struct HXvmObject {
    public: 
    uint64_t m_Flags;
    uint64_t m_Value;
    
    public: 
    HXvmObject(const HXvmObject&);
    HXvmObject(uint64_t, uint64_t);
    HXvmObject();
    const HXvmObject& operator=(const HXvmObject&);
    bool operator==(const HXvmObject&) const;
    bool operator!=(const HXvmObject&) const;
};

struct SXvmBacktraceEntry {
    public: 
    char m_ModuleName[60];
    uint32_t m_Line;
    char m_FunctionName[60];
    uint32_t m_Col;

    public: 
    static const uint32_t MAX_CHARS;
};

struct SXvmBacktrace {
    public:
    SXvmBacktraceEntry* m_Entries;
    uint32_t m_Capacity;
    uint32_t m_Depth;
};

struct SXvmCallStat {
    public: 
    uint64_t m_HeapSize;
    uint64_t m_HeapUsage;
};

enum EXvmException : int32_t {
    E_XVM_EXCEPTION_NO_EXCEPTION = 0x0000,
    E_XVM_EXCEPTION_TYPE_NOT_FOUND = 0x0001,
    E_XVM_EXCEPTION_ATTRIBUTE_NOT_FOUND = 0x0002,
    E_XVM_EXCEPTION_CFUNCTION_NOT_FOUND = 0x0003,
    E_XVM_EXCEPTION_FUNCTION_NOT_FOUND = 0x0004,
    E_XVM_EXCEPTION_OUT_OF_MEMORY = 0x0005,
    E_XVM_EXCEPTION_OUT_OF_STRUCT_FIELDS = 0x0006,
    E_XVM_EXCEPTION_STACK_OVERFLOW = 0x0007,
    E_XVM_EXCEPTION_ARG_COUNT_MISMATCH = 0x0008,
    E_XVM_EXCEPTION_ARG_TYPE_MISMATCH = 0x0009,
    E_XVM_EXCEPTION_STACK_UNDERFLOW = 0x000a,
    E_XVM_EXCEPTION_GLOBAL_NOT_FOUND = 0x000b,
    E_XVM_EXCEPTION_INDEX_OUT_OF_RANGE = 0x000c,
    E_XVM_EXCEPTION_TYPE_MISMATCH = 0x000d,
    E_XVM_EXCEPTION_VOID_FUNCTION_DIDNOT_RETURN_NONE = 0x000e,
    E_XVM_EXCEPTION_TYPE_ERROR = 0x000f,
    E_XVM_EXCEPTION_ASSERTION_ERROR = 0x0010,
    E_XVM_EXCEPTION_INVALID_OPERATION = 0x0011,
    E_XVM_EXCEPTION_UNINITIALISED_VARIABLE = 0x0012,
    E_XVM_EXCEPTION_TOO_MUCH_PERSISTENT_DATA = 0x0013,
    E_XVM_EXCEPTION_TOO_MANY_PERSISTENT_VARIABLES = 0x0014,
    E_XVM_EXCEPTION_TYPE_IS_READONLY = 0x0015,
    E_XVM_EXCEPTION_WRAPPED_VALUE_MUST_NOT_BE_ZERO = 0x0016,
    E_XVM_EXCEPTION_MAX = 0x00ff,
};

struct SXvmExceptionInfo {
  public: 
  uint32_t m_LineNumber;
  uint32_t m_ColumnNumber;
  EXvmException m_Exception;
  uint32_t m_ArgumentCount;
  uint32_t m_ExpectedTypeSig;
  uint32_t m_GivenTypeSig;
  SXvmBacktrace m_Backtrace;
  char m_String[64];

  public: 
  static const uint32_t MAX_CHARACTERS_IN_STRING;
};

struct SXvmFunctionEntry {
    public: 
    void* m_Function;
    uint32_t m_NameHash;
    const char* m_Name;
    uint32_t m_TypeSig;
    unsigned char m_NArgs;
    unsigned char m_NRet;
};

struct SXvmNewLoaderParams {
    public: 
    void* (* m_MemoryAlloc)(void*, uint64_t, uint32_t);
    void (* m_MemoryFree)(void*, void*);
    void* m_MemoryContext;
    int32_t m_Reserved[5];
    
    public: 
    SXvmNewLoaderParams();
};

struct SXvmNewPersistentDictParams {
    public: 
    uint32_t m_VariableCount;
    uint32_t m_Size;
    void* (* m_MemoryAlloc)(void*, uint64_t, uint32_t);
    void (* m_MemoryFree)(void*, void*);
    void* m_MemoryContext;
    
    public: 
    SXvmNewPersistentDictParams();
};

struct SXvmNewSharedStateParams {
    public: 
    uint32_t m_Flags;
    uint32_t m_MaxGlobals;
    void* (* m_MemoryAlloc)(void*, uint64_t, uint32_t);
    void (* m_MemoryFree)(void*, void*);
    void* m_MemoryContext;
    uint64_t m_Reserved[8];
    
    public: 
    SXvmNewSharedStateParams();
};

struct SXvmNewStateParams {
    public: 
    uint32_t m_HeapSize;
    uint32_t m_Flags;
    uint16_t m_StackSize;
    void* (* m_MemoryAlloc)(void*, uint64_t, uint32_t);
    void (* m_MemoryFree)(void*, void*);
    void* m_MemoryContext;
    SXvmBacktrace m_Backtrace;
    uint64_t m_Reserved[6];
    
    public: 
    SXvmNewStateParams();
};

struct SXvmPersistentDictStats {
    public: 
    uint64_t m_Variables;
    uint64_t m_UsedVariables;
    uint64_t m_Storage;
    uint64_t m_UsedStorage;
};

struct SXvmStructType {
    public: 
    uint32_t m_NameHash;
    void (* m_SetAttr)(SXvmState*, void*, void*, const char*, uint32_t, HXvmObject);
    HXvmObject (* m_GetAttr)(SXvmState*, void*, void*, const char*, uint32_t);
    void* (* m_NewStruct)(SXvmState*, void*, void*, const HXvmObject*, uint32_t);
    const char* m_Name;
};

#endif