#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "space.h"
#include "game_management.h"

/* Funciones privadas */
STATUS game_load_object(Game* game, char* line);
STATUS game_load_player(Game* game, char* line);
STATUS game_load_space(Game* game, char* line);
STATUS game_load_link(Game* game, char* line);

char protected_files[4][100];

/* @brief Carga los datos del juego desde un archivo 

 * @author Javier Bernardo
 * 
 * @param game Puntero a la estructura del juego.
 * @param spacesFile Nombre del archivo desde donde hay que cargar los espacios
 * @param objectsFile Nombre del archivo desde donde hay que cargar los objetos
 * @param linksfile Nombre del archivo desde donde hay que cargar los links
 * @param playersFile Nombre del archivo desde donde hay que cargar los datos del jugador
 * @return OK si todo ha ido bien. ERROR en caso contrario.
 */
STATUS game_management_start_from_file(Game* game, char* spacesFile, char* objectsFile, char* linksfile, char* playersFile) {
    if(!game || !spacesFile || !objectsFile || !linksfile || !playersFile)
        return ERROR;
    
    strncpy(protected_files[0], spacesFile, 100);
    strncpy(protected_files[1], objectsFile, 100);
    strncpy(protected_files[2], linksfile, 100);
    strncpy(protected_files[3], playersFile, 100);
    
    if (game_management_load(game, playersFile) == ERROR)
        return ERROR;
        
    if (game_management_load(game, linksfile) == ERROR)
        return ERROR;
        
    if (game_management_load(game, spacesFile) == ERROR)
        return ERROR;
    
    if (game_management_load(game, objectsFile) == ERROR)
        return ERROR;
        
    return OK;
}

/** @brief Guarda los datos de la partida con el mismo formato que los ficheros de carga
 * @param game Un puntero al game desde donde se quieren guardar los datos
 * @param filename Archivo donde guardar los datos
 * @return OK si ha guardado correctamente o ERROR en caso contrario
 */
SAVE_STATUS game_management_save(Game* game, char* filename){
    FILE* fp = NULL;
    Space* space = NULL;
    Link* link = NULL;
    Player* player = NULL;
    Object* object = NULL; 
    Id id = NO_ID, north = NO_ID, south = NO_ID, east = NO_ID, west = NO_ID, up = NO_ID, down = NO_ID, open = NO_ID;
    Id space1 = NO_ID, space2 = NO_ID;
    int state = -1, max_objects = 0;
    char graphics[6][24] = {" ", " ", " "};
    Id location = NO_ID;
    char* name = NULL, *description = NULL, *longDescription = NULL, *obj_graphics = NULL;
    BOOL mobile = FALSE, moved = FALSE, hidden = FALSE, illuminates = FALSE, iluminated = FALSE;
    int i;
    if(!game || !filename)
        return BAD_ARGUMENTS;
    
    for(i = 0; i < 4; i++){
        if(strcmp(protected_files[i], filename) == 0)
            return PROTECTED_FILE;
    }
    
    fp = fopen(filename, "w");
    if(fp == NULL)
        return WRITE_FAILED;
    
    /* Guarda el jugador */
    player = game_get_player(game);
    id = player_Get_Id(player);
    name = player_Get_Name(player);
    location = player_Get_Location(player);
    max_objects = player_Get_Max_Objects(player);
    fprintf(fp, "#p:%ld|%s|%ld|%d|\n", id, name, location, max_objects);    
    
    /* Guardar los links */
    for(i=0; (link = game_get_link_at(game, i)) != NULL; i++){
        id = link_get_id(link);
        name = link_get_name(link);
        space1 = link_get_space1(link);
        space2 = link_get_space2(link);
        state = link_get_state(link);
        fprintf(fp, "#l:%ld|%s|%ld|%ld|%d|\n", id, name, space1, space2, state);
    }
    
    /* Guardar datos de los espacios */
    for(i=0; (space = game_get_space_at(game, i)) != NULL; i++){
        id = space_get_id(space);
        name = (char*) space_get_name(space);
        iluminated = space_get_iluminated(space);
        north = space_get_north(space);
        south = space_get_south(space);
        east = space_get_east(space);
        west = space_get_west(space);
        up = space_get_up(space);
        down = space_get_down(space);
        space_get_graphics(space, graphics);
        description = (char*) space_get_description(space);
        longDescription = (char*) space_get_long_description(space);
        fprintf(fp, "#s:%ld|%s|%d|%ld|%ld|%ld|%ld|%ld|%ld|%s@%s@%s@%s@%s@%s@%s|%s|\n", id, name, iluminated, north, east, south, west, up, down,
                                            graphics[0], graphics[1], graphics[2], graphics[3], graphics[4], graphics[5], description, longDescription);
    }
    
    
    /* Guarda los objetos */
    for(i=0; (object = game_get_object_at(game, i)) != NULL; i++){
        id = object_Get_Id(object);
        name = object_Get_Name(object);
        location = game_get_object_location(game, object);
        description = object_Get_Description(object);
        longDescription = object_Get_Description2(object);
        mobile = object_Get_Mobile(object);
        moved = object_Get_Moved(object);
        hidden = object_Get_Hidden(object);
        open = object_Get_Open(object);
        illuminates = object_Get_Illuminates(object);
        iluminated = object_Get_Light(object);
        obj_graphics = object_Get_Graphics(object);
        fprintf(fp, "#o:%ld|%s|%ld|%s|%s|%d|%d|%d|%ld|%d|%d|@@%s", id, name, location, description, longDescription, mobile, moved, hidden, open, illuminates, iluminated, obj_graphics);
    }
    
    fclose(fp);
    
    return SAVE_OK;
}

