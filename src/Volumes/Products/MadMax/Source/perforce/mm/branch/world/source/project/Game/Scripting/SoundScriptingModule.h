#ifndef PROJECT_GAME_SOUND_SCRIPTING_MODULE_H
#define PROJECT_GAME_SOUND_SCRIPTING_MODULE_H

#include "ctg/libs/Xvm2/main/source/common/xvm_vm.h"

class CSoundScriptingModule {
    public: 
    static SXvmDict* s_Module;
    static SXvmFunctionEntry s_Functions[0];
    
    public: 
    static void Register(SXvmSharedState*);
    static void UnRegister(SXvmSharedState*);
    static HXvmObject Set(SXvmState*, HXvmObject, HXvmObject);
    static HXvmObject SetIntegers(SXvmState*, HXvmObject, HXvmObject, HXvmObject, HXvmObject, HXvmObject, HXvmObject);
    static HXvmObject SetFloats(SXvmState*, HXvmObject, HXvmObject, HXvmObject, HXvmObject, HXvmObject, HXvmObject);
    static HXvmObject SetString(SXvmState*, HXvmObject, HXvmObject, HXvmObject);
    static HXvmObject SetHash(SXvmState*, HXvmObject, HXvmObject, HXvmObject);
    static HXvmObject SetVariableInteger(SXvmState*, HXvmObject, HXvmObject, HXvmObject, HXvmObject);
    static HXvmObject SetVariableFloat(SXvmState*, HXvmObject, HXvmObject, HXvmObject, HXvmObject);
    static HXvmObject SetVariableString(SXvmState*, HXvmObject, HXvmObject, HXvmObject, HXvmObject);
    static HXvmObject SetVariableHash(SXvmState*, HXvmObject, HXvmObject, HXvmObject, HXvmObject);
    static HXvmObject SetRouterVariableInteger(SXvmState*, HXvmObject, HXvmObject, HXvmObject, HXvmObject, HXvmObject, HXvmObject);
    static HXvmObject SetRouterVariableFloat(SXvmState*, HXvmObject, HXvmObject, HXvmObject, HXvmObject, HXvmObject, HXvmObject);
    static HXvmObject SetRouterVariableString(SXvmState*, HXvmObject, HXvmObject, HXvmObject, HXvmObject, HXvmObject, HXvmObject);
    static HXvmObject SetRouterVariableHash(SXvmState*, HXvmObject, HXvmObject, HXvmObject, HXvmObject, HXvmObject, HXvmObject);
    static HXvmObject GetInteger(SXvmState*, HXvmObject, HXvmObject);
    static HXvmObject GetFloat(SXvmState*, HXvmObject, HXvmObject);
    static HXvmObject GetHash(SXvmState*, HXvmObject, HXvmObject);
    static HXvmObject GetVariableInteger(SXvmState*, HXvmObject, HXvmObject, HXvmObject);
    static HXvmObject GetVariableFloat(SXvmState*, HXvmObject, HXvmObject, HXvmObject);
    static HXvmObject GetVariableHash(SXvmState*, HXvmObject, HXvmObject, HXvmObject);
};

#endif