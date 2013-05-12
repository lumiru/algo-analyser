
#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include <string>
#include <vector>

typedef enum { TYP_ERR = -1,
 TYP_VIDE = 0, TYP_ENTIER, TYP_REEL, TYP_CARACTERE, TYP_CHAINE,
 TYP_BOOLEEN, TYP_FICHIER, TYP_STRUCT } Type;

#include "functions.h" // Base : toLowerCase, firstLetterCap
#include "key.h"

class Structure;

class Variable {
  public:
    Variable();
    Variable(Type ntype, std::string nnom = NULL, bool nconstante = false, Structure* nstructure = NULL);

    void setType(Type ntype, Structure* nstructure = NULL);
    void setNom(std::string nnom);
    void setTableau(char taille = 0);
    void setConstante();
    void setPositif();

    Structure* getStructure() const;
    std::string getNom() const;
    Type getType() const;
    std::string strtype() const;
    std::string strbasetype() const;
    std::string instancier() const;
    bool isTableau() const;
    char getTableauDimension() const;

  protected:
    bool constante;
    bool positif;
    char tableau;
    Type type;
    std::string nom;
    Structure* structure;
};

typedef std::vector<Variable> tabVars;
int indexOfVar(const tabVars&, std::string);
bool hasVar(const tabVars&, const std::string);

#endif

