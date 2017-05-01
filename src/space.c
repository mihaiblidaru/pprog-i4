/** @brief Implementa el TAD space
 *      Define los campos de la estructura Space. Tambien define todas las
 *      funciones necesarias para trabajar con este tipo de datos
 *  
 *  @file space.c
 * 
 *  @author Profesores PPROG
 *  @author Javier Bernardo
 *  @author Mihai Blidaru
 *  @author Laura Bernal
 *  @author Sandra Benitez
 * 
 *  @version 2.0
 *  @date 20/02/2017
 */

/**
 * Cabeceras Libc
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Cabeceras propias
 */
#include "types.h"
#include "space.h"
#include "set.h"

/**
 * @brief Estructura de space
 * 
 */
struct _Space {
    Id id;                                  /*!< Id de una casilla */
    char name[WORD_SIZE];                   /*!< Nombre de una casilla */
    BOOL iluminated;                        /*!< Espacio iluminado o no */
    Id north;                               /*!< Id del enlace norte*/
    Id south;                               /*!< Id del enlace sur */    
    Id east;                                /*!< Id del enlace este */
    Id west;                                /*!< Id del enlace oeste */
    Id up;                                  /*!< Id del enlace hacia arriba */
    Id down;                                /*!< Id del enlace hacia abajo */
    char graphics[G_ROWS][G_COLUMNS];       /*!< Descripcion grafica de la casilla */
    char description[WORD_SIZE];            /*!< Descripcion textual de la casilla */
    char longDescription[WORD_SIZE];        /*!< Descripcion detallada de la casilla */
    Set* objects;                           /*!< Set que contiene los objetos de una casilla */
};

/*
 * @brief Crea un nuevo espacio y le asigna un Id y unos valores por defecto.
 *
 * @param space_id Un Id del nuevo espacio.
 * @return Un puntero al nuevo espacio. Devuelve NULL si no se ha podido crear.
 */
Space* space_create(Id space_id) {

    Space *newSpace = NULL;

    if (space_id == NO_ID)
        return NULL;

    newSpace = (Space *) calloc(1, sizeof (Space));

    if (newSpace == NULL) {
        return NULL;
    }
    newSpace->id = space_id;
    newSpace->name[0] = '\0';
    newSpace->iluminated = FALSE;
    newSpace->north = NO_ID;
    newSpace->south = NO_ID;
    newSpace->east = NO_ID;
    newSpace->west = NO_ID;
    newSpace->up = NO_ID;
    newSpace->down = NO_ID;
    strcpy(newSpace->graphics[0],"                       ");
    strcpy(newSpace->graphics[1],"                       ");
    strcpy(newSpace->graphics[2],"                       ");
    strcpy(newSpace->graphics[3],"                       ");
    strcpy(newSpace->graphics[4],"                       ");
    strcpy(newSpace->graphics[5],"                       ");
    newSpace->description[0] = '\0';
    newSpace->longDescription[0] = '\0';
    newSpace->objects = NULL;
    
    

    newSpace->objects = set_create();

    return newSpace;
}

/*
 * @brief Libera la memoria de un espacio.
 *
 * @param space Un puntero al espacio que se quiere destruir.
 * @return OK si se ha liberado correctamente, si no ERROR.
 */
STATUS space_destroy(Space* space) {
    if (!space) {
        return ERROR;
    }

    set_destroy(space->objects);
    free(space);
    space = NULL;

    return OK;
}

/*
 * @brief Pone nombre a un espacio.
 *
 * @param space Un puntero al espacio al que se le quiere poner nombre.
 * @param name El nombre que se le quiere poner.
 *
 * @return OK si se ha asignado correctamente el nombre, si no ERROR.
 */
STATUS space_set_name(Space* space, char* name) {
    if (!space || !name) {
        return ERROR;
    }

    if (!strcpy(space->name, name)) {
        return ERROR;
    }

    return OK;
}

/*
 * @brief Pone nombre una descripcion al espacio.
 *
 * @param space Un puntero al espacio al que se le quiere poner nombre.
 * @param description La descripcion que se le quiere poner.
 *
 * @return OK si se ha asignado correctamente el nombre, si no ERROR.
 */
