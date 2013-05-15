
#ifndef __FICHIER_H__
#define __FICHIER_H__

#include <unistd.h>
#include <string> // Type chaîne de caractères
#include <vector>
#include <iostream>
#include <fstream>
#include "functions.h"
#include "charset.h"

typedef std::vector<Mots> Lignes;
Lignes& ouvrir(const char* chemin);
void enregistrer(const char* chemin, std::string);
void gotoExeChemin(const char argv0[], char* cwd = NULL, int cwdTaille = 1);

#endif

