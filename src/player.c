/** 
 * @brief Define el TAD player
 * 
 * @file player.c
 * @author Mihai Blidaru
 * Pareja 7
 * @version 1.0 
 * @date 31-01-2017
 * @copyright GNU Public License
 */

/*
 * Cabeceras Libc 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Cabeceras propias 
 */
#include "player.h"
#include "inventory.h"
#include "types.h"
#include "set.h"

/**
 * @brief Estructura del modulo player
 *
 * id : identificador del jugador
 * name: nombre del jugador
 * object: Un conjunto donde se guardan las ids de los objetos que tiene el jugador
 * location: guarda la localización actual del jugador
 */

struct _Player {
    Id id;                  /*!< Id del jugador */
    char name[WORD_SIZE];   /*!< Nombre del jugador */
    Inventory* objects;     /*!< Inventario del jugador */
    Id location;            /*!< Localizacion del jugador */
};

/*
 * @brief Crea un nuevo jugador e inicializa sus campos
 *
 * @return El nuevo jugador
 */
Player* player_create() {
    Player* newPlayer = NULL;

    if (!(newPlayer = (Player*) calloc(1, sizeof (Player))))
        return NULL;

    if (!(newPlayer->objects = inventory_create())) {
        free(newPlayer);
        return NULL;
    }
    
    newPlayer->id = NO_ID;
    newPlayer->location = NO_ID;
    inventory_set_max(newPlayer->objects, 0);

    return newPlayer;
}

/*
 * @brief Destruye un jugador
 *
 * @param player El puntero del jugador.
 * @return Error si se ha hecho mal o Ok si se ha liberado correctamente.
 */
STATUS player_destroy(Player* player) {
    if (!player)
        return ERROR;
    inventory_destroy(player->objects);
    free(player);
    return OK;
}

/*
 * @brief Pone el id del jugador
 *
 * @param player El puntero del jugador.
 * @param player_id Id del jugador
 * @return El jugador
 */
Player* player_Set_Id(Player* player, Id player_id) {
    if (!player || player_id == NO_ID) {
        return NULL;
    }

    player->id = player_id;
    return player;
}

/*
 * @brief Pone el nombre del jugador
 *
 * @param player El puntero del jugador.
 * @param name Nombre del jugador
 * @return El jugador
 */
Player* player_Set_Name(Player* player, char* name) {
    if (!player || !name) {
        return NULL;
    }

    strncpy(player->name, name, WORD_SIZE);
    return player;

}

/*
 * @brief Pone la localizacion del jugador
 *
 * @param player El puntero del jugador.
 * @param location La localizacion del jugador
 * @return El jugador
 */
Player* player_Set_Location(Player* player, Id location) {
    if (!player || location == NO_ID) {
        return NULL;
    }
    player->location = location;
    return player;
}

/*
 * @brief Asigna el número maximo de objetos que puede llevar el jugador
 * @author Mihai Blidaru
 * @param player El jugador al que se le quiere cambiar el numero máximo de objetos
 * @param max_objects Número máximo de objetos que puede llevar el jugador
 * @return Devuelve un puntero al jugador si todo ha ido bien o NULL en caso contrario.
 */
Player* player_Set_Max_Objects(Player *player, int max_objects){
    if (!player || max_objects < 1 || max_objects > MAX_SET)
        return NULL;
    if(!inventory_set_max(player->objects, max_objects))
        return NULL;
    return player;
}

/*
 * @brief Obtiene el id del jugador
 *
 * @param player El puntero del jugador.
 * @return El id del jugador
 */
Id player_Get_Id(Player* player) {
    if (!player) {
        return NO_ID;
    }
    
    return player->id;
}

/*
 * @brief Obtiene el nombre del jugador
 *
 * @param player El puntero del jugador.
 * @return El nombre del jugador
 */
char* player_Get_Name(Player* player) {
    if (!player) {
        return NULL;
    }
    
    return player->name;
}

/*
 * @brief Obtiene la localizacion del jugador
 *
 * @param player El puntero del jugador.
 * @return La localizacion del jugador
 */
Id player_Get_Location(Player* player) {
    if (!player) {
        return NO_ID;
    }
    return player->location;
}

/*
 * @brief Devuelve el número maximo de objetos que puede llevar el jugador
 * @author Sandra Benitez
 * @param player El jugador del que se quiere conocer el numero máximo de objetos
 * @return Devuelve el número máximo de objetos
 */
int player_Get_Max_Objects(Player *player){
    if (player && player->objects)
        return inventory_get_max(player->objects);
    
    return 0;
}   
    

/*
 * @brief Añade un objeto al Inventory del jugador
 * @author Mihai Blidaru
 * @param player El jugador al que se quiere añadir un objeto
 * @param object_id El id del objeto
 * @return OK si se hace bien, ERROR en caso contrario
 */
STATUS player_Add_Object(Player* player, Id object_id) {
    if (!player || object_id == NO_ID)
        return ERROR;

    if (inventory_add_object(player->objects, object_id) == ERROR)
        return ERROR;
    
    return OK;

}

/* 
 * @brief Borra un objeto del Inventory del jugador
 * @author Mihai Blidaru
 * @param player El jugador al que se quiere quitar un objeto
 * @param object_id El id del objeto
 */
STATUS player_Remove_Object(Player* player, Id object_id) {
    if (!player || object_id == NO_ID)
        return ERROR;

    if (inventory_remove_object(player->objects, object_id) == ERROR)
        return ERROR;

    return OK;

}

/*
 * @brief Comprueba si el jugador tiene un objeto determinado
 * @param player El jugador que se quiere comprobar
 * @param object_id El id del objeto
 * @return TRUE si el jugador tiene el objeto o FALSE en caso contrario o ERROR
 */
BOOL player_Has_Object(Player* player, Id object_id) {
    Set* set = NULL;
    if (!player || object_id == NO_ID)
        return FALSE;
        
    set = inventory_get_set(player->objects);
    return set_Id_is_in(set, object_id);
}

/*
 * @brief Imprime por pantalla los datos del jugador
 *
 * @param player El puntero del jugador.
 * @return Imprime por pantalla si hay jugador y da ERROR si lo contrario
 */
STATUS player_Print(Player* player) {
    int printedChars = 0;
    if (!player)
        return ERROR;

    printedChars += printf("Player Id: %ld, Player name: %s, Player location %ld, Player Objects: \n", player->id, player->name, player->location);
    
    inventory_print(stdout, player->objects);

    if (printedChars > 0)
        return OK;
    else
        return ERROR;
}