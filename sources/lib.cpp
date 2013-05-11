
#include "lib.h"

static std::vector<std::string> libFonctions;
static std::vector<Type> libFonctionsType;

void chargerLib(char argv0[]) {
  char cwd[1024];
  Lignes lignes;
  int i, l;
  Type type;

  gotoExeChemin(argv0, cwd, 1024);
  lignes = ouvrir("share/fonctions.dat");
  chdir(cwd);
  l = lignes.size();

  for(i = 0; i < l; ++i) {
    libFonctions.push_back(lignes[i][0]);
    libFonctionsType.push_back(intData2typ((int)str2int(lignes[i][2])));
  }
}

Type intData2typ(int type) {
  switch(type) {
    case 0:
      return TYP_VIDE;
    case 1:
      return TYP_CARACTERE;
    case 2:
      return TYP_ENTIER;
    case 3:
      return TYP_REEL;
    case 4:
      return TYP_BOOLEEN;
    case 5:
      return TYP_CHAINE;
    case 7:
      return TYP_FICHIER;
    default:
      return TYP_ERR;
  }
}

bool isLibFonction(std::string mot) {
  return hasString(libFonctions, toLowerCase(mot));
}
Type typeOfLibFonction(std::string mot) {
  int id = indexOfString(libFonctions, toLowerCase(mot));
  if(id >= 0 && id < libFonctions.size()) {
    return libFonctionsType[id];
  }
  else {
    throw "Aucune fonction \""+mot+"\" n'existe dans fonctions.dat.";
  }
}
