/** 
 * @brief Define un espacio
 * 
 * @file space.h
 * @author Profesores PPROG
 * @author Javier Bernardo
 * @version 1.0 
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

/* Cabeceras propias */
#include "types.h"
#include "set.h"

/**
 * Definición del tipo de dato Space 
 */
typedef struct _Space Space;

/**
 * Filas que ocupa la descripción grafica 
 */
#define G_ROWS 6

/**
 * Columnas que ocupa la descripción grafica 
 */
#define G_COLUMNS 24

/**
 * @brief Crea un nuevo espacio y le asigna un Id y unos valores por defecto.
 *
 * @param space_id Un Id del nuevo espacio.
 * @return Un puntero al nuevo espacio. Devuelve NULL si no se ha podido crear.
 */
Space* space_create(Id space_id);

/**
 * @brief Libera la memoria de un espacio
 *
 * @param space Un puntero al espacio que se quiere destruir
 * @return OK si se ha liberado correctamente, si no ERROR
 */
STATUS space_destroy(Space* space);

/**
 * @brief Pone nombre a un espacio.
 *
 * @param space Un puntero al espacio al que se le quiere poner nombre.
 * @param name El nombre que se le quiere poner.
 *
 * @return OK si se ha asignado correctamente el nombre, si no ERROR.
 */
STATUS space_set_name(Space* space, char* name);

/**
 * @brief Pone nombre una descripcion al espacio.
 *
 * @param space Un puntero al espacio al que se le quiere poner nombre.
 * @param description La descripcion que se le quiere poner.
 *
 * @return OK si se ha asignado correctamente el nombre, si no ERROR.
 */
STATUS space_set_description(Space* space, char* description);

/**
 * @brief Pone una descripcion detallada al espacio.
 *
 * @param space Un puntero al espacio al que se le quiere poner nombre.
 * @param description La descripcion que se le quiere poner.
 *
 * @return OK si se ha asignado correctamente el nombre, si no ERROR.
 */
STATUS space_set_long_description(Space* space, char* description);

/**
 * @brief Pone la descripcion de la casilla.
 *
 * @param space Un puntero al espacio.
 * @param graphics Una matriz que contiene la descripción grafica.
 * @return El espacio.
 */
Space* space_set_graphics(Space* space, char graphics[][G_COLUMNS]);

/**
 * @brief Pone un norte en el espacio
 *
 * @param space Un puntero al espacio
 * @param link_id Un Id que determina el espacio
 * @return OK si se ha realizado correctamente. Sino devuelve ERROR
 */
STATUS space_set_north(Space* space, Id link_id);

/**
 * @brief Pone un sur en el espacio
 *
 * @param space Un puntero al espacio
 * @param link_id Un Id que determina el espacio
 * @return OK si se ha realizado correctamente. Sino devuelve ERROR
 */
STATUS space_set_south(Space* space, Id link_id);

/**
 * @brief Pone un este en el espacio.
 *
 * @param space Un puntero al espacio.
 * @param link_id Un Id que determina el espacio.
 * @return OK si se ha realizado correctamente. Sino devuelve ERROR.
 */
STATUS space_set_east(Space* space, Id link_id);

/**
 * @brief Pone un oeste en el espacio
 *
 * @param space Un puntero al espacio
 * @param link_id Un Id que determina el espacio
 * @return OK si se ha realizado correctamente. Sino devuelve ERROR
 */
STATUS space_set_west(Space* space, Id link_id);

/**
 * @brief Pone un up en el espacio.
 *
 * @param space Un puntero al espacio.
 * @param link_id Un Id que determina el espacio.
 * @return OK si se ha realizado correctamente. Sino devuelve ERROR.
 */
STATUS space_set_up (Space* space, Id link_id);

/**
 * @brief Pone un down en el espacio.
 *
 * @param space Un puntero al espacio.
 * @param link_id Un Id que determina el espacio.
 * @return OK si se ha realizado correctamente. Sino devuelve ERROR.
 */
STATUS space_set_down (Space* space, Id link_id);

/**
 * @brief Obtienes el id del espacio.
 *
 * @param space Un puntero al espacio.
 * @return El id del espacio.
 */
Id space_get_id(Space* space);

