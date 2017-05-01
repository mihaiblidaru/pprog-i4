/**
 * @brief Programa para probar el modulo game.
 *       Progama para probar la correcta funcionalidad del
 *       nuevo TAD Game.
 *
 * @file game_test.c
 * @author Mihai Blidaru
 * @version 1.0
 * @date 24-04-2017
 */
 
/* Cabeceras Libc*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Cabeceras Propias */
#include "game.h"
#include "command.h"
#include "tests/game_test.h"
#include "tests/test.h"
/**
 * Número maximo de tests
 * @cond
 */
#define MAX_TESTS 53

typedef void(*test_function)();

static test_function tests[MAX_TESTS] = {
         test1_game_create,
         test1_game_destroy,
         test2_game_destroy,
         test1_game_update,
         test2_game_update,
         test3_game_update,
         test1_game_is_over,
         test2_game_is_over,
         test1_game_add_object,
         test2_game_add_object,
         test3_game_add_object,
         test1_game_add_space,
         test2_game_add_space,
         test3_game_add_space,
         test1_game_add_link,
         test2_game_add_link,
         test3_game_add_link,
         test1_game_add_player,
         test2_game_add_player,
         test3_game_add_player,
         test1_game_get_link,
         test2_game_get_link,
         test3_game_get_link,
         test1_game_get_link_at,
         test2_game_get_link_at,
         test3_game_get_link_at,
         test1_game_get_space,
         test2_game_get_space,
         test3_game_get_space,
         test1_game_get_space_at,
         test2_game_get_space_at,
         test3_game_get_space_at,
         test1_game_get_object_at,
         test2_game_get_object_at,
         test3_game_get_object_at,
         test1_game_get_die,
         test2_game_get_die,
         test1_game_get_player,
         test2_game_get_player,
         test1_game_get_obj_list_as_str,
         test2_game_get_obj_list_as_str,
         test1_game_get_last_inspected_space,
         test2_game_get_last_inspected_space,
         test1_game_get_last_inspected_object,
         test2_game_get_last_inspected_object,
         test3_game_get_last_inspected_object,
         test1_game_get_player_location,
         test2_game_get_player_location,
         test1_game_get_object_location,
         test2_game_get_object_location,
         test3_game_get_object_location,
         test1_game_get_dialogue,
         test2_game_get_dialogue
};

int main(int argc, char** argv){
    int test = 0;
    int all = 1;
    int i;
    
    if (argc < 2) {
        printf("Running all test for module game:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        if (test < 1 || test > MAX_TESTS) {
            printf("Error: unknown test %d\n", test);
            return EXIT_SUCCESS;
        }
        printf("Running test %d:\t", test);
    }
    if(all == 1){
        for(i = 0; i < MAX_TESTS;i++){
            (*tests[i])();
        }
    }else{
        (*tests[test-1])();
    }
    PRINT_PASSED_PERCENTAGE;

    return 1;
}

/**
 * @endcond
 */

/**
 * @test Prueba la funcion que reserva memoria para la estructra del jueg
 * @pre Se reserva memoria normalmente
 * @post La salida tiene que ser el juego inicializado
 */
void test1_game_create(){
    Game* game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game != NULL);
    game_destroy(game);
}

/**
 * @test Prueba la funcon que destruye un juego
 * @pre El juego se ha creado previamente
 * @post La salida esperada es OK
 */
void test1_game_destroy(){
    Game* game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_destroy(game) == OK);
}

/**
 * @test Prueba la funcon que destruye un juego
 * @pre El juego no se ha creado previamente
 * @post La salida esperada es ERROR
 */
void test2_game_destroy(){
    Game* game = NULL;
    PRINT_TEST_RESULT(game_destroy(game) == ERROR);
}

/**
 * @test Prueba la función que actualiza el juego
 * @pre El juego se ha creado y el comando ejecutado es valido
 * @post La salida esperada es OK
 */
