
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
    //Variable(const Variable& var);

    void setType(Type ntype, Structure* nstructure = NULL);
    void setNom(std::string nnom);
    void setTableau(char dimension = 0);
    void setConstante();
    void setPositif();

    void setTailleTableau(const std::vector<std::string>& tailles);
    void addTailleTableau(std::string taille);
    void clearTailleTableau();

    Structure* getStructure() const;
    std::string getNom() const;
    Type getType() const;
    std::string strtype() const;
    std::string strbasetype() const;
    std::string instancier() const;
    bool isTableau() const;
    char getTableauDimension() const;
    std::string getTailleTableau(int dimension) const;

  protected:
    bool constante;
    bool positif;

    // Dimension du tableau (-1 si n'est pas un tableau)
    char tableau;
    // Taille pour chaque dimension du tableau (vide si n'est pas un tableau).
    std::vector<std::string> tailleTableau;

    Type type;
    std::string nom;
    Structure* structure;
};

typedef std::vector<Variable> tabVars;
int indexOfVar(const tabVars&, std::string);
bool hasVar(const tabVars&, const std::string);

#endif

