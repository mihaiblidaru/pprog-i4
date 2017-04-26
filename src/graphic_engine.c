
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

STATUS graphic_engine_paint_spaces(Graphic_engine*, Game*, Space*);

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

    ge->map = screen_area_init(1, 1, 52, 15);
    ge->descript = screen_area_init(54, 1, 25, 15);
    ge->banner = screen_area_init(28, 17, 25, 1);
    ge->help = screen_area_init(1, 18, 78, 2);
    ge->feedback = screen_area_init(1, 21, 78, 2);

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
    Id id_back = NO_ID;
    Id id_next = NO_ID;
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
    Space* space_back = NULL;
    Space* space_next = NULL;
    Space* inspected_space = NULL;
    Object* inspected_object = NULL;
    Object* aux_obj = NULL;
    Link* link = NULL;
    
    Id objLoc = NO_ID;
    char str[WORD_SIZE];
    char aux[WORD_SIZE];
    char dir_left[5] = "    ";
    char dir_right[5] = "    ";
    char* description = NULL;
    char* obj;

    T_Command last_cmd = UNKNOWN;
    extern char *cmd_to_str[];

    int i, j;

    STATUS last_status = ERROR;

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
        screen_area_puts(ge->map, str);
        south_link = space_get_south(space_act);
        link = game_get_link(game, south_link);
        if(link){
            sprintf(str,"                       v %2ld v ", link_get_dest_from(link, id_act));
        }else{
            sprintf(str," ");
        }
        screen_area_puts(ge->map, str);
        /*
        north_link = space_get_north(space_act);
        south_link = space_get_south(space_act);
        link = game_get_link(game, north_link);
        if(link_get_space1(link) == id_act)
            id_back = link_get_space2(link);
        if(link_get_space2(link) == id_act)
            id_back = link_get_space1(link);
        
        link = game_get_link(game, south_link);
        if(link_get_space1(link) == id_act)
            id_next = link_get_space2(link);
        if(link_get_space2(link) == id_act)
            id_next = link_get_space1(link);
        
        if (id_back != NO_ID) {
            space_back = game_get_space(game, id_back);
            graphic_engine_paint_spaces(ge, game, space_back);

        }

        if (id_act != NO_ID) {
            if (id_back != NO_ID)
                screen_area_puts(ge->map, "                          ^");
            graphic_engine_paint_spaces(ge, game, space_act);

            if (id_next != NO_ID)
                screen_area_puts(ge->map, "                          v");
        }

        if (id_next != NO_ID) {
            space_next = game_get_space(game, id_next);
            graphic_engine_paint_spaces(ge, game, space_next);
        }*/
    }

    /* Paint the in the description area */

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
    if((inspected_object = game_get_last_inspected_object(game))){
        strcpy(aux, "Descripcion: ");
        strcat(aux, object_Get_Description(inspected_object));
        
        for(i=0, j = 0; aux[i] != 0; i++,  j = (j + 1) % 21 ){
            if(j == 15){
                for(i=i; aux[i] != ' '; i--);
                aux[i] = '\n';
            }
        }
        
        description = strtok(aux, "\n");
        sprintf(str, "  %s", description);
        screen_area_puts(ge->descript, str);
        
        if(description){
            while((description = strtok(NULL, "\n"))){
                sprintf(str, "    %s", description);
                screen_area_puts(ge->descript, str);
            }
        }
        inspected_object = NULL;
    }
    
    if((inspected_space = game_get_last_inspected_space(game))){
        strcpy(aux, "Descripcion: ");
        if((space_get_iluminated(inspected_space)) == TRUE){
            strcat(aux, space_get_long_description(inspected_space));
        }else{
            strcat(aux, space_get_description(inspected_space));
        }
        
        for(i=0, j = 0; aux[i] != 0; i++,  j = (j + 1) % 21 ){
            if(j == 15){
                for(i=i; aux[i] != ' '; i--);
                aux[i] = '\n';
            }
        }
        
        description = strtok(aux, "\n");
        sprintf(str, "  %s", description);
        screen_area_puts(ge->descript, str);
        
        if(description){
            while((description = strtok(NULL, "\n"))){
                sprintf(str, "    %s", description);
                screen_area_puts(ge->descript, str);
            }
        }
        
        inspected_space = NULL;
    }
    
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

