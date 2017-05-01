/**
 * @brief Programa para probar el modulo game_management.
 *       Progama para probar la correcta funcionalidad del
 *       nuevo TAD Game_management.
 *
 * @file game_management_test.c
 * @author Sandra Benítez 
 * @author Laura Bernal
 * @version 1.0
 * @date 24-04-2017
 */
 
/* Cabeceras Libc*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Cabeceras Propias */
#include "game.h"
#include "space.h"
#include "game_management.h"
#include "tests/game_management_test.h"
#include "tests/test.h"

/**
 * Número maximo de tests
 * @cond
 */
#define MAX_TESTS 6

int main(int argc, char** argv){
    int test = 0;
    int all = 1;
    
    if (argc < 2) {
        printf("Running all test for module Game_management:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
        }
    }
    
    if (all || test == 1) test1_game_management_start_from_file();
    if (all || test == 2) test2_game_management_start_from_file();
    if (all || test == 3) test1_game_management_save();
    if (all || test == 4) test2_game_management_save();
    if (all || test == 5) test1_game_management_load();
    if (all || test == 6) test2_game_management_load();
    
    PRINT_PASSED_PERCENTAGE;

    return 1;
}

/**
 * @endcond
 */
 
/*
 * @test Prueba la función que carga los datos del juego desde un archivo 
 * @pre  Se lee de forma correcta los archivos
 * @post La salida esperada es OK
 */
void test1_game_management_start_from_file(){
    Game* game = NULL;
    char* spacesFile = "spaces.dat";
    char* objectsFile = "objects.dat";
    char* linksfile = "links.dat";
    char* playersFile = "player.dat";
    game = game_create();
    PRINT_TEST_RESULT(game_management_start_from_file(game, spacesFile, objectsFile, linksfile, playersFile) == OK);
}

/*
 * @test Prueba la función que carga los datos del juego desde un archivo 
 * @pre  No se lee de forma correcta del archivo
 * @post La salida esperada es ERROR
 */
void test2_game_management_start_from_file(){
    Game* game = NULL;
    char* spacesFile = "spaces.dat";
    char* objectsFile = "objects.dat";
    char* linksfile = "links.dat";
    char* playersFile = "player.dat";
    
    PRINT_TEST_RESULT(game_management_start_from_file(game, spacesFile, objectsFile, linksfile, playersFile) == ERROR);
    
}

/*
 * @test Prueba que la función guarde los datos de la partida con el mismo formato que los ficheros de carga
 * @pre El juego se ha creado correctamente y el nombre del archivo es valido
 * @post La salida esperada es OK
 */
void test1_game_management_save(){
    Game * game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_management_save(game, "/tmp/tmp_save.dat") == SAVE_OK);
    game_destroy(game);
}

 /*
 * @test Prueba que la función guarde los datos de la partida con el mismo formato que los ficheros de carga
 * @pre El juego no ha sido inicializado y el nombre del archivo es nulo
 * @post La salida esperada es ERROR
 */
void test2_game_management_save(){
    Game* game = NULL;
    char* f = NULL;
    PRINT_TEST_RESULT(game_management_save(game, f) == BAD_ARGUMENTS);
}
 
 /*
 * @test Prueba la función que carga los datos del juego desde un archivo
 * @pre El nombre del fichero desde donde cargar los datos
 * @post La salida esperada es OK
 */
void test1_game_management_load(){
    Game * game = NULL;
    game = game_create();
    
    PRINT_TEST_RESULT(game_management_load(game, "player.dat") == OK);
}
 
 /*
 * @test Prueba la función que carga los datos del juego desde un archivo
 * @pre El juego está sin inicializar
 * @post La salida esperada es ERROR
 */
void test2_game_management_load(){
    Game* game = NULL;
 
    PRINT_TEST_RESULT(game_management_load(game, "player.dat") == ERROR);
}