#pragma once

#include <cstddef>
#include <vector>
#include <raylib.h>

extern size_t ship_start_size;
extern std::vector<std::vector<Texture>> ships;

void load_assets();