STATUS space_set_description(Space* space, char* description) {
    if (!space || !description) {
        return ERROR;
    }

    if (!strcpy(space->description, description)) {
        return ERROR;
    }

    return OK;
}

/*
 * @brief Pone una descripcion detallada al espacio.
 *
 * @param space Un puntero al espacio al que se le quiere poner nombre.
 * @param description La descripcion que se le quiere poner.
 *
 * @return OK si se ha asignado correctamente el nombre, si no ERROR.
 */
STATUS space_set_long_description(Space* space, char* description) {
    if (!space || !description) {
        return ERROR;
    }

    if (!strcpy(space->longDescription, description)) {
        return ERROR;
    }

    return OK;
}

/*
 * @brief Pone la descripcion de la casilla.
 *
 * @param space Un puntero al espacio.
 * @param graphics Una matriz que contiene la descripción grafica.
 * @return El espacio.
 */
Space* space_set_graphics(Space* space, char graphics[][G_COLUMNS]) {
    if (!space || !graphics)
        return NULL;
    strcpy(space->graphics[0], graphics[0]);
    strcpy(space->graphics[1], graphics[1]);
    strcpy(space->graphics[2], graphics[2]);
    strcpy(space->graphics[3], graphics[3]);
    strcpy(space->graphics[4], graphics[4]);
    strcpy(space->graphics[5], graphics[5]);
    return space;
}

/*
 * @brief Pone un norte en el espacio.
 *
 * @param space Un puntero al espacio.
 * @param link_id Un Id que determina el espacio.
 * @return OK si se ha realizado correctamente. Sino devuelve ERROR.
 */
STATUS space_set_north(Space* space, Id link_id) {
    if (!space || link_id == NO_ID) {
        return ERROR;
    }
    space->north = link_id;
    return OK;
}

/*
 * @brief Pone un sur en el espacio.
 *
 * @param space Un puntero al espacio.
 * @param link_id Un Id que determina el espacio.
 * @return OK si se ha realizado correctamente. Sino devuelve ERROR.
 */
STATUS space_set_south(Space* space, Id link_id) {
    if (!space || link_id == NO_ID) {
        return ERROR;
    }
    space->south = link_id;
    return OK;
}

/*
 * @brief Pone un este en el espacio.
 *
 * @param space Un puntero al espacio.
 * @param link_id Un Id que determina el espacio.
 * @return OK si se ha realizado correctamente. Sino devuelve ERROR.
 */
STATUS space_set_east(Space* space, Id link_id) {
    if (!space || link_id == NO_ID) {
        return ERROR;
    }
    space->east = link_id;
    return OK;
}

/*
 * @brief Pone un oeste en el espacio.
 *
 * @param space Un puntero al espacio.
 * @param link_id Un Id que determina el espacio.
 * @return OK si se ha realizado correctamente. Sino devuelve ERROR.
 */
STATUS space_set_west(Space* space, Id link_id) {
    if (!space || link_id == NO_ID) {
        return ERROR;
    }
    space->west = link_id;
    return OK;
}

/*
 * @brief Pone un up en el espacio.
 *
 * @param space Un puntero al espacio.
 * @param link_id Un Id que determina el espacio.
 * @return OK si se ha realizado correctamente. Sino devuelve ERROR.
 */
STATUS space_set_up (Space* space, Id link_id){
    if (!space || link_id == NO_ID)
        return ERROR;
    space->up = link_id;
    return OK;
}

/*
 * @brief Pone un down en el espacio.
 *
 * @param space Un puntero al espacio.
 * @param link_id Un Id que determina el espacio.
 * @return OK si se ha realizado correctamente. Sino devuelve ERROR.
 */
STATUS space_set_down (Space* space, Id link_id){
    if (!space || link_id == NO_ID)
        return ERROR;
    space->down = link_id;
    return OK;
}

/*
 * @brief Obtienes el id del espacio.
 *
 * @param space Un puntero al espacio.
 * @return El id del espacio.
 */
