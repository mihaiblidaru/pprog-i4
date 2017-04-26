/**
 * @brief Implementa el interpreatador de comandos
 *      Lee los comandos que introduce el usuario parseandolos al tipo de datos
 *      T_Command, para poder trabajar facilmente con estos comandos.
 * 
 * @file command.c
 * @author Profesores PPROG
 * @author Javier Bernardo
 * @version 2.0 
 * @date 19-12-2014 
 * @copyright GNU Public License
 */


/*
 * Cabeceras Libc 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Cabeceras propias
 */
#include "command.h"

/**
 * @cond
 * Longitud maxima del comando 
 */
#define CMD_LENGHT 30
/**
 * Numero maximo de comandos 
 */
#define N_CMD 14

/**
 * Representacion como cadena de los comandos
 */
char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Quit", "Take", "Leave", "Roll", "Go", "Inspect", "Turn On", "Turn Off", "Open", "Save", "Load", "Dir"};

/**
 * @brief Estructura del comando
 * 
 * Nueva estructura para guardar comandos.
 * Permite guardar el tipo de comando
 * y un parametro de ese comando.
 * 
 * Usado en funciones pick y 
 * @private
 */
struct _Command {
    T_Command cmd;  /*!< Comando introducido */
    char arg[4][20];   /*!< Argumento del comando */
};

/**
 * @endcond
 */
/* @brief  Crea e inicializa una estructura tipo Command
 * @author Mihai Blidaru
 * @return Una estructura command inicializada o NULL si hay algun error.
 */
Command* Command_ini() {
    Command* newCmdManager = NULL;
    if (!(newCmdManager = calloc(1, sizeof (Command))))
        return NULL;
    newCmdManager->cmd = NO_CMD;
    return newCmdManager;
}

/* @brief Libera memoria usada por una estructura Command
 * @author Mihai Blidaru
 * @param cmdManager La estructura command que se tiene que liberar
 * @return OK si se ha realizado correctamente o ERROR en caso contrario
 */
STATUS Command_destroy(Command* cmdManager) {
    if (!cmdManager)
        return ERROR;

    free(cmdManager);
    return OK;
}


/* @brief Guarda un comando en la estructura
 * @author Mihai Blidaru
 * @param cmdManager Una estructura tipo command
 * @param cmd El comando a guardar
 * @return OK si se ha guardado correctamente o error en caso contrario
 */
STATUS Command_set_cmd(Command* cmdManager, T_Command cmd) {
    if (!cmdManager || cmd < NO_CMD || cmd > DIR)
        return ERROR;

    cmdManager->cmd = cmd;

    return OK;
}

/* 
 * @brief Guarda el parametro de un comando en la estructura
 * @author Mihai Blidaru
 * @param cmdManager Una estructura tipo command
 * @param arg El parametro a guardar
 * @return OK si se ha guardado correctamente o error en caso contrario
 */
STATUS Command_set_cmd_arg(Command* cmdManager, char* arg, int index) {
    if (!cmdManager || !arg || index > 3 || index < 0)
        return ERROR;

    strcpy(cmdManager->arg[index], arg);

    return OK;
}


/* 
 * @brief Devuelve el comando guardado en la estructura
 * @author Mihai Blidaru
 * @param cmdManager La estructura Command de la cual leer los datos
 * @return El comando guardado
 */
T_Command Command_get_cmd(Command* cmdManager) {
    if (!cmdManager)
        return UNKNOWN;

    return cmdManager->cmd;
}

/*
 * @brief Devuelve el parametro del comando guardado en la estructura
 * @author Mihai Blidaru
 * @param cmdManager La estructura Command de la cual leer los datos
 * @return El parametro del comando guardado
 */
char* Command_get_cmd_arg(Command* cmdManager, int index) {
    if (!cmdManager)
        return NULL;

    return cmdManager->arg[index];
}

/* 
 * @brief Limpia los datos de una estructura Command
 * @author Mihai Blidaru
 * @param cmdManager Una estructura Command
 * @return OK si se ha hecho correctamente o ERROR en caso contrario
 */
STATUS Command_clear(Command* cmdManager) {
    int i = 0;
    if (!cmdManager)
        return ERROR;

    cmdManager->cmd = NO_CMD;
    for(i=0; i < 4;i++){
        strcpy(cmdManager->arg[i], "\0");      
    }
    
    return OK;
}

/* @brief Lee los comandos de introduce el usuario.
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
STATUS get_user_input(Command* cmdManager) {
    int i;
    T_Command cmd = UNKNOWN;
    char input[CMD_LENGHT] = "";
    char command[CMD_LENGHT] = "";
    char* toks = NULL;
    if (!cmdManager)
        return ERROR;

    if (fgets(input, CMD_LENGHT, stdin)) {
        if (strlen(input) > 0) {
            /* Borra el ultimo caracter del input (\n)*/
            if(input[strlen(input) - 1] == '\n')
                input[strlen(input) - 1] = 0;


            /* Separa el input en 2 trozos */
            if ((toks = strtok(input, " ")))
                strcpy(command, toks);
            for(i = 0; (i < 4) && (toks = strtok(NULL, " ")) != NULL;i++){
                Command_set_cmd_arg(cmdManager, toks, i);                
            }
            

            if (!strncmp(command, "q", CMD_LENGHT) || !strncmp(command, "quit", CMD_LENGHT)) {
                cmd = QUIT;
            } else if (!strncmp(command, "t", CMD_LENGHT) || !strncmp(command, "take", CMD_LENGHT)) {
                cmd = TAKE;
            } else if (!strncmp(command, "l", CMD_LENGHT) || !strncmp(command, "leave", CMD_LENGHT)) {
                cmd = LEAVE;
            } else if (!strncmp(command, "r", CMD_LENGHT) || !strncmp(command, "roll", CMD_LENGHT)) {
                cmd = ROLL;
            } else if (!strncmp(command, "g", CMD_LENGHT) || !strncmp(command, "go", CMD_LENGHT)) {
                cmd = GO;
            } else if (!strncmp(command, "i", CMD_LENGHT) || !strncmp(command, "inspect", CMD_LENGHT)) {
                cmd = INSPECT;
            } else if (!strncmp(command, "turnon", CMD_LENGHT)) {
                cmd = TURNON;
            } else if (!strncmp(command, "turnoff", CMD_LENGHT)) {
                cmd = TURNOFF;
            } else if (!strncmp(command, "open", CMD_LENGHT)) {
                cmd = OPEN;
            } else if (!strncmp(command, "save", CMD_LENGHT)) {
                cmd = SAVE;
            } else if (!strncmp(command, "load", CMD_LENGHT)) {
                cmd = LOAD;
            }else if (!strncmp(command, "dir", CMD_LENGHT)) {
                cmd = DIR;
            } else {
                cmd = UNKNOWN;
            }
        } else {
            cmd = UNKNOWN;
        }
    }

    Command_set_cmd(cmdManager, cmd);

    return OK;
}

