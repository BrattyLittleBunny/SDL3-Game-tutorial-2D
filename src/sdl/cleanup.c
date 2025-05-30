#include "common.h"

//will check the appresult for failure, if it is, then it quits
void SDL_AppQuit(void *appstate, SDL_AppResult result){

    AppState* state = (AppState*) appstate;

    for (int i = 0; i < entities_counnt; i++) {
        //if there's no cleanup function in the entity, just continue, don't crash.
        if (!entities[i].cleanup) continue;
        entities[i].cleanup();
    }
    SDL_DestroyRenderer(state->renderer);
    state->renderer = NULL;
    SDL_DestroyWindow(state->window);
    state->window = NULL;
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}