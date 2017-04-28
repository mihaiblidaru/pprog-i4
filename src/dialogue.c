#include <string.h>
#include "types.h"
#include "command.h"
#include "dialogue.h"
#include "game.h"
#include "string.h"
#include "space.h"
#include "link.h"
#include "game_management.h"
#include "object.h"
#include <stdlib.h>

struct _Dialogue{
    char last_text[WORD_SIZE];
    char text[WORD_SIZE];
};


BOOL dialogue_check_consecutive_error(Dialogue* d);

Dialogue* dialogue_ini(){
    Dialogue *d = NULL;
    
    if(!(d = calloc(1, sizeof(Dialogue))))
        return NULL;
    return d;    
}

void dialogue_destroy(Dialogue* d){
    if(d)
        free(d);
}

STATUS dialogue_set_text(Dialogue *d, char* txt){
    if(!d || !txt)
        return ERROR;
    
    strncpy(d->text, txt, WORD_SIZE);
    return OK;
}

char* dialogue_get_text(Dialogue * d){
    if(!d)
        return NULL;
    return d->text;
}

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
        strcat(d->text, space_get_description(space));
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

STATUS dialogue_unknown(Dialogue* d){
    if(!d)
        return ERROR;
    dialogue_set_text(d, "Esta no es una accion valida. Usa ""help"" para verlos comandos disponibles e intentalo de nuevo.");
    strcpy(d->last_text, d->text);
    return OK;
}

STATUS dialogue_dir(Dialogue* d){
    if(!d)
        return ERROR;
    dialogue_set_text(d, "Acabas de ver las conexiones de esta casilla. Si quieres volver a verlas usa el comando \"dir\"");
    strcpy(d->last_text, d->text);
    return OK;
    
}

