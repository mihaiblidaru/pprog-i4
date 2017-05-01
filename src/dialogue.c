/**
 * @brief Implementa Los dialogos del juego
 * 
 * @file dialogue.c
 * @author Mihai Blidaru
 * @author Sandra Benítez
 * @version 2.0 
 * @date 19-12-2014 
 * @copyright GNU Public License
 */

#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "command.h"
#include "dialogue.h"
#include "game.h"
#include "string.h"
#include "space.h"
#include "link.h"
#include "game_management.h"
#include "object.h"

#include "game_rules.h"

struct _Dialogue{
    char last_text[WORD_SIZE];
    char text[WORD_SIZE];
};
/* Funciones privadas */
BOOL dialogue_check_consecutive_error(Dialogue* d);/*!< @private */
STATUS dialogue_set_text(Dialogue *d, char* txt); /*!< @private */

/*
 * @brief Inicializa un modulo dialogo
 * @return Un dialogo inicializado
 */
Dialogue* dialogue_ini(){
    Dialogue *d = NULL;
    
    if(!(d = calloc(1, sizeof(Dialogue))))
        return NULL;
    return d;    
}
/*
 * @brief Libera la memoria usasa por un dialogo
 * @author Javier Bernardo
 * @param d El dialogo que se quiere destruir
 */
void dialogue_destroy(Dialogue* d){
    if(d)
        free(d);
}

/*
 * @brief Pone el texto de un dialogo
 * @param d Una estructura dialogo
 * @param txt El texto que se le quiere poner
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_set_text(Dialogue *d, char* txt){
    if(!d || !txt)
        return ERROR;
    
    strncpy(d->text, txt, WORD_SIZE);
    return OK;
}

/*
 * @breif Devuelve el texto del dialogo
 * @param d El dialogo del que se quiere leer el texto
 * @return El texto del dialogo
 */
char* dialogue_get_text(Dialogue * d){
    if(!d)
        return NULL;
    return d->text;
}

