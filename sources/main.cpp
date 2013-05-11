//#include <cstdlib> Commande system
#include <cstdio>
#include <string>
#include "fichier.h"
#include "analyse.h"

#define MAX_SOURCE_FILENAME_SIZE 256

using namespace std;

int main(int argc, char* argv[]) {
	// Liste des mots clefs
		// structure, struct
		// Prog, Programme
		// ssprog, sousprogramme, ssprogramme, sousprog, procedure
		// Vars, var, variables
		// si - alors / tant que, tq - faire / selon que, sq - vaut / pour - faire
		// et, ou
		// /!\ <- > = , = > == , <> > != , non > !, modulo > %
	// À la lecture
	// 1e lecture : architecture
		// Liste des structures
			// class Structure
		// Liste des (sous-)programmes
			// Gestion des prototypes
			// Liste des variables et leurs types
	// 2e lecture : transcription
		// Gestion de la fonction Afficher (%X?ld %X?s %X?c %X?lf…) et TODO Afficher("…"+var+"…"…)
		// Gestion de la fonction creertableau (utilisation de calculs et TODO multidimensions) :
			// (TYPE*) calloc ( (taille1 + 1) * (taille2 + 1)… ) sizeof( TYPE );
	int i, j;
	char source[MAX_SOURCE_FILENAME_SIZE];
	Lignes fichier;
	string data;

	try {
		source[0] = 0;
		for(i = 1; i < argc; i++) {
			if(argv[i][0] == '-') {
				switch(argv[i][1]) {
					default:
						// TODO [<destination>] directement en EXE
						// TODO -a Analyse seulement
						printf("%s <source>\nAnalyse le fichier source et le traduit en C++ dans destination.\n", argv[0]);
				}
			}
			else {
				j = -1;
				while(argv[i][++j] && j < MAX_SOURCE_FILENAME_SIZE) source[j] = argv[i][j];
				source[j] = 0;
			}
		}

		if(source[0]) {
			chargerLib(argv[0]);
			fichier = ouvrir(source);
			/**/data = analyse(fichier);
			sprintf(source, "%s.cpp", source);
			enregistrer(source, data);/*/

			i = 0;
			for (int l = fichier.size(); i < l; ++i)
			{
				j = 0;
				for (int s = fichier[i].size(); j < s; ++j)
				{
					printf("%s ", fichier[i][j].c_str());
				}
				printf("\n");
			}/**/
		}
	}
	catch(string err) {
		printf("Erreur : %s\n", err.c_str());
		return 1;
	}
	return 0;
}
