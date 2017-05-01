/**
 * @brief It defines a textual graphic engine
 *
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @author Javier Bernardo
 * @author Mihai Blidaru
 * @version 2.0
 * @date 13-03-2017
 * @copyright GNU Public License
 */

/**
 * Cabeceras Libc
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * Cabeceras propias
 */
#include "screen.h"
#include "graphic_engine.h"
#include "player.h"
#include "object.h"
#include "types.h"
#include "game.h"
#include "link.h"
#include "die.h"
#include "set.h"
#include "dialogue.h"

/**
 * @cond
 * @brief Estructura del graphic_engine
 *
 *  Define las 5 areas donde se ha a imprimir por pantalla.
 */
struct _Graphic_engine {
    Area *map;                  /*!< Puntero al mapa */
    Area *descript;             /*!< Puntero a la descripcion*/
    Area *banner;               /*!< Puntero al area */
    Area *help;                 /*!< Puntero a la ayuda */
    Area *feedback;             /*!< Puntero al area */
};

STATUS graphic_engine_print_inspect_object(FILE* fp, Object* inspected_object);
STATUS graphic_engine_print_inspect_space(FILE* fp, Game* game);

/**
 * @endcond
 */

/*
 * @brief Crea el motor del juego e inicializa las areas donde se va a imprimir
 *         por pantalla
 * @author Profesores PPROG
 * @return Un puntero al graphic_engine creado
 */
Graphic_engine *graphic_engine_create() {
    static Graphic_engine *ge = NULL;

    if (ge)
        return ge;

    screen_init();
    ge = (Graphic_engine *) malloc(sizeof (Graphic_engine));

    ge->map = screen_area_init(1, 1, 52, 14);
    ge->descript = screen_area_init(54, 1, 25, 14);
    ge->banner = screen_area_init(17, 16, 45, 1);
    ge->help = screen_area_init(15, 17, 49, 1);
    ge->feedback = screen_area_init(1, 18, 78, 3);

    return ge;
}

/*
 * @brief Libera la memoria ocupada por un graphic_engine
 *
 * @author Profesores PPROG
 * @param ge El graphic_engine que se tiene que destruir
 * @return Nada
 */
void graphic_engine_destroy(Graphic_engine *ge) {
    if (!ge)
        return;

    screen_area_destroy(ge->map);
    screen_area_destroy(ge->descript);
    screen_area_destroy(ge->banner);
    screen_area_destroy(ge->help);
    screen_area_destroy(ge->feedback);

    screen_destroy();
    free(ge);
}

