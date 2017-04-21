/**
 * @brief Implememtacion del set del juego
 *
 * @file set.c
 * @author Mihai Blidaru
 * @version 1.0
 * @date 23-02-2017
 */

/* Cabeceras Libc */
#include <stdlib.h>
#include <stdio.h>
/* Cabeceras propias */
#include "set.h"
#include "types.h"

/**
 * @brief Estructura de set
 * @private
 */
struct _Set {
    Id ids[MAX_SET];        /*!< Array de Id del Set*/
    unsigned short num;     /*!< Numero de ids contenidos en el set */
};


int set_get_index_id(Set* set, Id id); /*!< @private */

/* @brief Crea un nuevo conjunto
 * 
 * @author Mihai Blidaru
 * @return El nuevo conjunto creadoo o NULL si no se ha podido cread
 */
Set* set_create() {
    int i;
    Set* newSet = NULL;

    if (!(newSet = (Set*) malloc(sizeof (Set))))
        return NULL;
    for (i = 0; i < MAX_SET; i++) {
        newSet->ids[i] = NO_ID;
    }
    newSet->num = 0;
    return newSet;
}

/** @brief Libera memoria usada por un connjunto
 * 
 * @author Mihai Blidaru
 * 
 * @param set Conjunto que se tiene que destruir
 * @return OK si se ha realizado la operación correctamente o ERROR en caso contrario.
 */
STATUS set_destroy(Set* set) {
    if (!set)
        return ERROR;

    free(set);

    return OK;

}

/* @brief Comprueba si un id ya existe en el conjunto;
 *   
 *  @author Mihai Blidaru
 *  @param set Conjunto en el que buscar el Id
 *  @param id Id que se tiene que comprobar si existe
 * 
 *  @return TRUE si el Id se encuentra en el conjuto o FALSE en caso contrario.
 */
BOOL set_Id_is_in(Set* set, Id id) {
    int i;
    if (!set || id == NO_ID)
        return FALSE;

    for (i = 0; i < set->num; i++) {
        if (set->ids[i] == id) {
            return TRUE;
        }
    }

    return FALSE;
}

/* @brief Obtiene la posicion del id pasado como argumento en el array;
 *   
 *  @author Mihai Blidaru
 *  @param set Conjunto en el que buscar el Id
 *  @param id Id que se tiene que comprobar su posicion
 * 
 *  @return La posicion del id en el array
 */
int set_get_index_id(Set* set, Id id) {
    int i;
    if (!set || id == NO_ID)
        return NO_ID;

    for (i = 0; i < set->num; i++) {
        if (set->ids[i] == id) {
            return i;
        }
    }

    return NO_ID;
}

/* @brief Añade un nuevo id al conjunto
 * 
 * @author Mihai Blidaru
 * 
 * @param set Conjunto donde añadir el nuevo id.
 * @param id Id que se tiene que añadir al conjunto.
 * @return OK si se ha añadido correctamente el Id o ERROR en caso contrario.
 */
STATUS set_addId(Set* set, Id id) {
    if (!set || id == NO_ID)
        return ERROR;

    /* No se permiten ids duplicados */
    if (set_Id_is_in(set, id))
        return ERROR;
    if (set->num == MAX_SET) {
        return ERROR;
    }

    set->ids[set->num] = id;
    set->num++;
    return OK;
 
}

/** @brief Borra un id del Set.
 * 
 * @author Mihai Blidaru
 * 
 * @param set Conjunto donde borrar el id pasado como parametro
 * @param id Id que se tiene que borrar del conjunto
 * @return Conjunto.
 */
Set* set_delId(Set* set, Id id) {
    int index;
    if (!set || id == NO_ID)
        return NULL;

    if (!set->num)
        return NULL;

    index = set_get_index_id(set, id);
    if (index == NO_ID)
        return NULL;
    /* Desplaza los ids restantes a la izquierda */
    for (; index < set->num - 1; index++) {
        set->ids[index] = set->ids[index + 1];
    }

    set->num--;
    set->ids[set->num] = NO_ID;

    return set;

}

/* @brief Obtiene el numero de ids del set.
 * 
 * @author Mihai Blidaru
 * 
 * @param set Conjunto del que se quiere saber su numero de ids.
 * @return  Numero de ids.
 */
int set_getNumberOfIds(Set* set) {
    if (!set)
        return -1;

    return set->num;
}

/* @brief Imprime el set.
 * 
 * @author Mihai Blidaru
 * 
 * @param fp Archivo donde imprimir
 * @param set Conjunto a imprimir
 * @return El número de caracteres imprimidos
 */
int set_print(FILE* fp, Set* set) {
    int i, chars = 0;
    if (!set || !fp)
        return NO_ID;

    chars += fprintf(fp, "Numero Ids: %d\n", set->num);
    for (i = 0; i < set->num; i++) {
        chars += fprintf(fp, "[%ld] ", set->ids[i]);
    }

    chars += fprintf(fp, "\n");
    return chars;
}
