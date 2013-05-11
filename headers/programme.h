
#ifndef __PROGRAMME_H__
#define __PROGRAMME_H__

#include <string>
#include "structure.h"

class Programme : public Variable {
  public:
    Programme();
    Programme(std::string nnom);
    Programme(Type ntype, std::string nnom = NULL, Structure* nstructure = NULL);

    void addArgument(Variable);
    void addVariable(Variable);
    void addCode(std::string);
    void addCodeInstance(std::string);

    std::string signature() const;
    std::string instancier() const;

    // Vérifie si l'argument est définie dans le programme
    bool hasArgument(std::string) const;
    // Vérifie si une variable est définie dans le programme avant l'autre (variable ou argument)
    bool isBeforeVar(std::string isbef, std::string var) const;
    // Vérifie si la variable est définie dans le programme (variable ou argument)
    bool hasVariable(std::string) const;
    Variable getVariable(std::string) const;
  private:
    bool isMain;
    tabVars arguments;
    tabVars variables;
    std::string innerCode;
};

typedef std::vector<Programme> tabProgs;
int indexOfProg(tabProgs, std::string);
bool hasProg(tabProgs, std::string);

#endif

