#include <stdio.h>
#include <cmath>
#include "parseLib.h"
#include "parseCallback.h"
#include "calculadora.h"

int main(int argc, char* argv[]) {
	/*
	//PEQUENA PRUEBA
	int argctest = 5, aux;
	char* c1 = (char*)"TEST";
	char* c2 = (char*)"opcion";
	char* c3 = (char*)"-value";
	char* c4 = (char*)"-value";
	char* c5 = (char*)"-";
	char *argvtest[] = {c1, c2, c3, c4, c5};
	pCallback_t p = NULL;
	//FIN DE VARIABLES DE PRUEBA
	printf("Test start!\n");

	//PRUEBA RAPIDA
	aux = parseCmdLine(argctest, argvtest, p, NULL);
	printf("Function returned %d\n", aux);
	*/

	pCallback_t pToCallback = parseCallback;
	userData_t datos;
	
	int arguments = parseCmdLine(argc, argv, pToCallback, &datos);
	printf("Arguments: %d\n", arguments);
	if (arguments == -1)
	{
		printf("Error\n");
		return 0;
	}
	


	//printf("Operacion %d\n", datos.operacion);

	/*****************TESTING*******************
	int a, b, c, d, e;
	a = parseCallback((char*)"tan", (char*)"45", &datos);
	b = parseCallback((char*)"angulo", (char*)"grados", &datos);
	c = 3; //parseCallback(NULL, (char*)"redondeo3", &datos);
	d = 4;// parseCallback((char*)"suma", (char*)"1", &datos);
	e = 5;// parseCallback((char*)"suma", (char*)"1", &datos);
	printf("Operacion %d\n", datos.operacion);
	printf("Operando1: %f ... Operando2: %f\n", datos.operando1, datos.operando2);
	printf("Base: %f ...  Expo: %d\n", datos.base, datos.exponente);
	printf("returns %d, %d, %d, %d, %d\n", a, b, c, d, e);
	printf("Angulo %d\n", datos.angulo);
	********************************************/
	calculadora(datos);
	return 0;
}