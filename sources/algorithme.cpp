
#include "algorithme.h"

// Types personnels (structures)
void Algorithme::addType(Structure structure) {
  if(hasStruct(types, structure.getNom())) {
    throw "Erreur : la structure \""+structure.getNom()+"\" existe déjà.";
  }
  else {
    types.push_back(structure);
  }
}
bool Algorithme::hasType(std::string nom) {
  return hasStruct(types, nom);
}
Structure* Algorithme::getType(std::string nom) {
  int k = indexOfStruct(types, nom);
  if(k >= 0) {
    return &(types[k]);
  }
  throw "Vous essayez d'obtenir un type qui n'existe pas. Utilisez d'abord hasType.";
}

// Programmes et sous-programmes
void Algorithme::addProgramme(Programme prog) {
  if(hasProg(programmes, prog.getNom())) {
    throw "Erreur : le programme \""+prog.getNom()+"\" existe déjà.";
  }
  else {
    programmes.push_back(prog);
  }
}
int Algorithme::getProgID(std::string prog) const {
  return indexOfProg(programmes, prog);
}
Type Algorithme::getProgType(std::string prog) const {
  int id = getProgID(prog);
  if(id >= 0 && id < programmes.size()) {
    return programmes[id].getType();
  }
  else {
    throw "Aucun programme #"+int2str(id)+" n'existe (pV).";
  }
}
void Algorithme::addProgCode(int id, std::string code) {
  if(id >= 0 && id < programmes.size())
    programmes[id].addCode(code);
}
void Algorithme::addProgCodeInstance(int id, std::string var) {
  if(id >= 0 && id < programmes.size()) {
    programmes[id].addCodeInstance(var);
  }
  else {
    throw "Aucun programme #"+int2str(id)+" n'existe (aPCI).";
  }
}
bool Algorithme::hasArgument(int id, std::string arg) const {
  if(id >= 0 && id < programmes.size()) {
    return programmes[id].hasArgument(arg);
  }
  else {
    throw "Aucun programme #"+int2str(id)+" n'existe (hA).";
  }
}
bool Algorithme::isBeforeVar(int id, std::string isbef, std::string var) const {
  if(id >= 0 && id < programmes.size()) {
    return programmes[id].isBeforeVar(isbef, var);
  }
  else {
    throw "Aucun programme #"+int2str(id)+" n'existe (iBV).";
  }
}
bool Algorithme::hasVariable(int id, std::string var) const {
  if(id >= 0 && id < programmes.size()) {
    return programmes[id].hasVariable(var);
  }
  else {
    throw "Aucun programme #"+int2str(id)+" n'existe (hV).";
  }
}
Variable Algorithme::progVar(int id, std::string var) const {
  if(id >= 0 && id < programmes.size()) {
    return programmes[id].getVariable(var);
  }
  else {
    throw "Aucun programme #"+int2str(id)+" n'existe (pV).";
  }
}

bool Algorithme::key2C(int currentProg, std::string mot) {
  if(mot == "non" || mot == "no") {
    addProgCode(currentProg, "!");
  }
  else if(mot == "modulo") {
    addProgCode(currentProg, "%");
  }
  else if(mot == "et") {
    addProgCode(currentProg, "&&");
  }
  else if(mot == "ou") {
    addProgCode(currentProg, "||");
  }
  else if(mot == "vrai" || mot == "true") {
    addProgCode(currentProg, "true");
  }
  else if(mot == "faux" || mot == "false") {
    addProgCode(currentProg, "false");
  }
  else {
    return false;
  }
  return true;
}

std::string Algorithme::ecrire() const {
  std::string str = "#include <cstdlib>\n#include <cstdio>\n\
   \n#include \"libalgo.h\"\n\n";
  int l = types.size();
  int i, rec_i;

  for(i = 0; i < l; i++) {
    str += types[i].creer() + "\n";
  }

  l = programmes.size();
  if(l <= 0) {
    throw "Aucun programme à écrire.";
  }
  for(i = 0; i < l; ++i) {
    if(programmes[i].getNom() != "main") {
      str += programmes[i].signature() + ";\n";
    }
  }
  for(i = 0; i < l; ++i) {
    str += programmes[i].instancier() + "\n";
  }

  return str;
}
bool Algorithme::hasProgramme(std::string prog) const {
  return hasProg(programmes, prog);
}
