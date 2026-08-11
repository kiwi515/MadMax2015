#ifndef LIB_ARRAY_H
#define LIB_ARRAY_H

template <typename T>
class TArray {
    T** m_Begin;
    T** m_End;
    T** m_Last;
    uint16_t m_UserAllocated : 1;
};

#endif