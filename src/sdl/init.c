#include "init.h"

//called once before anything else. checks if it runs and returns an error code and quits if it doesn't
//we are initializing in this step
//the appstate pointer is a SDL thing (probably) and allows the application state to be called without need for global variables.
SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv){
    
    AppState* state = SDL_malloc(sizeof(AppState));
    *appstate = state;
    
    //if the initializing fails, returns an error for why it failed.
    if (!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Error initializing SDL: %s" , SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    //initializing window
    state->window = SDL_CreateWindow(
        //title, w, h, flags, are all part of Codium exstension to label arguments.
        "SDL3 Youtube Tutorial Game",
        1280,
        720,
        NULL
    );

    //Error check for window :3 won't add more comments unless they're unique for these
    if (!state->window){
        SDL_Log("Error creating window: %s" , SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    state->renderer = SDL_CreateRenderer(state->window, NULL);
    if (!state->renderer){
        SDL_Log("Error creating renderer: %s" , SDL_GetError());
        return SDL_APP_FAILURE;
    }

    //init_player 
    //the way the rendering works, map is first becuase if player was first it would make the player, then the map, then we
    //wouldn't be able to see the player, they'd be hidden under the map, not drawn on screen.
    init_map(state->renderer);
    init_Player(state->renderer);
    init_camera(state->renderer);

    //scales the game to the necessary resolution
    //320x180 or 640x320 <- resolutions, they scale to the window, so they'll just make things bigger to fit window
    //black bars will appear top and bottom if aspect ratio isn't the same :3
    SDL_SetRenderLogicalPresentation(state->renderer, 320, 180,SDL_LOGICAL_PRESENTATION_LETTERBOX);


    //if everything works, tells app to continue runnign. app fail and app success both close the window
    return SDL_APP_CONTINUE;
}