/*
 * @brief Contruye el texto del dialogo para el comando GO
 * @param d Una estructura dialogo
 * @param direction La direccion en la que se quiere mover
 * @param space La casilla destino
 * @param status Si se ha llevado a cabo con exito o no
 * @param dir_name la dirrecion introducida por teclado
 * @param link El enlace por el que se quiere pasar
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_go(Dialogue*d, DIRECTION direction, Space* space, STATUS status, char* dir_name, Link* link){
    if(!d || !space)
        return ERROR;
    
    memset(d->text, 0, WORD_SIZE);
    
    if(status == OK){
        strcat(d->text, "Has conseguido ir ");
        if(direction == SOUTH){
            strcat(d->text, "al sur");
        }else if(direction == NORTH){
            strcat(d->text, "al norte");
        }else if(direction == EAST){
            strcat(d->text, "al este");
        }else if(direction == WEST){
            strcat(d->text, "al oeste");
        }else if(direction == UP){
            strcat(d->text, "arriba");
        }else if(direction == DOWN){
            strcat(d->text, "abajo");
        }
        strcat(d->text, ". Ahora estas en ");
        strcat(d->text, space_get_name(space));
        strcat(d->text, ": ");
        if(space_get_iluminated(space)){
            strcat(d->text, space_get_long_description(space));
        }else{
            strcat(d->text, space_get_description(space));
        }
        strcpy(d->last_text, d->text);
    }else{
        if(direction != UNKNOWN_DIRECTION){
            strcat(d->text, "No puedes ir ");
            if(direction == SOUTH){
                strcat(d->text, "al sur.");
            }else if(direction == NORTH){
                strcat(d->text, "al norte.");
            }else if(direction == EAST){
                strcat(d->text, "al este.");
            }else if(direction == WEST){
                strcat(d->text, "al oeste.");
            }else if(direction == UP){
                strcat(d->text, "arriba.");
            }else if(direction == DOWN){
                strcat(d->text, "abajo.");
            }
            if(link == NULL){
                strcat(d->text, " No hay nada en esa direction.");
            }else if(link && link_get_state(link) == CLOSED){
                strcat(d->text, " Ese enlace esta bloqueado. Busca el objeto que sirve para abrirlo.");
            }
        }else{
            if(strlen(dir_name)){
                sprintf(d->text, "No he entendido a donde quieres ir: %s. Para ver la ayuda de los comandos usa ""help"".", dir_name);
            }else{
                sprintf(d->text, "No he entendido a donde quieres ir. Para ver la ayuda de los comandos usa ""help"".");
            }
            
        }
        
        dialogue_check_consecutive_error(d);
        strcpy(d->last_text, d->text);
    }
    
    return OK;
}

/*
 * @brief Contruye el texto del dialogo para comandos desconocidos
 * @param d Una estructura dialogo
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_unknown(Dialogue* d){
    if(!d)
        return ERROR;
    dialogue_set_text(d, "Esta no es una accion valida. Usa \"]help}\" para verlos comandos disponibles e intentalo de nuevo.");
    strcpy(d->last_text, d->text);
    return OK;
}

/*
 * @brief Contruye el texto del dialogo para el comando DIR
 * @param d Una estructura dialogo
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_dir(Dialogue* d){
    if(!d)
        return ERROR;
    dialogue_set_text(d, "Acabas de ver las conexiones de esta casilla. Si quieres volver a verlas usa el comando \"]dir}\"");
    strcpy(d->last_text, d->text);
    return OK;
}

/*
 * @brief Contruye el texto del dialogo para el comando TAKE
 * @param d Una estructura dialogo
 * @param object El objeto que se quiere llevar si existe
 * @param name El nombre introducido por teclado
 * @param status El codigo de error del comando
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_take(Dialogue* d, Object* object, char* name, TAKE_STATUS status){
    char aux[100] = "\0";
    if(!d)
        return ERROR;
    memset(d->text, 0, WORD_SIZE);
    if(status == TAKE_OK){
        strcat(d->text, "Te has llevado el objeto:[");
        strcat(d->text, object_Get_Name(object));
        strcat(d->text,"}. Para ver mas detalles usa inspect.");
    }else if(status == NOT_IN_SPACE || status == NO_OBJ){
        sprintf(aux,"Para llevarte un objeto([%s}) tienes que estar en la misma casilla.", name);
        strcat(d->text, aux);
    }else if(status == NOT_MOBILE){    
        strcat(d->text, "Ese objeto no se puede mover, no te lo puedes llevar.");
    }else if(status == INVENTORY_FULL){
        strcat(d->text, "Tienes el inventario lleno, no puedes llevar mas objetos.");
    }else if(status == GLOBAL_NO_ARGS){
        strcat(d->text, "Tienes que especificar el objeto que quieres llevarte.");
    }
    dialogue_check_consecutive_error(d);
    strcpy(d->last_text, d->text);
    return OK;
}
/*
 * @brief Contruye el texto del dialogo para el comando LEAVE
 * @param d Una estructura dialogo
 * @param object El objeto que se quiere dejar si existe
 * @param name El nombre introducido por teclado
 * @param status El codigo de error del comando
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_leave(Dialogue* d, Object*object, char* name, LEAVE_STATUS status){
    char aux[100] = "\0";
    if(!d)
        return ERROR;
    memset(d->text, 0, WORD_SIZE);
    if(status == LEAVE_OK){
        strcat(d->text, "Has dejado el objeto:[");
        strcat(d->text, object_Get_Name(object));
        strcat(d->text,"}. Para volver a cogerlo usa \"]take}\".");
    }else if(status == NOT_IN_INV){
        sprintf(aux,"Para dejar un objeto([%s}) tiene que estar en tu inventario.", name);
        strcat(d->text, aux);
    }else if(status == GLOBAL_NO_ARGS){
        strcat(d->text, "Tienes que especificar el objeto que quieres dejar.");
    }
    dialogue_check_consecutive_error(d);
    strcpy(d->last_text, d->text);
    return OK;
}

/*
 * @brief Contruye el texto del dialogo para el comando SAVE
 * @param d Una estructura dialogo
 * @param name El nombre del ficheri donde se quiere guardar
 * @param status El codigo de error del comando
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_save(Dialogue * d, char* name, DIALOGUE_SAVE_STATUS status){
    char aux[100] = "\0";
    if(!d)
        return ERROR;
    memset(d->text, 0, WORD_SIZE);
    if(status == SAVE_SAVE_OK){
        strcat(d->text, "He ha guardado la partida con exito en:[");
        strcat(d->text, name);
        strcat(d->text,"}. Para cargar usa \"]load}\".");
    }else if(status == SAVE_PROTECTED_FILE){
        sprintf(aux,"No se puede guardar en \"[%s}\", es un archivo protegido del juego.", name);
        strcat(d->text, aux);
    }else if(status == SAVE_WRITE_FAILED){
        strcat(d->text, "No se ha podido guardar la partida. Tienes que especificar donde quieres guardar.");
    }
    
    dialogue_check_consecutive_error(d);
    strcpy(d->last_text, d->text);
    return OK;
}

/*
 * @brief Contruye el texto del dialogo para el comando LOAD
 * @param d Una estructura dialogo
 * @param name El nombre del fichero desde el cual se quiere cargar
 * @param status El codigo de error del comando
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_load(Dialogue *d, char* name, DIALOGUE_LOAD_STATUS status){
    char aux[100] = "\0";
    if(!d)
        return ERROR;
    memset(d->text, 0, WORD_SIZE);
    if(status == LOAD_OK){
        strcat(d->text, "He ha cargado la partida con exito desde:[");
        strcat(d->text, name);
        strcat(d->text,"}. Para guardar partidas luego usa \"]save}\".");
    }else if(status == LOAD_ERROR){
        sprintf(aux,"No se puede cargar la partida desde \"[%s}\".", name);
        strcat(d->text, aux);
    }else if(status == GLOBAL_NO_ARGS){
        strcat(d->text, "No se ha podido cargar la partida. Tienes que especificar desde donde quieres cargar.");
    }

    dialogue_check_consecutive_error(d);
    strcpy(d->last_text, d->text);
    return OK;
}

/*
 * @brief Contruye el texto del dialogo para el comando ATTACK
 * @param d Una estructura dialogo
 * @param status El codigo de error del comando
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_attack(Dialogue* d, ATTACK_STATUS status){
    if(!d)
        return ERROR;
    memset(d->text, 0, WORD_SIZE);
    if(status == NOTHING_TO_ATTACK){
        strcat(d->text, "No hay nada que atacar aqui. Solo puedes atacar en casillas donde hay enemigos");
    }else if(status == BOSS1_OK){
        sprintf(d->text, "Parece que has \"derrotado\" al guardian y tienes el camino despejado. La proxima vez no tendras tanta suerte.");
    }else if(status == BOSS2_OK){
        sprintf(d->text, "Parece que has derrotado al protector del tesoro. Regoce tu premio!!!");
    }else if(status == WRONG_WEAPON){
        sprintf(d->text, "El enemigo es imune cualquier arma que tengas ahora. Busca otro arma y vuelve aqui para luchar.");
    }
    
    dialogue_check_consecutive_error(d);
    strcpy(d->last_text, d->text);
    return OK;
}

/*
 * @brief Contruye el texto del dialogo para el comando TAKE
 * @param d Una estructura dialogo
 * @param object El objeto que se quiere inspeccionar si existe
 * @param space El espacio que se quiere inspeccionar si existe
 * @param name El nombre introducido por teclado
 * @param status El codigo de error del comando
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_inspect(Dialogue* d, Object* object, Space* space, char* name, INSPECT_STATUS status){
     char aux[100] = "\0";
    if(!d)
        return ERROR;
    memset(d->text, 0, WORD_SIZE);
    
    if(strcmp(name, "space") == 0){
        strcat(d->text, "Acabas de ver los detalles de:[");
        strcat(d->text, space_get_name(space));
        strcat(d->text,"}. Para volver a verlos usa \"]inspect}\".");
    }else{
        if(status == INSPECT_OK){
            strcat(d->text, "Has inspeccionado el objeto: ");
            strcat(d->text, object_Get_Name(object));
            strcat(d->text,". Para volver sus detalles usa \"]inspect}\".");
        }else if(status == INSPECT_NO_OBJ){
            sprintf(aux,"Para inspecionar un objeto([%s}) tiene que estar en tu inventario o en la casilla actual.", name);
            strcat(d->text, aux);
        }else if(status == GLOBAL_NO_ARGS){
            strcat(d->text, "Tienes que especificar lo que quieres inspeccinar.");
        }
    }
    
    dialogue_check_consecutive_error(d);
    strcpy(d->last_text, d->text);
    return OK;
}

/*
 * @brief Contruye el texto del dialogo para el comando TAKE
 * @param d Una estructura dialogo
 * @param objName Nombre del objeto con el que se quiere abrir
 * @param linkName Nombre del link que se quiere abris
 * @param status Codigo de error de la operacion
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_open(Dialogue* d, char* objName, char* linkName, OPEN_STATUS status){
    if(!d)
        return ERROR;
    
    if(status == WRONG_SYNTAX){
        sprintf(d->text, "No he entendido lo quieres abrir y con que objeto. Prueba otra vez. ");
    }else if(status == NO_OBJECT){
        sprintf(d->text, "Para abrir algo tienes que tener el objeto en el inventario (%s). ", objName);
    }else if(status == NO_OBJECT){
        sprintf(d->text, "Para abrir un enlace tiene que pertenecer a esta casilla. ");
    }else if(status == NOT_SAME_ID){
        sprintf(d->text, "No puedes abrir[%s}usando[%s}. ", linkName, objName);
    }else if(status == OPEN_OK){
        sprintf(d->text, "Ya puedes pasar por[%s}. ", linkName);
    }
    
    dialogue_check_consecutive_error(d);
    strcpy(d->last_text, d->text);
    return OK;
}

/*
 * @brief Contruye el texto del dialogo para el comando TURN_ON
 * @param d Una estructura dialogo
 * @param object El objeto que se quiere encender
 * @param name El nombre introducido por teclado
 * @param status El codigo de error del comando
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_turn_on(Dialogue* d, Object*object, char* name, TURN_STATUS status){
    char aux[100] = "\0";
    if(!d)
        return ERROR;
    memset(d->text, 0, WORD_SIZE);
    if(status == TURN_OK){
        strcat(d->text, "Has encendido el objeto:[");
        strcat(d->text, object_Get_Name(object));
        strcat(d->text,"}. Para apagarlo usa \"]turnoff}\".");
    }else if(status == TURN_NOT_IN_INV){
        sprintf(aux,"Para encender un objeto([%s}) tiene que estar en tu inventario.", name);
        strcat(d->text, aux);
    }else if(status == TURN_NO_LIGHT){
        sprintf(aux,"Este objeto([%s}) no puede iluminar. No se puede apagar o encender", name);
        strcat(d->text, aux);
    }else if(status == TURN_ALREADY){
        sprintf(aux,"Este objeto([%s}) ya esta encendido. No hace falta que lo enciendas de nuevo.", name);
        strcat(d->text, aux);
    }else if(status == GLOBAL_NO_ARGS){
        strcat(d->text, "Tienes que especificar el objeto que quieres encender.");
    }
    dialogue_check_consecutive_error(d);
    strcpy(d->last_text, d->text);
    return OK;
}

/*
 * @brief Contruye el texto del dialogo para el comando TURN_ON
 * @param d Una estructura dialogo
 * @param object El objeto que se quiere apagar
 * @param name El nombre introducido por teclado
 * @param status El codigo de error del comando
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_turn_off(Dialogue* d, Object*object, char* name, TURN_STATUS status){
    char aux[100] = "\0";
    if(!d)
        return ERROR;
    memset(d->text, 0, WORD_SIZE);
    if(status == TURN_OK){
        strcat(d->text, "Has apagado el objeto:[");
        strcat(d->text, object_Get_Name(object));
        strcat(d->text,"}. Para encenderlo otra vez usa \"]turnon}\".");
    }else if(status == TURN_NOT_IN_INV){
        sprintf(aux,"Para apagar un objeto([%s}) tiene que estar en tu inventario.", name);
        strcat(d->text, aux);
    }else if(status == TURN_NO_LIGHT){
        sprintf(aux,"Este objeto([%s}) no puede iluminar. No se puede apagar o encender", name);
        strcat(d->text, aux);
    }else if(status == TURN_ALREADY){
        sprintf(aux,"Este objeto([%s}) ya esta apagado. No puedes apagarlo dos veces.", name);
        strcat(d->text, aux);
    }else if(status == GLOBAL_NO_ARGS){
        strcat(d->text, "Tienes que especificar el objeto que quieres apagar.");
    }
    dialogue_check_consecutive_error(d);
    strcpy(d->last_text, d->text);
    return OK;
}

/*
 * @brief Contruye el texto del dialogo para el comando HELP
 * @param d Una estructura dialogo
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_help(Dialogue *d){
    if(!d)
        return ERROR;
    dialogue_set_text(d, "Acabas de ver la pantalla de ayuda. Si se te olvida algun comando siempre puedes volver a mirar con \"]help}\".");
    strcpy(d->last_text, d->text);
    return OK;
}

/*
 * @brief Contruye el texto del dialogo para las reglas dej juego
 * @param d Una estructura dialogo
 * @param rule Codigo de la regla que se ha ejecutado
 * @return OK si el texto se ha asignado con exito o ERROR en caso contrario
 */
