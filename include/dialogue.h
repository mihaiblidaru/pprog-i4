/** 
 * @brief Implementa el dialogo del juego.
 *
 * @file dialogue.h
 * @author Profesores PPROG
 * @author Mihai Blidaru
 * @author Sandra Benítez
 * @version 3.0 
 * @date 09/03/2017
 * @copyright GNU Public License
 */

#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "space.h"
#include "link.h"
#include "object.h"
/**
 * Codigo de error global para acciones a los que no se han pasado los argumentos necesarios
 */
#define GLOBAL_NO_ARGS -20
/**
 * Declaración del tipo dialogo 
 */
typedef struct _Dialogue Dialogue;

/**
 * @brief Codigos de estado del comando TAKE
 */
typedef enum{
    NO_OBJ,
    NOT_IN_SPACE,
    NOT_MOBILE,
    INVENTORY_FULL,
    TAKE_OK
}TAKE_STATUS;

/**
 * @brief Codigos de estado del comando LEAVE
 */
typedef enum{
    NOT_IN_INV,
    LEAVE_OK
}LEAVE_STATUS;

/**
 * @brief Codigos de estado del comando SAVE
 */
typedef enum {
    SAVE_PROTECTED_FILE,       /*!< EL archivo donde se quiere guardar es un archivo protegido */
    SAVE_SAVE_OK,              /*!< Se ha gaurdado todo sin problemas */
    SAVE_WRITE_FAILED         /*!< No se puede escribir en ese archivo */
} DIALOGUE_SAVE_STATUS;

/**
 * @brief Codigos de estado del comando INSPECT
 */
typedef enum{
    INSPECT_NO_OBJ,
    INSPECT_OK
}INSPECT_STATUS;

/**
 * @brief Codigos de estado de los comandos TURNON TURNOFF
 */
typedef enum{
    TURN_NOT_IN_INV,
    TURN_NO_LIGHT,
    TURN_ALREADY,
    TURN_OK
}TURN_STATUS;

/**
 * @brief Codigos de estado del comando LOAD
 */
typedef enum{
    LOAD_OK,
    LOAD_ERROR
}DIALOGUE_LOAD_STATUS;

/**
 * @brief Codigos de idenficación de las reglas
 */
typedef enum{
    NO_RULE,
    LIGHT_OBJECT,
    LIGHT_SPACE,
    HIDE_OBJECT,
    LOSE_OBJECT,
    CLOSE_LINK,
    CHANGE_LAST_LINK
}GAME_RULES_LIST;

/**
 * @brief Codigos de estado del comando ATTACK
 */
typedef enum{
    NOTHING_TO_ATTACK,
    BOSS1_OK,
    BOSS2_OK,
    WRONG_WEAPON
}ATTACK_STATUS;

/**
 * @brief Codigos de estado del comando OPEN
 */
typedef enum{
    WRONG_SYNTAX,
    NO_OBJECT,
    NO_LINK,
    NOT_SAME_ID,
    OPEN_OK
}OPEN_STATUS;


/**
 * @brief Inicializa un modulo dialogo
 * @author Javier Bernardo
 * @return Un dialogo inicializado
 */
Dialogue* dialogue_ini();

/**
 * @brief Libera la memoria usasa por un dialogo
 * @author Javier Bernardo
 * @param d El dialogo que se quiere destruir
 */
void dialogue_destroy(Dialogue* d);

/**
 * @brief Devuelve el texto del dialogo
 * @param d El dialogo del que se quiere leer el texto
 * @return El texto del dialogo
 */
char* dialogue_get_text(Dialogue * d);

/**
 * @brief Contruye el texto del dialogo para el comando GO
 * @param d Una estructura dialogo
 * @param direction La direccion en la que se quiere mover
 * @param space La casilla destino
 * @param status Si se ha llevado a cabo con exito o no
 * @param dir_name la dirrecion introducida por teclado
 * @param link El enlace por el que se quiere pasar
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_go(Dialogue*d, DIRECTION direction, Space* space, STATUS status, char* dir_name, Link* link);

/**
 * @brief Contruye el texto del dialogo para comandos desconocidos
 * @param d Una estructura dialogo
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_unknown(Dialogue* d);

/**
 * @brief Contruye el texto del dialogo para el comando DIR
 * @param d Una estructura dialogo
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_dir(Dialogue* d);

/**
 * @brief Contruye el texto del dialogo para el comando TAKE
 * @param d Una estructura dialogo
 * @param object El objeto que se quiere llevar si existe
 * @param name El nombre introducido por teclado
 * @param status El codigo de error del comando
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_take(Dialogue* d, Object* object, char* name, TAKE_STATUS status);

/**
 * @brief Contruye el texto del dialogo para el comando LEAVE
 * @param d Una estructura dialogo
 * @param object El objeto que se quiere dejar si existe
 * @param name El nombre introducido por teclado
 * @param status El codigo de error del comando
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_leave(Dialogue* d, Object*object, char* name, LEAVE_STATUS status);

/**
 * @brief Contruye el texto del dialogo para el comando SAVE
 * @param d Una estructura dialogo
 * @param name El nombre del ficheri donde se quiere guardar
 * @param status El codigo de error del comando
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_save(Dialogue * d, char* name, DIALOGUE_SAVE_STATUS status);

/**
 * @brief Contruye el texto del dialogo para el comando LOAD
 * @param d Una estructura dialogo
 * @param name El nombre del fichero desde el cual se quiere cargar
 * @param status El codigo de error del comando
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_load(Dialogue *d, char* name, DIALOGUE_LOAD_STATUS status);

/**
 * @brief Contruye el texto del dialogo para el comando ATTACK
 * @param d Una estructura dialogo
 * @param status El codigo de error del comando
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_attack(Dialogue* d, ATTACK_STATUS status);

/**
 * @brief Contruye el texto del dialogo para el comando TAKE
 * @param d Una estructura dialogo
 * @param object El objeto que se quiere inspeccionar si existe
 * @param space El espacio que se quiere inspeccionar si existe
 * @param name El nombre introducido por teclado
 * @param status El codigo de error del comando
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_inspect(Dialogue* d, Object* object, Space* space, char* name, INSPECT_STATUS status);

/**
 * @brief Contruye el texto del dialogo para el comando TAKE
 * @param d Una estructura dialogo
 * @param objName Nombre del objeto con el que se quiere abrir
 * @param linkName Nombre del link que se quiere abris
 * @param status Codigo de error de la operacion
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_open(Dialogue* d, char* objName, char* linkName, OPEN_STATUS status);

/**
 * @brief Contruye el texto del dialogo para el comando TURN_ON
 * @param d Una estructura dialogo
 * @param object El objeto que se quiere encender
 * @param name El nombre introducido por teclado
 * @param status El codigo de error del comando
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_turn_on(Dialogue* d, Object*object, char* name, TURN_STATUS status);

/**
 * @brief Contruye el texto del dialogo para el comando TURN_ON
 * @param d Una estructura dialogo
 * @param object El objeto que se quiere apagar
 * @param name El nombre introducido por teclado
 * @param status El codigo de error del comando
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_turn_off(Dialogue* d, Object*object, char* name, TURN_STATUS status);

/**
 * @brief Contruye el texto del dialogo para el comando HELP
 * @param d Una estructura dialogo
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_help(Dialogue *d);

/**
 * @brief Contruye el texto del dialogo para las reglas dej juego
 * @param d Una estructura dialogo
 * @param rule Codigo de la regla que se ha ejecutado
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_game_rule(Dialogue *d, int rule);

#endif