#include "render.h"
//rendering screen
void app_render(void *appstate){
    
    //the variable state equals the appstate pointer.   
    AppState* state = (AppState*) appstate;
    SDL_RenderClear(state->renderer);
    SDL_SetRenderDrawColor(state->renderer, 0, 255, 0, 255);
    
    for (int i = 0; i < entities_counnt; i++) {
        if (!entities[i].render) continue;
        entities[i].render(state->renderer);
    }

    SDL_RenderPresent(state->renderer);

}