STATUS dialogue_game_rule(Dialogue *d, int rule){
    strcat(d->text, "!!ATENCION!! ");
    if(rule == LIGHT_OBJECT){
        strcat(d->text, "Hay un objeto que se enciende/apaga solo. A lo mejor hay fantasmas aqui");
    }else if(rule == LIGHT_SPACE){
        strcat(d->text, "Alguien esta jugando con las luces. A veces la momia hace eso para asustar a los visitantes.");
    }else if(rule == HIDE_OBJECT){
        strcat(d->text, "Un objeto acaba de desaparecer, a ver si lo puedes encontrar");
    }else if(rule == LOSE_OBJECT){
        strcat(d->text, "Se te acaba de perder un objeto. A ver si para la proxima aventura te compras otra mochila");
    }else if(rule == CHANGE_LAST_LINK){
        strcat(d->text, "La entrada a la sala del tesoro ha desaparecido. Encuentrala");
    }else if(rule == CLOSE_LINK){
        strcat(d->text, "Algun enlace se esta cerrando/abriendo solo, las fantasmas quieren asustarte.");
    }
    return OK;
}

/*
 * @brief Comprueba si se han producido 2 errores consecutivos en el mismo comando
 * @param d Una estructura dialogo
 * @return TRUE si se ha producido un error 2 veces. FALSE en caso contrario
 */
BOOL dialogue_check_consecutive_error(Dialogue* d){
    int len = 0;
    if(!d)
        return FALSE;
    len = strlen(d->text);

    if(strncmp(d->text, d->last_text, len) == 0){
        strcat(d->text, " Ya has probado esto antes y no ha funcionado.");
        return TRUE;
    }
    return FALSE;
}
