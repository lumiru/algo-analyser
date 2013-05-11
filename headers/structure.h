
#ifndef __STRUCTURE_H__
#define __STRUCTURE_H__

#include <string>
#include "functions.h" // Base : toLowerCase, firstLetterCap
#include "variable.h"
#include "key.h"

// Liste des structures
class Structure {
  public:
    Structure();
    Structure(std::string);

    void addAttribut(Variable);

    std::string getNom() const;
    std::string creer() const;
    bool hasAttribut(std::string) const;
    Variable getAttribut(std::string) const;
  private:
    std::string nom;
    tabVars attributs;
};

typedef std::vector<Structure> tabStructs;
int indexOfStruct(tabStructs, std::string);
bool hasStruct(tabStructs, std::string);

#endif

