#include <stdio.h>
#include "parseLib.h"

int main(int argc, char*argv[]) {
	//PEQUENA PRUEBA
	int argctest = 5, aux;
	char* c1 = (char*)"TEST";
	char* c2 = (char*)"opcion";
	char* c3 = (char*)"-value";
	char* c4 = (char*)"-value";
	char* c5 = (char*)"-";
	char *argvtest[] = {c1, c2, c3, c4, c5};
	pCallback p = NULL;
	//FIN DE VARIABLES DE PRUEBA
	printf("Test start!\n");
	
	//PRUEBA RAPIDA
	aux = parseCmdLine(argctest, argvtest, p, NULL);
	printf("Function returned %d\n", aux);
	return 0;
}