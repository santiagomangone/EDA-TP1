#include <stdio.h>
#include <stdlib.h>
#include "parseLib.h"

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
void standardKey(char *key);
void reverseKey(char *key);
 /*******************************************************************************
  *******************************************************************************
						 GLOBAL FUNCTION DEFINITIONS
  *******************************************************************************
  ******************************************************************************/

  /************************************  parseCmdLine  ***********************************/
int parseCmdLine(int argc, char* argv[], pCallback_t parseCallback, void* userData) {
	int counter = 0, i = 1, parseFSM = INIT;
	if (argc == 1) {														//Si no hay opciones ni parametros
		printf("NO ARGUMENTS DETECTED\n");
		return counter;														//Devuelvo que no hay nada
	}
	while (i < argc) {														//Mientras hayan argumentos por analizar
		switch (parseFSM){													//Se los analiza
			case INIT:														//Si recien se empieza, o se completo un analisis
				if (argv[i][0] == '-') {									//Si encuentro una posible clave
					parseFSM = KEY;											//Paso a analizarla
				}
				else{														//Si no es una potencial opcion
					parseFSM = PARAM;										//Paso a buscar un parametro
				}
				break;
			case KEY:
				if ((argv[i][1] == '\n')|| (argv[i][1] == '\0')) {		//Si la clave esta vacia
					printf("EMPTY KEY DETECTED!\n");
					parseFSM = ERROR;									//ERROR
				}
				else if (i == argc-1) {									//O si esa clave no tiene valor por ser el ultimo argumento
					printf("KEY WITHOUT VALUE DETECTED!\n");
					parseFSM = ERROR;									//ERROR
				}
				else {													//Si es una clave bien escrita
					parseFSM = VALUE;									//Se pasa a buscar el valor
				}
				break;
			case VALUE:													//Si la clave era valida y tenia valor
				standardKey(argv[i]);									//Se normaliza la clave (se remueve el guion)
				if(parseCallback(argv[i], argv[i+1], userData) == 0){	//Se llama al Callback para verificarla
					parseFSM = ERROR;									//Si no es valida, se reporta un error
				}
				else{													//Si no
					reverseKey(argv[i]);								//Se devuelve a la clave a su estado original
					i++;												//Se posiciona el puntero en el siguente
					i++;												//posible argumento
					counter++;											//Aumenta el contador
					parseFSM = INIT;									//Se reinicia la FSM
				}
				/*
				//Lo de abajo es solo para probar, eliminar en Release Version
				printf("KEY: %s\n", argv[i]);
				printf("VALUE: %s\n", argv[i+1]);
				i++;
				i++;
				counter++;
				parseFSM = INIT;
				*/
				break;
			case PARAM:															//Si se detecta un parametro
				if(parseCallback(NULL, argv[i], userData) == 0){			//Se chequea validez
					parseFSM = ERROR;											//Si el parametro es invalido tira error
				}
				else{															//Si es valido
					i++;														//Se posiciona el puntero en el siguiente argumento
					parseFSM = INIT;											//Se reinicia la FSM
				}
				/*
				//Lo de abajo es solo para probar, eliminar en Release Version
				printf("PARAM: %s\n", argv[i]);
				i++;
				counter++;
				parseFSM = INIT;
				*/
				break;
			case ERROR:													//En caso de eroor
				printf("ERROR DETECTED\n");	
				return ERR_CODE;										//Se devuelve el codigo de error
				break;
			default:													//No deberia llegar nunca a un default
				printf("Default case detected! Error in FSM\n");
				break;
		}
	}
	return counter;														//Se devuelve el contador
}
//Esta funcion toma una clave, y la acomoda para borrarle el guion '-'
void standardKey(char* key) {
	int i = 0;
	char aux;
	for (i = 0; (*(key + i + 1) != '\0') && (*(key + i + 1) != '\n'); i++) {	//Se recorre el string
		*(key + i) = *(key + i + 1);											//Moviendo los chars una posicion antes
	}
	*(key + i) = '\0';															//Se agrega el terminador anteultimo
	return;
}
//Esta funcion toma una clave con el guion '-' removido, y se lo agrega
void reverseKey(char* key) {
	int i = 0;
	char aux1, aux2;
	if(key == NULL)
		printf("Key pointer address is NULLPTR\n");	
	aux1 = *key;
	*key = '-';																	//Se vuelve a colocar el guion
	for (i = 1; *(key + i) != '\0'; i++) {										//Se acomodan los chars
		aux2 = *(key + i);														//En su posicion original
		*(key + i) = aux1;
		aux1 = aux2;
	}
	*(key + i) = aux1;															//Se devuelve el ultimo caracter.
	return;
}