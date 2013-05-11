
#include "key.h"

/* // lib.cpp
bool isLibFonction(std::string mot) {
  mot = toLowerCase(mot);
  const char reservesLEN = 109;
  const char* const reserves[] = {
    "afficher", "creertableau", "creerchainevide", "creerchaineinit", "detruirechaine",
    "creertableauchaines", "detruiretableauchaines", "nbchaines", "ajouterchaine", "duppliquerchaine",
    "suppprimerchainetab", "chercherchaine", "chercherchainepos", "concatchaines", "copierchaines",
    "split", "saisiechaine", "saisiechainelimitee", "saisiecaractere", "affichechaine",
    "ischaineValide", "copiechaine", "copiechainelimitee", "concatenechaine", "longueurchaine",
    "comparechaine", "cherchecaractere", "cherchecaracterepos", "setcaractere", "ajoutcaractere",
    "getcaractere", "nbcaracteres", "cherchepattern", "changepattern", "extractsouschaineinterv",
    "extractsouschaine", "ischainenumerique", "chainetoentier", "entiertochaine", "chainetoreel",
    "reeltochaine", "misenmajuscule", "miseenminuscule", "misemajusculecar", "miseminusculecar",
    "trim", "cosinus", "sinus", "tangente", "arccosinus",
    "arcsinus", "arctangente", "cosinushyp", "sinushyp", "tangentehyp",
    "exponentielle", "logarithme", "logarithme", "puissance", "factorielle",
    "racinecarree", "arrondisup", "valeurabsolue", "arrondiinf", "restediv",
    "getpi", "degretoradian", "ouverture", "fermeture", "viderbuffer",
    "lecture", "ecriture", "findefichier", "deplacecurseur", "findefichier",
    "modifieTailleEcranConsole", "positioncurseur", "chargecaractere", "sauvecaractere", "lectureligne",
    "ecritureligne", "videbuffer", "generateurnbaleatoire", "srand", "nombrealeatoire",
    "modifietailleecran", "effaceecran", "pause", "couleur", "queljouresttil",
    "codedate", "datetochaine", "datetochaineclair", "verifdate", "codetemps",
    "tempstochaine", "veriftemps", "isbissextile", "quantieme", "getquantieme",
    "getdateheurecourante", "codedatetostruct", "diffdatetemps", "decodetempsseconde", "diffnbjdate",
    "nbjours", "nbsecondes", "nbbissextile", "numsemainejour"
  };
  return hasString(reserves, reservesLEN, mot.c_str());
}
*/

bool isReserve(std::string mot) {
  mot = toLowerCase(mot);
  if(isType(mot) || isLibFonction(mot)) return true;
  const char reservesLEN = 36;
  const char* const reserves[] = {
    "date", "int", "double", "float", "const",
    "char", "long", "bool", "true", "false",
    "short", "void", "try", "catch", "throw",
    "this", "for", "while", "do", "if",
    "else", "return", "non", "retour", "retourne",
    "et", "ou", "and", "or", "xor",
    "main", "modulo", "no", "printf", "calloc",
    "sizeof"
  };
  return hasString(reserves, reservesLEN, mot.c_str());
}

bool isType(std::string mot) {
  mot = toLowerCase(mot);
  if(typeOfKey(mot) >= 0 || isPositif(mot) || isConstante(mot))
    return true;

  const char reservesLEN = 2;
  const char* const reserves[] = {
    "tableau", "de"
  };
  return hasString(reserves, reservesLEN, mot.c_str());
}

Type typeOfKey(std::string mot) {
  if(isEntier(mot)) {
    return TYP_ENTIER;
  }
  else if(isReel(mot)) {
    return TYP_REEL;
  }
  else if(isCaractere(mot)) {
    return TYP_CARACTERE;
  }
  else if(isChaine(mot)) {
    return TYP_CHAINE;
  }
  else if(isFichier(mot)) {
    return TYP_FICHIER;
  }
  else if(isBooleen(mot)) {
    return TYP_BOOLEEN;
  }
  return TYP_ERR;
}
std::string typeC(Type type) {
  if(type < TYP_STRUCT) {
    std::string toStr[] = {"void", "long", "double", "char", "char", "bool", "FILE*"};
    return toStr[type];
  }
  else {
    throw "Type #"+type+std::string(" inconnu.");
  }
}


bool isEntier(std::string mot) {
  const char reservesLEN = 6;
  const char* const reserves[] = {
    "entier", "entiere", "entiers", "entieres", "d'entier", "d'entiers"
  };
  return hasString(reserves, reservesLEN, mot.c_str());
}
bool isReel(std::string mot) {
  const char reservesLEN = 4;
  const char* const reserves[] = {
    "reel", "reels", "reelle", "reelles"
  };
  return hasString(reserves, reservesLEN, mot.c_str());
}
bool isCaractere(std::string mot) {
  const char reservesLEN = 3;
  const char* const reserves[] = {
    "caractere", "caracteres", "car"
  };
  return hasString(reserves, reservesLEN, mot.c_str());
}
bool isChaine(std::string mot) {
  const char reservesLEN = 2;
  const char* const reserves[] = {
    "chaine", "chaines"
  };
  return hasString(reserves, reservesLEN, mot.c_str());
}
bool isFichier(std::string mot) {
  const char reservesLEN = 3;
  const char* const reserves[] = {
    "desc", "descfi", "descripteur"
  };
  return hasString(reserves, reservesLEN, mot.c_str());
}
bool isBooleen(std::string mot) {
  const char reservesLEN = 4;
  const char* const reserves[] = {
    "booleen", "booleens", "booleenne", "booleennes"
  };
  return hasString(reserves, reservesLEN, mot.c_str());
}
bool isPositif(std::string mot) {
  const char reservesLEN = 9;
  const char* const reserves[] = {
    "positif", "positifs", "positive", "positives", "nonsigne",
    "relatif", "relatifs", "relative", "relatives"
  };
  return hasString(reserves, reservesLEN, mot.c_str());
}
bool isConstante(std::string mot) {
  const char reservesLEN = 3;
  const char* const reserves[] = {
    "const", "constant", "constante"
  };
  return hasString(reserves, reservesLEN, mot.c_str());
}
