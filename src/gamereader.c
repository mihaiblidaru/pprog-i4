/** 
 * @brief Este modulo se encarga de cargar los datos del juego. Carga las casillas
 *      los enlaces, los objetos y los datos del jugador.
 * @file gamereader.c
 * @author Javier Bernardo 
 * @author Mihai Blidaru
 * @version 2.2 
 * @date 31-01-2017
 * @copyright GNU Public License
 */

/* Cabeceras Libc */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Cabeceras propias */
#include "game.h"
#include "gamereader.h"
#include "types.h"
#include "space.h"
#include "link.h"


/* @brief Carga los datos del juego desde un archivo e inicializa la posición
 *         inicial del jugador y del objeto
 *  
 * @author Profesores PPROG
 * 
 * @param game Puntero a la estructura del juego.
 * @param spacesFile Nombre del archivo desde donde hay que cargar los espacios
 * @param objectsFile Nombre del archivo desde donde hay que cargar los objetos
 * @param linksfile Nombre del archivo desde donde hay que cargar los links
 * @param playersFile Nombre del archivo desde donde hay que cargar los datos del jugador
 * @return OK si todo ha ido bien. ERROR en caso contrario.
 */
STATUS game_create_from_file(Game* game, char* spacesFile, char* objectsFile, char* linksfile, char* playersFile) {

    if (game_load_links(game, linksfile) == ERROR)
        return ERROR;
        
    if (game_load_spaces(game, spacesFile) == ERROR)
        return ERROR;

    if (game_load_objects(game, objectsFile) == ERROR)
        return ERROR;
    
    if (game_load_players(game, playersFile) == ERROR)
        return ERROR;
        
    return OK;
}

/*
 * @brief Carga los espacio del juego y los objetos de cada espacio
 *  
 * @author Mihai Blidaru
 * 
 * @param game Un puntero a la estructura del juego
 * @param filename El nombre del archivo 
 * @return ERROR si se ha cargado mal los espacio u OK si se ha cargado bien los espacios.
 */
STATUS game_load_spaces(Game* game, char* filename) {
    FILE* file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char description[WORD_SIZE] = "";
    char long_description[WORD_SIZE] = "";
    char graphics[3][8] = {" ", " ", " "};
    BOOL graphics_loaded = TRUE;
    char* toks = NULL;
    int i;
    Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
    Space* space = NULL;
    STATUS status = OK;

    if (!filename) {
        return ERROR;
    }

    file = fopen(filename, "r");
    if (file == NULL) {
        return ERROR;
    }

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#s:", line, 3) == 0) {
            graphics_loaded = TRUE;
            toks = strtok(line + 3, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            north = atol(toks);
            toks = strtok(NULL, "|");
            east = atol(toks);
            toks = strtok(NULL, "|");
            south = atol(toks);
            toks = strtok(NULL, "|");
            west = atol(toks);

            for (i = 0; i < 3; i++) {
                toks = strtok(NULL, "|");
                if(!toks){
                    graphics_loaded = FALSE;
                    break;
                }
                strcpy(graphics[i], toks);
            }
            
            toks = strtok(NULL, "|");
            
            if(toks)
                strcpy(description, toks);
            toks = strtok(NULL, "|");
            
            if(toks)
                strcpy(long_description, toks); 

#ifdef DEBUG 
            printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
            space = space_create(id);
            if (space != NULL) {
                space_set_name(space, name);
                space_set_north(space, north);
                space_set_east(space, east);
                space_set_south(space, south);
                space_set_west(space, west);
                if(graphics_loaded)
                    space_set_graphics(space, graphics);
                space_set_description(space, description);
                space_set_long_description(space, long_description);
                if((game_add_space(game, space))==ERROR){
                    space_destroy(space);
                }
            }
        }
    }

    if (ferror(file)) {
        status = ERROR;
    }

    fclose(file);

    return status;
}

/*
 * @brief Carga los objetos de cada espacio
 *  
 * @author Javier Bernardo
 * 
 * @param game Un puntero a la estructura del juego
 * @param filename El nombre del archivo 
 * @return ERROR si se ha cargado mal los espacio u OK si se ha cargado bien los espacios.
 */
