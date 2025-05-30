//the define was stated as necesary in the source code for cutetile.h
#define CUTE_TILED_IMPLEMENTATION
#include "map.h"

static cute_tiled_map_t* map;
static cute_tiled_layer_t* layer; 
static cute_tiled_tileset_t* tileset;
static Texture* texture;

//need to remember to write a deallocating cleanup while i'm allocating memory. not after i've ran so many tests ;~;
static void cleanup(){
    if (texture){
        Texture* current_texture = texture;
        
        while(current_texture){
            
            Texture* next_texture =  current_texture->next;
            if (current_texture->texture){
                SDL_DestroyTexture(current_texture->texture);
            }
            
            SDL_free(current_texture);
            current_texture = next_texture;
        }
        
        texture = NULL;
    }

    if(map){
        cute_tiled_free_map(map);
        map = NULL;
    }
}

static void render(SDL_Renderer* renderer){
    //making a copy so we don't iterate through the global variable
    cute_tiled_layer_t* temp_layer = layer;
    
    //data is the value for the tile in the map
    while(temp_layer){
        //FOUND THE ERROR!!!!!!!! FORGOT THE FUCKING ! FOR TEMP LAYER. IT WAS CHEKCING IF IT HAD SHIT THEN 
        //CONTINUEING, NOT CONTINUEING WHEN IT HAD NOTHING D: HAD TO FUCKING LOOK AT THE SOURCE CODE FOR LIKE 2 HOURS QQ
        //FUCKING LITERALLY WENT LINE BY SHITTING LINE, CHARACTER BY CHARACTER... okay not that bad. I wrote some sdl logs
        //to print line numbers where i thought the problem was, and when they worked i knew it wasn't the problem. still
        //was hecking annoying D:
        if(!temp_layer->data){
            temp_layer = temp_layer->next;
            continue;
        }

        /*
        what this is saying is that in the array of "data" in map.json, which is being used by cutetile.h
        being referenced at the top of the map init, the height and width variables from teh json are also being used,
        for every [height] ticker it goes [width] in the index of the data field and uses that value as the title ID.
        the titleID, which is the ID to the tile in the tileset (which is obvious, i don't know why i didn't realise), 
        is then used to bring that image into the screen. 
        */
        for(int i = 0; i < map->height; i++){
            for(int j = 0; j < map->width; j++){
                int tile_ID = temp_layer->data[i * map->width + j];
                //0 means it's empty, so we don't want to draw anything
                if(tile_ID == 0) continue;

                Texture* temp_texture = texture;
                Texture* texture_to_use = NULL;

                while(temp_texture){
                    //if tile id's data, is within the TileSets range, it will use it.
                    //this is to figure out what tileset we are drawing from.
                    //if we had more tilesets it would help iterate between them, with one it was just confusing to figure out -_-
                    if(tile_ID >= temp_texture->firstGID &&
                        tile_ID <= temp_texture->firstGID + temp_texture->tileCount -1){
                            texture_to_use = temp_texture;
                            break;
                    }
                    temp_texture = temp_texture->next;

                }
                //if for some reason the texture didn't load, it'll skip it so we don't crash
                if(!texture_to_use)continue;
 
                //determins how wide the columns are :3 so if the tile set width is 30 and tile width is 5 we get 6 collumns :D
                int tileset_collumns = texture_to_use->tileset_Width / map->tilewidth;

                SDL_FRect src_rect = {
                    //the ID data, is the pixel on the sprite map. We are using it, minus the first, to get the relative index value for
                    //that texture on teh map, which gives us the top left pixel number. 
                    //then we mod it with the collumns to know which column it is, then with the width we can get
                    //the x coordinate for teh leftmost coordinate of the sprite
                    //for the height we divide by the columns to figure out what row we're on.
                    //if the tile ID is bigger than the number of columns, we know we're on the next row
                    //then we multiply that by height so we get the height
                    //for the top most coordinate of the sprite
                    //since this is a rectangle, if we combine those we get the top left
                    //then width and height let us know how far to grab :D
                    (tile_ID - texture_to_use->firstGID) % tileset_collumns * map->tilewidth,
                    (tile_ID - texture_to_use->firstGID) / tileset_collumns * map->tileheight,
                    map->tilewidth,
                    map->tileheight
                };
                //just multiplying the index by the widht/height to know where on screen to draw this :D
                SDL_FRect dst_rect = {
                    j * map->tilewidth - camera.x,
                    i * map->tileheight - camera.y,
                    map->tilewidth,
                    map->tileheight

                };

                SDL_RenderTexture(renderer, texture_to_use->texture, &src_rect, &dst_rect);
                
            }

        }
        //iterates the layer for teh while loop :3
        temp_layer = temp_layer->next;
    }
}

void init_map(SDL_Renderer* renderer){
    const char map_path[] = "./Tiled/map.json";
    map = cute_tiled_load_map_from_file(map_path, NULL);

    if (!map){
        SDL_Log("Error loading map");
    }

    layer = map->layers;
    tileset = map->tilesets;

    texture = SDL_malloc(sizeof(Texture));

    Texture* current_texture = texture;
    
    //because tileset is a link list, it always points to the next set, so this should keep going until NULL. :D
    while(tileset){

        //loading the current tileset, usually it would need a string, but can work with object->name.ptr, needed as a work around for 32bit builds. Can be found in the cutetile.h comments
        current_texture->texture = IMG_LoadTexture(renderer, tileset->image.ptr);

        if (!current_texture->texture){
            SDL_Log("Error loading texture for tileset.");
            //might need a change here to iterate to the next texture. like current_texture->texture = current_texture->next
            current_texture = current_texture->next;
            continue;
        }
        //if it reached here the texture loaded successfullly, if it didn't it would've continued the while loop
        SDL_Log("Texture loaded successfully.");
        
        SDL_SetTextureScaleMode(current_texture->texture, SDL_SCALEMODE_NEAREST);
        //copies all the variables from tileset into current texture variable
        current_texture->firstGID = tileset->firstgid;
        current_texture->tileCount = tileset->tilecount;
        current_texture->tileset_Width = tileset->imagewidth;
        current_texture->tileset_Height = tileset->imageheight;

        //moving to next tileset
        tileset = tileset->next;
        
        if(tileset){
            
            current_texture->next = SDL_malloc(sizeof(Texture));
            current_texture = current_texture->next;
        } else {
            current_texture->next = NULL;
        }

    }
    //might need to turn these into functions? we'll see in teh tutorial
    Entity map_e = {
        .render=render,
        .name="map",
        .cleanup=cleanup
    };
 
    create_entity(map_e);
}