/**
 * @brief Implementacion del conjuntos del juego
 *       Progama para probar la correcta funcionalidad del
 *       nuevo TAD Set.
 *
 * @file set_test.c
 * @author Javier Bernando y Mihai Blidaru
 * @version 1.0
 * @date 11-03-2017
 */
#include "set.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Definicion de la funcion main del set_test
 */
int main() {
    Set* set = set_create();
    if (!set) {
        printf("Error en create_set\n");
        return EXIT_FAILURE;
    }

    /* A�adir id 1*/
    printf("A�adiendo el Id 16: ");
    if (set_addId(set, 16) == ERROR)
        printf("Error en set_addId\n");

    printf("\nImprimiendo el set:\n");
    if (set_print(stdout, set) == NO_ID)
        printf("Error en set_print\n");

    /* A�adir id 2*/
    printf("\nA�adiendo el Id 2: ");
    if (set_addId(set, 2) == ERROR)
        printf("Error en set_addId\n");

    printf("\nImprimiendo el set:\n");
    if (set_print(stdout, set) == NO_ID)
        printf("Error en set_print\n");

    /* A�adir id 3*/
    printf("\nA�adiendo el Id 7: ");
    if (set_addId(set, 7) == ERROR)
        printf("Error en set_addId\n");

    printf("\nImprimiendo el set:\n");
    if (set_print(stdout, set) == NO_ID)
        printf("Error en set_print\n");

    /* A�adir id 4*/
    printf("\nA�adiendo el Id 32: ");
    if (set_addId(set, 32) == ERROR)
        printf("Error en set_addId\n");

    printf("\nImprimiendo el set:\n");
    if (set_print(stdout, set) == NO_ID)
        printf("Error en set_print\n");

    /* A�adir id 5*/
    printf("\nIntentando sobrepasar la capacidad del set: ");
    printf("\nA�adiendo el Id 5: ");
    if (set_addId(set, 35) == ERROR)
        printf("No se pueden a�adir m�s Ids\n");

    printf("\nImprimiendo el set:\n");
    if (set_print(stdout, set) == NO_ID)
        printf("Error en set_print\n");


    /* Borrar alguno de los ids*/
    printf("\nBorrando el Id 7: ");
    if (!(set = set_delId(set, 7)))
        printf("Error en set_delId");

    printf("\nImprimiendo el set:\n");
    if (set_print(stdout, set) == NO_ID)
        printf("Error en set_print\n");

    /* Intentando a�adir un id duplicado */
    printf("\nIntendando a�adir el Id 16 duplicado: ");
    if (set_addId(set, 16) == ERROR)
        printf("\nERROR: No se pueden a�adir Id duplicados\n");

    printf("\nImprimiendo el set:\n");
    if (set_print(stdout, set) == NO_ID)
        printf("Error en set_print\n");

    /* Borrar otro id */
    printf("\nBorrando el Id 16: ");
    if (!(set = set_delId(set, 16)))
        printf("Error en set_delId");

    printf("\nImprimiendo el set:\n");
    if (set_print(stdout, set) == NO_ID)
        printf("Error en set_print\n");


    /* Intentando borrar un id que no existe */
    printf("\nIntendando hacer un borrado doble del id 16:\n");
    if (!(set_delId(set, 16)))
        printf("ERROR: No se puede borrar un id que no existe\n");

    printf("\nImprimiendo el set:\n");
    if (set_print(stdout, set) == NO_ID)
        printf("Error en set_print\n");

    /* Destruir el set */
    printf("\nDestruyendo el set:\n\n ");
    if (set_destroy(set) == ERROR)
        printf("Error en destroy_set()\n");

    return EXIT_SUCCESS;
}
