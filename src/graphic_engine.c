
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

STATUS graphic_engine_print_inspect_object(Graphic_engine *ge, Object* inspected_object);
STATUS graphic_engine_print_inspect_space(Graphic_engine* ge, Game* game);

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
    ge->banner = screen_area_init(28, 16, 25, 1);
    ge->help = screen_area_init(1, 17, 78, 2);
    ge->feedback = screen_area_init(1, 20, 78, 2);

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
    Id id_act = NO_ID;
    Id id_east = NO_ID;
    Id id_west = NO_ID;
    Id id_up = NO_ID;
    Id id_down = NO_ID;
    
    Id south_link = NO_ID;
    Id north_link = NO_ID;
    Id east_link = NO_ID;
    Id west_link  = NO_ID;
	Id up_link = NO_ID;
	Id down_link = NO_ID;
    Space* space_act = NULL;
    Object* aux_obj = NULL;
    Link* link = NULL;
    
    Id objLoc = NO_ID;
    char str[WORD_SIZE];
    char aux[WORD_SIZE];
    char dir_left[5] = "    ";
    char dir_right[5] = "    ";
    char* obj;

    T_Command last_cmd = UNKNOWN;
    extern char *cmd_to_str[];

    int i, j;

    STATUS last_status = ERROR;
    
    if((game_get_last_inspected_object(game))){
    	graphic_engine_print_inspect_object(ge, game_get_last_inspected_object(game));
    }
	
	if((game_get_last_inspected_space(game))){
    	graphic_engine_print_inspect_space(ge, game);
    }
    /* Paint the in the map area */
    screen_area_clear(ge->map);
    if ((id_act = game_get_player_location(game)) != NO_ID) {
        space_act = game_get_space(game, id_act);
        north_link = space_get_north(space_act);
        east_link = space_get_east(space_act);
        west_link = space_get_west(space_act);
        up_link = space_get_up(space_act);
        down_link = space_get_down(space_act);
        id_east = link_get_dest_from(game_get_link(game,east_link), id_act);
        id_west = link_get_dest_from(game_get_link(game,west_link), id_act);
        id_up = link_get_dest_from(game_get_link(game,up_link), id_act);
        id_down = link_get_dest_from(game_get_link(game,down_link), id_act);
        link = game_get_link(game, north_link);
        obj = game_get_obj_list_as_str(game, space_act);
        screen_area_puts(ge->map, " ");
        if(link){
            sprintf(str,"                       ^ %2ld ^ ", link_get_dest_from(link, id_act));
        }else{
            sprintf(str," ");
        }
        screen_area_puts(ge->map, str);
        sprintf(str,"        *----------------------------------*");
        screen_area_puts(ge->map, str);
        if(id_up != NO_ID)
        	sprintf(str,"        |            Up ^: %2ld           %2ld |", id_up, id_act);
        else
        	sprintf(str,"        |                               %2ld |", id_act);
        screen_area_puts(ge->map, str);
        if(player_Has_Object(game_get_player(game), 7)){
            sprintf(str,"        | _|'v'|_                          |");
        }else{
            sprintf(str,"        |  .,,,.                           |");
        }
        screen_area_puts(ge->map, str);
        sprintf(str,"        |  | oo|                           |");
        screen_area_puts(ge->map, str);
        sprintf(str,"        |  \\- /                            |");
        screen_area_puts(ge->map, str);
        
        if(id_west != NO_ID)
        	sprintf(dir_left,"%2ld <", id_west);
        if(id_east != NO_ID)
        	sprintf(dir_right,"> %2ld ", id_east);
        	
        sprintf(str,"   %s |  '||'                            |  %s", dir_left, dir_right);
        screen_area_puts(ge->map, str);
        sprintf(str,"        | ' || '                           |");
        screen_area_puts(ge->map, str);
        sprintf(str,"        |  _/\\_                            |");
        screen_area_puts(ge->map, str);
        if(id_down != NO_ID)
        	sprintf(str,"        |             Down v: %2ld           |", id_down);
        else
        	sprintf(str,"        |                                  |");
        
        screen_area_puts(ge->map, str);
        sprintf(str,"        |%s                     |",obj);
        screen_area_puts(ge->map, str);
                sprintf(str,"        *----------------------------------*");
        free(obj);
        screen_area_puts(ge->map, str);
        south_link = space_get_south(space_act);
        link = game_get_link(game, south_link);
        if(link){
            sprintf(str,"                       v %2ld v ", link_get_dest_from(link, id_act));
        }else{
            sprintf(str," ");
        }
        screen_area_puts(ge->map, str);
       
    }

    /* Imprimir la localizacion de los objetos */
    screen_area_clear(ge->descript);
    sprintf(str, "  Object location: ");
    screen_area_puts(ge->descript, str);

    for (i=0; (aux_obj = game_get_object_at(game,i)); i++) {
        objLoc = game_get_object_location(game, aux_obj);
        if (objLoc != NO_ID && objLoc != PLAYER_INV_LOCATION) {
            sprintf(str, "   O%ld(%s):%ld ",object_Get_Id(aux_obj), object_Get_Name(aux_obj), objLoc);
            screen_area_puts(ge->descript, str);
        }
    }
    

    /* Imprimir los objetos del Jugador*/

    sprintf(aux, "  Player Objects: ");
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
    screen_area_puts(ge->descript, " ");
    /* Imprimir el valor de la ultima tirada */
    sprintf(str, "  Last die value: ");
    if (die_get_number(game_get_die(game))) {
        sprintf(str, "%s %d", str, die_get_number(game_get_die(game)));
    } else {
        sprintf(str, "%s None", str);
    }
    screen_area_puts(ge->descript, str);
    
    screen_area_puts(ge->descript, " ");

    /* Paint the in the banner area */
    screen_area_puts(ge->banner, " The game of the Goose ");

    /* Paint the in the help area */
    screen_area_clear(ge->help);
    sprintf(str, " The commands you can use are: (t)ake + <object>, (l)leave + <object> ");
    screen_area_puts(ge->help, str);
    sprintf(str, "     (r)oll, (g)o + [(n)orth, (s)outh, (e)ast, (w)est], quit or q");
    screen_area_puts(ge->help, str);

    /* Paint the in the feedback area */
    last_cmd = game_get_last_command(game);
    last_status = game_get_last_status(game);

    /* Imprimir el ultimo comando ejecutado junto con su estado */
    if (last_status == OK) {
        sprintf(str, " %s: %s", cmd_to_str[last_cmd - NO_CMD], "OK");
    } else if (last_status == ERROR) {
        sprintf(str, " %s: %s", cmd_to_str[last_cmd - NO_CMD], "ERROR");
    } else {
        sprintf(str, " %s", cmd_to_str[last_cmd - NO_CMD]);
    }
    screen_area_puts(ge->feedback, str);

    /* Dump to the terminal */
    screen_paint();
    printf("prompt:> ");
}