/* 
 * @brief Carga los datos del juego desde un archivo
 * @param game Un puntero al juego donde cargar los datos
 * @param filename nombre del archivo desde donde cargar los datos
 * @return OK si se ha cargado correctamente o ERROR en caso contrario
 */
STATUS game_management_load(Game* game, char* filename){
    FILE* fp = NULL;
    char line[WORD_SIZE] = "\0";
    STATUS status = UNDEFINED;
    
    if(!(fp = fopen(filename, "r")))
        return ERROR;
    
    while (fgets(line, WORD_SIZE, fp)) {
        if (strncmp("#s:", line, 3) == 0) {
            status = game_load_space(game, line);
        }else if (strncmp("#o:", line, 3) == 0) {
            status = game_load_object(game, line);
        }else if (strncmp("#l:", line, 3) == 0) {
            status = game_load_link(game, line);
        }else if (strncmp("#p:", line, 3) == 0) {
            status = game_load_player(game, line);
        }
        
        if(status == ERROR){
            fclose(fp);
            return ERROR;
        }
    }
    
    fclose(fp);
    return OK;
}

/*
 * @brief Carga los espacio del juego 
 *  
 * @author Mihai Blidaru
 * 
 * @param game Un puntero a la estructura del juego
 * @param line La linea que contiene los datos de la casilla
 * @return ERROR si se ha cargado mal los espacio u OK si se ha cargado bien los espacios.
 */
