#ifndef PROJECT_GAME_GAME_GUI_H
#define PROJECT_GAME_GAME_GUI_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct SGameGuiAmmoPickup {
    int32_t m_WeaponId;
    int32_t m_Change;
    int32_t m_Total;
};

#endif