/** 
 * @brief Imlementación del TAD Objeto
 * 
 * @file object.c
 * @author Javier Bernardo
 * Pareja 7
 * @version 1.0 
 * @date 31-01-2017
 * @copyright GNU Public License
 */

/**
 * Cabeceras Libc 
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Cabeceras propias 
 */
#include "object.h"
#include "types.h"

/**
 * @brief Estructura del Object
 * @cond
 */
struct _Object {
    Id id;                    /*!< Id del objeto */
    char name[WORD_SIZE];     /*!< Nombre del objeto */
    char desc[WORD_SIZE];     /*!< Descripcion del objeto */
    char desc2[WORD_SIZE];    /*!< Descripcion del objeto si no esta en su espacio */
    BOOL mobile;              /*!< TRUE si se puede mover, FALSE en caso contrario */
    BOOL moved;               /*!< TRUE si es movido, FALSE en caso contrario */ 
    BOOL hidden;              /*!< TRUE si esta oculto, FALSE en caso contrario */
    Id open;                  /*!< Id si puede abrir el link, NO_ID en caso contrario */
    BOOL illuminates;         /*!< TRUE si puede iluminar el espacio, FALSE en caso contrario */
    BOOL light_on;            /*!< TRUE si esta encendido, FALSE en caso contrario */
    char graphics[WORD_SIZE];
};

/**
 * @endcond
 */ 
 
/*
 * @brief Reservamos memoria para un nuevo objeto.
 *
 * @return Devuelve el objeto creado
 */
Object* object_create() {
    Object *object = NULL;
    object = (Object*) malloc(sizeof (Object));

    object->id = NO_ID;
    object->name[0] = '\0';
    object->graphics[0] = '\0';
    object->mobile = FALSE;
    object->moved = FALSE;
    object->hidden = FALSE;
    object->open = NO_ID;
    object->illuminates = FALSE;
    object->light_on = FALSE;

    return object;
}

/*
 * @brief Destruye un objeto
 * @date 12-12-2005
 * @param object El puntero del objeto.
 * @return Error si se ha hecho mal o Ok si se ha liberado correctamente.
 */
STATUS object_destroy(Object* object) {
    if (!object)
        return ERROR;

    free(object);
    return OK;
}

/*
 * @brief Pone el id del objeto
 *
 * @param object El puntero del objeto.
 * @param id Id que recibe para el objeto
 * @return El objeto con el nuevo id
 */
Object* object_Set_Id(Object* object, Id id) {
    if (!object || id == NO_ID)
        return NULL;
    object->id = id;
    return object;
}

/*
 * @brief Pone el nombre del objeto
 *
 * @param object El puntero del objeto.
 * @param name Nombre que recibe para el objeto
 * @return El objeto con el nuevo nombre
 */
Object* object_Set_Name(Object* object, char *name) {
    if (!object || !name)
        return NULL;
    strncpy(object->name, name, WORD_SIZE);
    return object;

}

/*
 * @brief Le asigna al objeto descripción grafica del objeto
 *
 * @param object El puntero del objeto.
 * @return El objeto actualizado o NULL si se produce algun error
 */
Object* object_Set_Graphics(Object* object, char *graphics) {
    if (!object || !graphics)
        return NULL;
    strncpy(object->graphics, graphics, WORD_SIZE);
    return object;
}

/*
 * @brief Pone la descripción  del objeto
 *
 * @param object El puntero del objeto.
 * @param desc Descripcion  que recibe para el objeto
 * @return El objeto con la nueva descripción
 */
Object* object_Set_Description(Object* object, char *desc) {
    if (!object || !desc)
        return NULL;
    strncpy(object->desc, desc, WORD_SIZE);
    return object;

}

/*
 * @brief Pone la descripción dos del objeto
 *
 * @param object El puntero del objeto.
 * @param desc2 Descripcion  que recibe para el objeto
 * @return El objeto con la nueva descripción
 */
Object* object_Set_Description2(Object* object, char *desc2) {
    if (!object || !desc2)
        return NULL;
    strncpy(object->desc2, desc2, WORD_SIZE);
    return object;

}
/*
 * @brief Pone la disponibilidad de movimiento del objeto
 *
 * @param object El puntero del objeto.
 * @param mobile Estado que recibe para el objeto
 * @return Ok si se hace, ERROR en caso contrario
 */
STATUS object_Set_Mobile(Object* object, const BOOL mobile) {
    if (!object || (mobile != TRUE && mobile != FALSE))
        return ERROR;
    
    object->mobile = mobile;
    return OK;
}
/*
 * @brief Pone si se ha mpvido el objeto
 *
 * @param object El puntero del objeto.
 * @param moved Estado que recibe para el objeto
 * @return Ok si se hace, ERROR en caso contrario
 */
STATUS object_Set_Moved(Object* object, const BOOL moved) {
    if (!object)
        return ERROR;
    
    object->moved = moved;
    return OK;
}
/*
 * @brief Pone la situacion del objeto, oculto o no oculto
 *
 * @param object El puntero del objeto.
 * @param hidden Estado que recibe para el objeto
 * @return Ok si se hace, ERROR en caso contrario
 */
