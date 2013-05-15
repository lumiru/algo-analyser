
#ifndef __ANALYSE_H__
#define __ANALYSE_H__

#include <string>
#include <vector>
#include <queue>
#include "algorithme.h"
#include "fichier.h"

enum Node {
  NODE_TYPE, NODE_STRUCT_NAME, NODE_STRUCT,
  NODE_PRG, NODE_PRG_TYPE, NODE_VARS, NODE_DEB,
  NODE_SI, NODE_SINON,
  NODE_TQ, NODE_FTQ,
  NODE_POUR,
  NODE_SQ, NODE_CAS,
  NODE_COND, NODE_PAR, NODE_CRO, NODE_ROW // Condition / Parenthèses / Crochet
};
typedef enum Node Node;

std::string analyse(Lignes&);
std::string afficher(Algorithme&, int currentProg, Lignes&, int i, int j);
void creertableau(Algorithme& algo, Variable& var, const int currentProg, const Lignes& lignes, int& i, int& j);

#endif

