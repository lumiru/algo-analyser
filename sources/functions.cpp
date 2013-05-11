
#include "functions.h"
using namespace std;

string toLowerCase( string str ) {
	int l = str.size();
	int i;
	char c;

	for(i = 0; i < l; i++) {
		c = str[i] ;
		if ( c >= 'A' && c <= 'Z' ) {
			str[i] = c + ( 'a' - 'A' );
		}
	}
	return retirerAccents(str);
}

string firstLetterCap( string str ) {
	str = toLowerCase(str);
	int i = 0, l = str.size();
	char c;

	while(i < l && (c = str[i]) && (c < 'a' || c > 'z')) ++i;
	if ( c >= 'a' && c <= 'z' ) {
		str[i] = c - ( 'a' - 'A' );
	}
	return retirerAccents(str);
}

string retirerAccents(string message) {
	string accent     = "ÀÁÂÃÄÅàáâãäåÒÓÔÕÖØòóôõöøÈÉÊËèéêëÌÍÎÏìíîïÙÚÛÜùúûüÿÑñÇç";
	string sansAccent = "AAAAAAaaaaaaOOOOOOooooooEEEEeeeeIIIIiiiiUUUUuuuuyNnCc";
	int i=0,j=0,k=0,taille;
	int nbAccent = sansAccent.size();

	taille = message.size();

	for(i = 0; i < taille; i++) {
		// En UTF-8, un caractère accentué = 2 caractères
		for(j = 0; j < nbAccent*2; j += 2) {
			if(message[i]==accent[j] && message[i+1]==accent[j+1]) {
				message[i]=sansAccent[j/2];
				for(k=i+1;k<taille;k++) {
					message[k]=message[k+1];
				}
				message=message.substr(0,taille-1);
				taille=message.size();
			}
		}
	}

	return message;
}

Mots& decoupeMots(string str) {
	int i, l = str.size();
	char c = 0; // Caractère courant
	Mots* mots = new Mots(); // Liste de mot à retourner
	int dernierMot = -1; // Numéro du dernier mot
	char inSth = 0; // Définit le type de mot courant
	bool ajouter = false; // Vrai si la chaîne tampon doit être ajouté à la liste de mots
	char prevC; // Caractère précédent
	string newstr = ""; // Chaîne tampon (prochain mot)

	for(i = 0; i < l; i++) {
		prevC = c;
		c = str[i];
		ajouter = false;
		// "Mot multiple" (chaine ou commentaire)
		if(inSth) {
			ajouter = true;
			// '"' (chaîne) ou '*' (commentaire)
			if(inSth == c) {
				// Chaine ou caractère
				if(inSth == '"' || inSth == '\'') {
					if(prevC != '\\') {
						inSth = 0;
					}
				}
				// Commentaire
				else if(inSth == '/') {
					if(prevC == '*') {
						inSth = 0;
					}
				}
			}
			// Entier ou flottant
			if(inSth == '0') {
				if((c < '0' || c > '9') && c != '.') {
					inSth = 0;
					ajouter = false;
				}
			}
			// Mot clef ou nom de variable
			else if(inSth == 'a') {
				// Caractère '\'' pour les mots clef "jusqu'à" et "tableau d'entiers"
				if( (c < '0' || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || c > 'z')
				 && c != '_' && c != '\'' ) {
					inSth = 0;
					ajouter = false;
				}
			}
			// Opérateur à double signe
			else if(inSth == '<' || inSth == '=' || inSth == '>') {
				if(c != '=' && (inSth != '<' || (c != '-' && c != '>'))) {
					ajouter = false;
				}
				inSth = 0;
			}
			// Flottant ou attribut
			else if(inSth == '.') {
				if(c >= '0' && c <= '9') {
					inSth = '0';
				}
				else {
					inSth = 0;
					ajouter = false;
				}
			}
			// Commentaire
			else if(inSth == '*') {
				// Monoligne
				if(c == '/') {
					// mots.pop_back();
					/*for(; i < l; i++) {
						(*mots)[dernierMot].push_back(str[i]);
					}
					return *mots;*/
					inSth = '/';
				}
				// Multiligne
				else if(c == '*') {
					inSth = '/';
				}
				// Division
				else {
					inSth = 0;
					ajouter = false;
				}
			}
			if(ajouter) {
				(*mots)[dernierMot].push_back(c);
			}
		}
		if(inSth == 0 && ajouter == false && c > ' ') {
			// . : Un flottant ou un attribut
			// [] : Ne commence jamais
			if(c >= '0' && c <= '9') {
				inSth = '0';
			}
			else if( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' ) {
				inSth = 'a';
			}
			else if(c == '"' || c == '\'' || c == '<' || c == '=' || c == '>' || c == '.') {
				inSth = c;
			}
			else if(c == '/') {
				inSth = '*';
			}
			newstr.push_back(c);
			mots->push_back(newstr);
			dernierMot++;
			newstr = "";
		}
	}
	return *mots;
}

string int2str(long n) {
	ostringstream oss;

	oss << n;
	return oss.str();
}
long str2int(std::string str) {
	int i, l = str.size();
	long ret = 0;
	char c;

	for(i = 0; i < l; ++i) {
		c = str[i];
		if(c >= '0' && c <= '9') {
			ret = ret*10 + (long) (str[i] - '0');
		}
		else {
			return -1;
		}
	}

	return ret;
}

bool hasString(vector<string> tab, string str) {
	return indexOfString(tab, str) > -1;
}
bool hasString(const char* const tab[], const int len, const char* str) {
	int i, j, l = 0, OK;

	while(str[l]) ++l;
	for(i = 0; i < len; ++i) {
		for(j = 0, OK = 0; tab[i][j] && j < l && j == OK; ++j) {
			if(tab[i][j] == str[j]) ++OK;
		}
		if(OK == l && tab[i][j] == 0) {
			return true;
		}
	}
	return false;
}

int indexOfString(vector<string> tab, string str) {
	int i, l = tab.size();

	for(i = 0; i < l; ++i) {
		if(tab[i] == str) {
			return i;
		}
	}
	return -1;
}

bool hasCaractere(string str, char c) {
	int i, l = str.size();

	for(i = 0; i < l; ++i) {
		if(str[i] == c) return true;
	}
	return false;
}
