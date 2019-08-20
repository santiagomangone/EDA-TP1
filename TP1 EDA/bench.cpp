/***************************************************************************//**
  @file     +main.cpp+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

 /*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include "parseLib.h"
#include "parseCallback.h"
#include "calculadora.h"

/*******************************************************************************
* CONSTANT AND MACRO DEFINITIONS USING #DEFINE
******************************************************************************/
#define NCASES 5
#define NRO_DE_PRUEBAS 20
//#define NARGS 2

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static void testCmdLine(const char* testCase[], int* correctos, int* incorrectos);

 /*******************************************************************************
  *******************************************************************************
							 MAIN DE PRUEBAS
  *******************************************************************************
  ******************************************************************************/
int main(int argc, char* argv[]) {

	const char* testCase1[] = { "parse.exe", "--" };			//, 2=NARGS
	const char* testCase2[] = { "parse.exe", "suma-"};
	const char* testCase3[] = { "parse.exe", "- " };
	const char* testCase4[] = { "parse.exe", "--" };
	const char* testCase5[] = { "parse.exe","-suma", "-suma"} };

	typedef char* argvTest[];

	argvTest argvT1w[] = {"prueba.exe" , "--", "or"};
	argvTest argvT2w[] = { "prueba.exe" , "-"};
	argvTest argvT3w[] = { "prueba.exe" , };
	argvTest argvT4w[] = { "prueba.exe" , ""};
	argvTest argvT5w[] = { "prueba.exe" , };
	argvTest argvT6w[] = { "prueba.exe" , };
	argvTest argvT7w[] = { "prueba.exe" , };
	argvTest argvT8w[] = { "prueba.exe" , };
	argvTest argvT9w[] = { "prueba.exe" , };
	argvTest argvT10w[] = { "prueba.exe" , };

	argvTest argvT1r[] = { "prueba.exe" };
/*
	argvTest argvT1[] = { "prueba.exe" , };
	argvTest argvT1[] = { "prueba.exe" , };
	argvTest argvT1[] = { "prueba.exe" , };
	argvTest argvT1[] = { "prueba.exe" , };
	argvTest argvT1[] = { "prueba.exe" , };
	argvTest argvT1[] = { "prueba.exe" , };
	argvTest argvT1[] = { "prueba.exe" , };
	argvTest argvT1[] = { "prueba.exe" , };
	argvTest argvT1[] = { "prueba.exe" , };
	argvTest argvT1[] = { "prueba.exe" , };
	argvTest argvT1[] = { "prueba.exe" , };
	argvTest argvT1[] = { "prueba.exe" , };
	argvTest argvT1[] = { "prueba.exe" , };
	argvTest argvT1[] = { "prueba.exe" , };
	argvTest argvT1[] = { "prueba.exe" , };
	argvTest argvT1[] = { "prueba.exe" , };
	argvTest argvT1[] = { "prueba.exe" , };
	argvTest argvT1[] = { "prueba.exe" , };
	*/

	argvTest* allTests[NRO_DE_PRUEBAS];



	pCallback_t pToCallback = parseCallback;
	userData_t datos;

	int check, correctos = 0, incorrectos = 0, i;


	//Pruebas a parseLib(CmdLine).
														//Comienza a pruebar uno por uno. 
														//Notar que los casos en la matriz son tomados por nuestras convenciones como incorrectos
														//y es por eso que en caso de que no se hallen errores se incremente "correctos".
	
	for(int i=0 ; i< ; i++)

		testCmdLine(testCase1, &correctos, &incorrectos);
		testCmdLine(testCase2, &correctos, &incorrectos);
		testCmdLine(testCase3, &correctos, &incorrectos);
		testCmdLine(testCase4, &correctos, &incorrectos);
		testCmdLine(testCase5, &correctos, &incorrectos);

	//Pruebas a parseCallback. 


	/*check = parseCallback(Key,value , userdata)
		if (check == 0)
			incorrectos++;	//Si devuelve error, directamente ya sabemos que es error, no hace falta ver el resultado.
		else
		{
			//¿¿Analisis de la respuesta obtenida??	Debo evaluar si es correcta o no, ¿tengo que hacer un user data para cada caso?.
			correctos++;
		}*/

		//Resumen de pruebas

	printf("Resumen de las pruebas realizadas: \n Correctos:%d  Incorrectos:%d", correctos, incorrectos);
	return 0;
}

static void testCmdLine(const char * testCase [], int  int* correctos, int* incorrectos)
{
	static int nroDePrueba;
	pCallback_t pToCallback = parseCallback;
	userData_t datosPrueba;
	int check;
	check = parseCmdLine(NARGS, testCase, pToCallback, &datosPrueba);

	printf("INICIO DE PRUEBA _%d_\n\n", nroDePrueba);
	if (check == -1)
	{
		(*incorrectos)++;

	}
	else
	{
		(*correctos)++;
	}
	printf("\nFIN DE PRUEBA _%d_\n", nroDePrueba++);
	return;
}