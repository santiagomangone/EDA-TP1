#include <stdio.h>
#include <math.h>
#include "calculadora.h"

#define PI 3.141592654

static unsigned int factorial(unsigned int n);

void calculadora(void) {
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
			printf("El denominador es cero, la divisi�n no est� definida.\n");
		printf("%f / %f = %f\n", datos.operando1, datos.operando2, datos.operando1 / datos.operando2);
		break;
	case fact:
		if (datos.operando1 < 0 || (datos.operando1) != (int)datos.operando1)
			printf("Error. El factorial est� definido sobre los naturales y el cero.");
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
			printf("La ra�z cuadrada no est� definida para n�meros negativos.\n");
		else
			printf("sqrt(%f) = %f\n", datos.operando1, sqrt(datos.operando1));
		break;
	case ln:
		if (datos.operando1 < 0)
			printf("El logaritmo natural no est� definido para n�meros negativos.\n");
		else
			printf("ln(%f) = %f\n", datos.operando1, log(datos.operando1));
		break;
	case logd:
		if (datos.operando1 < 0)
			printf("El logaritmo decimal no est� definido para n�meros negativos.\n");
		else
			printf("log(%.2f) = %.2f\n", datos.operando1, log10(datos.operando1));
		break;
	case modulo:
		printf("|%f| = %f\n", datos.operando1, abs(datos.operando1));
		break;
	case expo:
		if (datos.base < 0)
			printf("La potencia est� definida para base positiva o cero.\n");
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