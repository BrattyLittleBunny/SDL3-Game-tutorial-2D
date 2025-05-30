#include "iterate.h"
//all these defines for settings could be put into a settings structure and just need to reference them. possibly. maybe...
#define TARGET_FPS 60
//how many miliseconds between frames
#define TARGET_FRAME_TIME (1000/TARGET_FPS)

void app_wait_for_next_frame(void *appstate){
    AppState* state = (AppState*) appstate;

    Uint64 frame_time = SDL_GetTicks() - state->current_tick;

    //works but won't give precise results.
    if (frame_time < TARGET_FRAME_TIME) SDL_Delay(TARGET_FRAME_TIME - frame_time);

}

SDL_AppResult SDL_AppIterate(void *appstate){
    app_update(appstate);
    app_render(appstate);
    void app_wait_for_next_frame(void *appstate);
    return SDL_APP_CONTINUE;
}
