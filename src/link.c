/**
 * @brief Módulo que define el TAD Enlace así como las primitivas encargadas de trabajar 
 * con este TAD
 * 
 * @file link.c
 * @author Javier Bernardo
 * @version 1.0
 * @date 14-03-2017
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "link.h"
#include "types.h"

/**
 * @brief Estructura de link
 * 
 */
struct _Link{
	Id id;						/*!< La identidad del enlace */
	char name[WORD_SIZE];		/*!< El nombre del enlace */
	Id space1;					/*!< La identidad de uno de los espacios del enlace */
	Id space2;					/*!< La identidad del otro espacio del enlace */
	int state;					/*!< Un entero cuyo valor es 0 si el enlace está abierto 
									y 1 si está cerrado */
};

/* @brief Crea un nuevo link
 * 
 * @author Javier Bernardo
 * 
 * @return El nuevo link creado
 */
Link *link_create (){
    
    Link * link = NULL;
    
    link = (Link*)malloc(sizeof(Link));
    
    if(!link)   
        return NULL;
    link->id = NO_ID;
    link->name[0] = 0;
    link->space1 = NO_ID;
    link->space2 = NO_ID;
    link->state = OPENED;
    
    return link;
}

/* @brief Destruye el link
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @return OK si se destruido, ERROR en caso contrario
 */
STATUS link_destroy(Link *link){
    
    if(!link)
        return ERROR;
    free (link);

    return OK;
}

/* @brief Coloca la id del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @param id La id que se desea colocar
 * @return OK si se ha colocado bien la id, ERROR en caso contrario
 */
STATUS link_set_id(Link * link, Id id){
    
    if(!link || id == NO_ID)
        return ERROR;
        
    link->id = id;
    
    return OK;
}

/* @brief Obtiene la id del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @return La id del link
 */
Id link_get_id(Link* link){
    if(!link)
        return NO_ID;
        
    return link->id;
}

/* @brief Coloca el nombre del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @param name El nombre que se desea colocar
 * @return OK si se ha colocado bien el nombre, ERROR en caso contrario
 */
STATUS link_set_name(Link* link, char* name){
    if(!link||!name)
        return ERROR;
    strcpy(link->name, name);
    
    return OK;
}

/** @brief Obtiene el id de destino de un link desde una casilla dada.
 * @param link Puntero a link.
 * @param from Id de la casilla de origen.
 * @return El id de destino si se ha podido encontrar o NO_ID en caso contrario.
 */ 
Id link_get_dest_from(Link* link, Id from){
    if(!link || from == NO_ID)
        return NO_ID;
        
    if(link->space1 == from){
        return link->space2;
    }else if(link->space2 == from){
        return link->space1;        
    }

    return NO_ID;
}

/* @brief Obtiene el nombre del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * 
 * @return El nombre del link
 */
char* link_get_name(Link*link){
    if(!link)
        return NULL;
    return link->name;
}

/* @brief Coloca la id del spacio 1 del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @param id La id que se desea colocar
 * @return OK si se ha colocado bien la id, ERROR en caso contrario
 */
STATUS link_set_space1(Link* link, Id id){
    if(!link || id == NO_ID)
        return ERROR;
    link->space1 = id;
    
    return OK;
}

/* @brief Obtiene la id del spacio 1 del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @return El id del spacio 1
 */
Id link_get_space1(Link*link){
    if(!link)
        return NO_ID;
        
    return link->space1;
}

/* @brief Coloca la id del spacio 2 del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @param id La id que se desea colocar
 * @return OK si se ha colocado bien la id, ERROR en caso contrario
 */
STATUS link_set_space2(Link *link, Id id){
    if(!link  || id == NO_ID)
        return ERROR;
    link->space2 = id;
    
    return OK;
}

/* @brief Obtiene la id del spacio 2 del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @return Id del spacio 2 del link
 */
Id link_get_space2(Link *link){
    if(!link)
        return NO_ID;
    return link->space2;
}

/* @brief Coloca el estado del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @param state El estado al que se quiere poner el link
 * @return OK si se ha colocado bien el estado, ERROR en caso contrario
 */
STATUS link_set_state(Link* link, int state){
	if(!link || (state != 0 && state != 1))
		return ERROR;
	link->state = state;
	return OK;
}

/* @brief Obtiene el estado del link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @return El estado del link
 */
State link_get_state(Link *link){
    if(!link)
        return -1;
    return link->state;
}

/* @brief Imprime el link 
 * 
 * @author Javier Bernardo
 * 
 * @param link Puntero al link.
 * @return Impresion del link
 */
int link_print(Link* link) {
	int print = 0;
	if(!link)
		return -1;
	printf("----------------------------------\n");
	print += printf("Id -> %ld\n", link->id);
	print += printf("Name -> %s\n", link->name);
	print += printf("Space 1 -> %ld\n", link->space1);
	print += printf("Space 2 -> %ld\n", link->space2);
	print += printf("State -> %d\n", link->state);
	printf("----------------------------------\n");
	return print;
}  