/*
 * @brief Se encarga de pintar las casilla 
 *         A partir de una casilla central, pinta esa casilla y las casillas
 *	   adyacentes de la derecha e izquierda
 *  @author Mihai Blidaru
 *  @param ge El motor grafico
 *  @param game La estructura del juego
 *  @param space La casilla central
 *  @return OK si todo ha ido bien o ERROR en caso contrario
 */
STATUS graphic_engine_paint_spaces(Graphic_engine* ge, Game* game, Space* space) {
    Id id_act = NO_ID, id_east = NO_ID, id_west = NO_ID;
    Space* space_act = space, *space_east = NULL, *space_west = NULL;
    Link* west_link = NULL;
    Link* east_link = NULL;
    Id west_link_id = NO_ID;
    Id east_link_id = NO_ID;
    
    char graphics_act[G_ROWS][G_COLUMNS] = {
        {0}
    };
    char graphics_east[G_ROWS][G_COLUMNS] = {
        {0}
    };
    char graphics_west[G_ROWS][G_COLUMNS] = {
        {0}
    };

    char player[3] = "  ";
    char str[255] = "\0";
    char* padding = "                   ";
    char* obj = NULL, *obj_east = NULL, *obj_west = NULL;

    if (!ge || !game || !space)
        return ERROR;

    id_act = space_get_id(space);
    west_link_id = space_get_west(space_act);
    east_link_id = space_get_east(space_act);
    
    west_link = game_get_link(game,west_link_id);
    east_link = game_get_link(game,east_link_id);
    
    id_west = link_get_dest_from(west_link, id_act);
    id_east = link_get_dest_from(east_link, id_act);
    
    space_east = game_get_space(game, id_east);
    space_west = game_get_space(game, id_west);

    if (id_act == game_get_player_location(game)) {
        strncpy(player, "8D", 3);
    }

    if (id_act != NO_ID) {
        /* Si no hay casillas a la derecha o a la izquierda */
        if (id_east == NO_ID && id_west == NO_ID) {
            space_get_graphics(space, graphics_act);
            obj = game_get_obj_list_as_str(game, space);
            sprintf(str, "%s+-------------+", padding);
            screen_area_puts(ge->map, str);
            sprintf(str, "%s| %s        %2d|", padding, player, (int) id_act);
            screen_area_puts(ge->map, str);

            if (space_graphics_areEmpty(space_act) == FALSE) {
                sprintf(str, "%s|   %s   |", padding, graphics_act[0]);
                screen_area_puts(ge->map, str);
                sprintf(str, "%s|   %s   |", padding, graphics_act[1]);
                screen_area_puts(ge->map, str);
                sprintf(str, "%s|   %s   |", padding, graphics_act[2]);
                screen_area_puts(ge->map, str);
            }

            sprintf(str, "%s|%s|", padding, obj);
            screen_area_puts(ge->map, str);
            sprintf(str, "%s+-------------+", padding);
            screen_area_puts(ge->map, str);

            free(obj);

        } else if (id_east != NO_ID && id_west == NO_ID) {
            /*Cuando no hay una casilla adyacente a la izquierda y si a la derecha */
            space_get_graphics(space, graphics_act);
            space_get_graphics(space_east, graphics_east);
            obj = game_get_obj_list_as_str(game, space_act);
            obj_east = game_get_obj_list_as_str(game, space_east);

            sprintf(str, "%s+-------------+ %2ld +-----------+", padding, link_get_id(east_link));
            screen_area_puts(ge->map, str);
            sprintf(str, "%s| %s        %2d| -->|%2d         |", padding, player, (int) id_act, (int) id_east);
            screen_area_puts(ge->map, str);

            if (space_graphics_areEmpty(space_act) == FALSE || space_graphics_areEmpty(space_east) == FALSE) {
                sprintf(str, "%s|   %s   |    |  %s  |", padding, graphics_act[0], graphics_east[0]);
                screen_area_puts(ge->map, str);
                sprintf(str, "%s|   %s   |    |  %s  |", padding, graphics_act[1], graphics_east[1]);
                screen_area_puts(ge->map, str);
                sprintf(str, "%s|   %s   |    |  %s  |", padding, graphics_act[2], graphics_east[2]);
                screen_area_puts(ge->map, str);
            }
            
            obj_east[10] = '\0';
            sprintf(str, "%s|%s|    |%s |", padding, obj, obj_east);
            screen_area_puts(ge->map, str);
            sprintf(str, "%s+-------------+    +-----------+", padding);
            screen_area_puts(ge->map, str);

            free(obj);
            free(obj_east);
        } else if (id_east == NO_ID && id_west != NO_ID) {
            /*Cuando hay una casilla adyacente a la izquierda y no a la derecha */
            space_get_graphics(space, graphics_act);
            space_get_graphics(space_west, graphics_west);
            obj = game_get_obj_list_as_str(game, space_act);
            obj_west = game_get_obj_list_as_str(game, space_west);

            sprintf(str, "  +-----------+ %2ld +-------------+",  link_get_id(west_link));
            screen_area_puts(ge->map, str);
            sprintf(str, "  |         %2d|<-- | %s        %2d|", (int) id_west, player, (int) id_act);
            screen_area_puts(ge->map, str);

            if (space_graphics_areEmpty(space_act) == FALSE || space_graphics_areEmpty(space_west) == FALSE) {
                sprintf(str, "  |  %s  |    |   %s   |", graphics_west[0], graphics_act[0]);
                screen_area_puts(ge->map, str);
                sprintf(str, "  |  %s  |    |   %s   |", graphics_west[1], graphics_act[1]);
                screen_area_puts(ge->map, str);
                sprintf(str, "  |  %s  |    |   %s   |", graphics_west[2], graphics_act[2]);
                screen_area_puts(ge->map, str);
            }
            obj_west[10] = '\0';
            sprintf(str, "  |%s |    |%s|", obj_west, obj);
            screen_area_puts(ge->map, str);
            sprintf(str, "  +-----------+    +-------------+");
            screen_area_puts(ge->map, str);

            free(obj);
            free(obj_west);
        } else {

            /* cuando hay casillas adyacentes a los dos lados */
            space_get_graphics(space, graphics_act);
            space_get_graphics(space_east, graphics_east);
            space_get_graphics(space_west, graphics_west);
            obj = game_get_obj_list_as_str(game, space_act);
            obj_east = game_get_obj_list_as_str(game, space_east);
            obj_west = game_get_obj_list_as_str(game, space_west);

            sprintf(str, "  +-----------+ %2ld +-------------+ %2ld +-----------+", link_get_id(west_link),  link_get_id(east_link));
            screen_area_puts(ge->map, str);
            sprintf(str, "  |         %2d|<-- | %s        %2d| -->|         %2d|",
                    (int) id_west, player, (int) id_act, (int) id_east);
            screen_area_puts(ge->map, str);

            if (space_graphics_areEmpty(space_act) == FALSE) {
                sprintf(str, "  |  %s  |    |   %s   |    |  %s  |", graphics_west[0], graphics_act[0], graphics_east[0]);
                screen_area_puts(ge->map, str);
                sprintf(str, "  |  %s  |    |   %s   |    |  %s  |", graphics_west[1], graphics_act[1], graphics_east[1]);
                screen_area_puts(ge->map, str);
                sprintf(str, "  |  %s  |    |   %s   |    |  %s  |", graphics_west[2], graphics_act[2], graphics_east[2]);
                screen_area_puts(ge->map, str);
            }
            
            obj_west[10] = '\0';
            obj_east[10] = '\0';
            sprintf(str, "  |%s |    |%s|    |%s |", obj_west, obj, obj_east);
            screen_area_puts(ge->map, str);
            sprintf(str, "  +-----------+    +-------------+    +-----------+");
            screen_area_puts(ge->map, str);
            free(obj);
            free(obj_east);
            free(obj_west);
        }
    }
    return OK;
}