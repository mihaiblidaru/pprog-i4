/**
 * @brief Define las funciones para la prueba del modulo Game
 * 
 * @file game_test.h
 * @author Mihai Blidaru
 * @version 1.0 
 * @date 14-03-2017
 * @copyright GNU Public License
 */
#ifndef GAME_TEST_H
#define GAME_TEST_H

/**
 * @test Prueba la funcion que reserva memoria para la estructra del jueg
 * @pre Se reserva memoria normalmente
 * @post La salida tiene que ser el juego inicializado
 */
void test1_game_create();

/**
 * @test Prueba la funcon que destruye un juego
 * @pre El juego se ha creado previamente
 * @post La salida esperada es OK
 */
void test1_game_destroy();

/**
 * @test Prueba la funcon que destruye un juego
 * @pre El juego no se ha creado previamente
 * @post La salida esperada es ERROR
 */
void test2_game_destroy();

/**
 * @test Prueba la función que actualiza el juego
 * @pre El juego se ha creado y el comando ejecutado es valido
 * @post La salida esperada es OK
 */
void test1_game_update();

/**
 * @test Prueba la función que actualiza el juego
 * @pre El juego no se ha creado. El comando ejecutado es valido
 * @post La salida esperada es ERROR
 */
void test2_game_update();

/**
 * @test Prueba la función que actualiza el juego
 * @pre El juego se ha creado pero el comando ejecutado es invalido
 * @post La salida esperada es ERROR
 */
void test3_game_update();

/**
 * @test Prueba la función devuelve si el juego ha acabado o no
 * @pre El juego ha sido inicializado
 * @post La salida esperada es FALSE
 */
void test1_game_is_over();

/**
 * @test Prueba la función devuelve si el juego ha acabado o no
 * @pre El juego no ha sido inicializado
 * @post La salida esperada es TRUE, de esa forma en gameloop no se sigue jugando
 */
void test2_game_is_over();

/**
 * @test Prueba la función que añade un objeto al juego
 * @pre El juego y el objeto han sido inicializados correctamente
 * @post La salida esperada es OK
 */
void test1_game_add_object();

/**
 * @test Prueba la función que añade un objeto al juego
 * @pre El juego no ha sido inicializado pero el objeto si
 * @post La salida esperada es ERROR
 */
void test2_game_add_object();

/**
 * @test Prueba la función que añade un objeto al juego
 * @pre El juego ha sido inicializado pero el objeto no
 * @post La salida esperada es ERROR
 */
void test3_game_add_object();

/**
 * @test Prueba la función que añade un espacio al juego
 * @pre El juego y el espacio han sido inicializados correctamente
 * @post La salida esperada es OK
 */
void test1_game_add_space();

/**
 * @test Prueba la función que añade un espacio al juego
 * @pre El juego no ha sido inicializado pero el espacio si
 * @post La salida esperada es ERROR
 */
void test2_game_add_space();

/**
 * @test Prueba la función que añade un espacio al juego
 * @pre El juego ha sido inicializado pero el espacio no
 * @post La salida esperada es ERROR
 */
void test3_game_add_space();

/**
 * @test Prueba la función que añade un link al juego
 * @pre El juego y el link han sido inicializados correctamente
 * @post La salida esperada es OK
 */
void test1_game_add_link();
    

/**
 * @test Prueba la función que añade un link al juego
 * @pre El juego no ha sido inicializado pero el link si
 * @post La salida esperada es ERROR
 */
void test2_game_add_link();

/**
 * @test Prueba la función que añade un link al juego
 * @pre El juego ha sido inicializado pero el link no
 * @post La salida esperada es ERROR
 */
void test3_game_add_link();

/**
 * @test Prueba la función que añade un jugador al juego
 * @pre El juego y el jugador han sido inicializados correctamente
 * @post La salida esperada es OK
 */
void test1_game_add_player();

/**
 * @test Prueba la función que añade un jugador al juego
 * @pre El juego no ha sido inicializado pero el jugador si
 * @post La salida esperada es ERROR
 */
void test2_game_add_player();

/**
 * @test Prueba la función que añade un jugador al juego
 * @pre El juego ha sido inicializado pero el jugador no
 * @post La salida esperada es ERROR
 */
void test3_game_add_player();

/**
 * @test Prueba la función que devuelve el link con in id dado
 * @pre El juego y el link han sido creados correctamente
 * @post La salida debe ser el link creado anteriormente
 */
void test1_game_get_link();

/**
 * @test Prueba la función que devuelve el link con in id dado
 * @pre El juego no se ha creado pero el link si
 * @post La salida debe ser NULL
 */
void test2_game_get_link();

/**
 * @test Prueba la función que devuelve el link con in id dado
 * @pre El link buscado no coresponde con el id del link añadido
 * @post La salida debe ser NULL
 */
void test3_game_get_link();

/**
 * @test Prueba la función que devuelve el link en una posición dada
 * @pre El link ha sido añadido correctamente
 * @post La salida debe ser el link añadido anteriormente
 */
void test1_game_get_link_at();

/**
 * @test Prueba la función que devuelve el link en una posición dada
 * @pre La posición en la que se busca es -1
 * @post La salida debe ser NULL
 */
void test2_game_get_link_at();

/**
 * @test Prueba la función que devuelve el link en una posición dada
 * @pre El juego no se ha inicializado
 * @post La salida debe ser NULL
 */
void test3_game_get_link_at();

/**
 * @test Prueba la función que devuelve el espacio con in id dado
 * @pre El juego y el espacio han sido creados correctamente
 * @post La salida debe ser el espacio creado anteriormente
 */
void test1_game_get_space();