void test1_game_update(){
    Game* game = NULL;
    Command* cmd = NULL;
    game = game_create();
    cmd = Command_ini();
    Command_set_cmd(cmd, ROLL);
    PRINT_TEST_RESULT(game_update(game, cmd) == OK);
    Command_destroy(cmd);
    game_destroy(game);
}

/**
 * @test Prueba la función que actualiza el juego
 * @pre El juego no se ha creado. El comando ejecutado es valido
 * @post La salida esperada es ERROR
 */
void test2_game_update(){
    Game* game = NULL;
    Command* cmd = NULL;
    cmd = Command_ini();
    Command_set_cmd(cmd, ROLL);
    PRINT_TEST_RESULT(game_update(game, cmd) == ERROR);
    Command_destroy(cmd);
}

/**
 * @test Prueba la función que actualiza el juego
 * @pre El juego se ha creado pero el comando ejecutado es invalido
 * @post La salida esperada es ERROR
 */
void test3_game_update(){
    Game* game = NULL;
    Command* cmd = NULL;
    game = game_create();
    Command_set_cmd(cmd, ROLL);
    PRINT_TEST_RESULT(game_update(game, cmd) == ERROR);
    game_destroy(game);
}

/**
 * @test Prueba la función devuelve si el juego ha acabado o no
 * @pre El juego ha sido inicializado
 * @post La salida esperada es FALSE
 */
void test1_game_is_over(){
    Game* game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_is_over(game) == FALSE);
    game_destroy(game);
}

/**
 * @test Prueba la función devuelve si el juego ha acabado o no
 * @pre El juego no ha sido inicializado
 * @post La salida esperada es TRUE, de esa forma en gameloop no se sigue jugando
 */
void test2_game_is_over(){
    Game* game = NULL;
    PRINT_TEST_RESULT(game_is_over(game) == TRUE);
    game_destroy(game);
}

/**
 * @test Prueba la función que añade un objeto al juego
 * @pre El juego y el objeto han sido inicializados correctamente
 * @post La salida esperada es OK
 */
void test1_game_add_object(){
    Game* game = NULL;
    Object* object = NULL;
    game = game_create();
    object = object_create();
    PRINT_TEST_RESULT(game_add_object(game, object) == OK);
    game_destroy(game);
}

/**
 * @test Prueba la función que añade un objeto al juego
 * @pre El juego no ha sido inicializado pero el objeto si
 * @post La salida esperada es ERROR
 */
void test2_game_add_object(){
    Game* game = NULL;
    Object* object = NULL;
    object = object_create();
    PRINT_TEST_RESULT(game_add_object(game, object) == ERROR);
    object_destroy(object);
}

/**
 * @test Prueba la función que añade un objeto al juego
 * @pre El juego ha sido inicializado pero el objeto no
 * @post La salida esperada es ERROR
 */
void test3_game_add_object(){
    Game* game = NULL;
    Object* object = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_add_object(game, object) == ERROR);
    game_destroy(game);
}

/**
 * @test Prueba la función que añade un espacio al juego
 * @pre El juego y el espacio han sido inicializados correctamente
 * @post La salida esperada es OK
 */
void test1_game_add_space(){
    Game* game = NULL;
    Space* space = NULL;
    game = game_create();
    space = space_create(1);
    PRINT_TEST_RESULT(game_add_space(game, space) == OK);
    game_destroy(game);
}

/**
 * @test Prueba la función que añade un espacio al juego
 * @pre El juego no ha sido inicializado pero el espacio si
 * @post La salida esperada es ERROR
 */
void test2_game_add_space(){
    Game* game = NULL;
    Space* space = NULL;
    space = space_create(1);
    PRINT_TEST_RESULT(game_add_space(game, space) == ERROR);
    space_destroy(space);
}

