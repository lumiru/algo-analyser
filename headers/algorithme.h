
#ifndef __ALGORITHME_H__
#define __ALGORITHME_H__

#include <string>
#include "structure.h"
#include "programme.h"

class Algorithme {
  public:
    // Types personnels (structures)
    void addType(Structure);
    bool hasType(std::string);
    Structure* getType(std::string);

    // Programme et sous-programmes
    void addProgramme(Programme);
    int getProgID(std::string) const;
    Type getProgType(std::string) const;
    void addProgCode(int prog, std::string code);
    void addProgCodeInstance(int prog, std::string var);
    bool hasArgument(int, std::string) const;
    bool isBeforeVar(int, std::string isbef, std::string var) const;
    bool hasVariable(int, std::string) const;
    Variable progVar(int, std::string) const;

    bool key2C(int currentProg, std::string mot);

    std::string ecrire() const;
    bool hasProgramme(std::string) const;
  private:
    tabStructs types;
    tabProgs programmes;
};

#endif

