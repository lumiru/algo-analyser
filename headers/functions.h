
#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <string> // Type chaîne de caractères
#include <vector>
#include <sstream>

// Renvoie la chaine en minuscule
std::string toLowerCase( std::string str );
// Renvoie la chaine en minuscule avec la première lettre en majuscule
std::string firstLetterCap( std::string str );
// Renvoie la chaine sans accents (UTF-8)
std::string retirerAccents(std::string);

typedef std::vector<std::string> Mots;
// Découpe une chaine d'algo en "mots" directement exploitables
Mots& decoupeMots(std::string str);

// Transforme un nombre en string
std::string int2str(long);
// Transforme un string en nombre
long str2int(std::string);

// Vérifie la présence d'une chaine dans un tableau
bool hasString(std::vector<std::string>, std::string);
// Fonction C
bool hasString(const char* const tab[], const int len, const char* str);

int indexOfString(std::vector<std::string>, std::string);

// Vérifie la présence d'un caractère dans une chaine
bool hasCaractere(std::string str, char c);

#endif