STATUS object_Set_Hidden(Object* object, BOOL hidden) {
    if (!object)
        return ERROR;
    
    object->hidden = hidden;
    return OK;
}
/*
 * @brief Pone la situacion del link del objeto
 *
 * @param object El puntero del objeto.
 * @param open Estado que recibe para el objeto
 * @return Ok si se hace, ERROR en caso contrario
 */
STATUS object_Set_Open(Object* object, Id open) {
    if (!object)
        return ERROR;
    
    object->open = open;
    return OK;
} 

/*
 * @brief Pone la iluminacion del objeto
 *
 * @param object El puntero del objeto.
 * @param illuminates Estado que recibe para el objeto
 * @return Ok si se hace, ERROR en caso contrario
 */
STATUS object_Set_Illuminates(Object* object, BOOL illuminates) {
    if (!object)
        return ERROR;
    
    object->illuminates = illuminates;
    return OK;
} 

/*
 * @brief Pone el encendido del objeto
 *
 * @param object El puntero del objeto.
 * @param on Estado que recibe para el objeto
 * @return Ok si se hace, ERROR en caso contrario
 */
STATUS object_Set_Light(Object* object, BOOL on) {
    if (!object)
        return ERROR;
    if(!object->illuminates)
		return ERROR;
    object->light_on = on;
    return OK;
}

/*
 * @brief Obtiene el id del objeto
 *
 * @param object El puntero del objeto.
 * @return El id del objeto
 */
Id object_Get_Id(Object* object) {
    if (!object)
        return NO_ID;
    return object->id;
}

/*
 * @brief Obtiene el nombre del objeto
 *
 * @param object El puntero del objeto.
 * @return El nombre del objeto
 */
char* object_Get_Name(Object* object) {
    if (!object)
        return NULL;
    return object->name;
}

/*
 * @brief Obtiene la descripción grafica del objeto
 *
 * @param object El puntero del objeto.
 * @return La descripción grafica del objeto
 */
char* object_Get_Graphics(Object* object) {
    if (!object)
        return NULL;
    return object->graphics;
}

/*
 * @brief Obtiene la descripción del objeto
 *
 * @param object El puntero del objeto.
 * @return La descripción del objeto
 */
char* object_Get_Description(Object* object) {
    if (!object)
        return NULL;
    return object->desc;
}

/*
 * @brief Obtiene la descripción dos del objeto
 *
 * @param object El puntero del objeto.
 * @return La descripción del objeto
 */
char* object_Get_Description2(Object* object) {
    if (!object)
        return NULL;
    return object->desc2;
}

/*
 * @brief Obtiene la movibilidad del objeto
 *
 * @param object El puntero del objeto.
 * @return La movibilidad del objeto
 */
BOOL object_Get_Mobile(const Object *object) {
    if(!object)
        return FALSE;
    return object->mobile;
}

/*
 * @brief Obtiene si se ha movido el objeto
 *
 * @param object El puntero del objeto.
 * @return Si se ha movido o no el objeto
 */
BOOL object_Get_Moved(const Object *object) {
    if(!object)
        return FALSE;
    return object->moved;
}

/*
 * @brief Obtiene si se ha movido el objeto
 *
 * @param object El puntero del objeto.
 * @return Si se ha movido o no el objeto
 */
BOOL object_Get_Hidden(const Object *object) {
    if(!object)
        return FALSE;
    return object->hidden;
}

/*
 * @brief Obtiene si esta abierto el objeto
 *
 * @param object El puntero del objeto.
 * @return Si se ha abierto o no el link del objeto
 */
Id object_Get_Open(const Object *object){
    if(!object)
        return NO_ID;
    return object->open;
}

/*
 * @brief Obtiene si se ha iluminado el objeto
 *
 * @param object El puntero del objeto.
 * @return Si se ha iluminado o no el objeto
 */
BOOL object_Get_Illuminates(const Object *object) {
    if(!object)
        return FALSE;
    return object->illuminates;
}

/*
 * @brief Obtiene si se ha encendido el objeto
 *
 * @param object El puntero del objeto.
 * @return Si se ha encendido o no el objeto
 */
BOOL object_Get_Light(const Object *object) {
    if(!object)
        return FALSE;
    return object->light_on;
}
/*
 * @brief Imprime por pantalla el nombre del objeto y el id
 *
 * @param object El puntero del objeto.
 * @return Imprime por pantalla si OK y da ERROR si lo contrario
 */
STATUS object_print(Object* object) {
    int i = 0;

    if (!object)
        return ERROR;

    i = printf("Object Id: %ld, Object name: %s", object->id, object->name);
	i += printf("Description: %s\n", object->desc);
	i += printf("Alternative description: %s\n", object->desc2);

    if (i > 0)
        return OK;
    else
        return ERROR;
}