STATUS dialogue_take(Dialogue* d, Object* object, char* name, TAKE_STATUS status){
    char aux[100] = "\0";
    if(!d)
        return ERROR;
    memset(d->text, 0, WORD_SIZE);
    if(status == TAKE_OK){
        strcat(d->text, "Te has llevado el objeto: ");
        strcat(d->text, object_Get_Name(object));
        strcat(d->text,". Para ver mas detalles usa inspect.");
    }else if(status == NOT_IN_SPACE || status == NO_OBJ){
        sprintf(aux,"Para llevarte un objeto(%s) tienes que estar en la misma casilla.", name);
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

STATUS dialogue_leave(Dialogue* d, Object*object, char* name, LEAVE_STATUS status){
    char aux[100] = "\0";
    if(!d)
        return ERROR;
    memset(d->text, 0, WORD_SIZE);
    if(status == LEAVE_OK){
        strcat(d->text, "Has dejado el objeto: ");
        strcat(d->text, object_Get_Name(object));
        strcat(d->text,". Para volver a cogerlo usa \"take\".");
    }else if(status == NOT_IN_INV){
        sprintf(aux,"Para dejar un objeto(%s) tiene que estar en tu inventario.", name);
        strcat(d->text, aux);
    }else if(status == GLOBAL_NO_ARGS){
        strcat(d->text, "Tienes que especificar el objeto que quieres dejar.");
    }
    dialogue_check_consecutive_error(d);
    strcpy(d->last_text, d->text);
    return OK;
}

STATUS dialogue_save(Dialogue * d, char* name, DIALOGUE_SAVE_STATUS status){
    char aux[100] = "\0";
    if(!d)
        return ERROR;
    memset(d->text, 0, WORD_SIZE);
    if(status == SAVE_SAVE_OK){
        strcat(d->text, "He ha guardado la partida con exito en: ");
        strcat(d->text, name);
        strcat(d->text,". Para cargar usa \"load\".");
    }else if(status == SAVE_PROTECTED_FILE){
        sprintf(aux,"No se puede guardar en \"%s\", es un archivo protegido del juego.", name);
        strcat(d->text, aux);
    }else if(status == SAVE_WRITE_FAILED){
        strcat(d->text, "No se ha podido guardar la partida. Tienes que especificar donde quieres guardar.");
    }
    
    dialogue_check_consecutive_error(d);
    strcpy(d->last_text, d->text);
    return OK;
}

STATUS dialogue_inspect(Dialogue* d, Object* object, Space* space, char* name, INSPECT_STATUS status){
     char aux[100] = "\0";
    if(!d)
        return ERROR;
    memset(d->text, 0, WORD_SIZE);
    
    if(strcmp(name, "space") == 0){
        strcat(d->text, "Acabas de ver los detalles de: ");
        strcat(d->text, space_get_name(space));
        strcat(d->text,". Para volver a verlos usa \"inspect\".");
    }else{
        if(status == INSPECT_OK){
            strcat(d->text, "Has inspeccionado el objeto: ");
            strcat(d->text, object_Get_Name(object));
            strcat(d->text,". Para volver sus detalles usa \"inspect\".");
        }else if(status == INSPECT_NO_OBJ){
            sprintf(aux,"Para inspecionar un objeto(%s) tiene que estar en tu inventario o en la casilla actual.", name);
            strcat(d->text, aux);
        }else if(status == GLOBAL_NO_ARGS){
            strcat(d->text, "Tienes que especificar lo que quieres inspeccinar.");
        }
    }
    
    dialogue_check_consecutive_error(d);
    strcpy(d->last_text, d->text);
    return OK;
}

STATUS dialogue_turn_on(Dialogue* d, Object*object, char* name, TURN_STATUS status){
    char aux[100] = "\0";
    if(!d)
        return ERROR;
    memset(d->text, 0, WORD_SIZE);
    if(status == TURN_OK){
        strcat(d->text, "Has encendido el objeto: ");
        strcat(d->text, object_Get_Name(object));
        strcat(d->text,". Para apagarlo usa \"turnoff\".");
    }else if(status == TURN_NOT_IN_INV){
        sprintf(aux,"Para encender un objeto(%s) tiene que estar en tu inventario.", name);
        strcat(d->text, aux);
    }else if(status == TURN_NO_LIGHT){
        sprintf(aux,"Este objeto(%s) no puede iluminar. No se puede apagar o encender", name);
        strcat(d->text, aux);
    }else if(status == TURN_ALREADY){
        sprintf(aux,"Este objeto(%s) ya esta encendido. No hace falta que lo enciendas de nuevo.", name);
        strcat(d->text, aux);
    }else if(status == GLOBAL_NO_ARGS){
        strcat(d->text, "Tienes que especificar el objeto que quieres encender.");
    }
    dialogue_check_consecutive_error(d);
    strcpy(d->last_text, d->text);
    return OK;
}

STATUS dialogue_turn_off(Dialogue* d, Object*object, char* name, TURN_STATUS status){
    char aux[100] = "\0";
    if(!d)
        return ERROR;
    memset(d->text, 0, WORD_SIZE);
    if(status == TURN_OK){
        strcat(d->text, "Has apagado el objeto: ");
        strcat(d->text, object_Get_Name(object));
        strcat(d->text,". Para encenderlo otra vez usa \"turnon\".");
    }else if(status == TURN_NOT_IN_INV){
        sprintf(aux,"Para apagar un objeto(%s) tiene que estar en tu inventario.", name);
        strcat(d->text, aux);
    }else if(status == TURN_NO_LIGHT){
        sprintf(aux,"Este objeto(%s) no puede iluminar. No se puede apagar o encender", name);
        strcat(d->text, aux);
    }else if(status == TURN_ALREADY){
        sprintf(aux,"Este objeto(%s) ya esta apagado. No puedes apagarlo dos veces.", name);
        strcat(d->text, aux);
    }else if(status == GLOBAL_NO_ARGS){
        strcat(d->text, "Tienes que especificar el objeto que quieres apagar.");
    }
    dialogue_check_consecutive_error(d);
    strcpy(d->last_text, d->text);
    return OK;
}

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