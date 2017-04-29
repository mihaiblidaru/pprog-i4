#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "space.h"
#include "link.h"
#include "object.h"

#define GLOBAL_NO_ARGS -20
typedef struct _Dialogue Dialogue;

typedef enum{
    NO_OBJ,
    NOT_IN_SPACE,
    NOT_MOBILE,
    INVENTORY_FULL,
    TAKE_OK
}TAKE_STATUS;

typedef enum{
    NOT_IN_INV,
    LEAVE_OK
}LEAVE_STATUS;

typedef enum {
    SAVE_PROTECTED_FILE,       /*!< EL archivo donde se quiere guardar es un archivo protegido */
    SAVE_SAVE_OK,              /*!< Se ha gaurdado todo sin problemas */
    SAVE_WRITE_FAILED         /*!< No se puede escribir en ese archivo */
} DIALOGUE_SAVE_STATUS;

typedef enum{
    INSPECT_NO_OBJ,
    INSPECT_OK
}INSPECT_STATUS;

typedef enum{
    TURN_NOT_IN_INV,
    TURN_NO_LIGHT,
    TURN_ALREADY,
    TURN_OK
}TURN_STATUS;

typedef enum{
    NO_RULE,
    LIGHT_OBJECT,
    LIGHT_SPACE,
    HIDE_OBJECT,
    LOSE_OBJECT,
    CHANGE_LAST_LINK
}GAME_RULES_LIST;

Dialogue* dialogue_ini();
void dialogue_destroy(Dialogue* d);

char* dialogue_get_text(Dialogue * d);
STATUS dialogue_go(Dialogue*d, DIRECTION direction, Space* space, STATUS status, char* dir_name, Link* link);
STATUS dialogue_unknown(Dialogue* d);
STATUS dialogue_dir(Dialogue* d);
STATUS dialogue_take(Dialogue* d, Object* object, char* name, TAKE_STATUS status);
STATUS dialogue_leave(Dialogue* d, Object*object, char* name, LEAVE_STATUS status);
STATUS dialogue_turn_on(Dialogue* d, Object*object, char* name, TURN_STATUS status);
STATUS dialogue_turn_off(Dialogue* d, Object*object, char* name, TURN_STATUS status);
STATUS dialogue_inspect(Dialogue* d, Object* object, Space* space, char* name, INSPECT_STATUS status);
STATUS dialogue_save(Dialogue * d, char* name, DIALOGUE_SAVE_STATUS status);
STATUS dialogue_help(Dialogue *d);
STATUS dialogue_game_rule(Dialogue *d, int rule);
#endif