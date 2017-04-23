#ifndef GAMEMANAGEMENT_H
#define GAMEMANAGEMENT_H

STATUS game_management_save(Game* game, char* filename);
STATUS game_management_load(Game* game, char* filename);
STATUS game_management_start_from_file(Game* game, char* spacesFile, char* objectsFile, char* linksfile, char* playersFile);

typedef enum {
    PROTECTED_FILE, SAVE_OK, WRITE_FAILED
} SAVE_STATUS;

typedef enum {
    LOAD_OK, IO_ERROR, NO_PLAYER, NO_SPACES, NO_LINKS
} LOAD_STATUS;


#endif