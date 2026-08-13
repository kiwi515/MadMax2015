#ifndef LIB_XVM_VM_H
#define LIB_XVM_VM_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "libs/Xvm2/main/include/Xvm/xvm.h"

struct SXvmDict {
    public: 
    uint32_t m_NameHash;
    const char* m_Name;
    SXvmVariable* m_Variables;
    uint32_t m_VariablesCount;
    uint32_t m_VariablesCapacity;
    uint32_t m_PatchOffset;
    SXvmStructInstance m_ThisInstance;
};

struct SXvmFrameSave {
    public: 
    HXvmObject* m_SaveFp;
    SXvmFormatFunction* m_SaveFunction;
    uint32_t m_SavePC;
    uint32_t pad[3];
};

struct SXvmPersistentDictPtrs {
    public: 
    SXvmPersistentDict* m_Ptr;
    SXvmPersistentDict* m_PtrEA;
};

struct SXvmPersistentDict {
    public: 
    uint64_t m_Count;
    uint64_t m_MaxCount;
    uint64_t m_Size;
    uint64_t m_Offset;
    void* m_MemoryArea;
    SXvmVariable* m_LocalTable;
    SXvmPersistentDictPtrs m_NextDict;
    void* m_ThisEA;
    void* m_MemoryAreaEA;
    SXvmVariable* m_LocalTableEA;
    void* (* m_MemoryAlloc)(void*, uint64_t, uint32_t);
    void (* m_MemoryFree)(void*, void*);
    void* m_MemoryCtx;
};

struct SXvmSharedState {
    public: 
    void* (* m_MemoryAlloc)(void*, uint64_t, uint32_t);
    void (* m_MemoryFree)(void*, void*);
    void* m_MemoryContext;
    SXvmDict* m_Builtins;
    SXvmDict* m_Random;
    SXvmStructType* m_ModuleType;
    SXvmStructType* m_CModuleType;
    SXvmStructType* m_Vector4Type;
    SXvmStructType* m_Matrix4Type;
    SXvmStructType* m_PersistentType;
    SXvmDict m_Globals;
    bool m_GlobalsDirty;
    bool m_EnablePrintOutput;
};

struct SXvmState {
    public: 
    SXvmSharedState* m_SharedState;
    void* (* m_MemoryAlloc)(void*, uint64_t, uint32_t);
    void (* m_MemoryFree)(void*, void*);
    void* m_MemoryContext;
    uint64_t m_HeapStart;
    uint64_t m_HeapCurrent;
    SXvmCallStat m_CallStat;
    uint32_t m_Flags;
    HXvmObject* m_Stack;
    uint16_t m_StackSize;
    uint16_t m_StackTop;
    uint32_t m_Seed;
    uint64_t m_XvmRaiseException;
    _SETJMP_FLOAT128 m_JmpBuf[16];
    void* m_UserContext;
    uint32_t m_CurrentPC;
    SXvmFormatFunction* m_CurrentFunction;
    HXvmObject* m_CurrentFrame;
    SXvmFrameSave* m_FrameSave;
    SXvmExceptionInfo m_ExceptionInfo;
    HXvmObject m_ReturnValue;
    void* m_Debugger;
    SXvmPersistentDictPtrs m_NextDict;
    SXvmBacktrace m_Backtrace;
    
    public: 
    SXvmState(const SXvmState&);
    SXvmState();
    SXvmState& operator=(const SXvmState&);
};

struct SXvmStructInstance {
    public: 
    void* m_Instance;
    SXvmStructType* m_Type;
};

struct SXvmVariable {
    public: 
    HXvmObject m_Value;
    uint32_t m_NameHash;
    const char* m_Name;
  
    public: 
    SXvmVariable(const SXvmVariable&);
    SXvmVariable(uint32_t, const char*, HXvmObject);
    SXvmVariable& operator=(const SXvmVariable&);
};

#endif