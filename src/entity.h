//makes sure this header is only defined once to prevent compilation issues
#pragma once
#include <SDL3/SDL.h>
#include <string.h>
#define MAX_ENTITIES 100
//WHATEVER VALUE YOU want. Zen did 64, i think it should be less, due to each 1 being another byte
//apparentyl more than 64 breaks the program :I
#define MAX_NAME_LENGTH 64

//cleanup, handle events, update, render
//does not need a name because the alias defaults to itself and it isn't self referentiating
typedef struct{
    void (*cleanup)(void);
    void (*handle_events)(SDL_Event*);
    void (*update)(float);
    
    //sdl_renderer is the renderer (kinda obvious now :3)
    void (*render)(SDL_Renderer*);
    //using name to identify the Entity even if it switches positions
    char name[MAX_NAME_LENGTH];

} Entity;

extern Entity entities[MAX_ENTITIES];
extern int entities_counnt;
void create_entity(Entity entity);
void delete_entity(int index);
void swap_entity(int index1, int index2);
int get_entity_index(char *name);