/**
 * @brief Obtienes el nombre del espacio.
 *
 * @param space Un puntero al espacio.
 * @return El nombre del espacio.
 */
const char* space_get_name(Space* space);

/**
 * @brief Obtiene la descripcion de un espacio.
 *
 * @param space Un puntero al espacio al que se le quiere poner nombre.
 * @return La descripcion del espacio.
 */
const char * space_get_description(Space* space);

/**
 * @brief Obtiene la descripción detallada de un espacio.
 *
 * @param space Un puntero al espacio al que se le quiere poner nombre.
 * @return La descripción detallada del espacio.
 */

const char * space_get_long_description(Space* space);

/** 
 * @brief Devuelve la descripción grafica de la casilla.
 * @param[in] space Un puntero al espacio.
 * @param[out] dest Matriz donde guardar la descripción grafica.
 * @return Un puntero a la descripción grafica del espacio o NULL si hay algun error.
 */
Space* space_get_graphics(Space* space, char dest[][G_COLUMNS]);

/**
 * @brief Obtienes la lista de los objetos del espacio.
 *
 * @param space Un puntero al espacio.
 * @return La lista de los objetos del espacio.
 */
Set* space_get_objects(Space* space);

/**
 * @brief Obtienes el norte del espacio.
 *
 * @param space Un puntero al espacio.
 * @return El norte del espacio.
 */
Id space_get_north(Space* space);

/**
 * @brief Obtienes el sur del espacio.
 *
 * @param space Un puntero al espacio.
 * @return El sur del espacio.
 */
Id space_get_south(Space* space);

/**
 * @brief Obtienes el este del espacio.
 *
 * @param space Un puntero al espacio.
 * @return El este del espacio.
 */
Id space_get_east(Space* space);

/**
 * @brief Obtienes el oeste del espacio.
 *
 * @param space Un puntero al espacio.
 * @return El oeste del espacio.
 */
Id space_get_west(Space* space);

/**
 * @brief Obtienes la dirección hacia arriba del espacio.
 * @param space Un puntero al espacio.
 * @return La dirección hacia arriba del espacio.
 */
Id space_get_up(Space* space);

/**
 * @brief Obtienes la dirección hacia abajo del espacio.
 * @param space Un puntero al espacio.
 * @return La dirección hacia abajo del espacio.
 */
Id space_get_down(Space* space);

/**
 * @brief Añades el objeto al espacio.
 *
 * @param space Un puntero al espacio y una id del objeto.
 * @param object_id Id del objeto.
 * @return Ok si se añade el objeto o ERROR si no.
 */
STATUS space_add_object(Space* space, Id object_id);

/**
 * @brief Eliminas el objeto del espacio.
 *
 * @param space Un puntero al espacio.
 * @param object_id Identificador del objeto.
 * @return Ok si se elimina o ERROR si no.
 */
STATUS space_remove_object(Space* space, Id object_id);

/**
 * @brief Compruebas si el espacio tiene objeto.
 *
 * @param space Un puntero al espacio.
 * @param object_id Id del objeto.
 * @return funcion que coloca objeto.
 */
BOOL space_contains_object(Space* space, Id object_id);

/** 
 * @brief Devuelve si el espacio tiene descripcion grafica o no.
 * @param space Un puntero al espacio.
 * @return TRUE si los graficos están vacios o FALSE en caso contrario.
 */
BOOL space_graphics_areEmpty(Space* space);

/**
 * @brief Asigna la iluminación al espacio
 * @param space Un puntero al espacio 
 * @param iluminated variable de tipo BOOL
 * @return Devuelve OK si se realiza correctamente
 */
STATUS space_set_iluminated(Space* space,BOOL iluminated);

/**
 * @brief Devuelve si el espacio está iluminado
 * @param space Un puntero al espacio.
 * @return Devuelve el espacio iluminado
 */
BOOL space_get_iluminated(Space* space);

/**
 * @brief Imprime el espacio.
 * @param space Un puntero al espacio.
 * @return Impresion del objeto.
 */
int space_print_graphics(Space* space);

/**
 * @brief Imprimes lo que hay en el espacio.
 *
 * @param space Un puntero al espacio.
 * @return El contenido del espacio.
 */
STATUS space_print(Space* space);

#endif
