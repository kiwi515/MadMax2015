#ifndef PROJECT_GAME_GAME_OBJECT_LIST_MODULE_H
#define PROJECT_GAME_GAME_OBJECT_LIST_MODULE_H

#include "libs/Xvm2/main/source/common/xvm_vm.h"

class CGameObjectListModule {
    public: 
    static SXvmDict* s_Module;
    static SXvmFunctionEntry Functions[0];
    
    public: 
    static void Register(SXvmSharedState*);
    static void UnRegister(SXvmSharedState*);
    static HXvmObject Clear(SXvmState*, HXvmObject);
    static HXvmObject Add(SXvmState*, HXvmObject, HXvmObject);
    static HXvmObject Rem(SXvmState*, HXvmObject, HXvmObject);
    static HXvmObject Get(SXvmState*, HXvmObject, HXvmObject);
    static HXvmObject NbGameObjects(SXvmState*, HXvmObject);
    static HXvmObject HasObject(SXvmState*, HXvmObject, HXvmObject);
};

#endif