/**
 * @test Prueba la función que añade un espacio al juego
 * @pre El juego ha sido inicializado pero el espacio no
 * @post La salida esperada es ERROR
 */
void test3_game_add_space(){
    Game* game = NULL;
    Space* space = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_add_space(game, space) == ERROR);
    game_destroy(game);
}

/**
 * @test Prueba la función que añade un link al juego
 * @pre El juego y el link han sido inicializados correctamente
 * @post La salida esperada es OK
 */
void test1_game_add_link(){
    Game* game = NULL;
    Link* link = NULL;
    game = game_create();
    link = link_create();
    PRINT_TEST_RESULT(game_add_link(game, link) == OK);
    game_destroy(game);
}

/**
 * @test Prueba la función que añade un link al juego
 * @pre El juego no ha sido inicializado pero el link si
 * @post La salida esperada es ERROR
 */
void test2_game_add_link(){
    Game* game = NULL;
    Link* link = NULL;
    link = link_create();
    PRINT_TEST_RESULT(game_add_link(game, link) == ERROR);
    link_destroy(link);
}

/**
 * @test Prueba la función que añade un link al juego
 * @pre El juego ha sido inicializado pero el link no
 * @post La salida esperada es ERROR
 */
void test3_game_add_link(){
    Game* game = NULL;
    Link* link = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_add_link(game, link) == ERROR);
    game_destroy(game);
}

/**
 * @test Prueba la función que añade un jugador al juego
 * @pre El juego y el jugador han sido inicializados correctamente
 * @post La salida esperada es OK
 */
void test1_game_add_player(){
    Game* game = NULL;
    Player* player = NULL;
    game = game_create();
    player = player_create();
    PRINT_TEST_RESULT(game_add_player(game, player) == OK);
    game_destroy(game);
}

/**
 * @test Prueba la función que añade un jugador al juego
 * @pre El juego no ha sido inicializado pero el jugador si
 * @post La salida esperada es ERROR
 */
void test2_game_add_player(){
    Game* game = NULL;
    Player* player = NULL;
    player = player_create();
    PRINT_TEST_RESULT(game_add_player(game, player) == ERROR);
    player_destroy(player);
}

/**
 * @test Prueba la función que añade un jugador al juego
 * @pre El juego ha sido inicializado pero el jugador no
 * @post La salida esperada es ERROR
 */
void test3_game_add_player(){
    Game* game = NULL;
    Player* player = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_add_player(game, player) == ERROR);
    game_destroy(game);
}

/**
 * @test Prueba la función que devuelve el link con in id dado
 * @pre El juego y el link han sido creados correctamente
 * @post La salida debe ser el link creado anteriormente
 */
void test1_game_get_link(){
    Game* game = NULL;
    Link* link = NULL;
    game = game_create();
    link = link_create();
    link_set_id(link, 10);
    game_add_link(game, link);
    PRINT_TEST_RESULT(game_get_link(game, 10) == link);
    game_destroy(game);
}

/**
 * @test Prueba la función que devuelve el link con in id dado
 * @pre El juego no se ha creado pero el link si
 * @post La salida debe ser NULL
 */
void test2_game_get_link(){
    Game* game = NULL;
    Link* link = NULL;
    link = link_create();
    link_set_id(link, 10);
    game_add_link(game, link);
    PRINT_TEST_RESULT(game_get_link(game, 10) == NULL);
}

/**
 * @test Prueba la función que devuelve el link con in id dado
 * @pre El link buscado no coresponde con el id del link añadido
 * @post La salida debe ser NULL
 */
void test3_game_get_link(){
    Game* game = NULL;
    Link* link = NULL;
    game = game_create();
    link = link_create();
    link_set_id(link, 10);
    game_add_link(game, link);
    PRINT_TEST_RESULT(game_get_link(game, 9) == NULL);
    game_destroy(game);
}

/**
 * @test Prueba la función que devuelve el link en una posición dada
 * @pre El link ha sido añadido correctamente
 * @post La salida debe ser el link añadido anteriormente
 */
