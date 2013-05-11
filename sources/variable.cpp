
#include "variable.h"

// class Variable

Variable::Variable() {
	setType(TYP_VIDE);
	constante = false;
	tableau = -1;
	positif = false;
}
Variable::Variable(Type ntype, std::string nnom, bool nconstante, Structure* nstructure) {
	setType(ntype, nstructure);
	setNom(nnom);
	constante = nconstante;
	tableau = -1;
	positif = false;
}

void Variable::setType(Type ntype, Structure* nstructure) {
	type = ntype;
	if(ntype == TYP_STRUCT) {
		if(nstructure != NULL) {
			structure = nstructure;
		}
		else {
			throw "Impossible de créer une variable de type structure sans la structure associée.";
		}
	}
	else if(ntype == TYP_CHAINE) {
		setTableau();
		setTableau(1);
	}
}
void Variable::setNom(std::string nnom) {
	nom = toLowerCase(nnom);
	if(isReserve(nom)) {
		throw "Le nom \""+nnom+"\" est déjà réservé.";
	}
}
void Variable::setTableau(char taille) {
	if(taille == 0 && isTableau() == false) {
		tableau = 0;
	}
	else if(taille != 0 && isTableau()) {
		tableau += taille;
	}
	else if(isTableau()) {}
	else {
		throw "Cette variable n'est pas un tableau, vous ne pouvez pas lui ajouter de dimension.";
	}
}
void Variable::setConstante() {
	constante = true;
}
void Variable::setPositif() {
	positif = true;
}


Structure* Variable::getStructure() const {
	return structure;
}
std::string Variable::getNom() const {
	return nom;
}
Type Variable::getType() const {
	return type;
}

/* Définie dans structure.cpp
std::string Variable::strtype() const {
	if(type == TYP_STRUCT) {
		return NULL;
	}
	else if(type < TYP_STRUCT) {
		std::string deb = "";
		std::string fin = "";
		if(tableau > 0) {
			for(int i = 0; i < tableau; i++) {
				deb += "(*";
				fin += ")";
			}
		}
		std::string toStr[] = {"long", "double", "char", "char", "bool"};
		return deb + toStr[type] + fin;
	}
	else {
		throw "Type inconnu.";
	}
}*/
std::string Variable::instancier() const {
	return (constante?"const ":"") + std::string(positif?"unsigned ":"") + strtype() + " " + nom;
}
bool Variable::isTableau() const {
	return tableau >= 0;
}
char Variable::getTableauDimension() const {
	return tableau;
}

// TYPE tabVars
int indexOfVar(tabVars vars, std::string val) {
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
bool hasVar(tabVars vars, std::string val) {
	return indexOfVar(vars, val) != -1;
}
