
#include "analyse.h"
using namespace std;

string analyse(Lignes& lignes) {
	int i, j, nbmots, l = lignes.size();
	Type key; // Type de la variable / fonction courante
	string mot; // Mot courant
	int taille; // Taille du mot Courant
	string currentVar = ""; // Nom de la variable courante
	string iterateur = ""; // Nom de la variable itératrice pour la boucle courante
	int currentProg = -1; // ID du programme courant
	bool ptVirgule; // Vrai si la ligne doit être finie par un ";"
	bool ignPar = false;
	bool needBreak = false; // Vrai si un break est nécessaire avant le prochain cas
	vector<Node> tree; // Liste des nœuds courants
	Algorithme algo; // Algorithme à construire
	Programme prog; // Programme courant
	Structure structure; // Structure courante
	Variable var; // Variable courante

	tree.reserve(20); // Reserve une marge de 20 nœuds

	// 1e lecture : architecture
	for(i = 0; i < l; ++i) {
		try {
			nbmots = lignes[i].size();
			for(j = 0; j < nbmots; ++j) {
				mot = toLowerCase(lignes[i][j]);
				taille = mot.size();
				// Vérifier si c'est un commentaire
				if(taille >= 2 && mot[0] == '/' && (mot[1] == '/' || mot[1] == '*')) {
					// Commentaire multiligne à vérifier (déjà géré sur la première ligne)
					if(mot[1] == '*') {
						if(mot[taille-2] != '*' || mot[taille-1] != '/') {
							do {
								++i;
								nbmots = lignes[i].size();
								if(nbmots > 1) {
									j = 0;
									while(j < nbmots && ((j > 0 && (lignes[i][j-1][0] != '*' || lignes[i][j][0] != '/')) || j <= 0) &&
										((lignes[i][j].size() >= 2 && (lignes[i][j][lignes[i][j].size()-2] != '*' || lignes[i][j][lignes[i][j].size()-1] != '/')) || lignes[i][j].size() < 2)
									) ++j;
								}
								else if(nbmots == 1) {
									mot = lignes[i][0];
									taille = mot.size();
									if(taille >= 2 && mot[taille-2] == '*' || mot[taille-1] == '/') {
										j = 0;
									}
									else {
										j = nbmots;
									}
								}
							} while(i < l && (nbmots < 1 || j == nbmots));
						}
					}
					// Commentaire de ligne
					else {
						// On ignore le reste de la ligne
						j = nbmots;
					}
				}
				// Vérifier si le mot est autorisé
				// Si c'est un nom ou un mot-clef
				else if(taille > 0 && ( (mot[0] >= 'a' && mot[0] <= 'z') || mot[0] == '_')) {
					if(mot == "que") {}
					// Type / Structure / finStructure
					else if((mot == "type" || mot == "types") && tree.size() == 0) {
						tree.push_back(NODE_TYPE);
					}
					else if(mot == "struct" || mot == "structure") {
						if(tree.size() == 1 && tree[0] == NODE_TYPE) {
							tree.push_back(NODE_STRUCT_NAME);
						}
						else {
							throw mot;
						}
					}
					else if(mot == "finstruct" || mot == "finstructure") {
						if(tree.size() == 2 && tree[1] == NODE_STRUCT) {
							tree.pop_back();
							algo.addType(structure);
						}
						else {
							throw "Mot-clefs \""+mot+"\" mal placé";
						}
					}
					// (ss)prog / Var / Debut / [Fin en bas :p]
					else if(mot == "programme" || mot == "sousprogramme" || mot == "procedure"
					 || mot == "prog" || mot == "ssprog" || mot == "sousprog" || mot == "ssprogramme") {
						if(tree.size() == 1 && tree[0] == NODE_TYPE) {
							tree.pop_back();
						}
						if(tree.size() == 0) {
							tree.push_back(NODE_PRG);
							prog = Programme();
							if(mot == "programme" || mot == "prog") {
								prog = Programme("main");
							}
						}
						else {
							throw mot;
						}
					}
					else if(mot == "var" || mot == "vars" || mot == "variable" || mot == "variables") {
						if(tree.size() == 1 && tree[0] == NODE_PRG) {
							tree.push_back(NODE_VARS);
						}
						else {
							throw mot;
						}
					}
					else if(mot == "debut") {
						if(tree.size() == 2 && tree[1] == NODE_VARS) {
							tree.pop_back();
						}
						if(tree.size() == 1 && tree[0] == NODE_PRG) {
							tree.push_back(NODE_DEB);
						}
						else {
							throw mot;
						}
					}
					// Si / alors / sinon / finsi
					else if(mot == "si") {
						if(tree.size() > 1 && tree[1] == NODE_DEB) {
							// TODO Si sur la même ligne que sinon
							/*if(tree[tree.size()-1] == NODE_SINON) {
								tree.pop_back();
							}*/
							tree.push_back(NODE_SI);
							tree.push_back(NODE_COND);
						}
						else {
							throw mot;
						}
					}
					else if(mot == "alors") {
						if(tree.size() > 2 && tree[1] == NODE_DEB
						 && tree[tree.size()-2] == NODE_SI && tree[tree.size()-1] == NODE_COND) {
							tree.pop_back();
						}
						else {
							throw mot;
						}
					}
					else if(mot == "sinon") {
						if(tree.size() > 2 && tree[1] == NODE_DEB
						 && tree[tree.size()-1] == NODE_SI) {
							tree.pop_back();
							tree.push_back(NODE_SINON);
						}
						else {
							throw mot;
						}
					}
					else if(mot == "finsi") {
						if(tree[tree.size()-1] == NODE_SI || tree[tree.size()-1] == NODE_SINON) {
							tree.pop_back();
						}
						else {
							throw mot;
						}
					}
					// tq (tant [que]) / faire / fintq | faire / tq
					else if(mot == "tq" || mot == "tant" || mot == "tantque") {
						if(tree.size() > 1 && tree[1] == NODE_DEB
						 && tree[tree.size()-1] == NODE_FTQ && !hasString(lignes[i], "faire")) {
						 // Si on est dans un faire...tq()
						 // ET si aucun faire n'est sur la même ligne
						 // sinon c'est un nouveau tq()faire...fin
							tree.push_back(NODE_COND);
						}
						else if(tree.size() > 1 && tree[1] == NODE_DEB) {
							tree.push_back(NODE_TQ);
							tree.push_back(NODE_COND);
						}
						else {
							throw mot;
						}
					}
					else if(mot == "faire") {
						if(tree.size() > 2 && tree[1] == NODE_DEB
						 && (tree[tree.size()-2] == NODE_TQ || tree[tree.size()-2] == NODE_POUR)
						 && tree[tree.size()-1] == NODE_COND) {
							tree.pop_back();
						}
						else if(tree.size() > 1 && tree[1] == NODE_DEB) {
							tree.push_back(NODE_FTQ);
						}
						else {
							throw mot;
						}
					}
					else if(mot == "fintq" || mot == "fintantque") {
						if(tree.size() > 1 && tree[tree.size()-1] == NODE_TQ) {
							tree.pop_back();
						}
						else {
							throw mot;
						}
					}
					// Pour / faire (cf. tq) / finPour
					else if(mot == "pour") {
						if(tree.size() > 1 && tree[1] == NODE_DEB) {
							tree.push_back(NODE_POUR);
							tree.push_back(NODE_COND);
						}
						else {
							throw mot;
						}
					}
					// cf. Faire du TQ
					/*else if(mot == "faire") {
						else {
							throw mot
						}
					}*/
					else if(mot == "finpour") {
						if(tree.size() > 1 && tree[tree.size()-1] == NODE_POUR) {
							tree.pop_back();
						}
						else {
							throw mot;
						}
					}
					// sq (selon [que]) / vaut / cas / fincas (finsq)
					else if(mot == "sq" || mot == "selon" || mot == "selonque") {
						if(tree.size() > 1 && tree[1] == NODE_DEB) {
							tree.push_back(NODE_SQ);
							tree.push_back(NODE_COND);
						}
						else {
							throw mot;
						}
					}
					else if(mot == "vaut") {
						if(tree.size() > 1 && tree[1] == NODE_DEB
						 && tree[tree.size()-2] == NODE_SQ && tree[tree.size()-1] == NODE_COND) {
							tree.pop_back();
						}
						else {
							throw mot;
						}
					}
					else if(mot == "cas") {
						if(tree.size() > 1 && tree[1] == NODE_DEB 
						 && tree[tree.size()-1] == NODE_SQ) {
							tree.push_back(NODE_CAS);
						}
						else if(tree.size() > 1 && tree[tree.size()-1] == NODE_CAS) {}
						else {
							throw mot;
						}
					}
					else if(mot == "fincas" || mot == "finsq" || mot == "finselonque") {
						if(tree.size() > 1 && tree[tree.size()-1] == NODE_SQ) {
							tree.pop_back();
						}
						else {
							throw mot;
						}
					}
					// FIN
					else if(mot == "fin") {
						// TODO rassembler tous les "fin..." ici
						if(tree.size() == 2 && tree[1] == NODE_DEB) {
							tree.pop_back();
							tree.pop_back();
							algo.addProgramme(prog);
						}
						else {
							throw mot;
						}
					}
					/////////////////////////////////////////////////////// Nœud STRUCTURE
					else if(tree.size() > 1 && tree[tree.size()-1] == NODE_STRUCT_NAME) {
						tree.pop_back();
						tree.push_back(NODE_STRUCT);
						structure = Structure(mot);
					}
					else if(tree.size() > 1 && tree[tree.size()-1] == NODE_STRUCT) {
						var = Variable();
						for(; j < nbmots && (isType(lignes[i][j]) || algo.hasType(lignes[i][j])); ++j) {
							mot = toLowerCase(lignes[i][j]);
							key = typeOfKey(mot);
							if(key >= 0) {
								var.setType(key);
							}
							else if(isPositif(mot)) {
								var.setPositif();
							}
							else if(isConstante(mot)) {
								var.setConstante();
							}
							else if(mot == "tableau") {
								var.setTableau();
							}
							else if(algo.hasType(mot)) {
								var.setType(TYP_STRUCT, algo.getType(mot));
							}
						}
						if(j < nbmots) {
							var.setNom(lignes[i][j]);
							if(var.isTableau()) {
								for(++j; j < nbmots && (lignes[i][j][0] == '[' || lignes[i][j][0] == ']'); ++j) {
									mot = toLowerCase(lignes[i][j]);
									if(taille > 0 && mot[0] == '[') {
										if(tree.size() > 1 && tree[tree.size()-1] == NODE_ROW) {
											throw '[';
										}
										else {
											tree.push_back(NODE_ROW);
											var.setTableau(1);
										}
									}
									else if(taille > 0 && mot[0] == ']') {
										if(tree.size() > 1 && tree[tree.size()-1] == NODE_ROW) {
											tree.pop_back();
										}
										else {
											throw ']';
										}
									}
								}
							}
							structure.addAttribut(var);
						}
					}
					////////////////////////////////////////////////// Nœud SOUS-PROGRAMME
					else if(tree.size() >= 1 && tree[tree.size()-1] == NODE_PRG) {
						if(prog.getNom() == "") {
							prog = Programme(mot);
						}
						else if(prog.getNom() != "main") {
							throw mot;
						}
					}
					else if(tree.size() >= 1 && tree[tree.size()-1] == NODE_PRG_TYPE) {
						if(prog.getNom() == "main") {
							throw mot;
						}
						else if(isType(mot)) {
							key = typeOfKey(mot);
							if(key >= 0) {
								prog.setType(key);
							}
							tree.pop_back();
						}
						else if(algo.hasType(mot)) {
							prog.setType(TYP_STRUCT, algo.getType(mot));
							tree.pop_back();
						}
						else if(mot == "tableau") {
							prog.setTableau();
						}
						else {
							throw mot;
						}
					}
					///////////////////////////////////////// Arguments de SOUS-PROGRAMMES
					// TODO? Utiliser une fonction !
					else if(tree.size() >= 2 && tree[tree.size()-2] == NODE_PRG
					 && tree[tree.size()-1] == NODE_PAR) {
						var = Variable();
						for(; j < nbmots && (isType(lignes[i][j]) || algo.hasType(lignes[i][j])); ++j) {
							mot = toLowerCase(lignes[i][j]);
							key = typeOfKey(mot);
							if(key >= 0) {
								var.setType(key);
							}
							else if(isPositif(mot)) {
								var.setPositif();
							}
							else if(isConstante(mot)) {
								var.setConstante();
							}
							else if(mot == "tableau") {
								var.setTableau();
							}
							else if(algo.hasType(mot)) {
								var.setType(TYP_STRUCT, algo.getType(mot));
							}
						}
						if(j < nbmots) {
							var.setNom(lignes[i][j]);
							if(var.isTableau()) {
								for(++j; j < nbmots && (lignes[i][j][0] == '[' || lignes[i][j][0] == ']'); ++j) {
									mot = toLowerCase(lignes[i][j]);
									if(taille > 0 && mot[0] == '[') {
										if(tree.size() > 1 && tree[tree.size()-1] == NODE_ROW) {
											throw '[';
										}
										else {
											tree.push_back(NODE_ROW);
											var.setTableau(1);
										}
									}
									else if(taille > 0 && mot[0] == ']') {
										if(tree.size() > 1 && tree[tree.size()-1] == NODE_ROW) {
											tree.pop_back();
										}
										else {
											throw ']';
										}
									}
								}
								--j;
							}
							prog.addArgument(var);
						}
					}
					////////////////////////////////////////// Variables de SOUS-PROGRAMME
					else if(tree.size() > 1 && tree[tree.size()-1] == NODE_VARS) {
						var = Variable();
						for(; j < nbmots && (isType(lignes[i][j]) || algo.hasType(lignes[i][j])); ++j) {
							mot = toLowerCase(lignes[i][j]);
							key = typeOfKey(mot);
							if(key >= 0) {
								var.setType(key);
							}
							else if(isPositif(mot)) {
								var.setPositif();
							}
							else if(isConstante(mot)) {
								var.setConstante();
							}
							else if(mot == "tableau") {
								var.setTableau();
							}
							else if(algo.hasType(mot)) {
								var.setType(TYP_STRUCT, algo.getType(mot));
							}
						}
						if(j < nbmots) {
							do {
								var.setNom(lignes[i][j]);
								if(var.isTableau()) {
									while(++j < nbmots && (lignes[i][j][0] == '[' || lignes[i][j][0] == ']')) {
										mot = toLowerCase(lignes[i][j]);
										if(taille > 0 && mot[0] == '[') {
											if(tree.size() > 1 && tree[tree.size()-1] == NODE_ROW) {
												throw '[';
											}
											/*else if(var.getTableauDimension() >= 1) {
												throw string("Seuls les tableaux à une dimension sont autorisés.");
											}*/
											else {
												tree.push_back(NODE_ROW);
												var.setTableau(1);
											}
										}
										else if(taille > 0 && mot[0] == ']') {
											if(tree.size() > 1 && tree[tree.size()-1] == NODE_ROW) {
												tree.pop_back();
											}
											else {
												throw ']';
											}
										}
									}
									--j;
								}
								prog.addVariable(var);
								if(++j < nbmots && lignes[i][j] == "<-") {
									while(++j < nbmots && (lignes[i][j][0] != ',' || tree[tree.size()-1] == NODE_PAR)) {
										if(lignes[i][j][0] == '(') {
											tree.push_back(NODE_PAR);
										}
										else if(lignes[i][j][0] == ')') {
											tree.pop_back();
										}
									}
								}
								++j;
							} while(j < nbmots && lignes[i][j-1][0] == ',');
						}
					}
				}
				else if(taille > 0 && mot[0] == ':') {
					if(j >= 1) {
						mot = toLowerCase(lignes[i][j-1]);
					}
					if(tree.size() >= 1 && tree[tree.size()-1] == NODE_PRG) {
						tree.push_back(NODE_PRG_TYPE);
					}
					else if(tree.size() >= 1 && tree[tree.size()-1] == NODE_CAS) {
						tree.pop_back();
					}
					else if(tree.size() >= 1 && tree[tree.size()-1] == NODE_SQ
					 && j >= 1 && mot == "defaut") {
					}
					else if(j >= 1 && (mot == "var" || mot == "vars" || mot == "variable" || mot == "debut"
					 || mot == "variables" || mot == "type" || mot == "types")) {
					}
					else {
						throw ':';
					}
				}
				else if(taille > 0 && mot[0] == '(') {
					tree.push_back(NODE_PAR);
				}
				else if(taille > 0 && mot[0] == ')') {
					if(tree.size() > 1 && tree[tree.size()-1] == NODE_PAR) {
						tree.pop_back();
					}
					else {
						throw ')';
					}
				}
				else if(taille > 0 && mot[0] == '[') {
					tree.push_back(NODE_ROW);
				}
				else if(taille > 0 && mot[0] == ']') {
					if(tree.size() > 1 && tree[tree.size()-1] == NODE_ROW) {
						tree.pop_back();
					}
					else {
						throw ']';
					}
				}
			}
			if(tree.size() > 2 && tree[1] == NODE_DEB
			 && tree[tree.size()-2] == NODE_FTQ && tree[tree.size()-1] == NODE_COND) {
				tree.pop_back();
				tree.pop_back();
			}
		}
		catch(string err) {
			throw "Ligne "+int2str(i+1)+" : Mot-clef \""+err+"\" mal placé ("
			 +int2str(tree.size())+"."+int2str(tree[tree.size()-1])+").";
		}
		catch(char err) {
			throw "Ligne "+int2str(i+1)+" : Caractère '"+err+"' mal placé ("
			 +int2str(tree.size())+"."+int2str(tree[tree.size()-1])+").";
		}
	}
	if(tree.size() > 0) {
		throw string("Absence du mot-clef \"Fin\" à la fin du fichier.");
	}

	// 2e lecture : transcription
	for(i = 0; i < l; ++i) {
		try {
			if(currentProg != -1) {
				algo.addProgCode(currentProg, "\n");
				for(j = 1; j < tree.size(); ++j) {
					algo.addProgCode(currentProg, " ");
				}
			}
			nbmots = lignes[i].size();
			for(j = 0; j < nbmots; ++j) {
				mot = toLowerCase(lignes[i][j]);
				// Vérifier si c'est un commentaire
				taille = mot.size();
				if(taille >= 2 && mot[0] == '/' && (mot[1] == '/' || mot[1] == '*')) {
					// Commentaire multiligne à vérifier (déjà géré sur la première ligne)
					if(mot[1] == '*') {
						if(mot[taille-2] != '*' || mot[taille-1] != '/') {
							do {
								++i;
								nbmots = lignes[i].size();
								if(nbmots > 1) {
									j = 0;
									while(j < nbmots && ((j > 0 && (lignes[i][j-1][0] != '*' || lignes[i][j][0] != '/')) || j <= 0) &&
										((lignes[i][j].size() >= 2 && (lignes[i][j][lignes[i][j].size()-2] != '*' || lignes[i][j][lignes[i][j].size()-1] != '/')) || lignes[i][j].size() < 2)
									) ++j;
								}
								else if(nbmots == 1) {
									mot = lignes[i][0];
									taille = mot.size();
									if(taille >= 2 && mot[taille-2] == '*' || mot[taille-1] == '/') {
										j = 0;
									}
									else {
										j = nbmots;
									}
								}
							} while(i < l && (nbmots <= 1 || j == nbmots));
						}
					}
					// Commentaire de ligne
					else {
						// On ignore le reste de la ligne
						j = nbmots;
					}
				}
				// Vérifier si le mot est autorisé
				// Si c'est un nom ou un mot-clef
				else if(taille > 0 && ( (mot[0] >= 'a' && mot[0] <= 'z') || mot[0] == '_')) {
					if(j == 0 && (tree.size() <= 1 || (tree[tree.size()-1] != NODE_COND
					 && tree[tree.size()-1] != NODE_PAR))) {
						ptVirgule = true;
					}
					if(mot == "que") {}
					// Type / Structure / finStructure
					else if((mot == "type" || mot == "types") && tree.size() == 0) {
					}
					else if(mot == "struct" || mot == "structure") {
					}
					else if(mot == "finstruct" || mot == "finstructure") {
					}
					// (ss)prog / Var / Debut / [Fin en bas :p]
					else if(mot == "programme" || mot == "sousprogramme" || mot == "procedure"
					 || mot == "prog" || mot == "ssprog" || mot == "sousprog" || mot == "ssprogramme") {
						tree.push_back(NODE_PRG);
						if(mot == "programme" || mot == "prog") {
							currentProg = algo.getProgID("main");
						}
					}
					else if(mot == "var" || mot == "vars" || mot == "variable" || mot == "variables") {
						tree.push_back(NODE_VARS);
						algo.addProgCode(currentProg, "// Variables\n");
						ptVirgule = false;
					}
					else if(mot == "debut") {
						if(tree.size() == 2 && tree[1] == NODE_VARS) {
							tree.pop_back();
						}
						tree.push_back(NODE_DEB);
						algo.addProgCode(currentProg, "\n// Début\n");
						ptVirgule = false;
					}
					// Si / alors / sinon / finsi
					else if(mot == "si") {
						// TODO Si sur la même ligne que sinon
						/*if(tree[tree.size()-1] == NODE_SINON) {
							tree.pop_back();
						}*/
						tree.push_back(NODE_SI);
						tree.push_back(NODE_COND);
						algo.addProgCode(currentProg, "if(");
						ptVirgule = false;
					}
					else if(mot == "alors") {
						tree.pop_back();
						algo.addProgCode(currentProg, ") {");
					}
					else if(mot == "sinon") {
						tree.pop_back();
						tree.push_back(NODE_SINON);
						algo.addProgCode(currentProg, "} else {");
						ptVirgule = false;
					}
					else if(mot == "finsi") {
						tree.pop_back();
						algo.addProgCode(currentProg, "}");
						ptVirgule = false;
					}
					// tq (tant [que]) / faire / fintq | faire / tq
					else if(mot == "tq" || mot == "tant" || mot == "tantque") {
						if(tree.size() > 1 && tree[1] == NODE_DEB
						 && tree[tree.size()-1] == NODE_FTQ && !hasString(lignes[i], "faire")) {
						 // Si on est dans un faire...tq()
						 // ET si aucun faire n'est sur la même ligne
						 // sinon c'est un nouveau tq()faire...fin
							tree.push_back(NODE_COND);
							algo.addProgCode(currentProg, "} while(");
						}
						else if(tree.size() > 1 && tree[1] == NODE_DEB) {
							tree.push_back(NODE_TQ);
							tree.push_back(NODE_COND);
							algo.addProgCode(currentProg, "while(");
							ptVirgule = false;
						}
					}
					else if(mot == "faire") {
						if(tree.size() > 2 && tree[1] == NODE_DEB
						 && tree[tree.size()-2] == NODE_TQ
						 && tree[tree.size()-1] == NODE_COND) {
							tree.pop_back();
							algo.addProgCode(currentProg, ") {");
						}
						else if(tree.size() > 2 && tree[1] == NODE_DEB
						 && tree[tree.size()-2] == NODE_POUR
						 && tree[tree.size()-1] == NODE_COND) {
							tree.pop_back();
							if(iterateur == "") {
								algo.addProgCode(currentProg, ") {");
							}
							else {
								algo.addProgCode(currentProg, "; "+iterateur+"++ ) {");
								iterateur = "";
							}
						}
						else if(tree.size() > 1 && tree[1] == NODE_DEB) {
							tree.push_back(NODE_FTQ);
							algo.addProgCode(currentProg, "do {");
							ptVirgule = false;
						}
					}
					else if(mot == "fintq" || mot == "fintantque") {
						tree.pop_back();
						algo.addProgCode(currentProg, "}");
						ptVirgule = false;
					}
					// Pour / faire (cf. tq) / finPour
					else if(mot == "pour") {
						tree.push_back(NODE_POUR);
						tree.push_back(NODE_COND);
						algo.addProgCode(currentProg, "for(");
						ptVirgule = false;
						if(j+1 < nbmots && lignes[i][j+1][0] == '(') {
							ignPar = true;
							++j;
						}
					}
					// cf. Faire du TQ
					/*else if(mot == "faire") {
						else {
							throw mot
						}
					}*/
					else if(mot == "finpour") {
						tree.pop_back();
						algo.addProgCode(currentProg, "}");
						ptVirgule = false;
					}
					// sq (selon [que]) / vaut / cas / fincas (finsq)
					else if(mot == "sq" || mot == "selon" || mot == "selonque") {
						tree.push_back(NODE_SQ);
						tree.push_back(NODE_COND);
						algo.addProgCode(currentProg, "switch(");
						ptVirgule = false;
					}
					else if(mot == "vaut") {
						tree.pop_back();
						algo.addProgCode(currentProg, ") {");
						ptVirgule = false;
						needBreak = false;
					}
					else if(mot == "cas") {
						if(tree.size() > 1 && tree[1] == NODE_DEB 
						 && tree[tree.size()-1] == NODE_SQ) {
							tree.push_back(NODE_CAS);
						}
						if(needBreak) {
							algo.addProgCode(currentProg, "break;");
						}
						needBreak = true;
						algo.addProgCode(currentProg, "case");
					}
					else if(mot == "fincas" || mot == "finsq" || mot == "finselonque") {
						tree.pop_back();
						algo.addProgCode(currentProg, "}");
						ptVirgule = false;
					}
					// FIN
					else if(mot == "fin") {
						// TODO rassembler tous les "fin..." ici
						tree.pop_back();
						tree.pop_back();
						currentProg = -1;
					}
					/////////////////////////////////////////////////////// Nœud STRUCTURE
					else if(tree.size() > 1 && tree[tree.size()-1] == NODE_STRUCT_NAME) {
					}
					else if(tree.size() > 1 && tree[tree.size()-1] == NODE_STRUCT) {
					}
					////////////////////////////////////////////////// Nœud SOUS-PROGRAMME
					else if(tree.size() >= 1 && tree[tree.size()-1] == NODE_PRG) {
						if(currentProg == -1) currentProg = algo.getProgID(mot);
						ptVirgule = false;
					}
					else if(tree.size() >= 1 && tree[tree.size()-1] == NODE_PRG_TYPE) {
						tree.pop_back();
						ptVirgule = false;
					}
					///////////////////////////////////////// Arguments de SOUS-PROGRAMMES
					else if(tree.size() >= 2 && tree[tree.size()-2] == NODE_PRG
					 && tree[tree.size()-1] == NODE_PAR) {
						while(j < nbmots && (isType(lignes[i][j]) || algo.hasType(lignes[i][j]))) ++j;
						for(++j; j < nbmots && (lignes[i][j][0] == '[' || lignes[i][j][0] == ']'); ++j) {
							if(taille > 0 && lignes[i][j][0] == '[') {
								tree.push_back(NODE_ROW);
							}
							else if(taille > 0 && lignes[i][j][0] == ']') {
								tree.pop_back();
							}
						}
						--j;
						ptVirgule = false;
					}
					////////////////////////////////////////// Variables de SOUS-PROGRAMME
					else if(tree.size() > 1 && tree[tree.size()-1] == NODE_VARS) {
						while(j < nbmots && (isType(lignes[i][j]) || algo.hasType(lignes[i][j]))) ++j;
						if(j < nbmots) {
							do {
								algo.addProgCodeInstance(currentProg, lignes[i][j]);
								currentVar = lignes[i][j];
								var = algo.progVar(currentProg, currentVar);
								while(++j < nbmots && (lignes[i][j][0] == '[' || lignes[i][j][0] == ']')) {
									if(taille > 0 && lignes[i][j][0] == '[') {
										tree.push_back(NODE_ROW);
									}
									else if(taille > 0 && lignes[i][j][0] == ']') {
										tree.pop_back();
									}
								}
								if(j < nbmots && lignes[i][j] == "<-") {
									algo.addProgCode(currentProg, "=");
									while(++j < nbmots && (lignes[i][j][0] != ',' || tree[tree.size()-1] == NODE_PAR)) {
										// TODO Test de compatibilité des types
										mot = toLowerCase(lignes[i][j]);
										if( (mot[0] >= 'a' && mot[0] <= 'z') || mot[0] == '_') {
											// Chercher dans la liste des Arguments / Variables précédentes / Programmes
											key = typeOfKey(mot);
											if(key >= 0) {
												if(j-1 >= 0 && j+1 < nbmots
												 && lignes[i][j-1][0] == '(' && lignes[i][j+1][0] == ')') {
													algo.addProgCode(currentProg, typeC(key));
												}
											}
											else if(algo.key2C(currentProg, mot)) {}
											else if(algo.isBeforeVar(currentProg, mot, currentVar)) {
												var = algo.progVar(currentProg, mot);
												while(var.getType() == TYP_STRUCT
												 && j + 2 < nbmots && lignes[i][j+1] == ".") {
													j += 2;
													if(var.getStructure()->hasAttribut(lignes[i][j]) == false) {
														throw "La variable \""+mot+"\" n'a pas d'attribut \""+lignes[i][j]+"\".";
													}
													mot += "."+lignes[i][j];
													var = var.getStructure()->getAttribut(lignes[i][j]);
												}
												/* Inutile, [] suffisent !
												if(var.isTableau() && j + 1 < nbmots
												 && lignes[i][j+1][0] == '[') {
													++j;
													tree.push_back(NODE_ROW);
													mot = "*("+mot+" + ";
												}*/
												algo.addProgCode(currentProg, mot);
											}
											else if(mot == "creertableau" && j + 1 < nbmots
											 && lignes[i][j+1][0] == '(') {
												algo.addProgCode(currentProg, "new "+var.strbasetype()+"[");
												creertableau(algo,currentProg,lignes,i,j);
												algo.addProgCode(currentProg, "]");
											}
											else if(algo.hasProgramme(mot) || isLibFonction(mot)) {
												algo.addProgCode(currentProg, mot);
											}
											else {
												throw "Mot \""+mot+"\" inconnu.";
											}
										}
										else {
											if(mot[0] == ')') {
												algo.addProgCode(currentProg, mot);
												tree.pop_back();
											}
											else {
												algo.addProgCode(currentProg, mot);
												if(mot[0] == '(') {
													tree.push_back(NODE_PAR);
												}
											}
										}
									}
								}
								algo.addProgCode(currentProg, ";");
							} while(++j < nbmots && lignes[i][j-1][0] == ',');
						}
						ptVirgule = false;
					}
					else if(tree.size() > 1 && tree[1] == NODE_DEB) {
						key = typeOfKey(mot);
						if(key >= 0) {
							if(j-1 >= 0 && j+1 < nbmots
							 && lignes[i][j-1][0] == '(' && lignes[i][j+1][0] == ')') {
								algo.addProgCode(currentProg, typeC(key));
							}
						}
						else if(algo.key2C(currentProg, mot)) { }
						else if(mot == "defaut") {
							if(needBreak) {
								algo.addProgCode(currentProg, "break;");
							}
							algo.addProgCode(currentProg, "default");
						}
						else if(mot == "jusqu'a") {
							algo.addProgCode(currentProg, "; "+currentVar+" <=");
							iterateur = currentVar;
						}
						else if(mot == "aupasde") {
							algo.addProgCode(currentProg, "; "+iterateur+" +=");
							iterateur = "";
						}
						else if(mot == "retour" || mot == "retourne"
						 || mot == "renvoi" || mot == "renvoie") {
							algo.addProgCode(currentProg, "return");
						}
						else if(mot == "clavier") {
							algo.addProgCode(currentProg, "stdin");
						}
						else if(algo.hasVariable(currentProg, mot)) {
							var = algo.progVar(currentProg, mot);
							while(var.getType() == TYP_STRUCT
							 && j + 2 < nbmots && lignes[i][j+1] == ".") {
								j += 2;
								if(var.getStructure()->hasAttribut(lignes[i][j]) == false) {
									throw "La variable \""+mot+"\" n'a pas d'attribut \""+lignes[i][j]+"\".";
								}
								mot += "."+lignes[i][j];
								var = var.getStructure()->getAttribut(lignes[i][j]);
							}
							
							/* Inutile, [] suffisent !
							if(var.isTableau() && j + 3 < nbmots
							 && lignes[i][j+1][0] == '[' && lignes[i][j+3][0] == ']') {
								j += 2;
								mot = "*("+mot+" + " + lignes[i][j] + ")";
								++j;
							}*/
							algo.addProgCode(currentProg, mot);
							currentVar = mot;
						}
						else if(mot == "creertableau" && j + 1 < nbmots
						 && lignes[i][j+1][0] == '(') {
							algo.addProgCode(currentProg, "new "+var.strbasetype()+"[");
							creertableau(algo,currentProg,lignes,i,j);
							algo.addProgCode(currentProg, "]");
						}
						else if(mot == "afficher" && j + 3 < nbmots
						 && lignes[i][j+1][0] == '(' && lignes[i][j+3][0] == ')') {
							j += 2;
							algo.addProgCode(currentProg, "printf("+lignes[i][j]+")");
							++j;
						}
						else if(mot == "afficher") {
							algo.addProgCode(currentProg, "printf");
							if(j + 1 < nbmots && lignes[i][j+1][0] == '(') {
								++j;
								if(tree.size() >= 2 && currentProg != -1) {
									algo.addProgCode(currentProg, "(");
								}
								tree.push_back(NODE_PAR);
								if(++j >= nbmots) {
									++i;
									j = 0;
								}
								if(lignes[i][j][0] != '"') {
									throw "Fonction Afficher mal utilisée.";
								}
							}
							algo.addProgCode(currentProg, afficher(algo, currentProg, lignes, i, j));
						}
						else if(algo.hasProgramme(mot) || isLibFonction(mot)) {
							algo.addProgCode(currentProg, mot);
						}
						else {
							throw "Mot \""+mot+"\" inconnu.";
						}
					}
				}
				else if(taille > 0 && mot[0] == ':') {
					if(tree.size() >= 1 && tree[tree.size()-1] == NODE_PRG) {
						tree.push_back(NODE_PRG_TYPE);
					}
					else if(tree.size() >= 1 && tree[tree.size()-1] == NODE_CAS) {
						tree.pop_back();
						algo.addProgCode(currentProg, mot);
					}
					else if(tree.size() >= 1 && tree[tree.size()-1] == NODE_SQ) {
						algo.addProgCode(currentProg, mot);
					}
				}
				else if(taille > 0 && mot[0] == '(') {
					if(tree.size() >= 2 && currentProg != -1) {
						algo.addProgCode(currentProg, mot);
					}
					tree.push_back(NODE_PAR);
				}
				else if(taille > 0 && mot[0] == ')') {
					if(ignPar) {
						ignPar = false;
					}
					else {
						tree.pop_back();
						if(tree.size() >= 2 && currentProg != -1) {
							algo.addProgCode(currentProg, mot);
						}
					}
				}
				else if(taille > 0 && mot[0] == '[') {
					algo.addProgCode(currentProg, mot);
					tree.push_back(NODE_ROW);
				}
				else if(taille > 0 && mot[0] == ']') {
					algo.addProgCode(currentProg, mot);
					/* Inutile, [] suffisent !
					if(tree[tree.size()-1] == NODE_ROW) {
						algo.addProgCode(currentProg, ")");
					} */
					tree.pop_back();
				}
				else if(mot == "<-") {
					algo.addProgCode(currentProg, "=");
				}
				else if(mot == "<>") {
					algo.addProgCode(currentProg, "!=");
				}
				else if(mot == "=") {
					algo.addProgCode(currentProg, "==");
				}
				else if(taille > 0 && mot[0] == ','
				 && tree.size() >= 2 && tree[tree.size()-2] == NODE_PRG) {
				}
				else {
					algo.addProgCode(currentProg, lignes[i][j]);
				}
			}
			if(tree.size() > 2 && tree[1] == NODE_DEB
			 && tree[tree.size()-2] == NODE_FTQ && tree[tree.size()-1] == NODE_COND) {
				tree.pop_back();
				tree.pop_back();
				algo.addProgCode(currentProg, ");");
				ptVirgule = false;
			}
			if(ptVirgule && (tree.size() <= 1 || (tree[tree.size()-1] != NODE_COND
			 && tree[tree.size()-1] != NODE_PAR))) {
				algo.addProgCode(currentProg, ";");
				ptVirgule = false;
			}
		}
		catch(string err) {
			throw "Ligne "+int2str(i+1)+" : "+err;
		}
		catch(const char* err) {
			throw "Ligne "+int2str(i+1)+" : "+string(err);
		}
	}
	if(tree.size() > 0) {
		throw "Erreur inconnue à la deuxième lecture ("+int2str(tree.size())+").";
	}

	return algo.ecrire();
}

