#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "space.h"
#include "link.h"
#include "object.h"

typedef struct _Dialogue Dialogue;

typedef enum{
    NO_OBJ,
    NOT_IN_SPACE,
    NOT_MOBILE,
    INVENTORY_FULL,
    TAKE_OK
}TAKE_STATUS;


Dialogue* dialogue_ini();
void dialogue_destroy(Dialogue* d);

char* dialogue_get_text(Dialogue * d);
STATUS dialogue_go(Dialogue*d, DIRECTION direction, Space* space, STATUS status, char* dir_name, Link* link);
STATUS dialogue_unknown(Dialogue* d);
STATUS dialogue_dir(Dialogue* d);
STATUS dialogue_take(Dialogue* d, Object* object, char* name, TAKE_STATUS status);

#endif