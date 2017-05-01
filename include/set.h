/** 
 *  @file set.h
 *  @author Mihai Blidaru
 *  @brief Definicion de los prototipos de las primitivas del TAD Set
 *  @version 1.0
 *  @date 20/03/2017
 */

#ifndef SET_H
#define SET_H

#include <stdio.h>
#include "types.h"

/**
 * Número máximo de ids permitidos en un set
 */
#define MAX_SET 15

/**
 * @brief Definicion de la estructura set
 */
typedef struct _Set Set;

/** @brief Crea un nuevo conjunto
 * 
 * @author Mihai Blidaru
 * @return El nuevo conjunto creadoo o NULL si no se ha podido cread
 */
Set* set_create();

/** @brief Libera memoria usada por un connjunto
 * 
 * @author Mihai Blidaru
 * 
 * @param set Conjunto que se tiene que destruir
 * @return OK si se ha realizado la operación correctamente o ERROR en caso contrario.
 */
STATUS set_destroy(Set* set);

/** @brief Añade un nuevo id al conjunto
 * 
 * @author Mihai Blidaru
 * 
 * @param set Conjunto donde añadir el nuevo id.
 * @param id Id que se tiene que añadir al conjunto.
 * @return OK si se ha añadido correctamente el Id o ERROR en caso contrario.
 */
STATUS set_addId(Set* set, Id id);

/** @brief Borra un id del Set.
 * 
 * @author Mihai Blidaru
 * 
 * @param set Conjunto donde borrar el id pasado como parametro
 * @param id Id que se tiene que borrar del conjunto
 * @return Conjunto.
 */
Set* set_delId(Set* set, Id id);

/** @brief Comprueba si un id ya existe en el conjunto;
 *   
 *  @author Mihai Blidaru
 *  @param set Conjunto en el que buscar el Id
 *  @param id Id que se tiene que comprobar si existe
 * 
 *  @return TRUE si el Id se encuentra en el conjuto o FALSE en caso contrario.
 */
BOOL set_Id_is_in(Set* set, Id id);

/** @brief Obtiene el numero de ids del set.
 * 
 * @author Mihai Blidaru
 * 
 * @param set Conjunto del que se quiere saber su numero de ids.
 * @return  Numero de ids.
 */
int set_getNumberOfIds(Set* set);

/** @brief Imprime el set.
 * 
 * @author Mihai Blidaru
 * 
 * @param fp Archivo donde imprimir
 * @param set Conjunto a imprimir
 * @return El número de caracteres imprimidos
 */
int set_print(FILE* fp, Set* set);

#endif