string afficher(Algorithme& algo, int currentProg, Lignes& lignes, int i, int j) {
	int nblignes = lignes.size(); // Nombre de lignes du fichier
	int nbmots = lignes[i].size(); // Nombre de mot de la ligne courante
	string chaine = lignes[i][j]; // Chaîne du format à afficher
	int l = chaine.size(); // Taille de la chaîne
	string mot; // Mot courant
	Type key; // Type de la variable courante
	queue<Type> types; // File des types des variables à afficher dans l'ordre donné
	int treesize = 1;
	int nbignnodes = 0;
	Variable var; // Variable courante
	Structure structure; // Structure courante

	while(treesize > 0 && i < nblignes) {
		while(treesize > 0 && ++j < nbmots) {
			mot = lignes[i][j];
			if(mot[0] == '(') {
				++treesize;
			}
			else if(mot[0] == ')') {
				--treesize;
			}
			else if(mot[0] == ',') {}
			else if((mot[0] >= '0' && mot[0] <= '9')
			 || mot[0] == '.' || mot[0] == '\''
			 || (mot[0] >= 'a' && mot[0] <= 'z')) {
				key = typeOfKey(mot);
				if(key >= 0) {
					if(j-1 >= 0 && j+1 < nbmots
					 && lignes[i][j-1][0] == '(' && lignes[i][j+1][0] == ')') {
						types.push(key);
						++nbignnodes; // '('
						--treesize; // ')'
					}
				}
				else if(mot[0] >= '0' && mot[0] <= '9') {
					if(hasCaractere(mot, '.')) {
						types.push(TYP_REEL);
					}
					else {
						types.push(TYP_ENTIER);
					}
				}
				else if(mot[0] == '.') {
					types.push(TYP_REEL);
				}
				else if(mot[0] == '\'') {
					types.push(TYP_CARACTERE);
				}
				else if(algo.hasVariable(currentProg, mot)) {
					var = algo.progVar(currentProg, mot);
					while(var.getType() == TYP_STRUCT
					 && j + 2 < nbmots && lignes[i][j+1] == ".") {
						j += 2;
						if(var.getStructure()->hasAttribut(lignes[i][j]) == false) {
							throw "La variable \""+mot+"\" n'a pas d'attribut \""+lignes[i][j]+"\".";
						}
						mot += "."+lignes[i][j];
						var = var.getStructure()->getAttribut(lignes[i][j]);
					}
					types.push(var.getType());
				}
				else if(algo.hasProgramme(mot)) {
					types.push(algo.getProgType(mot));
				}
				else if(isLibFonction(mot)) {
					types.push(typeOfLibFonction(mot));
				}
				while(i < nblignes && nbignnodes >= 0) {
					while(nbignnodes >= 0 && ++j < nbmots) {
						mot = lignes[i][j];
						if(mot[0] == '(') {
							++nbignnodes;
						}
						else if(mot[0] == ')') {
							--nbignnodes;
						}
						else if(mot[0] == ',' && nbignnodes == 0) {
							--nbignnodes;
						}
					}
					if(nbignnodes >= 0) {
						++i;
						nbmots = lignes[i].size();
					}
				}
				--j;
				nbignnodes = 0;
			}
		}
		++i;
		j = -1;
		nbmots = lignes[i].size();
	}

	for(i = 0; i < l; ++i) {
		if(chaine[i] == '{') {
			chaine[i] = '%';
		}
		else if(chaine[i] == '}') {
			switch(types.front()) {
			case TYP_ENTIER :
				chaine[i] = 'd';
				chaine.insert(i, 1, 'l');
				++l;
			break;
			case TYP_REEL :
				chaine[i] = 'f';
				chaine.insert(i, 1, 'l');
				++l;
			break;
			case TYP_CARACTERE :
				chaine[i] = 'c';
			break;
			case TYP_CHAINE :
				chaine[i] = 's';
			break;
			case TYP_BOOLEEN :
				throw "Le type booléen ne peut être affiché directement.";
			break;
			case TYP_STRUCT :
				throw "Une structure ne peut être affichée directement.";
			break;
			default:
				throw "Vous essayez d'afficher un type inconnu.";
			}
			types.pop();
		}
	}
	return chaine;
}

void creertableau(Algorithme& algo, const int currentProg, const Lignes& lignes, int& i, int& j) {
	int nblignes = lignes.size(); // Nombre de lignes du fichier
	int nbmots = lignes[i].size(); // Nombre de mot de la ligne courante
	string mot; // Mot courant
	int treesize = 1;

	algo.addProgCode(currentProg, "(");
	j+=2;
	while(treesize > 0 && i < nblignes) {
		while(treesize > 0 && j < nbmots) {
			mot = toLowerCase(lignes[i][j]);
			if(mot[0] == '(') {
				++treesize;
				algo.addProgCode(currentProg, mot);
			}
			else if(mot[0] == ')') {
				--treesize;
				if(treesize == 0) {
					algo.addProgCode(currentProg, "+1");
				}
				algo.addProgCode(currentProg, mot);
			}
			else if(mot[0] == ',' && treesize == 1) {
				algo.addProgCode(currentProg, "+1)*(");
			}
			else {
				algo.addProgCode(currentProg, mot);
			}

			++j;
		}

		if(treesize > 0) {
			++i;
			j = 0;
			nbmots = lignes[i].size();
		}
	}
}