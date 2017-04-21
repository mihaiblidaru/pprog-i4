/**
 * @brief Implementa el nuevo TAD Link (Enlace).
 *      Sirve para enlazar de forma más potente las casillas
 * @file link.h
 * @version 1.0
 * 
*/

#ifndef LINK_H
#define LINK_H

#include "types.h"
/**
 * Numero maximo de enlaces permitidos 
 */
#define MAX_LINK 10000 

/**
 * @brief Estructura de link
 * 
 */
typedef struct _Link Link;

/**
 * @brief Define los posibles estados de un enlace
 */
typedef enum {
    OPENED,     /*!< Enlace abierto*/
    CLOSED      /*!< Enlace cerrado*/
} State;

/** @brief Crea un nuevo link
 * 
 * @author Javier Bernardo
 * 
 * @return El nuevo link creado
 */
Link *link_create ();

/** @brief Destruye el link
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @return OK si se destruido, ERROR en caso contrario
 */
STATUS link_destroy(Link *link);

/** @brief Coloca la id del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @param id La id que se desea colocar
 * @return OK si se ha colocado bien la id, ERROR en caso contrario
 */
STATUS link_set_id(Link * link, Id id);

/** @brief Obtiene la id del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @return La id del link
 */
Id link_get_id(Link* link);

/** @brief Coloca el nombre del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @param name El nombre que se desea colocar
 * @return OK si se ha colocado bien el nombre, ERROR en caso contrario
 */
STATUS link_set_name(Link* link, char* name);

/** @brief Obtiene el nombre del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * 
 * @return El nombre del link
 */
char* link_get_name(Link*link);

/** @brief Coloca la id del spacio 1 del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @param id La id que se desea colocar
 * @return OK si se ha colocado bien la id, ERROR en caso contrario
 */
STATUS link_set_space1(Link* link, Id id);

/** @brief Obtiene la id del spacio 1 del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @return El id del spacio 1
 */
Id link_get_space1(Link*link);

/** @brief Coloca la id del spacio 2 del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @param id La id que se desea colocar
 * @return OK si se ha colocado bien la id, ERROR en caso contrario
 */
STATUS link_set_space2(Link *link, Id id);

/** @brief Obtiene la id del spacio 2 del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @return Id del spacio 2 del link
 */
Id link_get_space2(Link *link);

/** @brief Coloca el estado del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @param state El estado al que se quiere poner el link
 * @return OK si se ha colocado bien el estado, ERROR en caso contrario
 */
STATUS link_set_state(Link* link, int state);

/** @brief Obtiene el estado del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @return El estado del link
 */
State link_get_state(Link *link);  

/** @brief Obtiene el id de destino de un link desde una casilla dada.
 * @param link Puntero a link.
 * @param from Id de la casilla de origen.
 * @return El id de destino si se ha podido encontrar o NO_ID en caso contrario.
 */ 
Id link_get_dest_from(Link* link, Id from);

/** @brief Imprime el link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @return Impresion del link
 */
int link_print(Link* link);


#endif