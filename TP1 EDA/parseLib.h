#pragma once

#define ERR_CODE	-1

typedef int (*pCallback) (char *, char *, void *);

enum parseFSM{INIT, KEY, VALUE, PARAM, ERROR};

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData);