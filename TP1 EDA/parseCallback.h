/***************************************************************************//**
  @file     +parseCallback.h+
  @brief    +valida las entradas del usuaria por consola y guarda los datos en la estructura dada.+
  @author   +Grupo 3. TP1.+
 ******************************************************************************/
#ifndef _parseCallback_H_
#define _parseCallback_H_

#include <stdio.h>
#include <stdio.h>
#include "calculadora.h"

 /*******************************************************************************
  * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
  ******************************************************************************/
int parseCallback(char* key, char* value, void* userData);

#endif