void test1_game_get_link_at(){
    Game* game = NULL;
    Link* link = NULL;
    game = game_create();
    link = link_create();
    game_add_link(game, link);
    PRINT_TEST_RESULT(game_get_link_at(game, 0) == link);
    game_destroy(game);
}

/**
 * @test Prueba la función que devuelve el link en una posición dada
 * @pre La posición en la que se busca es -1
 * @post La salida debe ser NULL
 */
void test2_game_get_link_at(){
    Game* game = NULL;
    Link* link = NULL;
    link = link_create();
    game_add_link(game, link);
    PRINT_TEST_RESULT(game_get_link_at(game, -1) == NULL);
}

/**
 * @test Prueba la función que devuelve el link en una posición dada
 * @pre El juego no se ha inicializado
 * @post La salida debe ser NULL
 */
void test3_game_get_link_at(){
    Game* game = NULL;
    Link* link = NULL;
    link = link_create();
    game_add_link(game, link);
    PRINT_TEST_RESULT(game_get_link_at(game, 0) == NULL);
}

/**
 * @test Prueba la función que devuelve el espacio con in id dado
 * @pre El juego y el espacio han sido creados correctamente
 * @post La salida debe ser el espacio creado anteriormente
 */
void test1_game_get_space(){
    Game* game = NULL;
    Space* space = NULL;
    game = game_create();
    space = space_create(10);
    game_add_space(game, space);
    PRINT_TEST_RESULT(game_get_space(game, 10) == space);
    game_destroy(game);
}

/**
 * @test Prueba la función que devuelve el espacio con in id dado
 * @pre El juego no se ha creado pero el espacio si
 * @post La salida debe ser NULL
 */
void test2_game_get_space(){
    Game* game = NULL;
    Space* space = NULL;
    space = space_create(2);
    game_add_space(game, space);
    PRINT_TEST_RESULT(game_get_space(game, 10) == NULL);
}

/**
 * @test Prueba la función que devuelve el espacio con in id dado
 * @pre El espacio buscado no coresponde con el id del espacio añadido
 * @post La salida debe ser NULL
 */
void test3_game_get_space(){
    Game* game = NULL;
    Space* space = NULL;
    game = game_create();
    space = space_create(2);
    game_add_space(game, space);
    PRINT_TEST_RESULT(game_get_space(game, 9) == NULL);
    game_destroy(game);
}

/**
 * @test Prueba la función que devuelve el espacio en una posición dada
 * @pre El espacio ha sido añadido correctamente
 * @post La salida debe ser el espacio añadido anteriormente
 */
void test1_game_get_space_at(){
    Game* game = NULL;
    Space* space = NULL;
    game = game_create();
    space = space_create(2);
    game_add_space(game, space);
    PRINT_TEST_RESULT(game_get_space_at(game, 0) == space);
    game_destroy(game);
}

/**
 * @test Prueba la función que devuelve el espacio en una posición dada
 * @pre La posición en la que se busca es -1
 * @post La salida debe ser NULL
 */
void test2_game_get_space_at(){
    Game* game = NULL;
    Space* space = NULL;
    space = space_create(2);
    game_add_space(game, space);
    PRINT_TEST_RESULT(game_get_space_at(game, -1) == NULL);
}

/**
 * @test Prueba la función que devuelve el espacio en una posición dada
 * @pre El juego no se ha inicializado
 * @post La salida debe ser NULL
 */
void test3_game_get_space_at(){
    Game* game = NULL;
    Space* space = NULL;
    space = space_create(2);
    game_add_space(game, space);
    PRINT_TEST_RESULT(game_get_space_at(game, 0) == NULL);
}

/**
 * @test Prueba la función que devuelve el objeto en una posición dada
 * @pre El objeto ha sido añadido correctamente
 * @post La salida debe ser el objeto añadido anteriormente
 */