STATUS game_load_space(Game* game, char* line) {
    char name[WORD_SIZE] = "";
    char description[WORD_SIZE] = "";
    char long_description[WORD_SIZE] = "";
    char graphics[6][24] = {" ", " ", " "};
    BOOL graphics_loaded = TRUE;
    char* toks = NULL;
    int i, aux = 0;
    BOOL iluminated = FALSE;
    Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID, up = NO_ID, down = NO_ID;
    Space* space = NULL;
    STATUS status = OK;
    

    if (!game || !line) {
        return ERROR;
    }

    graphics_loaded = TRUE;
    toks = strtok(line + 3, "|");
    id = atol(toks);
    toks = strtok(NULL, "|");
    strcpy(name, toks);
    toks = strtok(NULL, "|");
    if((aux = atoi(toks)) == 1)
        iluminated = TRUE;
    toks = strtok(NULL, "|");
    north = atol(toks);
    toks = strtok(NULL, "|");
    east = atol(toks);
    toks = strtok(NULL, "|");
    south = atol(toks);
    toks = strtok(NULL, "|");
    west = atol(toks);
    toks = strtok(NULL, "|");
    up = atol(toks);
    toks = strtok(NULL, "|");
    down = atol(toks);
    for (i = 0; i < 6; i++) {
        toks = strtok(NULL, "@");
        if(!toks){
            graphics_loaded = FALSE;
            break;
        }
        strcpy(graphics[i], toks);
    }
        
    if((toks = strtok(NULL, "|")))
        strcpy(description, toks);
    
    if((toks = strtok(NULL, "|")))
        strcpy(long_description, toks); 

#ifdef DEBUG 
    printf("Leido: %ld|%s|%ld|%ld|%ld|%ld|%ld|%ld|\n", id, name, north, east, south, west, up, down);
#endif
        space = space_create(id);
        if (space != NULL) {
            space_set_name(space, name);
            space_set_iluminated(space, iluminated);
            space_set_north(space, north);
            space_set_east(space, east);
            space_set_south(space, south);
            space_set_west(space, west);
            space_set_up(space, up);
            space_set_down(space, down);
            if(graphics_loaded)
                space_set_graphics(space, graphics);
            space_set_description(space, description);
            space_set_long_description(space, long_description);
            if((game_add_space(game, space))==ERROR){
                space_destroy(space);
            }
        }
    return status;
}

/*
 * @brief Carga los objetos del juego
 *  
 * @author Javier Bernardo
 * 
 * @param game Un puntero a la estructura del juego
 * @param line La linea que contiene los datos del objeto
 * @return ERROR si se ha cargado mal u OK si se ha cargado bien los espacios.
 */
STATUS game_load_object(Game* game, char* line) {
    Id id = NO_ID, location = NO_ID, opens = NO_ID;
    char name[WORD_SIZE] = "\0";
    char description1[WORD_SIZE] = "\0";
    char description2[WORD_SIZE] = "\0";
    char graphics[WORD_SIZE];
    char line_copy[WORD_SIZE] = "\0";
    int aux = 0;
    BOOL mobile = FALSE;
    BOOL moved = FALSE;
    BOOL hidden = FALSE;
    BOOL illuminates = FALSE;
    BOOL light_on = FALSE;
    Object* object = NULL;
    Space* space = NULL;
    char* toks = NULL;
    strncpy(line_copy, line, WORD_SIZE);
    toks = strtok(line + 3, "|");
    id = atol(toks);
    toks = strtok(NULL, "|");
    strcpy(name, toks);
    toks = strtok(NULL, "|");
    location = atol(toks);
    toks = strtok(NULL, "|");
    strcpy(description1, toks);
    toks = strtok(NULL, "|");
    strcpy(description2, toks);
    toks = strtok(NULL, "|");
    if((aux = atoi(toks)) == 1) /* Movible*/
        mobile = TRUE;
    aux = 0;
    toks = strtok(NULL, "|");
    if((aux = atoi(toks)) == 1)/* Movido */
        moved = TRUE;
    aux = 0;
    toks = strtok(NULL, "|");
    if((aux = atoi(toks)) == 1)/* Oculto */
        hidden = TRUE;
    toks = strtok(NULL, "|");
    opens = atol(toks); /* Abre*/
    aux = 0;
    toks = strtok(NULL, "|");
    if((aux = atoi(toks)) == 1) /* Ilumina */
        illuminates = TRUE;
    aux = 0;
    toks = strtok(NULL, "|");
    if((aux = atoi(toks)) == 1) /* encendido */
        light_on = TRUE;
    
    
    for(aux = 0; (line_copy[aux] != '@' || line_copy[aux+1] != '@') ; aux++);
    strcpy(graphics, line_copy+aux+2);

#ifdef DEBUG 
        printf("Leido: %ld|%s|%ld|%s|%s|%d|%d|%d|%ld|%d|%d|\n", id, name, location, description1, description2, mobile, moved, hidden, opens, illuminates, light_on);
#endif
    if(!(object = object_create()))
        return ERROR;
    
        
    object_Set_Id(object, id);
    object_Set_Name(object, name);
    object_Set_Description(object, description1);
    object_Set_Description2(object, description2);
    object_Set_Mobile(object, mobile);
    object_Set_Graphics(object, graphics);
    object_Set_Moved(object, moved);
    object_Set_Hidden(object, hidden);
    object_Set_Open(object, opens);
    object_Set_Illuminates(object, illuminates);
    object_Set_Light(object, light_on);
    if(game_add_object(game, object) == ERROR){
        object_destroy(object);
        return ERROR;
    }
    if(location != PLAYER_INV_LOCATION){
        space = game_get_space(game, location);
        space_add_object(space, id);    
    }else{
        player_Add_Object(game_get_player(game), id);        
    }
    
    return OK;
}