/*
 * @brief Imprime el juego por pantalla
 *
 * @author Profesores PPROG
 * @author Javier Bernardo
 * @param ge Puntero a un graphic_engine
 * @param game Puntero a un juego
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
    Id id_act = NO_ID, id_east = NO_ID, id_west = NO_ID, id_up = NO_ID, id_down = NO_ID;
    Id south_link = NO_ID, north_link = NO_ID, east_link = NO_ID, west_link  = NO_ID, up_link = NO_ID, down_link = NO_ID;
	Link* l_south = NULL, *l_north = NULL, *l_east = NULL, *l_west = NULL;
	Dialogue* dialogue = NULL;
    Space* space_act = NULL;
    Player* player;
    Object* aux_obj = NULL;
    char graphics[6][24];
    BOOL has_light = FALSE;
    Id objLoc = NO_ID;
    char str[WORD_SIZE];
    char aux[WORD_SIZE];
    char dir_left[5] = "    ";
    char dir_right[5] = "    ";
    char open_left[3][2] = {"|","|", "|"};
    char open_right[3][2] = {"|","|", "|"};
    char* obj;


    int i, j, size;


    if((game_get_last_inspected_object(game))){
    	graphic_engine_print_inspect_object(stdout, game_get_last_inspected_object(game));
    }

	if((game_get_last_inspected_space(game))){
    	graphic_engine_print_inspect_space(stdout, game);
    }
    /* Paint the in the map area */
    screen_area_clear(ge->map);
    if ((id_act = game_get_player_location(game)) != NO_ID) {
        space_act = game_get_space(game, id_act);
        space_get_graphics(space_act, graphics);
        north_link = space_get_north(space_act);
        south_link = space_get_south(space_act);
        east_link = space_get_east(space_act);
        west_link = space_get_west(space_act);
        up_link = space_get_up(space_act);
        down_link = space_get_down(space_act);
        l_north = game_get_link(game, north_link);
        l_south  = game_get_link(game, south_link);
        l_east = game_get_link(game, east_link);
        l_west = game_get_link(game, west_link);
        id_east = link_get_dest_from(l_east, id_act);
        id_west = link_get_dest_from(l_west, id_act);
        id_up = link_get_dest_from(game_get_link(game,up_link), id_act);
        id_down = link_get_dest_from(game_get_link(game,down_link), id_act);
        obj = game_get_obj_list_as_str(game, space_act);
        player = game_get_player(game);

        for(i = 0; (aux_obj = game_get_object_at(game,i)) != NULL; i++){
        	if(player_Has_Object(player, object_Get_Id(aux_obj)) && object_Get_Light(aux_obj)){
        		has_light = TRUE;
        		break;
        	}
        }

        screen_area_puts(ge->map, " ");
        if(l_north){
            sprintf(str,"                       ^ %2ld ^ ", link_get_dest_from(l_north, id_act));
        }else{
            sprintf(str," ");
        }
        screen_area_puts(ge->map, str);
        if(link_get_state(l_north) == OPENED && link_get_dest_from(l_north, id_act) != NO_ID){
        	sprintf(str,"        *--------------/    \\--------------*");
        }else{
			sprintf(str,"        *----------------------------------*");
        }
        screen_area_puts(ge->map, str);
        if(id_up != NO_ID)
        	sprintf(str,"        |            Up ^: %2ld           %2ld |", id_up, id_act);
        else
        	sprintf(str,"        |                               %2ld |", id_act);
        screen_area_puts(ge->map, str);
        if(player_Has_Object(game_get_player(game), 7)){
            sprintf(str,"        |[_|'v'|_} %s |", graphics[0]);
        }else{
            sprintf(str,"        |[ .,,,.}  %s |", graphics[0]);
        }
        screen_area_puts(ge->map, str);
        sprintf(str,"        |[ | oo|}  %s |", graphics[1]);
        screen_area_puts(ge->map, str);
        if(link_get_state(l_west) == OPENED){
        	open_left[0][0] = '/';
        	open_left[1][0] = ' ';
        	open_left[2][0] = '\\';
        }

        if(link_get_state(l_east) == OPENED){
        	open_right[0][0] = '\\';
        	open_right[1][0] = ' ';
        	open_right[2][0] = '/';
        }

        sprintf(str,"        %s[ \\- /}   %s %s", open_left[0], graphics[2], open_right[0]);
        screen_area_puts(ge->map, str);

        if(id_west != NO_ID)
        	sprintf(dir_left,"%2ld <", id_west);
        if(id_east != NO_ID)
        	sprintf(dir_right,"> %2ld ", id_east);

        sprintf(str,"   %s %s[ '||'}   %s %s  %s", dir_left, open_left[1], graphics[3], open_right[1], dir_right);
        screen_area_puts(ge->map, str);
        sprintf(str,"        %s[' || '}  %s %s", open_left[2], graphics[4], open_right[2]);
        screen_area_puts(ge->map, str);
        sprintf(str,"        |[ _/\\_}   %s |", graphics[5]);
        screen_area_puts(ge->map, str);
        if(id_down != NO_ID)
        	sprintf(str,"        |             Down v: %2ld           |", id_down);
        else
        	sprintf(str,"        |                                  |");

        screen_area_puts(ge->map, str);
        if(space_get_iluminated(space_act) == TRUE || has_light == TRUE)
        	sprintf(str,"        |%s|",obj);
        else
        	sprintf(str,"        |##################################|");

        screen_area_puts(ge->map, str);
        if(link_get_state(game_get_link(game, south_link)) == OPENED){
        	sprintf(str,"        *--------------\\    /--------------*");
        }else{
			sprintf(str,"        *----------------------------------*");
        }

        free(obj);
        screen_area_puts(ge->map, str);
        if(l_south){
            sprintf(str,"                       v %2ld v ", link_get_dest_from(l_south, id_act));
        }else{
            sprintf(str," ");
        }
        screen_area_puts(ge->map, str);

    }

    /* Imprimir la localizacion de los objetos */
    screen_area_clear(ge->descript);
    sprintf(str, " Objetos cercanos: ");
    screen_area_puts(ge->descript, str);

    for (i=0; (aux_obj = game_get_object_at(game,i)); i++){
        objLoc = game_get_object_location(game, aux_obj);
        if(object_Get_Hidden(aux_obj) == FALSE){
	        if (objLoc == id_act) {
	            sprintf(str, "  O%ld(%ld) - %s",object_Get_Id(aux_obj), objLoc, object_Get_Name(aux_obj));
	            screen_area_puts(ge->descript, str);
	        }
        }
    }


    /* Imprimir los objetos del Jugador*/

	screen_area_puts(ge->descript, " ");
    sprintf(aux, "  Objetos del jugador: ");
    screen_area_puts(ge->descript, aux);

    aux_obj = NULL;
    for (i = 0, j = 0; i < MAX_OBJECTS && (aux_obj = game_get_object_at(game,i)); i++) {
        if (player_Has_Object(game_get_player(game), object_Get_Id(aux_obj)) == TRUE) {
            sprintf(str, "   O%ld(%s) ",object_Get_Id(aux_obj), object_Get_Name(aux_obj));
            screen_area_puts(ge->descript, str);
            j++;
        }
    }
    if(j==0)
        screen_area_puts(ge->descript, "     None");
    /* Imprimir el valor de la ultima tirada */
    	screen_area_puts(ge->descript, " ");
    if (die_get_number(game_get_die(game))){
        sprintf(str, " Valor del dado: %d", die_get_number(game_get_die(game)));
    	screen_area_puts(ge->descript, str);
    }


    /* Paint the in the banner area */
    sprintf(str, "%s","{Indiana Jones 2D: En busca del arca perdido}");
    /*sprintf(str, "%s","\33[1;32m Indiana Jones 2D: En busca del arca perdido \33[0m");*/
    screen_area_puts(ge->banner, str);

    /* Paint the in the help area */
    screen_area_clear(ge->help);
    sprintf(str, " Para ver los comandos disponibles escribe:]Help}");
    screen_area_puts(ge->help, str);

    /* Paint the in the feedback area */

    /* Imprimir el dialogo */
    screen_area_clear(ge->feedback);
    dialogue = game_get_dialogue(game);
	strcpy(aux, dialogue_get_text(dialogue));
	size = strlen(aux);
	if(size > 76){
		for(i = 0, j = 0; i < size; i++, j++){
			if(j == 76){
				for(i = i; (&(aux[i])) != aux; i--){
					if(aux[i] == ' '){
						aux[i] = '\n';
						break;
					}
				}
				j=0;
			}
		}
		obj = strtok(aux, "\n");

		sprintf(str, " %s", obj);
		screen_area_puts(ge->feedback, str);
		while((obj = strtok(NULL, "\n"))){
			sprintf(str, " %s", obj);
			screen_area_puts(ge->feedback, str);
		}

	}else{
		sprintf(str, " %s", aux);
		screen_area_puts(ge->feedback, str);
	}


    /* Dump to the terminal */
    screen_paint();
    printf("prompt:> ");
}