void test1_game_get_object_at(){
    Game* game = NULL;
    Object* object = NULL;
    game = game_create();
    object = object_create();
    game_add_object(game, object);
    PRINT_TEST_RESULT(game_get_object_at(game, 0) == object);
    game_destroy(game);
}

/**
 * @test Prueba la función que devuelve el objeto en una posición dada
 * @pre La posición en la que se busca es -1
 * @post La salida debe ser NULL
 */
void test2_game_get_object_at(){
    Game* game = NULL;
    Object* object = NULL;
    object = object_create();
    game_add_object(game, object);
    PRINT_TEST_RESULT(game_get_object_at(game, -1) == NULL);
}

/**
 * @test Prueba la función que devuelve el objeto en una posición dada
 * @pre El juego no se ha inicializado
 * @post La salida debe ser NULL
 */
void test3_game_get_object_at(){
    Game* game = NULL;
    Object* object = NULL;
    object = object_create();
    game_add_object(game, object);
    PRINT_TEST_RESULT(game_get_object_at(game, 0) == NULL);
}

/**
 * @test Prueba la función que devuelve el dado del juego
 * @pre El juego ha sido creado correctamente
 * @post La salida debe ser un puntero distinto de NULL
 */
void test1_game_get_die(){
    Game* game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_get_die(game) != NULL);
    game_destroy(game);
}

/**
 * @test Prueba la función que devuelve el dado del juego
 * @pre El juego no ha sido inicializado
 * @post La salida debe ser NULL
 */
void test2_game_get_die(){
    Game* game = NULL;
    PRINT_TEST_RESULT(game_get_die(game) == NULL);
}

/**
 * @test Prueba la función que devuelve el jugador del juego
 * @pre El juego y el jugador han sido creado correctamente
 * @post La salida debe ser un puntero distinto de NULL
 */
void test1_game_get_player(){
    Game* game = NULL;
    Player* player = NULL;
    game = game_create();
    player = player_create();
    game_add_player(game, player);
    PRINT_TEST_RESULT(game_get_player(game) != NULL);
    game_destroy(game);
}

/**
 * @test Prueba la función que devuelve el jugador del juego
 * @pre El juego ha sido inicializado pero no se ha añadido ningun jugador
 * @post La salida debe ser NULL
 */
void test2_game_get_player(){
    Game* game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_get_player(game) == NULL);
    game_destroy(game);
}

/**
 * @test Prueba la funcion que devuelve la lista de objetos de una casilla como cadena
 * @pre El juego, una casilla, y un objeto han sido añadidos correctamente
 * @post La salida esperada es la lista de objetos de la casilla
 */
void test1_game_get_obj_list_as_str(){
    Game* game = NULL;
    Space* space = NULL;
    Object* object = NULL;
    char* aux = NULL;
    game = game_create();
    space = space_create(2);
    game_add_space(game, space);
    object = object_create();
    object_Set_Id(object, 1);
    game_add_object(game, object);
    space_add_object(space, 1);
    aux = game_get_obj_list_as_str(game, space);
    PRINT_TEST_RESULT(strncmp(aux, " O1", 3) == 0);
    game_destroy(game);
}

/**
 * @test Prueba la funcion que devuelve la lista de objetos de una casilla como cadena
 * @pre El juego no se ha inicializado
 * @post La salida esperada es NULL
 */
void test2_game_get_obj_list_as_str(){
    Game* game = NULL;
    Space* space;
    char* aux = NULL;
    space = space_create(3);
    game_add_space(game, space);
    space_add_object(space, 1);
    aux = game_get_obj_list_as_str(game, space);
    PRINT_TEST_RESULT(aux == NULL);
    space_destroy(space);
}

/**
 * @test Prueba la función que devuelve el ultimo espacio inspeccionado
 * @pre El juego ha sido creado, se ha añadido un espacio y se ha colocado al jugador dentro
 * @post La salida esperada es la casilla en la que esta el jugador
 */
