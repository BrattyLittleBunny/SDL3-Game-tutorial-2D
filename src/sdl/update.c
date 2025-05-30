#include "update.h"

//updating state
void app_update(void *appstate){
    
    AppState* state = (AppState*) appstate;

    state->last_tick = state->current_tick;
    state->current_tick = SDL_GetTicks();
    //the /1000 is to turn it into seconds
    state->delta_time = (state->current_tick - state->last_tick) / 1000.0f;

    for (int i = 0; i < entities_counnt; i++) { 
        if (!entities[i].update) continue;
        entities[i].update(state->delta_time);
    }
    
}