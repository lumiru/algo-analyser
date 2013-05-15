
#include "fichier.h"

using namespace std;

Lignes& ouvrir(const char* chemin) {
	Lignes* lignes = new Lignes();

	// Définition de charset
	ifstream filec(chemin); // Obligation d'en déclarer 2 à cause de Windows… Mais pourquoi :'( ?
	if(filec.fail()) {
		throw "Impossible d'ouvrir le fichier "+string(chemin)+".";
	}
	Charset charset = getCharset(filec);
	filec.close();

	ifstream file(chemin);
	lireBOM(file); // Met le curseur après le BOM pour l'écarter de la lecture du fichier.
	string line;
	Mots mots;

	while(getline(file, line)) {
		if(charset == CHARSET_ISO_8859) {
			line = iso8859ToUtf8(line);
		}
		line = retirerAccents(line);
		mots = decoupeMots(line);
		lignes->push_back(mots);
	}

	file.close();
	return *lignes;
}

void enregistrer(const char* chemin, std::string data) {
	ofstream file(chemin);
	if(file.fail()) {
		throw "Impossible d'ouvrir le fichier "+string(chemin)+".";
	}
	file << data;
	file.close();
}

void gotoExeChemin(const char argv0[], char* cwd, int cwdTaille) {
	char exe[200];
	int i = -1;

	if(cwd != NULL) {
		if(getcwd(cwd, cwdTaille) == NULL) {
			cwd[0] = '.';
			cwd[1] = 0;
			cerr << "Une erreur s'est produite pendant l'obtention du dossier de travail." << endl;
		}
	}
	// Copie
	while(argv0[++i]) exe[i] = argv0[i];
	exe[i] = 0;
	// -----
	// Tronque à partir du dernier '\\' (Windows) ou '/' (UNIX)
	while(exe[--i] != '\\' && exe[i] != '/') exe[i] = 0;
	// -------
	
	if(chdir(exe) == -1) {
		cerr << "Impossible de se déplacer dans le dossier \"" << string(exe) << "\"." << endl;
	}
}
