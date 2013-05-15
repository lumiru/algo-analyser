
#include "structure.h"

Structure::Structure() {}
Structure::Structure(std::string nnom) {
  nom = firstLetterCap(nnom);
  if(isReserve(nom)) {
    throw "Le nom \""+nnom+"\" est déjà réservé.";
  }
}

void Structure::addAttribut(Variable attr) {
  if(hasVar(attributs, attr.getNom())) {
    throw "Erreur : l'attribut \""+attr.getNom()+"\" existe déjà dans la structure \""+nom+"\".";
  }
  else {
    attributs.push_back(attr);
  }
}
std::string Structure::getNom() const {
  return nom;
}
std::string Structure::creer() const {
  std::string listVars = "";
  int l = attributs.size();
  int i;

  for(i = 0; i < l; i++) {
    listVars += "\n  "+attributs[i].instancier()+";";
  }

  return "typedef struct "+nom+" "+nom+";\nstruct "+nom+" {"+listVars+"\n};";
}
bool Structure::hasAttribut(std::string attr) const {
  return hasVar(attributs, attr);
}
Variable Structure::getAttribut(std::string attr) const {
  int id = indexOfVar(attributs, attr);

  if(id == -1) {
    throw "Erreur : l'attribut \""+attr+"\" n'existe pas.";
  }

  return attributs[id];
}

// Necessaire pour l'acces à l'attribut nom de structure
std::string Variable::strtype() const {
  return strbasetype() + (tableau - (type == TYP_CHAINE?1:0) > 0?"*":"");
}
std::string Variable::strbasetype() const {
  std::string rtype = "";
  if(nom == "main") {
    return "int";
  }
  if(type == TYP_STRUCT) {
    rtype = structure->getNom();
  }
  else if(type < TYP_STRUCT) {
    rtype = typeC(type);
  }
  else {
    throw "Type inconnu.";
  }
  return rtype;
}

// TYPE tabStructs
int indexOfStruct(const tabStructs& vars, std::string val) {
  int l = vars.size();
  int i;
  val = firstLetterCap(val);

  for(i = 0; i < l; i++) {
    if(vars[i].getNom() == val) {
      return i;
    }
  }
  return -1;
}
bool hasStruct(const tabStructs& vars, const std::string val) {
  return indexOfStruct(vars, val) != -1;
}