STATUS graphic_engine_print_inspect_object(Graphic_engine *ge, Object* inspected_object){
	char* aux;
	char str[100] = "\0";
	char graphics[WORD_SIZE];
	int i;
	int ngLines = 0;
	int drawn_lines = 0;
	if(!ge || !inspected_object)
		return ERROR;
		
	puts("\033[2J"); /*Clear the terminal*/
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~                                                                              ~\n");
    
   	printf("~  Objecto:                                                                    ~\n");	
	printf("~       Id:           %2ld                                                       ~\n", object_Get_Id(inspected_object));
	aux = object_Get_Name(inspected_object);
	printf("~       Nombre:       %s", aux);
	for(i = 57 - strlen(aux); i > 0; i--, printf(" "));
	if(object_Get_Moved(inspected_object) == TRUE){
		aux = object_Get_Description2(inspected_object);
	}else{
		aux = object_Get_Description(inspected_object);
	}
	printf("~\n~       Descripcion:  %s", aux);
	for(i = 57 - strlen(aux); i > 0; i--, printf(" "));
	if(object_Get_Mobile(inspected_object) == TRUE)
		strcpy(str, "SI");
	else
		strcpy(str, "NO");
		
	printf("~\n~       Movible:      %s                                                       ~\n", str);
	
	if(object_Get_Open(inspected_object) != NO_ID)
		strcpy(str, "SI");
	else
		strcpy(str, "NO");
		
	printf("~       Abre:         %s                                                       ~\n", str);
	
	if(object_Get_Illuminates(inspected_object) == TRUE)
		strcpy(str, "SI");
	else
		strcpy(str, "NO");
		
	printf("~       Ilumina:      %s                                                       ~\n", str);
	drawn_lines = 9;
	if(object_Get_Illuminates(inspected_object) == TRUE){
		if(object_Get_Light(inspected_object)==TRUE)
			strcpy(str, "SI");
		else
			strcpy(str, "NO");
		printf("~       Encendido:    %s                                                       ~\n", str);
		drawn_lines++;
	}
	
	printf("~                                                                              ~\n");
	drawn_lines += 1;	
	strncpy(graphics, object_Get_Graphics(inspected_object), WORD_SIZE);
	
	aux = strtok(graphics, "@");
	if(aux){
		printf("~          %s", aux);
		for(i = 68 - strlen(aux); i > 0; i--, printf(" "));
		printf("~\n");
		drawn_lines++;
		for(i = 1; (aux = strtok(NULL, "@")) != NULL && aux[0] != '\n'; i++){
			printf("~          %s", aux);
			for(i = 68 - strlen(aux); i > 0; i--, printf(" "));
			printf("~\n");
			ngLines++;
			drawn_lines++;
		}
	}
	
	for(i=drawn_lines; i < 22; i ++){
		printf("~                                                                              ~\n");
	}
	
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Press Enter to continue: ");
    fgets(str, 100, stdin);
    
   return OK;
}