STATUS game_load_objects(Game* game, char* filename) {
    FILE* fp = NULL;
    char line[WORD_SIZE] = "\0";
    char objName[WORD_SIZE] = "\0";
    char objDesc[WORD_SIZE] = "\0";
    Id objId = NO_ID, space_id = NO_ID;
    char* toks = NULL;
    Object* newObj = NULL;
    Space* space;

    if (!(fp = fopen(filename, "r"))) {
        return ERROR;
    }

    while (fgets(line, WORD_SIZE, fp)) {
        if (strncmp("#o:", line, 3) == 0) {
            toks = strtok(line + 3, "|");
            objId = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(objName, toks);
            toks = strtok(NULL, "|");
            space_id = atol(toks);
            toks = strtok(NULL, "|");
            if(toks)
                strcpy(objDesc, toks);
        
#ifdef DEBUG 
            printf("Leido: %ld|%s|\n", objId, objName);
#endif
            newObj = object_create();
            object_Set_Id(newObj, objId);
            object_Set_Name(newObj, objName);
            object_Set_Description(newObj, objDesc);
            if(game_add_object(game, newObj) == ERROR){
                object_destroy(newObj);
                continue;
            }
            space = game_get_space(game, space_id);
            space_add_object(space, objId);
        }
    }

    fclose(fp);
    return OK;
}

/* @brief Carga los enlaces desde un archivo
 *  @author Mihai Blidaru
 *  @param game Un juego
 *  @param filename Nombre del archivo desde el cual se cargan los enlaces
 *  
 *  @return OK si ha conseguido cargar correctamente o ERROR en caso contrario.
 */
STATUS game_load_links(Game* game, char* filename) {
    FILE* fp = NULL;
    char line[WORD_SIZE] = "\0";
    char linkName[WORD_SIZE] = "\0";
    Id linkId = NO_ID, state = NO_ID, space1 = NO_ID, space2 = NO_ID;
    char* toks = NULL;
    Link* newLink = NULL;

    if (!(fp = fopen(filename, "r"))) {
        return ERROR;
    }

    while (fgets(line, WORD_SIZE, fp)) {
        if (strncmp("#l:", line, 3) == 0) {
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
            printf("Leido: %ld|%s|%ld|%ld\n", linkId, linkName, space1, space2);
#endif
            newLink = link_create();
            link_set_id(newLink, linkId);
            link_set_name(newLink, linkName);
            link_set_space1(newLink, space1);
            link_set_space2(newLink, space2);
            link_set_state(newLink, state);
            if(game_add_link(game,newLink) == ERROR){
                link_destroy(newLink);
            }
        }
    }

    fclose(fp);
    return OK;
}

/* @brief Carga los datos del jugador desde un archivo
*  @author Mihai Blidaru
*  @param game Un juego
*  @param filename Nombre del archivo desde el cual se cargan los datos del jugador
*  
*  @return OK si ha conseguido cargar correctamente o ERROR en caso contrario.
*/
STATUS game_load_players(Game* game, char* filename){
    FILE* fp = NULL;
    char line[WORD_SIZE] = "\0";
    char playerName[WORD_SIZE] = "\0";
    Id player_id = NO_ID, location = NO_ID;
    int maxObj = 0;
    char* toks = NULL;
    Player* newPlayer = NULL;

    if (!(fp = fopen(filename, "r"))) {
        return ERROR;
    }

    while (fgets(line, WORD_SIZE, fp)) {
        if (strncmp("#p:", line, 3) == 0) {
            toks = strtok(line + 3, "|");
            player_id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(playerName, toks);
            toks = strtok(NULL, "|");
            location = atol(toks);
            toks = strtok(NULL, "|");
            maxObj = atol(toks);
            
#ifdef DEBUG 
            printf("Leido: %ld|%s|%ld|\n", player_id, playerName, location);
#endif
            if(!(newPlayer = player_create())){
                fclose(fp);
                return ERROR;
            }
            player_Set_Id(newPlayer, player_id);
            player_Set_Name(newPlayer, playerName);
            player_Set_Location(newPlayer, location);
            player_Set_Max_Objects(newPlayer, maxObj);
            game_add_player(game, newPlayer);
        }
    }

    fclose(fp);
    return OK;
}