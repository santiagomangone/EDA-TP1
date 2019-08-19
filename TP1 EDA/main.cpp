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
 *******************************************************************************
									MAIN
 *******************************************************************************
 ******************************************************************************/
int main(int argc, char* argv[]) {

	pCallback_t pToCallback = parseCallback;
	userData_t datos;
	
	int arguments = parseCmdLine(argc, argv, pToCallback, &datos);

	if (arguments == -1)
	{
		printf("Error\n");
		return 0;
	}
	
	calculadora(datos);
	return 0;
}