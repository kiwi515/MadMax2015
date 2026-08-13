#ifndef ENGINE_VARIANT_H
#define ENGINE_VARIANT_H

enum EVariantType : int32_t { // could be defined elsewhere
    T_VARIANT_UNASSIGNED = 0x0000,
    T_VARIANT_INTEGER = 0x0001,
    T_VARIANT_FLOAT = 0x0002,
    T_VARIANT_STRING = 0x0003,
    T_VARIANT_VEC2 = 0x0004,
    T_VARIANT_VEC3 = 0x0005,
    T_VARIANT_VEC4 = 0x0006,
    T_VARIANT__DO_NOT_USE_1 = 0x0007,
    T_VARIANT_MAT4x4 = 0x0008,
    T_VARIANT_VEC_INTS = 0x0009,
    T_VARIANT_VEC_FLOATS = 0x000a,
    T_VARIANT_VEC_BYTES = 0x000b,
    T_VARIANT__DO_NOT_USE_2 = 0x000c,
    T_VARIANT_OBJECTID = 0x000d,
    T_VARIANT_VEC_EVENTS = 0x000e,
};

template <typename T> 
class TVariant {
    
};

#endif