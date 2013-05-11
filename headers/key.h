
#ifndef __KEY_H__
#define __KEY_H__

#include <string>
#include "functions.h"
#include "variable.h"

#include "lib.h" // bool isLibFonction(std::string mot);

bool isReserve(std::string mot);

bool isType(std::string mot);

Type typeOfKey(std::string mot);
std::string typeC(Type type);

bool isEntier(std::string mot);
bool isReel(std::string mot);
bool isCaractere(std::string mot);
bool isChaine(std::string mot);
bool isFichier(std::string mot);
bool isBooleen(std::string mot);
bool isPositif(std::string mot);
bool isConstante(std::string mot);

#endif
