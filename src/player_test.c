/** 
 * @brief Prueba el módulo Player
 * 
 * @file player_test.c
 * @author Mihai Blidaru
 * @version 2.0 
 * @date 29-03-2017
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "test.h"
#include "tests/player_test.h"
#include "player.h"

/**
 * @cond
 * Número máximo de Pruebas para el módulo player 
 * 
 */
#define MAX_TESTS 31

/** 
 * @brief Funcion principal de pruebas para el modulo Player. 
 * 
 * Dos modos de ejecucion:
 *   1.-Si se ejecuta sin parametros se ejecutan todas las pruebas 
 *   2.-Si se ejecuta con un numero entre 1 y el numero de pruebas solo ejecuta 
 *      la prueba indicada  
 *  @private
 */
int main(int argc, char** argv) {

    int test = 0;
    int all = 1;
    
    if (argc < 2) {
        printf("Running all test for module Player:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
        }  
    }
        
    if (all || test == 1) test1_player_create();
    if (all || test == 2) test1_player_set_name();
    if (all || test == 3) test2_player_set_name();
    if (all || test == 4) test3_player_set_name();
    if (all || test == 5) test1_player_set_id();
    if (all || test == 6) test2_player_set_id();
    if (all || test == 7) test3_player_set_id();
    if (all || test == 8) test1_player_set_location();
    if (all || test == 9) test2_player_set_location();
    if (all || test == 10) test3_player_set_location();
    if (all || test == 11) test1_player_get_id();
    if (all || test == 12) test2_player_get_id();
    if (all || test == 13) test3_player_get_id();
    if (all || test == 14) test1_player_get_name();
    if (all || test == 15) test2_player_get_name();
    if (all || test == 16) test3_player_get_name();
    if (all || test == 17) test1_player_get_location();
    if (all || test == 18) test2_player_get_location();
    if (all || test == 19) test3_player_get_location();
    if (all || test == 20) test1_player_add_object();
    if (all || test == 21) test2_player_add_object();
    if (all || test == 22) test3_player_add_object();
    if (all || test == 23) test1_player_remove_object();
    if (all || test == 24) test2_player_remove_object();
    if (all || test == 25) test3_player_remove_object();
    if (all || test == 26) test4_player_remove_object();
    if (all || test == 27) test1_player_set_max_objects();
    if (all || test == 28) test2_player_set_max_objects();
    if (all || test == 29) test3_player_set_max_objects();
    if (all || test == 30) test4_player_set_max_objects();
    if (all || test == 21) test1_player_has_object();
    if (all || test == 32) test2_player_has_object();
    if (all || test == 33) test3_player_has_object();
    
    PRINT_PASSED_PERCENTAGE;
    return 0;

}

/**
 * @endcond
 */
 
/* 
 * @test Prueba si se crea correctamente un jugador
 * @post Un puntero no nulo al jugador creado
 */ 
void test1_player_create(){
    Player* player = NULL;
    player = player_create();
    PRINT_TEST_RESULT(player != NULL);
    player_destroy(player);
}

/* 
 * @test Prueba si se le asigna correctamente un nombre a un jugador
 * @pre El nombre del jugador
 * @post La salida tiene que ser el puntero al jugador
 */  
void test1_player_set_name() {
    Player *player;
    player = player_create();
    PRINT_TEST_RESULT(player_Set_Name(player, "Bob") == player);
    player_destroy(player);
}

/* 
 * @test Prueba asignar un nombre a un jugador sin inicializar
 * @pre El jugador al que establecer el nombre es un puntero a NULL
 * @post La salida debe ser NULL
 */ 
void test2_player_set_name() {
    Player *player = NULL;
    PRINT_TEST_RESULT(player_Set_Name(player, "hola") == NULL);
}

/* 
 * @test Prueba asignarle un nombre nulo a un jugador
 * @pre La cadena que se quiere asignar es un puntero a NULL
 * @post La salida tiene que ser NULL
 */  
void test3_player_set_name() {
    Player *player = NULL;
    player = player_create();
    PRINT_TEST_RESULT(player_Set_Name(player, NULL) == NULL);
    player_destroy(player);
}

/* 
 * @test Prueba asignar un id a un jugador en condiciones normales
 * @pre Al jugador se le asigna un id cualquiera mayor que cero
 * @post La salida tiene que ser el puntero al jugador
 */ 
void test1_player_set_id() {
    Player *player;
    player = player_create();
    PRINT_TEST_RESULT(player_Set_Id(player, 10) == player);
    player_destroy(player);
}

/* 
 * @test Prueba asignar un id a un jugador sin inicializar
 * @pre El jugador al que establecer el nombre es un puntero a NULL
 * @post La salida esperada es NULL
 */ 
void test2_player_set_id() {
    Player *player = NULL;
    PRINT_TEST_RESULT(player_Set_Id(player, 10) == NULL);
}

/*
 * @test Prueba asignar un id a un jugador
 * @pre El id que se quiere asignar es NO_ID
 * @post La salida que se espera es NULL
 */
