
#ifndef __CHARSET_H__
#define __CHARSET_H__

// #include <stdio.h> // I/O Terminal
#include <fstream>
#include <string> // Type chaîne de caractères
#include <vector>

enum Charset {
  // Gérés :
  CHARSET_ASCII = 0,
  CHARSET_UTF8 = 1,
  CHARSET_ISO_8859 = 2,
  CHARSET_CP_1252 = 3, // MS AINSI
  // Non gérés :
  CHARSET_UTF16 = 4,
  CHARSET_UTF32 = 5,
  CHARSET_UTF7 = 6,
  CHARSET_UTF_EBCDIC = 7,
  CHARSET_BOCU1 = 8,
  CHARSET_SCSU = 9,
  // BOM non trouvé, utiliser findCharset
  CHARSET_BOM_NOT_FIND = -1
};
typedef enum Charset Charset;

// Permet d'obtenir le CHARSET du fichier <file>
Charset getCharset(std::ifstream& file);

// Lit l'entête BOM laissé par les systèmes Microsoft (mais pas tous ><)
// Renvoie un CHARSET
Charset lireBOM(std::ifstream& file);

// À utiliser sur lireBOM retourne CHARSET_BOM_NOT_FIND
// Analyse les caractères spéciaux du fichier pour définir un charset.
// Renvoie : 
//  - CHARSET_ASCII si aucun caractère spécial trouvé ;
//  - CHARSET_UTF8 ;
//  - CHARSET_ISO_8859.
Charset findCharset(std::ifstream& file);

/**
  * Functions to Convert beetween different charset
  * author Julien Folly
  * edited by Frédéric Turpin (2011.12.25)
  * version C++ 1.0
  */
// ISO-8859-15 -> UTF-8
std::string iso8859ToUtf8(std::string capSrc);

#endif

