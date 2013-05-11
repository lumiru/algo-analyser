
#ifndef __LIB_H__
#define __LIB_H__

#include <unistd.h>
#include <cstdio>
#include <string> // Type chaîne de caractères
#include <vector>
#include "variable.h"
#include "fichier.h"
#include "functions.h"

void chargerLib(char* argv0);
Type intData2typ(int type);
bool isLibFonction(std::string);
Type typeOfLibFonction(std::string);

#endif

