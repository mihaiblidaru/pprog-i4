/** 
 * @brief Define el TAD player y los prototipos de las funciones necesarias
 *        para trabajar con este TAD.
 * 
 * @file player.h
 * @author Mihai Blidaru
 * Pareja 7
 * @version 1.0 
 * @date 31-01-2017
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

/* Cabeceras propias */
#include "types.h"
#include "set.h"
#include "inventory.h"

#define PLAYER_INV_LOCATION -65535

/**
 * @brief Definicion de la estructura player
 */
typedef struct _Player Player;

/**
 * @brief Crea un nuevo jugador e inicializa sus campos
 *
 * @return El nuevo jugador
 */
Player* player_create();

/**
 * @brief Destruye un jugador
 *
 * @param player El puntero del jugador.
 * @return Error si se ha hecho mal o Ok si se ha liberado correctamente.
 */
STATUS player_destroy(Player* player);

/**
 * @brief Pone el id del jugador
 *
 * @param player El puntero del jugador.
 * @param player_id Id del jugador
 * @return El jugador
 */
Player* player_Set_Id(Player* player, Id player_id);

/**
 * @brief Pone el nombre del jugador
 *
 * @param player El puntero del jugador.
 * @param name Nombre del jugador
 * @return El jugador
 */
Player* player_Set_Name(Player* player, char* name);

/**
 * @brief Pone la localizacion del jugador
 *
 * @param player El puntero del jugador.
 * @param location La localizacion del jugador
 * @return El jugador
 */
Player* player_Set_Location(Player* player, Id location);

/**
 * @brief Asigna el número maximo de objetos que puede llevar el jugador
 * @author Mihai Blidaru
 * @param player El jugador al que se le quiere cambiar el numero máximo de objetos
 * @param max_objects Número máximo de objetos que puede llevar el jugador
 * @return Devuelve un puntero al jugador si todo ha ido bien o NULL en caso contrario.
 */
Player* player_Set_Max_Objects(Player *player, int max_objects);

/**
 * @brief Obtiene el id del jugador
 *
 * @param player El puntero del jugador.
 * @return El id del jugador
 */
Id player_Get_Id(Player* player);

/**
 * @brief Obtiene el nombre del jugador
 *
 * @param player El puntero del jugador.
 * @return El nombre del jugador
 */
char* player_Get_Name(Player* player);

/**
 * @brief Obtiene la localizacion del jugador
 *
 * @param player El puntero del jugador.
 * @return La localizacion del jugador
 */
Id player_Get_Location(Player* player);

/**
 * @brief Devuelve el número maximo de objetos que puede llevar el jugador
 * @author Sandra Benitez
 * @param player El jugador del que se quiere conocer el numero máximo de objetos
 * @return Devuelve el número máximo de objetos
 */
int player_Get_Max_Objects(Player *player);

/** 
 * @brief Añade un objeto al Inventory del jugador
 * @author Mihai Blidaru
 * @param player El jugador al que se quiere añadir un objeto
 * @param object_id El id del objeto
 * @return OK si se hace bien, ERROR en caso contrario
 */
STATUS player_Add_Object(Player* player, Id object_id);

/** 
 * @brief Borra un objeto del Inventory del jugador
 * @author Mihai Blidaru
 * @param player El jugador al que se quiere quitar un objeto
 * @param object_id El id del objeto
 */
STATUS player_Remove_Object(Player* player, Id object_id);

/**
 * @brief Comprueba si el jugador tiene un objeto determinado
 * @param player El jugador que se quiere comprobar
 * @param object_id El id del objeto
 * @return TRUE si el jugador tiene el objeto o FALSE en caso contrario o ERROR
 */
BOOL player_Has_Object(Player* player, Id object_id);

/**
 * @brief Imprime por pantalla los datos del jugador
 *
 * @param player El puntero del jugador.
 * @return Imprime por pantalla si hay jugador y da ERROR si lo contrario
 */
STATUS player_Print(Player* player);

#endif