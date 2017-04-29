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

/** @mainpage Juego de la Oca - Tercera Iteración del Proyecto (I3): Prototipo de Juego Conversacional
 * En la tercera iteración (I3) se continúa con el desarrollo del
 * proyecto y de las habilidades y los conceptos necesarios para <br>
 * ello, así como con la introducción y uso  de herramientas apropiadas 
 * para dicha actividad. En esta iteración se abandonará <br>
 * el Juego de la Oca como referencia para el desarrollo, 
 * puesto que deja de ser un modelo adecuado para ilustrar las <br>
 * funcionalidades adicionales necesarias para completar un sistema 
 * que soporte Aventuras Conversacionales. Sin embargo, se demostrará <br>
 * la versatilidad del sistema conseguido, creando una nueva edición 
 * del Juego de la Oca  que  utilice  las nuevas versiones de los <br>
 * módulos  del  proyecto obtenidas  como  resultado de esta iteración.
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
    BOOL noVerbose = FALSE;
    FILE* logfile = NULL;
    int game_rules_run = 0;
    

    /* Se parsean los argumentos*/
    if (argc < 5) {
        fprintf(stderr, "Use: %s <spaces_file> <objects_data_file> <links_file> <player_file> -nv -l <log_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-nv")) {
            noVerbose = TRUE;
            break;
        }
    }
    
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-l")) {
            logging = TRUE;
            break;
        }
    }
    
    if(noVerbose == TRUE && logging == FALSE){
        fprintf(stderr, "You can't use -nv (No verbose) without -l (log)\n");
        fprintf(stderr, "Use: %s <spaces_file> <objects_data_file> <links_file> <player_file> -nv -l <log_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (logging) {
        if (i == argc - 1) {
            fprintf(stderr, "Use: %s <spaces_file> <objects_file> <links_file> <player_file> -nv -l <log_name>\n", argv[0]);
            return EXIT_FAILURE;
        }
        
        if(!strcmp(argv[i+1], "-nv")){
            fprintf(stderr, "Token -nv is reserved, chose other name for the logdfile\n");
            fprintf(stderr, "Use: %s <spaces_file> <objects_data_file> <links_file> <player_file> -nv -l <log_name>\n", argv[0]);
            return EXIT_FAILURE;
        }
        
        /* Si se introduce un comando ./exe spaces.dat objects.dat -l objects.dat */
        if (!strcmp(argv[i + 1], argv[1]) || !strcmp(argv[i + 1], argv[2]) || !strcmp(argv[i + 1], argv[3]) || !strcmp(argv[i + 1], argv[4])) {
            fprintf(stderr, "Can not read/write the same file\n");
            return EXIT_FAILURE;
        }

        if (!(logfile = fopen(argv[i + 1], "w"))) {
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
    
    if(noVerbose == FALSE){
        graphic_engine_play_intro(stdout);
    }
    while ((Command_get_cmd(command_Manager) != QUIT) && !game_is_over(game)) {
        if(noVerbose == FALSE)
            graphic_engine_paint_game(gengine, game);
        
        Command_clear(command_Manager);
        get_user_input(command_Manager);
        if(Command_get_cmd(command_Manager) == DIR && noVerbose == FALSE){
            graphic_engine_paint_directions(stdout, game);
        }else if(Command_get_cmd(command_Manager) == HELP && noVerbose == FALSE){
            graphic_engine_paint_help(stdout);
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

    if (logging)
        fclose(logfile);

    /* Se destruye el juego */
    game_destroy(game);
    if(noVerbose == FALSE)
        graphic_engine_destroy(gengine);
    
    Command_destroy(command_Manager);
    return EXIT_SUCCESS;
}

