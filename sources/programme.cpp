
#include "programme.h"

Programme::Programme() {
  isMain = false;
  setType(TYP_VIDE);
  nom = "";
  constante = false;
  tableau = 0;
  positif = false;
  innerCode = "";
}
Programme::Programme(std::string nnom) {
  isMain = false;
  setType(TYP_VIDE);
  nom = toLowerCase(nnom);
  if(nom == "main") {
    setType(TYP_ENTIER);
    isMain = true;
  }
  else if(isReserve(nom)) {
    throw "Le nom \""+nnom+"\" est déjà réservé.";
  }
  constante = false;
  tableau = 0;
  positif = false;
  innerCode = "";
}
Programme::Programme(Type ntype, std::string nnom, Structure* nstructure) {
  isMain = false;
  setType(ntype);
  nom = toLowerCase(nnom);
  if(nom == "main") {
    setType(TYP_ENTIER);
    isMain = true;
  }
  else if(isReserve(nom)) {
    throw "Le nom \""+nnom+"\" est déjà réservé.";
  }
  constante = false;
  tableau = 0;
  if(ntype == TYP_STRUCT) {
    if(nstructure != NULL) {
      structure = nstructure;
    }
    else {
      throw "Impossible de créer un programme de type de retour structure sans structure associée.";
    }
  }
  else if(ntype == TYP_CHAINE) {
    setTableau(1);
  }
  innerCode = "";
}


void Programme::addArgument(Variable var) {
  if(hasVar(arguments, var.getNom())) {
    throw "L'argument \""+var.getNom()+"\" existe déjà dans le programme \""+nom+"\".";
  }
  else {
    arguments.push_back(var);
  }
}
void Programme::addVariable(Variable var) {
  if(hasVar(variables, var.getNom())) {
    throw "La variable \""+var.getNom()+"\" a déjà été instanciée dans le programme \""+nom+"\".";
  }
  else if(hasVar(arguments, var.getNom())) {
    throw "La variable \""+var.getNom()+"\" a déjà été instanciée dans le programme \""+nom+"\" en tant qu'argument.";
  }
  else {
    variables.push_back(var);
  }
}
void Programme::addCode(std::string code) {
  innerCode += code + " ";
}
void Programme::addCodeInstance(std::string var) {
  int k = indexOfVar(variables, var);
  if(k >= 0) {
    addCode(variables[k].instancier());
  }
  else {
    throw "La variable \"" + var + "\" n'existe pas dans le programme \""+nom+"\".";
  }
}


std::string Programme::signature() const {
  std::string listArgs = "";
  int l = arguments.size();
  int i;

  for(i = 0; i < l; i++) {
    listArgs += (i>0?", ":"") + arguments[i].instancier();
  }

  return strtype() + " " + nom + "("+listArgs+")";
}
std::string Programme::instancier() const {
  /*std::string listVars = "";
  int l = variables.size();
  int i;
  
  for(i = 0; i < l; i++) {
    listVars += "  " + variables[i].instancier() + ";\n";
  }*/

  return signature() + " {\n"+innerCode+"\n}"; //listVars+"}";
}

bool Programme::hasArgument(std::string arg) const {
  return hasVar(arguments, arg);
}
bool Programme::isBeforeVar(std::string isbef, std::string var) const {
  int idBef = indexOfVar(variables, isbef);
  return hasArgument(isbef)
   || ( idBef < indexOfVar(variables, var) && idBef >= 0 );
}
bool Programme::hasVariable(std::string var) const {
  return hasVar(variables, var) || hasArgument(var);
}
Variable Programme::getVariable(std::string var) const {
  if(hasArgument(var)) {
    return arguments[indexOfVar(arguments, var)];
  }
  else if(hasVariable(var)) {
    return variables[indexOfVar(variables, var)];
  }
  else {
    throw "Le programme \""+nom+"\" ne dispose d'aucune variable \""+var+"\".";
  }
}

// TYPE tabProgs
int indexOfProg(const tabProgs& vars, std::string val) {
  int l = vars.size();
  int i;
  val = toLowerCase(val);

  for(i = 0; i < l; i++) {
    if(vars[i].getNom() == val) {
      return i;
    }
  }
  return -1;
}
bool hasProg(const tabProgs& vars, const std::string val) {
  return indexOfProg(vars, val) != -1;
}
