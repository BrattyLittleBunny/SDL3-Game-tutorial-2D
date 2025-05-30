#pragma once
#include "entity.h"
#include "player.h"
//#include <SDL3/SDL.h>
//#include "common.h"


//x position, y position, width, height
typedef struct {
    float x, y, w, h;
} Camera;

extern Camera camera;
void init_camera(SDL_Renderer* renderer);