/*
 * @brief Imprime los detalles del ultimo objeto inspeccionado
 * @author Mihai Blidaru
 * @param fp Descriptor del fichero donde imprimir
 * @param game Un puntero a la estructura del
 * @return OK si todo ha ido bien o ERROR en caso contrario
 */
STATUS graphic_engine_print_inspect_object(FILE* fp, Object* inspected_object){
	char* aux;
	char str[250] = "\0";
	char graphics[WORD_SIZE];
	int i;
	int ngLines = 0;
	int drawn_lines = 0;
	int size;
	if(!fp || !inspected_object)
		return ERROR;

	puts("\033[2J"); /*Clear the terminal*/
	fprintf(fp, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    fprintf(fp, "~                                                                              ~\n");
   	fprintf(fp, "~    Objeto:                                                                   ~\n");
	fprintf(fp, "~       Id:           %2ld                                                       ~\n", object_Get_Id(inspected_object));
	aux = object_Get_Name(inspected_object);
	fprintf(fp, "~       Nombre:       %s", aux);
	for(i = 57 - strlen(aux); i > 0; i--, fprintf(fp, " "));

	if(object_Get_Moved(inspected_object) == TRUE){
		strcpy(str, object_Get_Description2(inspected_object));
	}else{
		strcpy(str, object_Get_Description(inspected_object));
	}
	drawn_lines = 5;
    size = strlen(str);
	if (size > 56){
		for(i = 56; i >0; i--){
			if(str[i] == ' '){
				str[i] = '\n';
				break;
			}
		}
		aux = strtok(str, "\n");
		fprintf(fp, "~\n~       Descripcion:  %s", aux);
		for(i = 22 +strlen(aux); i < 79; i++, fprintf(fp, " "));
		aux = strtok(NULL, "\n");
		fprintf(fp, "~\n~                     %s", aux);
		for(i = 22 +strlen(aux); i < 79; i++, fprintf(fp, " "));
		drawn_lines += 2;
	}else{
		fprintf(fp, "~\n~       Descripcion:  %s", str);
		for(i = 22 +strlen(str); i < 79; i++, fprintf(fp, " "));
		drawn_lines++;
	}

	if(object_Get_Mobile(inspected_object) == TRUE)
		strcpy(str, "SI");
	else
		strcpy(str, "NO");

	fprintf(fp, "~\n~       Movible:      %s                                                       ~\n", str);

	if(object_Get_Open(inspected_object) != NO_ID)
		strcpy(str, "SI");
	else
		strcpy(str, "NO");

	fprintf(fp, "~       Abre:         %s                                                       ~\n", str);

	if(object_Get_Illuminates(inspected_object) == TRUE)
		strcpy(str, "SI");
	else
		strcpy(str, "NO");

	fprintf(fp, "~       Ilumina:      %s                                                       ~\n", str);
	drawn_lines += 3;
	if(object_Get_Illuminates(inspected_object) == TRUE){
		if(object_Get_Light(inspected_object)==TRUE)
			strcpy(str, "SI");
		else
			strcpy(str, "NO");
		fprintf(fp, "~       Encendido:    %s                                                       ~\n", str);
		drawn_lines++;
	}

	fprintf(fp, "~                                                                              ~\n");
	drawn_lines++;
	strncpy(graphics, object_Get_Graphics(inspected_object), WORD_SIZE);

	aux = strtok(graphics, "@");
	if(aux){
		fprintf(fp, "~          %s", aux);
		for(i = 68 - strlen(aux); i > 0; i--, fprintf(fp, " "));
		fprintf(fp, "~\n");
		drawn_lines++;
		for(i = 1; (aux = strtok(NULL, "@")) != NULL && aux[0] != '\n'; i++){
			fprintf(fp, "~          %s", aux);
			for(i = 68 - strlen(aux); i > 0; i--, fprintf(fp, " "));
			fprintf(fp, "~\n");
			ngLines++;
			drawn_lines++;
		}
	}

	for(i=drawn_lines; i < 21; i ++){
		fprintf(fp, "~                                                                              ~\n");
	}

	fprintf(fp, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    fprintf(fp, "Press Enter to continue: ");
    fgets(str, 100, stdin);

   return OK;
}

/*
 * @brief Imprime los detalles del ultimo espacio inspeccionado
 * @author Mihai Blidaru
 * @param fp Descriptor del fichero donde imprimir
 * @param game Un puntero a la estructura del
 * @return OK si todo ha ido bien o ERROR en caso contrario
 */
STATUS graphic_engine_print_inspect_space(FILE* fp, Game* game){
	Space* inspected_space = NULL;
	Object* object = NULL;
	char* aux;
	int i, j = 0, size;
	char str[250] = "\0";
	int drawn_lines = 0;
	char graphics[6][24];
    if(!fp || !game)
    	return ERROR;

    inspected_space = game_get_last_inspected_space(game);
    space_get_graphics(inspected_space, graphics);
    puts("\033[2J"); /*Clear the terminal*/
    fprintf(fp, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    fprintf(fp, "~                                                                              ~\n");
    fprintf(fp, "~  Casilla:                                                                    ~\n");
    fprintf(fp, "~                                                                              ~\n");
    fprintf(fp, "~       Id:           %2ld                                                       ~\n", space_get_id(inspected_space));
	aux = (char*) space_get_name(inspected_space);
	fprintf(fp, "~       Nombre:       %s", aux);
	for(i = 57 - strlen(aux); i > 0; i--, fprintf(fp, " "));


	if(space_get_iluminated(inspected_space) == TRUE){
		strcpy(str, (char*) space_get_long_description(inspected_space));
	}else{
		strcpy(str, (char*) space_get_description(inspected_space));
	}
	drawn_lines = 6;
    size = strlen(str);
	if (size > 56){
		for(i = 56; i >0; i--){
			if(str[i] == ' '){
				str[i] = '\n';
				break;
			}
		}
		aux = strtok(str, "\n");
		fprintf(fp, "~\n~       Descripcion:  %s", aux);
		for(i = 57 - strlen(aux); i > 0; i--, fprintf(fp, " "));
		aux = strtok(NULL, "\n");
		fprintf(fp, "~\n~                     %s", aux);
		for(i = 57 - strlen(aux); i > 0; i--, fprintf(fp, " "));
		drawn_lines += 2;
	}else{
		fprintf(fp, "~\n~       Descripcion:  %s", str);
		for(i = 22 + strlen(str); i < 79; i++, fprintf(fp, " "));
		drawn_lines++;
	}

	if(space_get_iluminated(inspected_space) == TRUE)
		strcpy(str, "SI");
	else
		strcpy(str, "NO");

	fprintf(fp, "~\n~       Iluminado:    %s                                                       ~", str);

	drawn_lines++;

    fprintf(fp, "\n~       Objetos:      ");
	for(i = 0; (object = game_get_object_at(game, i)) != NULL; i++){
		if(object_Get_Hidden(object) == FALSE){
			if(space_contains_object(inspected_space, object_Get_Id(object))){
				fprintf(fp, "%s ", object_Get_Name(object));
				j += strlen(object_Get_Name(object)) + 1;
			}
		}
	}
	for(i = j+21; i < 78; i++, fprintf(fp, " "));

	drawn_lines++;

	fprintf(fp, "~\n~                                                                              ");
	fprintf(fp, "~\n~                                                                              ");
	fprintf(fp, "~\n~                         *************************                            ");
	for(i=0;i<6;i++){
	fprintf(fp, "~\n~                         *%s*                            ", graphics[i]);
	}
	fprintf(fp, "~\n~                         *************************                            ");
	drawn_lines += 10;


    for(i=drawn_lines; i < 21; i ++){
		fprintf(fp, "~\n~                                                                              ");
	}
    fprintf(fp, "~\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    fprintf(fp, "Press Enter to continue: ");
    fgets(str, 100, stdin);
	return OK;
}

/*
 * @brief Imprime las direcciones adyacentes de una casilla
 * @author Mihai Blidaru
 * @param fp Descriptor del fichero donde imprimir
 * @param game Un puntero a la estructura del juego
 */
void graphic_engine_paint_directions(FILE* fp, Game* game){
	Space* space;
    Link* north_link = NULL, *south_link = NULL, *east_link = NULL, *west_link = NULL, *up_link = NULL, *down_link = NULL;
    Id id_act = NO_ID;
    Id dest_north = NO_ID, dest_south = NO_ID, dest_east = NO_ID, dest_west = NO_ID, dest_up = NO_ID, dest_down = NO_ID;
    char centered_text[100]="\0";
    char aux[100] = "\0";
    int spaces = 0, i;

    if(!fp || !game)
		return;

    id_act = game_get_player_location(game);
    space = game_get_space(game, id_act);
    north_link = game_get_link(game, space_get_north(space));
    south_link = game_get_link(game, space_get_south(space));
    east_link = game_get_link(game, space_get_east(space));
    west_link = game_get_link(game, space_get_west(space));
    up_link = game_get_link(game, space_get_up(space));
    down_link = game_get_link(game, space_get_down(space));
    dest_north = link_get_dest_from(north_link, id_act);
    dest_south = link_get_dest_from(south_link, id_act);
    dest_east = link_get_dest_from(east_link, id_act);
    dest_west = link_get_dest_from(west_link, id_act);
    dest_up = link_get_dest_from(up_link, id_act);
    dest_down = link_get_dest_from(down_link, id_act);

    puts("\033[2J"); /*Clear the terminal*/
    fprintf(fp, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    if(dest_up != NO_ID){
    	sprintf(aux, "%2ld : %s", dest_up, space_get_name(game_get_space(game,dest_up)));
    	fprintf(fp, "~%s", aux);
    	for(i = 2 + strlen(aux); i < 80; i++, fprintf(fp, " "));
    	fprintf(fp, "~\n~   ^                                                                          ~\n");
    	fprintf(fp, "~   | -> Enlace: %s", link_get_name(up_link));
    	for(i=16 + strlen(link_get_name(up_link));i < 78; i++, fprintf(fp, " "));
    	fprintf(fp, "~\n~   Up                                                                         ~\n");
    }else{
	    fprintf(fp, "~                                                                              ~\n");
	    fprintf(fp, "~                                                                              ~\n");
	    fprintf(fp, "~                                                                              ~\n");
	    fprintf(fp, "~                                                                              ~\n");
    }
    if(dest_north != NO_ID){
	    sprintf(aux, "%2ld : %s", dest_north, space_get_name(game_get_space(game,dest_north)));
	    spaces = 78 - strlen(aux);

	    for(i=0; i< (spaces/2); i++){
	        centered_text[i] = ' ';
	    }
	    strcat(centered_text, aux);
	    while(strlen(centered_text) < 78){
	        strcat(centered_text, " ");
	    }
	    fprintf(fp, "~%s~\n", centered_text);
	    fprintf(fp, "~                                      ^                                       ~\n");
		fprintf(fp, "~                                    . N .-> Enlace: %s", link_get_name(north_link));
		for(i=52+strlen(link_get_name(north_link));i < 78; i++, fprintf(fp, " "));
    }else{
    	fprintf(fp, "~                                                                              ~\n");
    	fprintf(fp, "~                                      ^                                       ~\n");
		fprintf(fp, "~                                    . N .                                     ");
    }
	fprintf(fp, "~\n~                                  .` )|( `.                                   ~\n~");
	if(dest_west != NO_ID){
		sprintf(aux, "Enlace: %s", link_get_name(west_link));
		for(i = 28- strlen(aux); i > 0 ; i--, fprintf(fp, " "));
		fprintf(fp, "%s <- .` )  |  ( `.                                 ~\n", aux);
		fprintf(fp, "~                              .\\ )    |    ( `.                               ~\n~");
		sprintf(aux, "%2ld : %s", dest_west, space_get_name(game_get_space(game,dest_west)));
		for(i = 27- strlen(aux); i > 0 ; i--, fprintf(fp, " "));

	}else{
		strcpy(aux, "                           ");
		fprintf(fp, "                                .` )  |  ( `.                                 ~\n");
		fprintf(fp, "~                              .` )    |    ( `.                               ~\n~");
	}
	fprintf(fp, "%s <` W)-----O-----(E `> ", aux);

	if(dest_east != NO_ID){
		sprintf(aux, "%ld: %s", dest_east, space_get_name(game_get_space(game,dest_east)));
		fprintf(fp, "%s", aux);
		for(i=28-strlen(aux); i > 0; i--, fprintf(fp, " "));
		fprintf(fp, "~\n~                             `.  )    |    (  \\`                              ~\n");
	    fprintf(fp, "~                               `.  )  |  (  .` -> Enlace: %s", link_get_name(east_link));
	    for(i = 20- strlen(link_get_name(east_link)); i > 0 ; i--, fprintf(fp, " "));
	}else{
		fprintf(fp, "                            ");
		fprintf(fp, "~\n~                             `.  )    |    (  .`                              ~\n");
	    fprintf(fp, "~                               `.  )  |  (  .`                                ");
	}


	fprintf(fp, "~\n~                                 `.  )|(  .`                                  ~\n");
	if(dest_south != NO_ID){
		fprintf(fp, "~                                   `. S .`->Enlace: %s", link_get_name(south_link));

		for(i=52 + strlen(link_get_name(south_link));i < 78; i++, fprintf(fp, " "));
		fprintf(fp, "~\n~                                      v                                       ~\n");

  	   	sprintf(aux, "%2ld : %s", dest_south, space_get_name(game_get_space(game, dest_south)));
	    spaces = 78 - strlen(aux);
	    for(i=0; i< 100; i++){
	        centered_text[i] = '\0';
	    }

	    for(i=0; i< (spaces/2); i++){
	        centered_text[i] = ' ';
	    }
	    strcat(centered_text, aux);
	    while(strlen(centered_text) < 78){
	        strcat(centered_text, " ");
	    }

	    fprintf(fp, "~%s~\n", centered_text);
    }else{
    	fprintf(fp, "~                                   `. S .`                                    ~\n");
		fprintf(fp, "~                                      v                                       ~\n");
		fprintf(fp, "~                                                                              ~\n");
    }

     if(dest_down != NO_ID){
    	fprintf(fp, "~  Down                                                                        ~\n");
    	fprintf(fp, "~    v -> Enlace: %s", link_get_name(down_link));
    	for(i=17 +strlen(link_get_name(down_link));i < 78; i++, fprintf(fp, " "));
    	sprintf(aux, "%2ld : %s", dest_down, space_get_name(game_get_space(game,dest_down)));
    	fprintf(fp, "~\n~ %s", aux);
    	for(i = 1 + strlen(aux);i < 78; i++, fprintf(fp, " "));
    }else{
	    fprintf(fp, "~                                                                              ~\n");
	    fprintf(fp, "~                                                                              ~\n");
	    fprintf(fp, "~                                                                              ");
    }


    fprintf(fp, "~\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    fprintf(fp, "Press Enter to continue:> ");

    fgets(aux, 100, stdin);
}

/*
 * @brief Imprime la pantalla de ayuda
 * @author Javier Bernardo
 * @param fp Descriptor del fichero donde imprimir
 */
void graphic_engine_paint_help(FILE* fp){
	char dummy[2];
	if(!fp)
		return;

	puts("\033[2J"); /*Clear the terminal*/
	fprintf(fp, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	fprintf(fp, "~                                                                              ~\n");
    fprintf(fp, "~      Comandos disponibles:                                                   ~\n");
    fprintf(fp, "~              (g)o        (n)orth, (s)outh, (e)ast, (w)est, (u)p, (d)own      ~\n");
    fprintf(fp, "~              (d)ir       Para ver las direcciones disponibles                ~\n");
    fprintf(fp, "~              (i)nspect   \"space\"                                             ~\n");
    fprintf(fp, "~              (i)nspect   <nombre del objeto>                                 ~\n");
    fprintf(fp, "~              (t)ake      <nombre del objeto>                                 ~\n");
	fprintf(fp, "~              (l)eave     <nombre del objeto>                                 ~\n");
    fprintf(fp, "~              turnon      <nombre del objeto>                                 ~\n");
    fprintf(fp, "~              turnoff     <nombre del objeto>                                 ~\n");
    fprintf(fp, "~              (o)pen      <link> with <nombre del objeto>                     ~\n");
    fprintf(fp, "~              roll                                                            ~\n");
    fprintf(fp, "~              attack                                                          ~\n");
    fprintf(fp, "~                                                                              ~\n");
    fprintf(fp, "~      Gestion de la partida:                                                  ~\n");
    fprintf(fp, "~              save        <nombre del archivo>                                ~\n");
    fprintf(fp, "~              load        <nombre del archivo                                 ~\n");
	fprintf(fp, "~      Ayuda:                                                                  ~\n");
    fprintf(fp, "~              help        Aparece esta pantalla de ayuda                      ~\n");
    fprintf(fp, "~                                                                              ~\n");
    fprintf(fp, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    fprintf(fp, "Press Enter to continue: ");
    fgets(dummy, 2, stdin);
}


/*
 * @brief Imprime la panatlla de final de juego
 * @author Mihai Blidaru
 * @param fp Descriptor del fichero donde imprimir
 */
void graphic_engine_game_over(FILE* fp){
	if(!fp)
		return;
		puts("\033[2J"); /*Clear the terminal*/
		fprintf(fp, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		fprintf(fp, "~                                                                             ~\n");
		fprintf(fp, "~                          _.--.                     !!!FELICIDADES!!!        ~\n");
		fprintf(fp, "~                      _.-'_:-'||                                             ~\n");
		fprintf(fp, "~                  _.-'_.-::::'||                 HAS ENCONTRADO EL ARCA      ~\n");
		fprintf(fp, "~             _.-:'_.-::::::'  ||                PERDIDO Y HAS CONSEGUIDO     ~\n");
		fprintf(fp, "~           .'`-.-:::::::'     ||              SALIR DE LA PIRAMIDE CON VIDA  ~\n");
		fprintf(fp, "~          /.'`;|:::::::'      ||_                                            ~\n");
		fprintf(fp, "~         ||   ||::::::'     _.;._'-._         VUELVE A JUGAR CUANDO QUIERAS  ~\n");
		fprintf(fp, "~         ||   ||:::::'  _.-!oo @.!-._'-.       PARA EXPLORAR LOS MISTERIOS   ~\n");
		fprintf(fp, "~         \\'.  ||:::::.-!()oo @!()@.-'_.|      INDESCUBIERTOS DE LA PIRAMIDE  ~\n");
		fprintf(fp, "~          '.'-;|:.-'.&$@.& ()$%%-'o.'\\U||                                     ~\n");
		fprintf(fp, "~            `>'-.!@%%()@'@_%%-'_.-o _.|'||                .-\"\"\"\"\"\"-.           ~\n");
		fprintf(fp, "~             ||-._'-.@.-'_.-' _.-o  |'||              .'          '.         ~\n");
		fprintf(fp, "~             ||=[ '-._.-\\U/.-'    o |'||             /   O    -=-   \\        ~\n");
		fprintf(fp, "~             || '-.]=|| |'|      o  |'||            :                :       ~\n");
		fprintf(fp, "~             ||      || |'|        _| ';            |                |       ~\n");
		fprintf(fp, "~             ||      || |'|    _.-'_.-'             : ',          ,' :       ~\n");
		fprintf(fp, "~             |'-._   || |'|_.-'_.-'                  \\  '-......-'  /        ~\n");
		fprintf(fp, "~              '-._'-.|| |' `_.-'                      '.          .'         ~\n");
		fprintf(fp, "~                  '-.||_/.-'                            '-......-'           ~\n");
		fprintf(fp, "~                                                                             ~\n");
		fprintf(fp, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		fflush(fp);
		sleep(2);
		fprintf(fp,"\n");
}

 /*
 * @brief Imprime la intro del juego
 * @author Mihai Blidaru
 * @param fp Descriptor del fichero donde imprimir
 */
void graphic_engine_play_intro(FILE* fp){
	int i;
	if(!fp)
		return;
	for( i = 5; i>0; i--){
		puts("\033[2J"); /*Clear the terminal*/
		fprintf(fp, "*******************************************************************************\n");
		fprintf(fp, "*                                                                             *\n");
		fprintf(fp, "*                                     m^m                                     *\n");
		fprintf(fp, "*                                    /\"MMM\\                                   *\n");
		fprintf(fp, "*                                  /\"\"  MMMM\\                                 *\n");
		fprintf(fp, "*                                /\"\"     MMMM\\                                *\n");
		fprintf(fp, "*                              /\"\",,\"\",,,\"XXXXX\\                              *\n");
		fprintf(fp, "*                     ......./\"\"       \"   MMMMM\\.....                        *\n");
		fprintf(fp, "*                  ......../\"\"\"\" \"     \"\"   MMMMM\\.......                     *\n");
		fprintf(fp, "*               ........../\"\" \"  \"  \"\"\"     \"MMMMMM\\.......                   *\n");
		fprintf(fp, "*              ........./\"      \"          \"  MMMMMMM\\........                *\n");
		fprintf(fp, "*               ....../\"\"  \"    \"         \"    MMMMMMM\\......                 *\n");
		fprintf(fp, "*             ....../\"\"     \"\"     \"         \" \"MMMMMMM\\.......               *\n");
		fprintf(fp, "*            ...../\"\"   \"         \"     \"  \"     MMMMMMMM\\......              *\n");
		fprintf(fp, "*          ...../\"  \"   \" \"         \"\"     \"   \" \"MMMMMMMMM\\.....             *\n");
		fprintf(fp, "*         ..../\"\"               \"  \"              \"MMMMMMMMMM\\.....           *\n");
		fprintf(fp, "*        ..../   \"       \" \" \"         \"        \"  \"MMMMMMMMMM\\...            *\n");
		fprintf(fp, "*        ../\"             \"   \"  \"  \" \"    \"    \"   \"MMMMMMMMMMM\\..           *\n");
		fprintf(fp, "*        ./         \"    \"         \"                 MMMMMMMMMMMM\\..          *\n");
		fprintf(fp, "*          \" \"  \" \" \"     \"\"\"\"   \" \"                                          *\n");
		fprintf(fp, "*      Indiana Jones 2D: En busca del arca perdida - La piramide maldita      *\n");
		fprintf(fp, "*                                                                             *\n");
		fprintf(fp, "******************************* Empezando en %d ********************************", i);
		fflush(fp);
		sleep(1);
	}
}