/**
 * @test Prueba la función que devuelve el espacio con in id dado
 * @pre El juego no se ha creado pero el espacio si
 * @post La salida debe ser NULL
 */
void test2_game_get_space();

/**
 * @test Prueba la función que devuelve el espacio con in id dado
 * @pre El espacio buscado no coresponde con el id del espacio añadido
 * @post La salida debe ser NULL
 */
void test3_game_get_space();

/**
 * @test Prueba la función que devuelve el espacio en una posición dada
 * @pre El espacio ha sido añadido correctamente
 * @post La salida debe ser el espacio añadido anteriormente
 */
void test1_game_get_space_at();

/**
 * @test Prueba la función que devuelve el espacio en una posición dada
 * @pre La posición en la que se busca es -1
 * @post La salida debe ser NULL
 */
void test2_game_get_space_at();

/**
 * @test Prueba la función que devuelve el espacio en una posición dada
 * @pre El juego no se ha inicializado
 * @post La salida debe ser NULL
 */
void test3_game_get_space_at();

/**
 * @test Prueba la función que devuelve el objeto en una posición dada
 * @pre El objeto ha sido añadido correctamente
 * @post La salida debe ser el objeto añadido anteriormente
 */
void test1_game_get_object_at();

/**
 * @test Prueba la función que devuelve el objeto en una posición dada
 * @pre La posición en la que se busca es -1
 * @post La salida debe ser NULL
 */
void test2_game_get_object_at();

/**
 * @test Prueba la función que devuelve el objeto en una posición dada
 * @pre El juego no se ha inicializado
 * @post La salida debe ser NULL
 */
void test3_game_get_object_at();

/**
 * @test Prueba la función que devuelve el dado del juego
 * @pre El juego ha sido creado correctamente
 * @post La salida debe ser un puntero distinto de NULL
 */
void test1_game_get_die();

/**
 * @test Prueba la función que devuelve el dado del juego
 * @pre El juego no ha sido inicializado
 * @post La salida debe ser NULL
 */
void test2_game_get_die();

/**
 * @test Prueba la función que devuelve el jugador del juego
 * @pre El juego y el jugador han sido creado correctamente
 * @post La salida debe ser un puntero distinto de NULL
 */
void test1_game_get_player();

/**
 * @test Prueba la función que devuelve el jugador del juego
 * @pre El juego ha sido inicializado pero no se ha añadido ningun jugador
 * @post La salida debe ser NULL
 */
void test2_game_get_player();

/**
 * @test Prueba la funcion que devuelve la lista de objetos de una casilla como cadena
 * @pre El juego, una casilla, y un objeto han sido añadidos correctamente
 * @post La salida esperada es la lista de objetos de la casilla
 */
void test1_game_get_obj_list_as_str();

/**
 * @test Prueba la funcion que devuelve la lista de objetos de una casilla como cadena
 * @pre El juego no se ha inicializado
 * @post La salida esperada es NULL
 */
void test2_game_get_obj_list_as_str();

/**
 * @test Prueba la función que devuelve el ultimo espacio inspeccionado
 * @pre El juego ha sido creado, se ha añadido un espacio y se ha colocado al jugador dentro
 * @post La salida esperada es la casilla en la que esta el jugador
 */
void test1_game_get_last_inspected_space();

/**
 * @test Prueba la función que devuelve el ultimo espacio inspeccionado
 * @pre El juego no ha sido creado
 * @post La salida esperada es NULL
 */
void test2_game_get_last_inspected_space();

/**
 * @test Prueba la función que devuelve el ultimo objeto inspeccionado
 * @pre El nombre del objeto añadido es "obj"
 * @post La salida esperada es el objeto con nombre "obj"
 */
void test1_game_get_last_inspected_object();

/**
 * @test Prueba la función que devuelve el ultimo objeto inspeccionado
 * @pre El objeto está marcado como oculto
 * @post La salida esperada es NULL
 */
void test2_game_get_last_inspected_object();

/**
 * @test Prueba la función que devuelve el ultimo objeto inspeccionado
 * @pre El nombre del objeto no se corresponde con el del objeto del juego
 * @post La salida esperada es NULL
 */
void test3_game_get_last_inspected_object();

/**
 * @test Prueba la funcion que devuelve la localizacion del jugador
 * @pre El jugador se ha colocado en la casilla con id 2
 * @post La salida es 2, la localización del jugador
 */
void test1_game_get_player_location();

/**
 * @test Prueba la funcion que devuelve la localizacion del jugador
 * @pre El jugador no se ha añadido al juego
 * @post La salida es NO_ID, localizacion nula
 */
void test2_game_get_player_location();

/**
 * @test Prueba la funcion que devuelve la localizacion de un objeto
 * @pre El objeto se ha añadido en la casilla con id 2
 * @post La salida es 2, la localización del objeto
 */
void test1_game_get_object_location();

/**
 * @test Prueba la funcion que devuelve la localizacion de un objeto
 * @pre El objeto no se ha añadido al juego
 * @post La salida es NO_ID - localizacion nula
 */
void test2_game_get_object_location();

/**
 * @test Prueba la funcion que devuelve la localizacion de un objeto
 * @pre El objeto está marcado como oculto
 * @post La salida es NO_ID - localizacion nula
 */
void test3_game_get_object_location();


/**
 * @test Prueba la función que devuelve el dialogo del juego
 * @pre El juego ha sido creado correctamente
 * @post La salida debe ser un puntero distinto de NULL
 */
void test1_game_get_dialogue();

/**
 * @test Prueba la función que devuelve el dialogo del juego
 * @pre El juego no ha sido inicializado
 * @post La salida debe ser NULL
 */
void test2_game_get_dialogue();

#endif