Id space_get_id(Space* space) {
    if (!space) {
        return NO_ID;
    }
    return space->id;
}

/*
 * @brief Obtienes el nombre del espacio.
 *
 * @param space Un puntero al espacio.
 * @return El nombre del espacio.
 */
const char * space_get_name(Space* space) {
    if (!space) {
        return NULL;
    }
    return space->name;
}

/*
 * @brief Obtiene la descripcion de un espacio.
 *
 * @param space Un puntero al espacio al que se le quiere poner nombre.
 * @return La descripcion del espacio.
 */
const char * space_get_description(Space* space) {
    if (!space) {
        return NULL;
    }
    return space->description;
}


/*
 * @brief Obtiene la descripcion detallada de un espacio.
 *
 * @param space Un puntero al espacio al que se le quiere poner nombre.
 * @return La descripción detallada del espacio.
 */
const char * space_get_long_description(Space* space) {
    if (!space) {
        return NULL;
    }
    return space->longDescription;
}


/* @brief Devuelve la descripción grafica de la casilla.
 * @param[in] space Un puntero al espacio.
 * @param[out] dest Matriz donde guardar la descripción grafica.
 * @return Un puntero a la descripción grafica del espacio o NULL si hay algun error.
 */
Space* space_get_graphics(Space* space, char dest[][G_COLUMNS]) {
    if (!space)
        return NULL;

    strcpy(dest[0], space->graphics[0]);
    strcpy(dest[1], space->graphics[1]);
    strcpy(dest[2], space->graphics[2]);
    strcpy(dest[3], space->graphics[3]);
    strcpy(dest[4], space->graphics[4]);
    strcpy(dest[5], space->graphics[5]);

    return space;
}

/*
 * @brief Obtienes la lista de los objetos del espacio.
 *
 * @param space Un puntero al espacio.
 * @return La lista de los objetos del espacio.
 */
Set* space_get_objects(Space* space) {
    if (!space) {
        return NULL;
    }

    return space->objects;
}

/*
 * @brief Obtienes el norte del espacio.
 *
 * @param space Un puntero al espacio.
 * @return El norte del espacio.
 */
Id space_get_north(Space* space) {
    if (!space) {
        return NO_ID;
    }
    return space->north;
}

/*
 * @brief Obtienes el sur del espacio.
 *
 * @param space Un puntero al espacio.
 * @return El sur del espacio.
 */
Id space_get_south(Space* space) {
    if (!space) {
        return NO_ID;
    }
    return space->south;
}

/*
 * @brief Obtienes el este del espacio.
 *
 * @param space Un puntero al espacio.
 * @return El este del espacio.
 */
Id space_get_east(Space* space) {
    if (!space) {
        return NO_ID;
    }
    return space->east;
}

/*
 * @brief Obtienes el oeste del espacio.
 *
 * @param space Un puntero al espacio.
 * @return El oeste del espacio.
 */
Id space_get_west(Space* space) {
    if (!space) {
        return NO_ID;
    }
    return space->west;
}

/*
 * @brief Obtienes la dirección hacia arriba del espacio.
 * @param space Un puntero al espacio.
 * @return Posición hacia arriba del espacio.
 */
Id space_get_up(Space* space) {
    if (!space) {
        return NO_ID;
    }
    return space->up;
}

/*
 * @brief Obtienes la dirección hacia abajo del espacio.
 * @param space Un puntero al espacio.
 * @return Posición hacia abajo del espacio.
 */
Id space_get_down(Space* space) {
    if (!space) {
        return NO_ID;
    }
    return space->down;
}

/*
 * @brief Añades el objeto al espacio.
 *
 * @param space Un puntero al espacio.
 * @param object_id Id del objeto.
 * @return Ok si se añade el objeto o ERROR si no.
 */
STATUS space_add_object(Space* space, Id object_id) {
    if (!space || object_id == NO_ID)
        return ERROR;

    if (set_addId(space->objects, object_id) == ERROR)
        return ERROR;

    return OK;

}

