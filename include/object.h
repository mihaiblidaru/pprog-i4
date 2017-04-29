/** 
 * @brief Define la interfaz pública del TAD Objeto
 * 
 * @file object.h
 * @author Javier Bernardo
 * @version 1.0 
 * @date 31-01-2017
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

/**
 * @brief Definicion de la estructura objecto
 */
typedef struct _Object Object;

/**
 * @brief Reservamos memoria para un nuevo objeto.
 *
 * @return Devuelve el objeto creado
 */
Object* object_create();

/**
 * @brief Destruye un objeto
 * @date 12-12-2005
 * @param object El puntero del objeto.
 * @return Error si se ha hecho mal o Ok si se ha liberado correctamente.
 */
STATUS object_destroy(Object* object);

/**
 * @brief Pone el id del objeto
 *
 * @param object El puntero del objeto.
 * @param object_id Id que recibe para el objeto
 * @return El objeto con el nuevo id
 */
Object* object_Set_Id(Object* object, Id object_id);

/**
 * @brief Pone el nombre del objeto
 *
 * @param object El puntero del objeto.
 * @param name Nombre que recibe para el objeto
 * @return El objeto con el nuevo nombre
 */
Object* object_Set_Name(Object* object, char* name);

/**
 * @brief Pone la descripción  del objeto
 *
 * @param object El puntero del objeto.
 * @param description Descripcion  que recibe para el objeto
 * @return El objeto con la nueva descripción
 */
Object* object_Set_Description(Object* object, char* description);

/**
 * @brief Pone la descripción dos del objeto
 *
 * @param object El puntero del objeto.
 * @param desc2 Descripcion  que recibe para el objeto
 * @return El objeto con la nueva descripción
 */
Object* object_Set_Description2(Object* object, char *desc2);

/**
 * @brief Pone la disponibilidad de movimiento del objeto
 *
 * @param object El puntero del objeto.
 * @param mobile Estado que recibe para el objeto
 * @return Ok si se hace, ERROR en caso contrario
 */
STATUS object_Set_Mobile(Object* object, const BOOL mobile);

/**
 * @brief Pone si se ha mpvido el objeto
 *
 * @param object El puntero del objeto.
 * @param moved Estado que recibe para el objeto
 * @return Ok si se hace, ERROR en caso contrario
 */
STATUS object_Set_Moved(Object* object, const BOOL moved);

/**
 * @brief Pone la situacion del objeto, oculto o no oculto
 *
 * @param object El puntero del objeto.
 * @param hidden Estado que recibe para el objeto
 * @return Ok si se hace, ERROR en caso contrario
 */
STATUS object_Set_Hidden(Object* object, BOOL hidden);

/**
 * @brief Pone la situacion del link del objeto
 *
 * @param object El puntero del objeto.
 * @param open Estado que recibe para el objeto
 * @return Ok si se hace, ERROR en caso contrario
 */
STATUS object_Set_Open(Object* object, Id open); 

/**
 * @brief Pone la iluminacion del objeto
 *
 * @param object El puntero del objeto.
 * @param illuminates Estado que recibe para el objeto
 * @return Ok si se hace, ERROR en caso contrario
 */
STATUS object_Set_Illuminates(Object* object, BOOL illuminates);

/**
 * @brief Pone el encendido del objeto
 *
 * @param object El puntero del objeto.
 * @param on Estado que recibe para el objeto
 * @return Ok si se hace, ERROR en caso contrario
 */
STATUS object_Set_Light(Object* object, BOOL on);

/**
 * @brief Obtiene el id del objeto
 *
 * @param object El puntero del objeto.
 * @return El id del objeto
 */
Id object_Get_Id(Object* object);

/**
 * @brief Obtiene el nombre del objeto
 *
 * @param object El puntero del objeto.
 * @return El nombre del objeto
 */
char* object_Get_Name(Object* object);

/**
 * @brief Obtiene la descripción del objeto
 *
 * @param object El puntero del objeto.
 * @return La descripción del objeto
 */
char* object_Get_Description(Object* object);

/**
 * @brief Obtiene la descripción dos del objeto
 *
 * @param object El puntero del objeto.
 * @return La descripción del objeto
 */
char* object_Get_Description2(Object* object);

/**
 * @brief Obtiene la movibilidad del objeto
 *
 * @param object El puntero del objeto.
 * @return La movibilidad del objeto
 */
BOOL object_Get_Mobile(const Object *object);

/**
 * @brief Obtiene si se ha movido el objeto
 *
 * @param object El puntero del objeto.
 * @return Si se ha movido o no el objeto
 */
BOOL object_Get_Moved(const Object *object);

/**
 * @brief Obtiene si se ha movido el objeto
 *
 * @param object El puntero del objeto.
 * @return Si se ha movido o no el objeto
 */
BOOL object_Get_Hidden(const Object *object);

/**
 * @brief Obtiene si esta abierto el objeto
 *
 * @param object El puntero del objeto.
 * @return Si se ha abierto o no el link del objeto
 */
Id object_Get_Open(const Object *object);

/**
 * @brief Obtiene si se ha iluminado el objeto
 *
 * @param object El puntero del objeto.
 * @return Si se ha iluminado o no el objeto
 */
BOOL object_Get_Illuminates(const Object *object);

/**
 * @brief Obtiene si se ha encendido el objeto
 *
 * @param object El puntero del objeto.
 * @return Si se ha encendido o no el objeto
 */
BOOL object_Get_Light(const Object *object);
/**
 * @brief Imprime por pantalla el nombre del objeto y el id
 *
 * @param object El puntero del objeto.
 * @return Imprime por pantalla si OK y da ERROR si lo contrario
 */
STATUS object_print(Object* object);

Object* object_Set_Graphics(Object* object, char *graphics);

char* object_Get_Graphics(Object* object);

#endif