void test1_game_get_last_inspected_space(){
    Game* game = NULL;
    Space* space = NULL;
    Player* player = NULL;
    Command* cmd = NULL;
    game = game_create();
    space = space_create(2);
    cmd = Command_ini();
    game_add_space(game, space);
    player = player_create();
    player_Set_Location(player, 2);
    game_add_player(game, player);
    Command_set_cmd(cmd, INSPECT);
    Command_set_cmd_arg(cmd, "s", 0);
    game_update(game, cmd);
    PRINT_TEST_RESULT(game_get_last_inspected_space(game) == space);
    game_destroy(game);
}

/**
 * @test Prueba la función que devuelve el ultimo espacio inspeccionado
 * @pre El juego no ha sido creado
 * @post La salida esperada es NULL
 */
void test2_game_get_last_inspected_space(){
    Game* game = NULL;
    PRINT_TEST_RESULT(game_get_last_inspected_space(game) == NULL);
}

/**
 * @test Prueba la función que devuelve el ultimo objeto inspeccionado
 * @pre El nombre del objeto añadido es "obj"
 * @post La salida esperada es el objeto con nombre "obj"
 */
void test1_game_get_last_inspected_object(){
    Game* game = NULL;
    Space* space = NULL;
    Player* player = NULL;
    Command* cmd = NULL;
    Object* object = NULL;
    game = game_create();
    space = space_create(2);
    object = object_create();
    object_Set_Id(object, 1);
    object_Set_Name(object, "obj");
    object_Set_Hidden(object, FALSE);
    cmd = Command_ini();
    player = player_create();
    player_Set_Location(player, 2);
    player_Set_Max_Objects(player, 1);
    player_Add_Object(player, 1);
    game_add_space(game, space);
    game_add_player(game, player);
    game_add_object(game, object);
    Command_set_cmd(cmd, INSPECT);
    Command_set_cmd_arg(cmd, "obj", 0);
    game_update(game, cmd);
    PRINT_TEST_RESULT(game_get_last_inspected_object(game) == object);
    game_destroy(game);
}

/**
 * @test Prueba la función que devuelve el ultimo objeto inspeccionado
 * @pre El objeto está marcado como oculto
 * @post La salida esperada es NULL
 */
void test2_game_get_last_inspected_object(){
    Game* game = NULL;
    Space* space = NULL;
    Player* player = NULL;
    Command* cmd = NULL;
    Object* object = NULL;
    game = game_create();
    space = space_create(2);
    object = object_create();
    object_Set_Id(object, 1);
    object_Set_Name(object, "obj");
    object_Set_Hidden(object, TRUE);
    cmd = Command_ini();
    player = player_create();
    player_Set_Location(player, 2);
    player_Set_Max_Objects(player, 1);
    player_Add_Object(player, 1);
    game_add_space(game, space);
    game_add_player(game, player);
    game_add_object(game, object);
    Command_set_cmd(cmd, INSPECT);
    Command_set_cmd_arg(cmd, "obj", 0);
    game_update(game, cmd);
    PRINT_TEST_RESULT(game_get_last_inspected_object(game) == NULL);
    game_destroy(game);
}

/**
 * @test Prueba la función que devuelve el ultimo objeto inspeccionado
 * @pre El nombre del objeto no se corresponde con el del objeto del juego
 * @post La salida esperada es NULL
 */
