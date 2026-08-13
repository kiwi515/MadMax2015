#ifndef LIB_SOCKET_HELPER_H
#define LIB_SOCKET_HELPER_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct s_linger {
    public:
    int32_t l_onoff;
    int32_t l_linger;
};

#endif