#include "camera.h"

//initial camera position with width and height
//width and height can be found in the  SDL_SetRenderLogicalPresentation in init.c
Camera camera = {0, 0, 320, 180};

static void update(float delta_time){
    camera.x = player_position.x - camera.w / 2;
    camera.y = player_position.y - camera.h / 2;

    if (camera.x <= 0) camera.x = 0;
    if (camera.y <= 0) camera.y = 0;
    
    //420 is the arbitrary border, so 420 - camera w/h will give top left pixel to place camera :D
    if (camera.x + camera.w >= 420) camera.x = 420 - camera.w;
    if (camera.y + camera.h >= 240) camera.y = 240 - camera.h;
}

void init_camera(SDL_Renderer* renderer){
    Entity camera = {
        .update = update,
        .name = "camera"
    };

    create_entity(camera);
}