STATUS graphic_engine_print_inspect_space(Graphic_engine* ge, Game* game){
	Space* inspected_space = NULL;
	Object* object = NULL;
	char* aux;
	int i, j = 0;
	char str[100] = "\0";
	int drawn_lines = 0;
    if(!ge || !game)
    	return ERROR;
    
    inspected_space = game_get_last_inspected_space(game);
    	
    puts("\033[2J"); /*Clear the terminal*/
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~                                                                              ~\n");
    printf("~  Casilla:                                                                    ~\n");	
    printf("~                                                                              ~\n");
    printf("~       Id:           %2ld                                                       ~\n", space_get_id(inspected_space));
	aux = (char*) space_get_name(inspected_space);
	printf("~       Nombre:       %s", aux);
	for(i = 57 - strlen(aux); i > 0; i--, printf(" "));
	if(space_get_iluminated(inspected_space) == TRUE){
		aux = (char*) space_get_long_description(inspected_space);
	}else{
		aux = (char*) space_get_description(inspected_space);
	}
	printf("~\n~       Descripcion:  %s", aux);
	for(i = 57 - strlen(aux); i > 0; i--, printf(" "));
	
	if(space_get_iluminated(inspected_space) == TRUE)
		strcpy(str, "SI");
	else
		strcpy(str, "NO");
		
	printf("~\n~       Iluminado:    %s                                                       ~", str);
	
	drawn_lines = 8;
    
    printf("\n~       Objetos:      ");
	for(i = 0; (object = game_get_object_at(game, i)) != NULL; i++){
		if(object_Get_Hidden(object) == FALSE){
			if(space_contains_object(inspected_space, object_Get_Id(object))){
				printf("%s ", object_Get_Name(object));
				j += strlen(object_Get_Name(object)) + 1;
			}
		}
	}
	
	for(i = j+21; i < 78; i++, printf(" "));
	
    for(i=drawn_lines; i < 22; i ++){
		printf("~\n~                                                                              ");
	}
    printf("~\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Press Enter to continue: ");
    fgets(str, 100, stdin);
	return OK;
}


