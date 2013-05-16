//---------------------------------------------------------------------------
//
// Name:  Bibliothèque de gestion de chaînes de caractères
// Author:  MILONE Alain
// Created: Septembre 2011
// Description: Bibliothèque simplifiant la gestion des chaînes en C++
// en supprimant toute référence à un pointeur
// Fournit aussi des fonctions permettant de gérer des tableaux de chaînes de caractères
//
//---------------------------------------------------------------------------

#ifndef AMLIB_H
#define AMLIB_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <locale>
//#include <windows.h>

#ifndef chaine
	#define chaine char*
#endif
#ifndef texte
	#define texte char*
#endif
#ifndef tableauchaines
	#define tableauchaines char**
#endif
#ifndef tabchaines
	#define tabchaines char**
#endif
#ifndef touttype
    #define touttype void*
#endif
#ifndef desc
    #define desc FILE*
#endif

typedef bool booleen ;
typedef long entier ;
typedef double reel  ;
typedef char caractere ;

/**** 1° PARTIE : GESTION DE CHAINES ET DE TABLEAUX DE CHAINES  ****/
void generateurnbaleatoire ( ) ;
// Fonction de gestion de chaîne
chaine creerchainevide ( entier taille ) ;	// chaîne vide de taille donnée
chaine creerchaineinit ( chaine unechaine ) ;	// chaîne fournie avec création à sa taille
void detruirechaine ( chaine unechaine ) ;
//-----------------------------------------------------------------------------------------------------
// Fonction de gestion de tableau de chaînes
tableauchaines creertableauchaines ( entier nb )  ;
void detruiretableauchaines ( tableauchaines tab ) ;
entier nbchaines ( tableauchaines tab ) ;
booleen ajouterchaine ( tableauchaines tab, chaine ch ) ;
chaine duppliquechaine ( tableauchaines tab, entier pos ) ;
bool supprimerchainetab  ( tableauchaines tabCh, int i ) ;
entier chercherchaine ( tableauchaines tab, chaine ch ) ;
entier chercherchainepos ( tableauchaines tab, chaine ch, entier pos ) ;
bool copierchaines ( tableauchaines tabDest, tableauchaines tabSour ) ;
chaine concatchaines ( tableauchaines tabch, int pos  ) ;
tableauchaines split ( chaine unechaine, caractere sep );
//-----------------------------------------------------------------------------------------------------
chaine saisiechaine (  ) ;		// saisie d'une chaîne au clavier
chaine saisiechainelimitee ( entier taille ) ;	// saisie d'une chaîne au clavier avec taille max
booleen affichechaine ( texte unechaine, booleen rc ) ;
booleen ischainevalide ( texte unechaine ) ;
//-----------------------------------------------------------------------------------------------------
chaine copiechaine ( chaine chdest, chaine chsour ) ; // copie de chaîne sans contrôle si chDest a une taille supérieure à chSour
chaine copiechainelimitee ( chaine chdest, chaine chsour, entier taille ) ; // copie de chaîne avec copie maximal de taille caractères ( il faut que taille >= longueurChaine ( chDest ))
chaine concatenechaine ( chaine chdest, chaine chsour ) ;
entier longueurchaine ( chaine ch ) ;
entier comparechaine ( chaine ch1, chaine ch2 ) ;
//-----------------------------------------------------------------------------------------------------
int saisiecaractere ( ) ;
entier cherchecaractere ( chaine unechaine, caractere c ) ;
entier cherchecaracterepos ( chaine unechaine, caractere c, entier pos ) ;
entier setcaractere ( chaine unechaine, caractere c, entier pos ) ;
bool ajoutcaractere ( chaine unechaine, entier longueur, caractere c  ) ;
caractere getcaractere ( chaine unechaine, entier pos ) ;
entier nboccurencescar ( chaine unechaine, caractere car ) ;
entier cherchepattern ( chaine unechaine, chaine pattern ) ;
booleen changepattern ( chaine unechaine, chaine pattern, entier pos ) ;
chaine extractsouschaineinterv ( chaine unechaine, entier debut, entier nb ) ;
chaine extractsouschaine ( chaine unechaine, entier debut ) ;
chaine chainetotabcar ( chaine ch ) ;
chaine tabcartochaine ( chaine tabcar ) ;
//-----------------------------------------------------------------------------------------------------
booleen ischainenumerique ( chaine unechaine ) ;
entier chainetoentier ( chaine unechaine ) ;
chaine entiertochaine ( entier entier ) ;
reel chainetoreel ( chaine unechaine ) ;
chaine reeltochaine ( reel nb, entier dec, booleen tronque ) ;
//-----------------------------------------------------------------------------------------------------
booleen miseenminuscule ( chaine uneChaine ) ;
booleen miseenmajuscule ( chaine uneChaine ) ;
booleen trim ( chaine uneChaine ) ;
//------------------------------------------------------------------------------------------------------

/**** 2° PARTIE : ACCES A LA BIBLIOTHEQUE MATH  ****/

double degretoradian ( double val ) ;
double getpi ( ) ;
double cosinus ( double val ) ;
double sinus ( double val ) ;
double tangente ( double val ) ;
double arccosinus ( double val ) ;
double arcsinus ( double val ) ;
double arctangente ( double val ) ;
double cosinushyp ( double val ) ;
double sinushyp ( double val ) ;
double tangentehyp ( double val ) ;
double exponentielle ( double val ) ;
double logarithme ( double val ) ;
double logarithme10 ( double val ) ;
double puissance ( double base, double exp ) ;
long factorielle ( int n ) ;
double racinecarree ( double val ) ;
double arrondisup ( double val ) ;
double arrondiinf ( double val  ) ;
double valeurabsolue ( double val ) ;
double restediv ( double num, double denom ) ;

/*** 3° PARTIE : SOUS-PROGRAMMES D'ACCES AUX FICHIERS   ****/ 

FILE* ouverture ( const chaine nom , chaine mode ) ;
int fermeture ( desc descfichier ) ;
int videbuffer ( desc descfichier ) ;
int lecture ( void* buffer, int taille, int nb, desc descfichier ) ;
int ecriture ( void* buffer, int taille, int nb, desc descfichier ) ;
int findefichier ( desc descfichier ) ;
long deplacecurseur ( desc descfichier, long  depl, int orig ) ;
long positioncurseur ( desc descfichier ) ;
int chargecaractere ( desc descfichier ) ;
int ecriturecaractere ( int c, desc descfichier ) ;
chaine lectureligne ( chaine buffer, int nb, desc descfichier ) ;
int ecritureligne ( chaine buffer, desc descfichier ) ;

 /*** 4 PARTIE : SOUS-PROGRAMMES DIVERS   ****/ 
     
int nombrealeatoire ( int debut, int fin ) ;
//void modifietailleconsole( int nbcol, int nblig ) ;
//void effaceecran ( ) ;
//void pause ( ) ;
//void couleur( int couleurdutexte,int couleurdufond ) ;

#endif