void test3_game_get_last_inspected_object(){
    Game* game = NULL;
    Space* space = NULL;
    Player* player = NULL;
    Command* cmd = NULL;
    Object* object = NULL;
    game = game_create();
    space = space_create(2);
    object = object_create();
    object_Set_Id(object, 1);
    object_Set_Name(object, "obj");
    object_Set_Hidden(object, TRUE);
    cmd = Command_ini();
    player = player_create();
    player_Set_Location(player, 2);
    player_Set_Max_Objects(player, 1);
    player_Add_Object(player, 1);
    game_add_space(game, space);
    game_add_player(game, player);
    game_add_object(game, object);
    Command_set_cmd(cmd, INSPECT);
    Command_set_cmd_arg(cmd, "obj2", 0);
    game_update(game, cmd);
    PRINT_TEST_RESULT(game_get_last_inspected_object(game) == NULL);
    game_destroy(game);
}

/**
 * @test Prueba la funcion que devuelve la localizacion del jugador
 * @pre El jugador se ha colocado en la casilla con id 2
 * @post La salida es 2, la localización del jugador
 */
void test1_game_get_player_location(){
    Game* game = NULL;
    Player* player = NULL;
    game = game_create();
    player = player_create();
    player_Set_Location(player, 2);
    game_add_player(game, player);
    PRINT_TEST_RESULT(game_get_player_location(game) == 2);
    game_destroy(game);
}

/**
 * @test Prueba la funcion que devuelve la localizacion del jugador
 * @pre El jugador no se ha añadido al juego
 * @post La salida es NO_ID, localizacion nula
 */
void test2_game_get_player_location(){
    Game* game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_get_player_location(game) == NO_ID);
    game_destroy(game);
}

/**
 * @test Prueba la funcion que devuelve la localizacion de un objeto
 * @pre El objeto se ha añadido en la casilla con id 2
 * @post La salida es 2, la localización del objeto
 */
void test1_game_get_object_location(){
    Game* game = NULL;
    Space* space = NULL;
    Object* object = NULL;
    game = game_create();
    space = space_create(2);
    object = object_create();
    object_Set_Id(object, 1);
    object_Set_Name(object, "obj");
    object_Set_Hidden(object, TRUE);
    space_add_object(space, 1);
    game_add_space(game, space);
    game_add_object(game, object);
    PRINT_TEST_RESULT(game_get_object_location(game, object) == 2);
    game_destroy(game);
}

/**
 * @test Prueba la funcion que devuelve la localizacion de un objeto
 * @pre El objeto no se ha añadido al juego
 * @post La salida es NO_ID - localizacion nula
 */
void test2_game_get_object_location(){
    Game* game = NULL;
    Space* space = NULL;
    Object* object = NULL;
    game = game_create();
    space = space_create(2);
    space_add_object(space, 1);
    game_add_space(game, space);
    game_add_object(game, object);
    PRINT_TEST_RESULT(game_get_object_location(game, object) == NO_ID);
    game_destroy(game);
}

/**
 * @test Prueba la funcion que devuelve la localizacion de un objeto
 * @pre El objeto está marcado como oculto
 * @post La salida es NO_ID - localizacion nula
 */
void test3_game_get_object_location(){
    Game* game = NULL;
    Space* space = NULL;
    Object* object = NULL;
    game = game_create();
    space = space_create(2);
    object = object_create();
    object_Set_Id(object, 1);
    object_Set_Name(object, "obj");
    object_Set_Hidden(object, TRUE);
    game_add_space(game, space);
    game_add_object(game, object);
    PRINT_TEST_RESULT(game_get_object_location(game, object) == NO_ID);
    game_destroy(game);
}


/**
 * @test Prueba la función que devuelve el dialogo del juego
 * @pre El juego ha sido creado correctamente
 * @post La salida debe ser un puntero distinto de NULL
 */
void test1_game_get_dialogue(){
    Game* game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_get_dialogue(game) != NULL);
    game_destroy(game);
}

/**
 * @test Prueba la función que devuelve el dialogo del juego
 * @pre El juego no ha sido inicializado
 * @post La salida debe ser NULL
 */
void test2_game_get_dialogue(){
    Game* game = NULL;
    PRINT_TEST_RESULT(game_get_dialogue(game) == NULL);
}