STATUS graphic_engine_paint_directions(Game* game){
	Space* space;
    Link* north_link = NULL, *south_link = NULL, *east_link = NULL, *west_link = NULL, *up_link = NULL, *down_link = NULL;
    Id id_act = NO_ID;
    Id dest_north = NO_ID, dest_south = NO_ID, dest_east = NO_ID, dest_west = NO_ID, dest_up = NO_ID, dest_down = NO_ID;
    char centered_text[100]="\0";
    char aux[100] = "\0";
    int spaces = 0, i;
    
    if(!game)
		return ERROR;
    
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
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    if(dest_up != NO_ID){
    	sprintf(aux, "%2ld : %s", dest_up, space_get_name(game_get_space(game,dest_up)));
    	printf("~%s", aux);
    	for(i=3+strlen(link_get_name(up_link));i < 78; i++, printf(" "));
    	printf("~\n~   ^                                                                          ~\n");
    	printf("~   | -> Enlace: %s", link_get_name(up_link));
    	for(i=16 + strlen(link_get_name(up_link));i < 78; i++, printf(" "));
    	printf("~\n~   Up                                                                         ~\n");
    }else{
	    printf("~                                                                              ~\n");
	    printf("~                                                                              ~\n");
	    printf("~                                                                              ~\n");
	    printf("~                                                                              ~\n");
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
	    printf("~%s~\n", centered_text);
	    printf("~                                      ^                                       ~\n");
		printf("~                                    . N .-> Enlace: %s", link_get_name(north_link));
		for(i=52+strlen(link_get_name(north_link));i < 78; i++, printf(" "));
    }else{
    	printf("~                                                                              ~\n");
    	printf("~                                      ^                                       ~\n");
		printf("~                                    . N .                                     ");
    }
	printf("~\n~                                  .` )|( `.                                   ~\n~");
	if(dest_west != NO_ID){
		sprintf(aux, "Enlace: %s", link_get_name(west_link));
		for(i = 28- strlen(aux); i > 0 ; i--, printf(" "));
		printf("%s <- .` )  |  ( `.                                 ~\n", aux);
		printf("~                              .\\ )    |    ( `.                               ~\n~");
		sprintf(aux, "%2ld : %s", dest_west, space_get_name(game_get_space(game,dest_west)));
		for(i = 27- strlen(aux); i > 0 ; i--, printf(" "));
		
	}else{
		strcpy(aux, "                           ");
		printf("                                .` )  |  ( `.                                 ~\n");
		printf("~                              .` )    |    ( `.                               ~\n~");
	}
	printf("%s <` W)-----O-----(E `> ", aux);
	
	if(dest_east != NO_ID){
		sprintf(aux, "%ld: %s", dest_east, space_get_name(game_get_space(game,dest_east)));
		printf("%s", aux);
		for(i=28-strlen(aux); i > 0; i--, printf(" "));
		printf("~\n~                             `.  )    |    (  \\`                              ~\n");
	    printf("~                               `.  )  |  (  .` -> Enlace: %s", link_get_name(east_link));	
	    for(i = 20- strlen(link_get_name(east_link)); i > 0 ; i--, printf(" "));
	}else{
		printf("                            ");
		printf("~\n~                             `.  )    |    (  .`                              ~\n");
	    printf("~                               `.  )  |  (  .`                                ");
	}
	
	
	printf("~\n~                                 `.  )|(  .`                                  ~\n");
	if(dest_south != NO_ID){
		printf("~                                   `. S .`->Enlace: %s", link_get_name(south_link));
		
		for(i=52 + strlen(link_get_name(south_link));i < 78; i++, printf(" "));
		printf("~\n~                                      v                                       ~\n");

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
	    
	    printf("~%s~\n", centered_text);
    }else{
    	printf("~                                   `. S .`                                    ~\n");
		printf("~                                      v                                       ~\n");
		printf("~                                                                              ~\n");
    }
    
     if(dest_down != NO_ID){
    	printf("~  Down                                                                        ~\n");
    	printf("~    v -> Enlace: %s", link_get_name(down_link));
    	for(i=17 +strlen(link_get_name(down_link));i < 78; i++, printf(" "));
    	sprintf(aux, "%2ld : %s", dest_down, space_get_name(game_get_space(game,dest_down)));
    	printf("~\n~ %s", aux);
    	for(i = 1 + strlen(aux);i < 78; i++, printf(" "));
    }else{
	    printf("~                                                                              ~\n");
	    printf("~                                                                              ~\n");
	    printf("~                                                                              ");
    }
    
    
    printf("~\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Press Enter to continue:> ");
    
    fgets(aux, 100, stdin);
    return OK;
}
	