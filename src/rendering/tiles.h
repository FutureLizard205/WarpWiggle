#pragma once

#include <stdbool.h>
#include "../sdlInclude.h"

#include "../globalStructs.h"
#include "renderer.h"


#include <stdio.h>
void drawMapTiles(appData_t *app, textures_t *textures, mapData_t *mapData, uint_fast16_t hOffset, uint_fast16_t vOffset);
