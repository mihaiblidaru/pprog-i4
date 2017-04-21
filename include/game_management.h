#ifndef GAMEMANAGEMENT_H
#define GAMEMANAGEMENT_H

STATUS game_management_save(Game* game, char* filename);
STATUS game_management_load(Game* game, char* filename);
STATUS game_management_start_from_file(Game* game, char* spacesFile, char* objectsFile, char* linksfile, char* playersFile);


#endif