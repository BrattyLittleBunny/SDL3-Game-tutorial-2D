#include "entity.h"
Entity entities[MAX_ENTITIES];
int entities_counnt = 0;

//3 functions, create entities, change entities, swap entities

//creating entities (obviously). 
//when passed new entities, it'll add them to the entity array, allowing them to be rendered.
void create_entity(Entity entity){
    if (entities_counnt < MAX_ENTITIES) {
        entities[entities_counnt] = entity;
        entities_counnt++;

    } else {
        SDL_Log("Max entities reached\n");
    }
}

//removing entities from the array then cleaning it up and deleting the data, then overighting it. 
//Index is the index location of the entity you want removed
void delete_entity(int index){
    if (index < 0 || index >= MAX_ENTITIES){
        SDL_Log("Entity Index is not valid, %d", index);
        return;
    }
    //cleaning up, and deleting the entity
    entities[index].cleanup();

    //shifting all the values from the right of the index, left. To overight the value at index.
    for (int i = index; i < MAX_ENTITIES; i++){
        entities[i] = entities[i+1];
    }
    entities_counnt--;
}

//the 2 index's of what we want to swap
//the one being swapped to is index1 and the one that is being swapped with is index2
void swap_entity(int index1, int index2){
    if (index1 < 0 || index1 >= MAX_ENTITIES || index2 < 0 || index2 >= MAX_ENTITIES){
        SDL_Log("Invalid index %d and %d for swapping", index1, index2);
        return;
    }
    //creating a temp copy of the entity
    Entity temp = entities[index1];

    entities[index1] = entities[index2];
    entities[index2] = temp;
}

int get_entity_index(char *name){
    for (int i = 0; i < entities_counnt; i++){
        if (strcmp(entities[i].name, name) == 0) return i;
    }
    //-1 just informs us we didn't get a match
    return -1;
}
