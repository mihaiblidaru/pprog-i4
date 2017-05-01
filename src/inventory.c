/**
 * @brief Implememtacion del inventario del juego
 *
 * @file inventory.c
 * @author Laura Bernal y Sandra Benítez
 * @version 1.0
 * @date 14-03-2017
 */

/*+
 * Cabeceras Libc
 */
#include <stdlib.h>
#include <stdio.h>
/**
 * Cabeceras propias 
 */
#include "set.h"
#include "inventory.h"
#include "types.h"

/**
 * @brief Estructura de Inventory
 * 
 */
struct _Inventory{
    Set* identificadores;       /*!< Un puntero al conjunto de identidades contenidas en el inventario */
    int maxIds;	                /*!< Un entero, correspondiente al número máximo de objetos permitidos en el inventario */
			
};

/*
 * @brief Crea el inventario e inicializa sus campos
 * @author Laura Bernal y Sandra Benitez
 * 
 * @return Puntero a inventory
 */
Inventory* inventory_create(){
    Inventory* inventory = NULL;
    
    inventory = (Inventory*)calloc(1, sizeof(Inventory));
    if(!inventory)
        return NULL;
    inventory->identificadores = set_create();
    inventory->maxIds = 0;
    
    return inventory;
}

/*
 * @brief Destruye un inventario
 *
 * @param inventory Inventario que se desea eliminar
 * @return OK si se ha liberado correctamente, ERROR en caso contrario
 */
STATUS inventory_destroy(Inventory* inventory){
    if(!inventory)
        return ERROR;
    
    set_destroy(inventory->identificadores);
    
    free(inventory);
    
    return OK;
}

/*
 * @brief Añade un objeto al inventario
 *
 * @param inventory Inventario al que se desea añadir objeto
 * @param id Id del objeto a añadir
 * @return Un array de Ids de los objetos que tiene el jugador
 */
STATUS inventory_add_object(Inventory* inventory,Id id){
    if(!inventory)
        return ERROR;
        
    if(set_getNumberOfIds(inventory->identificadores) == inventory->maxIds)
        return ERROR;
    
    if(set_addId(inventory->identificadores,id)==OK)
        return OK;
    
    return ERROR;
}

/*
 * @brief Modifica el numero de objetos del inventario
 *
 * @param inventory Inventario en el que se quiere poner el numero maximo de ids
 * @param NumIds El numero maximo de ids a colocar
 * @return OK si se ha realizado correctamente, ERROR en caso contrario
 */
STATUS inventory_set_max(Inventory* inventory, int NumIds){
    if (!inventory || NumIds < 1)
        return ERROR;
        
    inventory->maxIds = NumIds;   
    return OK;
}

/*
 * @brief Obtiene el número de objetos de un inventario
 *
 * @param inventory Inventario del que se obtiene el numero maximo de objetos
 * @return Número de objetos de un inventario
 */
int inventory_get_max (Inventory* inventory){
    if (!inventory)
        return -1;
    return inventory->maxIds;
}

/*
 * @brief Elimina un objeto del inventario
 *
 * @param inventory Inventario de que eliminar el objeto
 * @param id Id del objeto a eliminar
 * @return OK si se ha realizado correctamente, ERROR en caso contrario
 */
STATUS inventory_remove_object (Inventory* inventory, Id id){
    if (!inventory)
        return ERROR;
    
    if (set_delId(inventory->identificadores, id) != NULL)
        return OK;
    return ERROR;
}

/*
 * @brief Devuelve el conjunto de identificadores
 *
 * @param inventory Inventario del que se desea obtener el conjunto de identificadores
 * @return Conjunto de identificadores
 */
Set* inventory_get_set(Inventory* inventory){
    if(!inventory)
        return NULL;
    
    return inventory->identificadores;
}

/*
 * @brief Imprime los datos de un inventario
 *
 * @param inventory 
 * @param fp Archivo 
 * @return OK si se ha realizado correctamente, ERROR en caso contrario
 */
STATUS inventory_print(FILE* fp, Inventory* inventory){
    if (!fp || !inventory)
        return ERROR;
    fprintf(fp, "Número máximo de ids: %d\n", inventory->maxIds);
    
    if(set_print(fp, inventory->identificadores)!=ERROR)
        return OK;
        
    return ERROR;
}