/* @brief Carga los enlaces
 *  @author Mihai Blidaru
 *  @param game Un juego
 *  @param line Linea del archivo que contiene los datos del link
 *  
 *  @return OK si ha conseguido cargar correctamente o ERROR en caso contrario.
 */
STATUS game_load_link(Game* game, char* line) {
    char linkName[WORD_SIZE] = "\0";
    Id linkId = NO_ID, state = NO_ID, space1 = NO_ID, space2 = NO_ID;
    char* toks = NULL;
    Link* newLink = NULL;

    if(!game || !line)
        return ERROR;
        
    toks = strtok(line + 3, "|");
    linkId = atol(toks);
    toks = strtok(NULL, "|");
    strcpy(linkName, toks);
    toks = strtok(NULL, "|");
    space1 = atol(toks);
    toks = strtok(NULL, "|");
    space2 = atol(toks);
    toks = strtok(NULL, "|");
    state = atol(toks);
        
#ifdef DEBUG 
    printf("#l:%ld|%s|%ld|%ld|%ld|\n", linkId, linkName, space1, space2, state);
#endif

    if(!(newLink = link_create())){
        return ERROR;
    }
    
    link_set_id(newLink, linkId);
    link_set_name(newLink, linkName);
    link_set_space1(newLink, space1);
    link_set_space2(newLink, space2);
    link_set_state(newLink, state);
    if(game_add_link(game,newLink) == ERROR){
        link_destroy(newLink);
        return ERROR;
    }

    return OK;
}

/* @brief Carga los datos del jugador
*  @author Mihai Blidaru
*  @param game Un juego
*  @param line Linea del archivo que contiene los datos del jugador
*  
*  @return OK si ha conseguido cargar correctamente o ERROR en caso contrario.
*/
STATUS game_load_player(Game* game, char* line){
    char playerName[WORD_SIZE] = "\0";
    Id player_id = NO_ID, location = NO_ID;
    int maxObj = 0;
    char* toks = NULL;
    Player* newPlayer = NULL;
    
    if(!game || !line)
        return ERROR;
    
    toks = strtok(line + 3, "|");
    player_id = atol(toks);
    toks = strtok(NULL, "|");
    strcpy(playerName, toks);
    toks = strtok(NULL, "|");
    location = atol(toks);
    toks = strtok(NULL, "|");
    maxObj = atol(toks);
            
#ifdef DEBUG 
    printf("#p:%ld|%s|%ld|%d|\n", player_id, playerName, location, maxObj);
#endif
    if(!(newPlayer = player_create())){
        return ERROR;
    }
    player_Set_Id(newPlayer, player_id);
    player_Set_Name(newPlayer, playerName);
    player_Set_Location(newPlayer, location);
    player_Set_Max_Objects(newPlayer, maxObj);
    if((game_add_player(game, newPlayer)) == ERROR){
        player_destroy(newPlayer);
        return ERROR;
    }

    return OK;
}