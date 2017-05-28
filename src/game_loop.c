/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Mihai Blidaru
 * @author Javier Bernardo
 * @version 1.0
 * @date 31-01-2017
 * @copyright GNU Public License
 */

/** @mainpage Indiana Jones 2D - Juego Conversacional
 * En la cuarta iteración (I4) se continúa con el desarrollo del
 * proyecto y de las habilidades y los conceptos necesarios para <br>
 * ello, así como con la introducción y uso  de herramientas apropiadas 
 * para dicha actividad. En esta iteración se abandonará <br>
 * el Juego de la Oca como referencia para el desarrollo, 
 * puesto que deja de ser un modelo adecuado para ilustrar las <br>
 * funcionalidades adicionales necesarias para completar un sistema 
 * que soporte Aventuras Conversacionales. Se creará un nuevo juego<br>
 * que demostrara las habilidades adquiridas por el equipo. <br>

 *  @section dev Desarolladores
 * - Javier Bernardo
 * - Laura Bernal
 * - Mihai Blidaru
 * - Sandra Benítez
 */ 




/* Cabeceras Libc */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

/* Cabeceras propias */
#include "graphic_engine.h"
#include "game.h"
#include "game_management.h"
#include "command.h"
#include "game_rules.h"

/** @brief Punto de entrada del juego. Se encarga de inicializar y ejecutar el juego
 *
 *  @author Profesores PPROG
 *  @author Mihai Blidaru
 *  @private
 *
 */
int main(int argc, char *argv[]) {
    int i;
    Game* game = NULL;
    Graphic_engine *gengine;
    Command* command_Manager = NULL;
    STATUS result = ERROR;
    extern char *cmd_to_str[];
    char *stat_to_str[2] = {"ERROR", "OK"};
    BOOL logging = FALSE;
    int log_argc = 0;
    int nv_argc = 0;
    int nr_argc = 0;
    int nw_argc = 0;
    BOOL noVerbose = FALSE;
    BOOL no_wait = FALSE;
    FILE* logfile = NULL;
    T_Command last_command = UNKNOWN;
    int game_rules_run = 0;
    

    /* Se parsean los argumentos*/
    if (argc < 5) {
        fprintf(stderr, "Use: %s <spaces_file> <objects_data_file> <links_file> <player_file> -nv -no_rule -no_wait -l <log_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (i = 1, log_argc = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-nv")) {
            noVerbose = TRUE;
            nv_argc = i;
        }else if (!strcmp(argv[i], "-l")) {
            logging = TRUE;
            log_argc = i;
        }else if (!strcmp(argv[i], "-no_rule")) {
            game_rules_run = INT_MIN;
            nr_argc = i;
        }else if (!strcmp(argv[i], "-no_wait")) {
            no_wait = TRUE;
            nw_argc = 0;
        }
    }
    
    if(noVerbose == TRUE && logging == FALSE){
        fprintf(stderr, "You can't use -nv (No verbose) without -l (log)\n");
        fprintf(stderr, "Use: %s <spaces_file> <objects_data_file> <links_file> <player_file> -nv -no_rule -no_wait -l <log_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (logging) {
        if (i == argc - 1) {
            fprintf(stderr, "Use: %s <spaces_file> <objects_file> <links_file> <player_file> -nv -no_rule -no_wait -l <log_name>\n", argv[0]);
            return EXIT_FAILURE;
        }
        
        if((log_argc == (nv_argc - 1)) || (log_argc == (nr_argc - 1)) || (log_argc == (nw_argc - 1)) ){
            fprintf(stderr, "You can't use that filename. Chose other.\n");
            fprintf(stderr, "Use: %s <spaces_file> <objects_data_file> <links_file> <player_file> -nv -no_rule -no_wait -l <log_name>\n", argv[0]);
            return EXIT_FAILURE;
        }
        
        /* Si se introduce un comando ./exe spaces.dat objects.dat -l objects.dat */
        if (!strcmp(argv[i + 1], argv[1]) || !strcmp(argv[i + 1], argv[2]) || !strcmp(argv[i + 1], argv[3]) || !strcmp(argv[i + 1], argv[4])) {
            fprintf(stderr, "Can not read/write the same file\n");
            return EXIT_FAILURE;
        }

        if (!(logfile = fopen(argv[log_argc + 1], "w"))) {
            fprintf(stderr, "Could not create log file. Make sure you have permisions.\n");
            return EXIT_FAILURE;
        }
    }

    /* Se inicia el juego */
    if (!(command_Manager = Command_ini())) {
        fprintf(stderr, "Error while initializing game.\n");
        if (logging)
            fclose(logfile);
        return EXIT_FAILURE;
    }
    
    if(!(game = game_create())){
        fprintf(stderr, "Error while initializing game.\n");
        Command_destroy(command_Manager);
        if (logging)
            fclose(logfile);
        return EXIT_FAILURE;
    }
    
    if (game_management_start_from_file(game, argv[1], argv[2], argv[3], argv[4]) == ERROR) {
        fprintf(stderr, "Error while initializing game.\n");
        Command_destroy(command_Manager);
        game_destroy(game);
        if (logging)
            fclose(logfile);
        return EXIT_FAILURE;
    }

    if(noVerbose == FALSE){
        if ((gengine = graphic_engine_create()) == NULL) {
            fprintf(stderr, "Error while initializing graphic engine.\n");
            Command_destroy(command_Manager);
            game_destroy(game);
            if (logging)
                fclose(logfile);
            return EXIT_FAILURE;
        }
    }
    
    if(noVerbose == FALSE && no_wait == FALSE){
        graphic_engine_play_intro(stdout);
    }
    while ((Command_get_cmd(command_Manager) != QUIT) && !game_is_over(game)) {
        if(noVerbose == FALSE)
            graphic_engine_paint_game(gengine, game);
        
        Command_clear(command_Manager);
        get_user_input(command_Manager);
         last_command = Command_get_cmd(command_Manager);
        if(last_command == DIR && noVerbose == FALSE){
            graphic_engine_paint_directions(stdout, game);
            game_rules_run--;
        }else if(last_command == HELP && noVerbose == FALSE){
            graphic_engine_paint_help(stdout);
            game_rules_run--;
        }
        sleep(1);
        if(last_command == SAVE || last_command == LOAD || last_command == INSPECT || last_command == UNKNOWN){
            game_rules_run--;
        }
        
        result = game_update(game, command_Manager);
        if(game_rules_run == 2){
            game_rules_run_random_rule(game);
            game_rules_run = 0;
        }
        if (logging){
            fprintf(logfile, "%s %s: %s\n", cmd_to_str[Command_get_cmd(command_Manager) - NO_CMD], Command_get_cmd_arg(command_Manager, 0), stat_to_str[result]);
            fflush(logfile); /* Forzar la escritura despues de cada comando */
        }
        game_rules_run++;
        
    }
    
    if(game_is_over(game) == TRUE){
        graphic_engine_game_over(stdout);
    }

    if (logging)
        fclose(logfile);

    /* Se destruye el juego */
    game_destroy(game);
    if(noVerbose == FALSE)
        graphic_engine_destroy(gengine);
    
    Command_destroy(command_Manager);
    return EXIT_SUCCESS;
}