void test3_player_set_id() {
    Player *player = NULL;
    player = player_create();
    PRINT_TEST_RESULT(player_Set_Id(player, NO_ID) == NULL);
    player_destroy(player);
}

/* 
 * @test Prueba asignarle una localización a un jugador en condiciones 
 * @pre El jugador ha sido previamente inicializado y la localización que se le asigna es valida
 * @post La salida es el puntero al jugador
 */
void test1_player_set_location() {
    Player *player;
    player = player_create();
    PRINT_TEST_RESULT(player_Set_Location(player, 5) == player);
    player_destroy(player);
}

/* 
 * @test Prueba asignarle una localización a un jugador sin inicializar.
 * @pre El jugador no ha sido inicializado previamente
 * @post La salida que se espera es NULL
 */
void test2_player_set_location() {
    Player *player = NULL;
    PRINT_TEST_RESULT(player_Set_Location(player, 10) == NULL);
}

/*
 * @test Prueba asignarle una localización invalida a un jugador.
 * @pre La localización que se quiere asignar al jugador es es negativa
 * @post La salida esperada es NULL
 */
void test3_player_set_location() {
    Player *player;
    player = player_create();
    PRINT_TEST_RESULT(player_Set_Location(player, -1) == NULL);
    player_destroy(player);
}

/*
 * @test Prueba leer el id de un jugador
 * @pre Al jugador se le ha asignado previamente el id 12
 * @post La salida esperada es el id asignado antes (12)
 */
void test1_player_get_id(){
    Player *player = NULL;
    player = player_create();
    player_Set_Id(player, 12);
    PRINT_TEST_RESULT(player_Get_Id(player) == 12);
    player_destroy(player);
}

/*
 * @test Prueba leer el id de un jugador
 * @pre El jugador no ha sido inicializado previamente
 * @post La salida esperada es NO_ID
 */
void test2_player_get_id(){
    Player *player = NULL;
    PRINT_TEST_RESULT(player_Get_Id(player) == NO_ID);
}

/*
 * @test Intenta leer el id del jugador
 * @pre Al jugador no se le ha asignado ninguna id todavia
 * @post La salida esperada es NO_ID
 */
void test3_player_get_id(){
    Player *player = NULL;
    player = player_create();
    PRINT_TEST_RESULT(player_Get_Id(player) == NO_ID);
    player_destroy(player);
}

/*
 * @test Intenta leer el nombre de un jugador
 * @pre Al jugador se le ha asignado previamente el nombre "Bob"
 * @post La salida esperada es el nombre asignado antes : "Bob"
 */
void test1_player_get_name(){
    Player *player = NULL;
    player = player_create();
    player_Set_Name(player, "Bob");
    PRINT_TEST_RESULT(strcmp(player_Get_Name(player), "Bob") == 0);
    player_destroy(player);  
}

/*
 * @test Prueba leer el nombre de un jugador
 * @pre El jugador está sin inicializar
 * @post La salida debe ser NULL
 */
void test2_player_get_name(){
    Player *player = NULL;
    PRINT_TEST_RESULT(player_Get_Name(player) == NULL);
}

/*
 * @test Prueba leer el nombre de un jugador
 * @pre Al jugador no se le ha dado ningun nombre previamente
 * @post La salida esperada es una cadena vacía
 */
void test3_player_get_name(){
    Player *player = NULL;
    player = player_create();
    PRINT_TEST_RESULT(strcmp(player_Get_Name(player), "") == 0);
    player_destroy(player);
}

/*
 * @Prueba Leer la localización de un jugador
 * @pre Al jugador se le ha asignado previamente la localización 12
 * @post La salida esperada es la localización previamente asignada (12)
 */
void test1_player_get_location(){
    Player *player = NULL;
    player = player_create();
    player_Set_Location(player, 12);
    PRINT_TEST_RESULT(player_Get_Location(player) == 12);
    player_destroy(player);
}

/*
 * @test Prueba leer la localización del jugador
 * @pre El jugador no ha sido inicializado
 * @post La salida esperada es NO_ID
 */
void test2_player_get_location(){
    Player *player = NULL;
    PRINT_TEST_RESULT(player_Get_Location(player) == NO_ID);
}

/*
 * @test Prueba leer la localización del jugador
 * @pre Al jugador no se le ha asignado ninguna localización todavía
 * @post La salida que se espera es NO_ID
 */
void test3_player_get_location(){
    Player *player = NULL;
    player = player_create();
    PRINT_TEST_RESULT(player_Get_Location(player) == NO_ID);
    player_destroy(player);
}

/*
 * @test Prueba añadir un objeto a un jugador
 * @pre El jugador está sin inicializar
 * @post La salida que se espera es ERROR
 */
void test1_player_add_object(){
    Player* player = NULL;
    PRINT_TEST_RESULT(player_Add_Object(player, 10) == ERROR);
}

