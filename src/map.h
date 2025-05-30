#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "entity.h"
//what cute tiled does is help translate the map json into pixels on the screen (i think)
#include "external/cute_tiled.h"
#include "camera.h"

//probably needs to add a name before the brackets. Texture would make it work. It's because it's self referencing without a name.
//Won't work right now, will keep as is until can see if it should work in teh tutorial (I WAS RIGHT!!! I'M SO HECKING AMAZING AT EVERYTHING I DO!!!!)
//i believe this is for the tileset that is used use for the textures
typedef struct Texture{
    SDL_Texture* texture;
    int firstGID;
    int tileCount;
    int tileset_Width;
    int tileset_Height;
    struct Texture* next;
    
} Texture;

void init_map(SDL_Renderer* renderer);