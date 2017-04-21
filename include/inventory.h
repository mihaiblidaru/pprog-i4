/** 
 * @brief Define la interfaz pública del TAD Inventory
 * 
 * @file inventory.h
 * @author Sandra Benítez y Laura Bernal
 * @version 1.0 
 * @date 14-03-2017
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "set.h"
#include "types.h"

/**
 * @brief Definicion de la estructura del inventario
 */
typedef  struct _Inventory Inventory;

/**
 * @brief Crea el inventario e inicializa sus campos
 * @author Laura Bernal y Sandra Benitez
 * 
 * @return Puntero a inventory
 */
Inventory* inventory_create();

/**
 * @brief Destruye un inventario
 *
 * @param inventory Inventario que se desea eliminar
 * @return OK si se ha liberado correctamente, ERROR en caso contrario
 */
STATUS inventory_destroy(Inventory* inventory);

/**
 * @brief Añade un objeto al inventario
 *
 * @param inventory Inventario al que se desea añadir objeto
 * @param id Id del objeto a añadir
 * @return Un array de Ids de los objetos que tiene el jugador
 */
STATUS inventory_add_object(Inventory* inventory,Id id);

/**
 * @brief Modifica el numero de objetos del inventario
 *
 * @param inventory Inventario en el que se quiere poner el numero maximo de ids
 * @param NumIds El numero maximo de ids a colocar
 * @return OK si se ha realizado correctamente, ERROR en caso contrario
 */
STATUS inventory_set_max (Inventory* inventory, int NumIds);

/**
 * @brief Obtiene el número de objetos de un inventario
 *
 * @param inventory Inventario del que se obtiene el numero maximo de objetos
 * @return Número de objetos de un inventario
 */
int inventory_get_max (Inventory* inventory);

/**
 * @brief Elimina un objeto del inventario
 *
 * @param inventory Inventario de que eliminar el objeto
 * @param id Id del objeto a eliminar
 * @return OK si se ha realizado correctamente, ERROR en caso contrario
 */
STATUS inventory_remove_object (Inventory* inventory, Id id);

/**
 * @brief Devuelve el conjunto de identificadores
 *
 * @param inventory Inventario del que se desea obtener el conjunto de identificadores
 * @return Conjunto de identificadores
 */
Set* inventory_get_set(Inventory* inventory);

/**
 * @brief Imprime los datos de un inventario
 *
 * @param inventory 
 * @param fp Archivo 
 * @return OK si se ha realizado correctamente, ERROR en caso contrario
 */
STATUS inventory_print(FILE* fp, Inventory* inventory);

#endif