/*
 * @test Prueba añadir un objeto a un jugador en condiciones normales
 * @pre El jugador ha sido correctamente inicializado y el id del objeto es valido
 * @post La salida debe ser OK
 */
void test2_player_add_object(){
    Player *player = NULL;
    player = player_create();
    player_Set_Max_Objects(player, 1);
    PRINT_TEST_RESULT(player_Add_Object(player, 10) == OK);
    player_destroy(player);
}

/*
 * @test Prueba añadir un objeto al inventario del jugador
 * @pre El objeto tiene id -1
 * @post La salida que se espera es ERROR
 */
void test3_player_add_object(){
    Player *player = NULL;
    player = player_create();
    PRINT_TEST_RESULT(player_Add_Object(player, -1) == ERROR);
    player_destroy(player);
}


/*
 * @test Prueba quitar un objeto al jugador en condiciones normales
 * @pre Al jugador se le añade un objeto
 * @post La salida que se espera es OK
 */
void test1_player_remove_object(){
    Player *player = NULL;
    player = player_create();
    player_Set_Max_Objects(player, 1);
    player_Add_Object(player, 2);
    PRINT_TEST_RESULT(player_Remove_Object(player, 2) == OK);
    player_destroy(player);
}

/*
 * @test Prueba quitar un objeto a un jugador
 * @pre Al jugador no se le ha añadido todavía ningun objeto
 * @post La salida que se espera es ERROR
 */
void test2_player_remove_object(){
    Player *player = NULL;
    player = player_create();
    PRINT_TEST_RESULT(player_Remove_Object(player, 2) == ERROR);
    player_destroy(player);
}

/*
 * @test Prueba quitar un objeto a un jugador
 * @pre El jugador está sin inicializar
 * @post La salida que se espera es ERROR
 */
void test3_player_remove_object(){
    Player *player = NULL;
    PRINT_TEST_RESULT(player_Remove_Object(player, 2) == ERROR);
}

/*
 * @test Prueba quitar un objeto al jugador
 * @pre El objeto ya ha sido borrado anteriormente
 * @post La salida que se espera es ERROR
 */
void test4_player_remove_object(){
    Player *player = NULL;
    player = player_create();
    player_Add_Object(player, 2);
    player_Remove_Object(player, 2);
    PRINT_TEST_RESULT(player_Remove_Object(player, 2) == ERROR);
    player_destroy(player);
}

/*
 * @test Prueba poner el número máximo de objetos de un jugador
 * @pre Las condiciones son normales: jugador inicializado, número de objeto dentro de limites.
 * @post La salida debe ser el puntero al jugador
 */
void test1_player_set_max_objects(){
    Player *player = NULL;
    player = player_create();
    PRINT_TEST_RESULT(player_Set_Max_Objects(player, 5) == player);
    player_destroy(player);
}


/*
 * @test Prueba poner el número máximo de objetos de un jugador
 * @pre El número de objetos está por encima del limite permitido
 * @post La salida debe ser NULL
 */
void test2_player_set_max_objects(){
    Player *player = NULL;
    player = player_create();
    PRINT_TEST_RESULT(player_Set_Max_Objects(player, 9999) == NULL);
    player_destroy(player);
}

/*
 * @test Prueba poner el número máximo de objetos de un jugador
 * @pre El jugador está sin inicializar
 * @post La salida debe ser NULL
 */
void test3_player_set_max_objects(){
    Player *player = NULL;
    PRINT_TEST_RESULT(player_Set_Max_Objects(player, 5) == NULL);
}

/*
 * @test Prueba poner el numero máximo de objetos de un jugador
 * @pre El número de objetos es un número negativo
 * @post La salida debe ser NULL
 */
void test4_player_set_max_objects(){
    Player *player = NULL;
    player = player_create();
    PRINT_TEST_RESULT(player_Set_Max_Objects(player, -5) == NULL);
    player_destroy(player);
}

/*
 * @test Prubea si el jugador tiene un objeto en condiciones normales
 * @pre Se le añade un objeto al jugador
 * @post La salida debe ser TRUE
 */
void test1_player_has_object(){
    Player *player = NULL;
    player = player_create();
    player_Set_Max_Objects(player, 1);
    player_Add_Object(player, 1);
    PRINT_TEST_RESULT(player_Has_Object(player, 1) == TRUE);
    player_destroy(player);
}

/**
 * @test Prueba si el jugador tiene un objeto
 * @pre El jugador está sin inicializar
 * @post La salida debe ser FALSE
 */
void test2_player_has_object(){
    Player *player = NULL;
    PRINT_TEST_RESULT(player_Has_Object(player, 1) == FALSE);
}

/**
 * @test Prueba si el jugador tiene un objeto
 * @pre El jugador está inicializado pero no tiene ningun objeto
 * @post La salida debe ser FALSE
 */
void test3_player_has_object(){
    Player *player = NULL;
    player = player_create();
    PRINT_TEST_RESULT(player_Has_Object(player, 1) == FALSE);
    player_destroy(player);
}