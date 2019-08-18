#include <stdio.h>
#include <cmath>
#include "parseLib.h"
#include "parseCallback.h"

#define PI 3.141592654

static unsigned int factorial(unsigned int n);

int main(int argc, char*argv[]) {
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
	a = parseCallback((char*)"", (char*)"10.0", &datos);
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

	//ANGULOS
	if (datos.angulo == 0)
		datos.operando1 *= PI / 180;
	else if (datos.angulo == 2)
		datos.operando1 *= PI / 200;
	printf("Operando1: %f ... Operando2: %f\n", datos.operando1, datos.operando2);

	//REDONDEO
	if (datos.redondeo1 == true)
	{
		datos.operando1 = (int)(datos.operando1 * 10) / 10;
		datos.operando2 = (int)(datos.operando2 * 10) / 10;
	}
	else if (datos.redondeo2 == true)
	{
		datos.operando1 = (int)(datos.operando1 * 100) / 100;
		datos.operando2 = (int)(datos.operando2 * 100) / 100;
	}
	else if (datos.redondeo3 == true)
	{
		datos.operando1 = (int)(datos.operando1 * 1000) / 1000;
		datos.operando2 = (int)(datos.operando2 * 1000) / 1000;
	}
	else if (datos.redondeo4 == true)
	{
		datos.operando1 = (int)(datos.operando1 * 10000) / 10000;
		datos.operando2 = (int)(datos.operando2 * 10000) / 10000;
	}

	//CUENTAS
	switch (datos.operacion)
	{
	case suma:
		printf("%f + %f = %f\n", datos.operando1, datos.operando2, datos.operando1 + datos.operando2);
		break;
	case resta:
		printf("%f - %f = %f\n", datos.operando1, datos.operando2, datos.operando1 - datos.operando2);
		break;
	case producto:
		printf("%f * %f = %f\n", datos.operando1, datos.operando2, datos.operando1 * datos.operando2);
		break;
	case cociente:
		if (datos.operando2 == 0)
			printf("El denominador es cero, la división no está definida.\n");
		printf("%f / %f = %f\n", datos.operando1, datos.operando2, datos.operando1 / datos.operando2);
		break;
	case fact:
		if (datos.operando1 < 0 || (datos.operando1) != (int)datos.operando1)
			printf("Error. El factorial está definido sobre los naturales y el cero.");
		else
			printf("%.0f! = %u\n", datos.operando1, factorial((unsigned int)datos.operando1));
		break;
	case seno:
		printf("sen(%f) = %f\n", datos.operando1, sin(datos.operando1));
		break;
	case coseno:
		printf("cos(%f) = %f\n", datos.operando1, cos(datos.operando1));
		break;
	case tg:
		printf("tan(%f) = %f\n", datos.operando1, tan(datos.operando1));
		break;
	case raiz:
		if (datos.operando1 < 0)
			printf("La raíz cuadrada no está definida para números negativos.\n");
		else
			printf("sqrt(%f) = %f\n", datos.operando1, sqrt(datos.operando1));
		break;
	case ln:
		if (datos.operando1 < 0)
			printf("El logaritmo natural no está definido para números negativos.\n");
		else
			printf("ln(%f) = %f\n", datos.operando1, log(datos.operando1));
		break;
	case logd:
		if (datos.operando1 < 0)
			printf("El logaritmo decimal no está definido para números negativos.\n");
		else
			printf("log(%.2f) = %.2f\n", datos.operando1, log10(datos.operando1));
		break;
	case modulo:
		printf("|%f| = %f\n", datos.operando1, abs(datos.operando1));
		break;
	case expo:
		if (datos.base < 0)
			printf("La potencia está definida para base positiva o cero.\n");
		else
			printf("%f^%d = %f", datos.base, datos.exponente, exp(datos.exponente * log(datos.base)));
		break;
	}
	return 0;
}

//factorial
static unsigned int factorial(unsigned int n) {
	if (n < 1)
		return 1;
	else
		return n * factorial(n - 1);
}