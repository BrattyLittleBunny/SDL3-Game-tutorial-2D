#pragma once

#include "entity.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "camera.h"

typedef struct{
    float x, y;

} Position;

typedef struct{
    float w, h;

} SpriteSize;

extern Position player_position;

void init_Player(SDL_Renderer* renderer);