/*
 * @brief Eliminas el objeto del espacio.
 *
 * @param space Un puntero al espacio.
 * @param object_id Identificador del objeto.
 * @return Ok si se elimina o ERROR si no.
 */
STATUS space_remove_object(Space* space, Id object_id) {
    if (!space || object_id == NO_ID)
        return ERROR;

    if (set_delId(space->objects, object_id) == ERROR)
        return ERROR;

    return OK;

}

/*
 * @brief Compruebas si el espacio tiene objeto.
 *
 * @param space Un puntero al espacio.
 * @param object_id Id del objeto.
 * @return funcion que coloca objeto.
 */
BOOL space_contains_object(Space* space, Id object_id) {
    if (!space || object_id == NO_ID)
        return FALSE;

    return set_Id_is_in(space->objects, object_id);
}

/* 
 * @brief Devuelve si el espacio tiene descripcion grafica o no.
 * @param space Un puntero al espacio.
 * @return TRUE si los graficos están vacios o FALSE en caso contrario.
 */
BOOL space_graphics_areEmpty(Space* space) {
    int i, j, printableChars = 0;
    
    if (!space)
        return TRUE;
        
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 7; j++) {
            if (!isspace(space->graphics[i][j])) {
                printableChars++;
            }
        }
    }

    if (printableChars > 0)
        return FALSE;
    else
        return TRUE;
}

/*
 * @brief Asigna la iluminación al espacio
 * @param space Un puntero al espacio 
 * @param variable de tipo BOOL
 * @return Devuelve OK si se realiza correctamente
 */
STATUS space_set_iluminated(Space* space, BOOL iluminated){
    if(!space)
        return ERROR;
    space->iluminated = iluminated;
    return OK;
}

/*
 * @brief Devuelve si el espacio está iluminado
 * @param space Un puntero al espacio.
 * @return Devuelve el espacio iluminado
 */
BOOL space_get_iluminated(Space* space){
    if(!space)
        return FALSE;
    
    return space->iluminated;
}

/*
 * @brief Imprime el espacio.
 * @param space Un puntero al espacio.
 * @return Impresion del objeto.
 */
int space_print_graphics(Space* space) {
    int suma = 0;
    if (!space)
        return -1;
    suma += printf("  |    %s     |", space->graphics[0]);
    suma += printf("\n");
    suma += printf("  |    %s     |", space->graphics[1]);
    suma += printf("\n");
    suma += printf("  |    %s     |", space->graphics[2]);
    suma += printf("\n");
    return suma;
}

/*
 * @brief Imprimes lo que hay en el espacio.
 *
 * @param space Un puntero al espacio.
 * @return El contenido del espacio.
 */
STATUS space_print(Space* space) {
    Id idaux = NO_ID;

    if (!space) {
        return ERROR;
    }

    fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);
    fprintf(stdout, "Space objects : ");
    set_print(stdout, space->objects);
    fprintf(stdout, "Graphics:\n");
    space_print_graphics(space);

    idaux = space_get_north(space);
    if (NO_ID != idaux) {
        fprintf(stdout, "---> North link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No north link.\n");
    }

    idaux = space_get_south(space);
    if (NO_ID != idaux) {
        fprintf(stdout, "---> South link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No south link.\n");
    }

    idaux = space_get_east(space);
    if (NO_ID != idaux) {
        fprintf(stdout, "---> East link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No east link.\n");
    }

    idaux = space_get_west(space);
    if (NO_ID != idaux) {
        fprintf(stdout, "---> West link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No west link.\n");
    }
    
    idaux = space_get_up(space);
    if (NO_ID != idaux) {
        fprintf(stdout, "---> Up link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No up link.\n");
    }
    
     idaux = space_get_down(space);
    if (NO_ID != idaux) {
        fprintf(stdout, "---> Down link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No Down link.\n");
    }
    
    if(space_get_iluminated(space)==TRUE){
        fprintf(stdout,"Espacio: iluminated\n");
    } else {
        fprintf(stdout,"Espacio: No iluminated\n");
    }

    
    return OK;
}