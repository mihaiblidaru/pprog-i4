/** 
 * @brief Implementa el interpreatador de comandos.
 *      Lee los comandos que introduce el usuario parseandolos al tipo de datos
 *      T_Command, para poder trabajar facilmente con estos comandos.
 * @file command.h
 * @author Profesores PPROG
 * @author Javier Bernardo y Mihai Blidaru
 * @version 3.0 
 * @date 09/03/2017
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

/**
 * @brief Extension del comando
 */
#define CMD_LENGHT 30

/**
 * @brief Definicion de la estructura del comando
 */
typedef struct _Command Command; /*!< Tad Comando. Gestiona la entrada de comandos en el juego */

/**
 * @brief Define los tipos de comandos que existen en el juego
 */
typedef enum enum_Command {
    NO_CMD = -1,            /*!< Sin Comando */
    UNKNOWN,                /*!< Comando desconocido */
    QUIT,                   /*!< Comando salir */
    TAKE,                   /*!< Comando coger */
    LEAVE,                  /*!< Comando dejar */
    ROLL,                   /*!< Comando lanzar */
    GO,                     /*!< Comando ir */
    INSPECT,             /*!< Comando inspeccionar */
    TURNON,                 /*!< Comando encender */
    TURNOFF,                 /*!< Comando apagar */
    OPEN,                    /*!< Comando abrir */
    SAVE,
    LOAD,
    DIR
} T_Command;

/**
 * @brief  Crea e inicializa una estructura tipo Command
 * @author Mihai Blidaru
 * @return Una estructura command inicializada o NULL si hay algun error.
 */
Command* Command_ini();


/**
 * @brief Libera memoria usada por una estructura Command
 * @author Mihai Blidaru
 * @param cmdManager La estructura command que se tiene que liberar
 * @return OK si se ha realizado correctamente o ERROR en caso contrario
 */
STATUS Command_destroy(Command* cmdManager);

/** 
 * @brief Guarda un comando en la estructura
 * @author Mihai Blidaru
 * @param cmdManager Una estructura tipo command
 * @param cmd El comando a guardar
 * @return OK si se ha guardado correctamente o error en caso contrario
 */
STATUS Command_set_cmd(Command* cmdManager, T_Command cmd);

/** 
 * @brief Guarda un parametro de un comando en la estructura en una posición dada
 * @author Mihai Blidaru
 * @param cmdManager Una estructura tipo command
 * @param arg El parametro a guardar
 * @param index La posición donde se quiere guardar el parametro
 * @return OK si se ha guardado correctamente o error en caso contrario
 */
STATUS Command_set_cmd_arg(Command* cmdManager, char* arg, int index);

/** 
 * @brief Devuelve el comando guardado en la estructura
 * @author Mihai Blidaru
 * @param cmdManager La estructura Command de la cual leer los datos
 * @return El comando guardado
 */
T_Command Command_get_cmd(Command* cmdManager);

/** @brief Devuelve un parametro del comando guardado en la estructura en una posición dada
 *  @author Mihai Blidaru
 *  @param cmdManager La estructura Command de la cual leer los datos
 *  @param index El indice del parametro que se quiere leer
 *  @return El parametro del comando guardado
 */
char* Command_get_cmd_arg(Command* cmdManager, int index);

/** 
 * @brief Limpia los datos de una estructura Command
 * @author Mihai Blidaru
 * @param cmdManager Una estructura Command
 * @return OK si se ha hecho correctamente o ERROR en caso contrario
 */
STATUS Command_clear(Command* cmdManager);

/** @brief Lee los comandos de introduce el usuario.
 * 
 *      Lee por teclado el comando que introduce el usuario y comprueba que esta
 *      en la lista de los comandos permitidos. Guarda en la estructura Command los
 *      datos introducidos: en cmd guarda el tipo de comando y en arg guarda el argumento
 *      que tiene un comando
 *  
 *  @author Profesores PPROG
 *  @author Javier Bernardo
 *  @param cmdManager Una estructura tipo Command donde guardar los datos leidos por teclado
 *  @return OK si ha leido bien el comando o ERROR en caso contrario
 */
STATUS get_user_input(Command* cmdManager);



#endif
