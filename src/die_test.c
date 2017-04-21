/**
 * @brief Implementacion del dado en el juego
 *       Progama para probar la correcta funcionalidad del
 *       nuevo TAD Die.
 *
 * @file die_test.c
 * @author Javier Bernando
 * @version 1.0
 * @date 11-03-2017
 */

#include <stdio.h>
#include <stdlib.h>
#include "die.h"

/** 
 * @brief Funcion main del die_test.c
 */
int main(){
	int valor = 0;
	Die* die = NULL;
	printf("Crea el dado:\n");
	if(!(die = die_create(DIE_ID))){
		printf("Error al crear el dado");
	}else{
		printf("OK\n");
	}
	printf("\nImprimiendo el dado: \n");
	die_print(die);
	
	printf("\nTira el dado:\n");
	valor = die_roll(die);
	printf("El valor obtenido es: %hu\n", valor);
	
	printf("Mirar si el ultimo valor es correcto: ");
	if(valor != die_get_number(die)){
		printf("Error, valor incorrecto\n");
	}else{
		printf("Valor = %hu - correcto\n", die_get_number(die));
	}
	
	printf("Destruyendo el dado: ");
	if(die_destroy(die) == OK){
		printf("OK\n");
	}else{
		printf("ERROR\n");
	}
	
	return EXIT_SUCCESS; 
}