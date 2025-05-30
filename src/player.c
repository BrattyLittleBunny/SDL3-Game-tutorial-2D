#include "player.h"
//making this a define so if i change it it only needs to be changed in 1 spot
#define PLAYERSPEED 30
#define MAPWIDTH 420
#define MAPHEIGHT 240
//static is to keep the things accessable only in this file, to avoid conflicting names.
//declarations for grabing the player.
static SDL_Texture* player_texture;
static SDL_FRect sprite_portion = {17, 14, 15, 18};


//15, 18 is the size on the player rect in the init_payer function
static SpriteSize sprite_size = {15, 18};
Position player_position = {0,0};

static void cleanup(){
    if (player_texture){       
        SDL_DestroyTexture(player_texture);
    }
}

static void handle_events(){


}

//function (limits):
//if (position.y == 0 || position.y == map->height){player no loger moves that way}
//if (position.x == 0 || position.x == map->width){player no loger moves that way}
//maybe later add in if == 0 in map->layer1, no advance. just change map to have a invisible boundary layer
//maybe if layer->name == boundary && data = XX then stop.

static void update(float delta_time){
    const _Bool *keyboard_state = SDL_GetKeyboardState(NULL);

    if (keyboard_state[SDL_SCANCODE_W]){
        player_position.y -= PLAYERSPEED * delta_time;
    }
    if (keyboard_state[SDL_SCANCODE_S]){
        player_position.y += PLAYERSPEED * delta_time;
    }
    if (keyboard_state[SDL_SCANCODE_A]){
        player_position.x -= PLAYERSPEED * delta_time;
    }
    if (keyboard_state[SDL_SCANCODE_D]){
        player_position.x += PLAYERSPEED * delta_time;
    }
    
}

static void render(SDL_Renderer* renderer){
    //final position where the camera will be on the map :3
    //it's centering the camera and player
    float final_x = camera.w / 2 - sprite_size.w / 2;
    float final_y = camera.h / 2 - sprite_size.h / 2; 

    //making boundaries for the camera
    //getting the player position and subtracting half of it's width from that, 
    //without the division the player would snap when at a border and not be smooth.
    if (camera.x <= 0) final_x = player_position.x - sprite_size.w / 2;
    if (camera.y <= 0) final_y = player_position.y - sprite_size.h / 2;

    //making  boundaries for the bottom and right borders (make dynamic)
    //the 420 is arbitruary, it needs to be size of the map
    if (camera.x + camera.w >= MAPWIDTH) final_x = player_position.x - (MAPWIDTH - camera.w) - sprite_size.w / 2;
    if (camera.y + camera.h >= MAPHEIGHT) final_y = player_position.y - (MAPHEIGHT - camera.h) - sprite_size.h / 2;

    //draw our charactar. getting the position and size :3
    SDL_FRect player_rect = {
        final_x, 
        final_y, 
        sprite_size.w, 
        sprite_size.h
    };

    //first arg is the renderer, 2nd texture, 3rd is the source rectangle from the image(needs a pointer), the 4th is destination it'll be put on screen (requires pointer).
    //sdlfrect x, y, width, height
    SDL_RenderTexture(renderer, player_texture, &sprite_portion, &player_rect);
    
}

void init_Player(SDL_Renderer* renderer){
    //making a constant for where the filepath is. and creating a texture for the player, texture's don't require editing or movement.
    const char path[] = "./char_spritesheet.png";
    player_texture = IMG_LoadTexture(renderer, path);

    //was in render, but it only needs to be ran once, so we don't need it to be ran ever time it renders
    SDL_SetTextureScaleMode(player_texture, SDL_SCALEMODE_NEAREST);

    //these are all the function names of the player :D i think...
    Entity player = {
        cleanup,
        handle_events,
        update,
        render,
        "player"
    };
    
    create_entity(player);

}