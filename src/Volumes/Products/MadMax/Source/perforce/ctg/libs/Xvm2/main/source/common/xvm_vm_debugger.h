#ifndef LIB_XVM_VM_DEBUGGER_H
#define LIB_XVM_VM_DEBUGGER_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct SXvmBreakpoint { // not defined in resym
  uint32_t m_ModuleHash;
  uint32_t m_FunctionHash;
  uint32_t m_PC;
  uint32_t m_SourceLineNumber ;
  uint32_t m_Id;
};

#endif