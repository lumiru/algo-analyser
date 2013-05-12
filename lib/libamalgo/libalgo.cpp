//---------------------------------------------------------------------------
//
// Name:  Bibliothèque de gestion de chaînes et divers autres fonctionnalités pour 
// être utilisée conjointement avec l'analyseur d'algorithmes.
// Author:  MILONE Alain
// Created: Septembre 2011
// Description: Bibliothèque simplifiant la gestion des chaînes en C++
// en supprimant toute référence à un pointeur
//
//---------------------------------------------------------------------------
#include "libalgo.h"

/*** 1° PARTIE : SOUS-PROGRAMMES GERANT LES CHAINES ET LES TABLEAUX DE CHAINES ****/
  
  /* Ce sous-programme crée dynamiquement une chaîne vide ayant la taille souhaitée ( + 1 pour le 0 )
   * Renvoie un pointeur sur la zone ainsi allouée */
   chaine creerchainevide ( entier taille )
   {
        char *pt ;
     
      if ( taille <= 0 )	// taille non correcte
			return NULL ;
	  pt = ( char* ) calloc ( taille + 1, sizeof ( char )) ;
	  if ( pt )
		  return pt ;
	  else
		  return NULL ;
    }

  /* Ce sous-programme crée dynamiquement une chaîne avec le texte passé en pamamètre
   * Elle a la taille du texte ( + 1 pour le 0 )
   * Renvoie un pointeur sur la zone ainsi allouée */
   chaine creerchaineinit ( chaine unechaine )
   {
		int longueur = 0 ;
		char* ptemp ;
		char* pcour = unechaine ;
		char* pt ;
		int i = 0 ;

		if ( ! unechaine )	// il n'y a pas eu de chaîne passée en paramètre
			return NULL ;

      longueur = strlen ( unechaine ) ;
      pt = ( char* ) calloc ( longueur + 1, sizeof ( char )) ;
      strcpy ( pt, unechaine ) ;


		return pt ;
   }

   /* Sous-programme libérant la mémoire d'une chaîne créée par une des fonctions creeChaine ( ) */
   void detruirechaine ( chaine unechaine )
   {
      if ( unechaine )	// il y a bien une chaîne à détruire
         free ( unechaine ) ;
   }
   
   /* Sous-programme affichant la chaine passée en paramètre. Ajoute un retour chariot si rc = true */
   /* Renvoie false si la chaîne n'est pas valide */
   booleen affichechaine ( chaine unechaine, booleen rc )
   {
      if ( unechaine ) // il y a bien une chaîne à afficher
		{
	   	printf ( "%s" , unechaine ) ;
			if ( rc )
				printf ( "\n" ) ;
			return true ;
		}
		return false ;
   }

   /* Programme vérifiant qu'une chaine est valide ( elle a une zone mémoire attribuée ) */
   booleen ischainevalide ( chaine unechaine )
   {
		return  ( unechaine ) ? true : false ;
   }

   /* Sous-programme saisissant une chaine au clavier et la stockant dans une zone mémoire de la taille adéquate
    * Renvoie la chaine ainsi créée */
   chaine saisiechaine (  )
   {
		char c = 13 ;
   		char ch [ 1000 ] ;	// tampon de saisie
   		int i = 0 ;
   		char* pt ;
   		char* ptemp ;
   		int longueur = 0 ;

  		do
   		{
			   c = getc ( stdin ) ;		// récupération synchrone d'un caractère
			   if ( c == '\n' )
				  *(ch + i ) = '\0' ;		// transformation de l'ENTER en 0 de fin de chaîne
			   else
				  *(ch + i ) = c ;
		 	    i++ ;
   		} while ( c != '\n' ) ;

   		ptemp = ch ;
   		while ( *ptemp++ )		// calcul de la longueur de la chaîne passée en paramètre
			   longueur++ ;

		   ptemp = ch ;
		   i = 0 ;
		   pt = ( char*) calloc ( longueur + 1, sizeof ( char )) ;
   		
         while ( *( pt + i ) = *ptemp++ )   // équivalent à strcpy ( ptemp,  uneChaine ) ;
			   i++ ;
   		return pt ;
   }

   /* Sous-programme saisissant une chaine au clavier et la stockant dans une zone mémoire de la taille spécifiée
    * Tronque la chaine saisie si elle a une taille supérieure à la taille spécifiée
    * Renvoie la chaine ainsi créée */
    chaine saisiechainelimitee ( entier taille )
   {
		char c = 13 ;
   		char ch [ 1000 ] ;		// Tampon de saisie
   		int i = 0 ;
   		int longueur = 0 ;
   		char* pt ;
   		char* ptemp ;

		if ( taille <= 0 )	// la taille n'est pas correcte. Si taille = 1 permet de saisir un seul caractère
			return NULL ;

  		do {
			   c = getc ( stdin ) ;		// récupération synchrone d'un caractère
			   if ( c == '\n' )			// transformation de l'ENTER en 0 de fin de chaîne
				  *(ch + i ) = '\0' ;
			   else
				  *(ch + i ) = c ;
			   i++ ;
   	} while (( c != '\n' ) && ( i <= taille )) ;

   	if ( i > taille )		// cas où il y a troncature
   		*(ch + i - 1 ) = '\0' ;

   	ptemp = ch ;
   	while ( *ptemp++ )		// calcul de la longueur de la chaîne passée en paramètre
			   longueur++ ;

		ptemp = ch ;
		i = 0 ;
		pt = ( char*) calloc ( longueur + 1, sizeof ( char )) ;
   	while ((*( pt + i ) = *ptemp++ ) && ( i < longueur ))   // équivalent à strcpy ( ) ;
			i++ ;
		*( pt + i ) = '\0' ;	// pour s'assurer que c'est une chaîne
		return pt ;
   }
   
    /* Calcul de la longueur d'une chaine
    * Equivalent à strlen ( )
	* Renvoie -1 si la chaine n'est pas valide */
   entier longueurchaine ( chaine ch )
   {
		return strlen ( ch ) ;
   }
   
   // sous programme ne renvoyant qu'un caractere
   int saisiecaractere ( )
   {
      return getchar ( ) ;
   }
   
   /*************** SOUS-PROGRAMMES DE MANIPULATION DE CHAINES COMPLETES  *********************/

   /* Sous-programme copiant le contenu d'une chaîne dans une autre
    * Il ne fait aucun contrôle sur la taille de la chaine source
    * ( en particulier elle ne vérifie pas que la zone mémoire destination est suffisante )
	*  Renvoie le nombre de caractères copiés ( -1 si erreur )*/

   chaine copiechaine ( chaine chdest, chaine chsour )
   {
	  	return strcpy ( chdest, chsour ) ;
   }

   /* Sous-programme copiant le contenu d'une chaîne dans une autre
    * Il ne copie en fait que les n premiers caractères de la chaine source
    * ( c'est à dire la chaine ou une partie de la chaine )
    * Renvoie le nombre de caractères copiés ( -1 si erreur )*/
   chaine copiechainelimitee ( chaine chdest, chaine chsour, entier taille )
   {
        return strncpy ( chdest, chsour, taille ) ;
   }

   /* Sous-programme concaténant une chaine à une autre
    * Equivalent à strcat ( )
	* Ne vérifie pas que la chDest peut contenir en plus chSour
	* Renvoie la longueur de la chaîne résultante ou -1 si erreur */
   chaine concatenechaine ( chaine chdest, chaine chsour )
   {
	  return strcat ( chdest, chsour ) ;
   }

     /* Sous-programme comparant 2 chaines entre elles
    * Renvoie 0 si les 2 chaînes sont égales, <0 si ch1 < ch2, >0 si ch1 > ch2
    * Equivalent à strcmp ( )
	* Ne fait pas de contrôle sur les chaînes passées en paramètre */
   entier comparechaine ( chaine ch1, chaine ch2 )
   {
	   return strcmp ( ch1, ch2 ) ;
   }
   
    /*************** SOUS-PROGRAMMES DE MANIPULATION DE CARACTERES  *********************/

   /* Sous-programme cherchant la première occurence d'un caractère dans une chaîne
    * Renvoie la position du caractère trouvé ( 1 pour 1° position )
	* Renvoie -1 si non trouvé et -2 si la chaine n'était pas valide */
   entier cherchecaractere ( chaine unechaine, caractere c )
   {
	    int i = 0 ;

	    if ( ! unechaine )	// uneChaine nulle
			return -2 ;

		while ( *( unechaine + i ) != '\0' )
		{
			if ( *( unechaine + i ) == c )
				return i + 1 ;
			i++ ;
		}
		return -1 ;
	}

   /* Sous-programme cherchant la première occurence d'un caractère dans une chaîne
    * à partir de la position pos passée en paramètre ( pos = 1 début de chaîne )
	* Renvoie la position du caractère trouvé.
	* Renvoie -1 si non trouvé ou si pos > taille.
	* Renvoie -2 si la chaine n'est pas valide */
	entier cherchecaracterepos ( chaine unechaine, caractere c, entier pos )
    {
		int i ;

		if ( ! unechaine ) 	// uneChaine non valide
			return -2 ;

		if (( pos > 0 ) && ( pos < longueurchaine ( unechaine )))
		{
			i = pos - 1;
			while ( *( unechaine + i ) != '\0' )
			{
				if ( *( unechaine + i ) == c )
					return i + 1 ;
				i++ ;
			}
		}
		return -1 ;
	}

   /* Sous-programme changeant le caractère situé à la position pos ( pos = 1 -> 1° caractère ) 
    * dans uneChaine par le caractère c passé en paramètre
    * Renvoie -1 si la chaîne n'est pas valide ou si pos est supérieur à la longueur de la chaine */
	entier setcaractere ( chaine unechaine, caractere c, entier pos )
	{
		int longueur ;

		if ( ! unechaine )	// chaine non valide
			return -1 ;

		longueur = longueurchaine ( unechaine ) ;

		if (( pos > 0 ) && ( pos <= longueur ))
		{
			*( unechaine + pos - 1 ) = c ;
			return pos ;
		}
		return -1 ;
	}
	
	/* Sous-programme ajoutant le caractère c à la fin de la chaine uneChaine 
	 * Renvoie null si la chaine n'est pas valide */
	chaine ajoutcaractere ( chaine unechaine, caractere c )
	{
		int longueur ;
		char* temp ;

		if ( ! unechaine )	// chaine non valide
			return NULL ;

		longueur = longueurchaine ( unechaine ) ;
		temp = ( char* ) calloc ( longueur + 2, sizeof ( char )) ;
		strcpy ( temp, unechaine ) ;
		temp [ longueur ] = c ;
		longueur++ ;
		temp [ longueur ] = '\0' ;
		free ( unechaine ) ;
	
		return temp ;
	}
	
	/* Sous-programme renyoyant le caractère situé à la position pos ( pos = 1 -> premier caractère
	 * Renvoie 0 ( = code ASCII 0 ) si la chaîne n'est pas valide ou si la position n'est pas valide */
	caractere getcaractere ( chaine unechaine, entier pos )
	{
		int longueur ;

		if ( ! unechaine )	// chaine non valide
			return 0 ;

		longueur = longueurchaine ( unechaine ) ;
		if (( pos > 0 ) && ( pos <= longueur ))
			return *( unechaine + pos - 1 ) ;		// renvoie le caractère souhaité

		return 0 ;
	}
	
	/* Sous-programme renvoyant le nombre d'occurences du caractère car dans la chaine uneChaine
	 * Renvoie -1 si la chaîne n'est pas valide */
	entier nboccurencescar ( chaine unechaine, caractere car )
	{
		int i = 0 ;
		int nb = 0 ;
		
		if ( ! unechaine )	// chaine non valide
			return -1 ;
		
		while ( *( unechaine + i )) 
		{
			if ( *( unechaine + i ) == car )
				nb++ ;
			i++ ;
		}
		return nb ;
	}
	
  /******************************* SOUS-PROGRAMMES DE GESTION DE PATTERNS **********************************/

   /* Sous-programme cherchant la position  du pattern passé en paramètre dans la chaine uneChaine
    * Renvoie la position du premier caractère du pattern ( 1 : le pattern est en première position )
	* Renvoie -1 si une des chaines n'est pas valide*/
	entier cherchepattern ( chaine unechaine, chaine pattern )
	{
		int i = 0  ;          	// déplacement par offest dans la chaîne
		int j ;    				// déplacement par offset dans la chaîne et le pattern
		int lCh = 0 ;
		int lPat = 0 ;
		char* ptemp = unechaine ;

		if (( ! unechaine )	|| ( ! pattern )) // une au moins des chaines est non valide
			return -2 ;

		while ( *ptemp++ )
			lCh++ ;
		ptemp = pattern ;
		while ( *ptemp++ )
			lPat++ ;

		if ( lPat > lCh )
			return -2 ;		// code d'erreur
		else	/* Recherche jusqu'à ce qu'on arrive à l'endroit où il n'est plus possible que le pattern existe */
		{
			while ( i  <  lCh - lPat )
			{
				if  ( *pattern == *( unechaine + i )) 	//   occurrence du 1° caractère trouvée
				{
					j = 1 ;
					while (( *( pattern + j ) ==  *( unechaine + i + j )) && ( *( pattern + j )))
				   		j++ ;
					if ( *( pattern + j ) == '\0' )  // on est sorti de la boucle parce qu'on a atteint le fin du pattern
				    	return  i + 1 ;	 // le pattern commence à la position i
			    }		// sinon chercher plus loin
				i++ ;
			}
			return -1 ;
		}
	}
	
  	/* Sous-programme remplaçant une partie de la chaine uneChaine ( à partir de la position pos ( >= 1 )) par le pattern pattern
  	 * Renvoie true si la modification a eu lieu
     * Renvoie false si elle n'a pas pu être réalisée ( uneChaine ou pattern invalide, pos < 0, pos + longueur pattern > longueur uneChaine ) */
	booleen changepattern ( chaine unechaine, chaine pattern, entier pos )
	{
		char* pCour ;
		int lch, lpat ;
		int i = 0 ;

		if (( unechaine == NULL ) || ( pattern == NULL ))
			return false ;
		else
		{
			lch = longueurchaine ( unechaine ) ;
			lpat = longueurchaine ( pattern ) ;
			if (( pos <= 0 ) || (( pos + lpat ) > lch ))
				return false ;
			else
			{
				pCour = unechaine + pos - 1 ;
				while ( i < lpat )
				{
					*( pCour + i ) = * ( pattern + i ) ;
					i++ ;
				}
				return true ;
			}
		}
	}

  	/* Sous-programme renvoyant une sous-chaine commençant au caractère d'indice debut ( i = 1 pour 1° caractère )
	 * et faisant nb caractères
     * Renvoie NULL si uneChaine est vide ou si les indices sont mauvais ( = 0 ou debut >= longueurchaine ou debut + nb > longueurchaine )
     * Sinon renvoie la sous-chaine extraite  */
	chaine extractsouschaineinterv ( chaine unechaine, entier debut, entier nb )
	{
		char* pt ;
		char* pCour ;
		int longueur ;
		int i = 0 ;
		debut-- ; // pour se remettre dans le contexte c

		if ( unechaine == NULL )
			return NULL ;
		else
		{
			longueur = longueurchaine ( unechaine ) ;
			if (( debut < 0 ) || ( nb < 0 ) || ( debut > longueur  ) || (( debut + nb ) > longueur ))
				return NULL ;
			else
			{
				pt = ( char*) calloc ( nb + 1, sizeof ( char )) ;
				pCour = unechaine + debut ;
				while ( i < nb )
				{
					*( pt + i ) = *( pCour + i ) ;
					i++ ;
				}
				*( pt + i ) = '\0' ;
				return pt ;
			}
		}
	}

	 /* Sous-programme renvoyant une sous-chaine commençant au caractère d'indice debut ( i = 1 pour 1° caractère )
	  * jusqu'à la fin de la chaîne
      * Renvoie NULL si uneChaine est vide ou si les indices sont mauvais ( = 0 ou debut >= longueurchaine )
      * Sinon renvoie la sous-chaine extraite  */
	chaine extractsouschaine ( chaine unechaine, entier debut )
	{
		char* pt ;
		char* pCour ;
		int longueur ;
		int i = 0 ;

		if ( unechaine == NULL )
			return NULL ;
		else
		{
			longueur = longueurchaine ( unechaine ) ;
			if (( debut <= 0 ) || ( debut > longueur - 1 ))
				return NULL ;
			else
			{
				pt = ( char* ) calloc ( ( longueur - debut ) + 1, sizeof ( char )) ;
				pCour = unechaine + debut - 1 ;
				while ( *( pCour + i ))
				{
					*( pt + i ) = * ( pCour + i ) ;
					i++ ;
				}
				*( pt + i ) = '\0' ;
				return pt ;
			}
		}
	}
	
	/******************************* SOUS-PROGRAMMES DE CONVERSION DE CHAINES **********************************/
	

	/* Ce sous-programme vérifie qu'une chaine est à un format numérique valide.
	 * si le parametre cas = ENTIER les formats valides sont : xxx ou +xxx ou -xxx ( nb de x variable )
	 * si le parametre cas = REEL les formats valides sont : xxx ou +xxx ou -xxx
	            ou xxx.xxx ou xxx,xxx ou +xxx.xxx ou +xxx,xxx ou -xxx.xxx ou -xxx,xxx
	 * Il doit être appelé avant toute tentative de conversion.
	 * Renvoie vrai si la chaîne est conforme
	 * Renvoie faux si le format n'est compatible ou qu'il y a trop de séparateur décimal ou si la chaine n'est pas valide */
	booleen ischainenumerique ( chaine unechaine )
	{
		char* pcour = unechaine ;
		int nbpoint = 0 ;

		if ( ! unechaine )	// chaine non valide
			return false ;

        // test du premier caractère qui doit être un digit ou '+' ou '-'
		if ((( *pcour < '0' ) || ( *pcour > '9' )) && ( *pcour != '-' ) && ( *pcour != '+' ))
			return false ;
		pcour++ ;
        // test des autres caracteres : Digit ou point décimal
		while ( *pcour )
		{
			if ((( *pcour >= '0' ) && ( *pcour <= '9')) || ( *pcour == '.' ) || ( *pcour == ',' ))
			{
            if ( *pcour == ',' )       // si c'est une virgule -->  transformation en .
               *pcour = '.' ;
            if ( *pcour == 0 ) 
               nbpoint++ ;
            pcour++ ;
         }
			else
				return false ;
		}
		if ( nbpoint > 1 )    // il ne peut y avoir qu'un délimiteur décimal
		   return false ;

      return true ;
	}


   /* Sous-programme convertissant une chaîne passée en paramètre en entier
    * Renvoie 0 si un des caractères de la chaîne n'est pas un digit ( sauf si - ou + )
    * ( Attention 0 peut aussi être une valeur valide si la chaîne représentait 0 )
	* Le sous programme ne fait aucune vérifiction sur la validité de la chaîne */
	entier chainetoentier ( chaine unechaine )
	{
		char* pt ;
		long val = 0 ;
		int i ;
		bool negatif = false ;

		trim ( unechaine ) ; // élimination des espaces en trop en tête ou en queue de chaine
		pt = unechaine ;
		if ( *pt == '-' )	// prise en compte des valeurs négatives
			negatif = true ;

		while ( *pt )
		{
			if ((( *pt >= '0' ) && ( *pt <= '9' )) || ( *pt == '-' ) || ( *pt == '+' ))
			{
				if (( *pt >= '0' ) && ( *pt <= '9' ))
				{
					i = *pt - '0' ;		// convertion d'un caractère en sa valeur numérique
					val = ( 10 * val ) + i ;	// calcul itératif de la valeur
					// 10 fois la valeur du caractère précédent + valeur du caractère
				}
				pt++ ;
			}
			else
				return 0 ;
		}

		if ( negatif )
			return -val ;	// remise en forme en cas de valeur négative
		else
			return val ;
	}

   /* Sous-programme convertissant une chaîne passée en paramètre en un double
    * Renvoie 0 si un des caractères de la chaîne n'est pas un digit ( sauf si - ou +  et , ou . )
    * ( Attention 0 peut aussi être une valeur valide si la chaîne représentait 0 )
	* Le sous programme ne fait aucune vérifiction sur la validité de la chaîne */
	reel chainetoreel ( chaine unechaine )
	{
		char* pt ;
		double val = 0.0 ;
		double decimal = 0.0 ;
		double dec = 0.1 ;
		int i ;
		bool negatif = false ;
		bool apresVirgule = false ;

		trim ( unechaine ) ;
		pt = unechaine ;

		if ( *pt == '-' )		// prise en compte d'une valeur négative
			negatif = true ;

		while (( *pt ) || ( *pt == ',' ) || ( *pt == '.' ))
		{
			if ((( *pt >= '0' ) && ( *pt <= '9' )) || ( *pt == '-' ) || ( *pt == '+' ))
			{
				if (( *pt >= '0' ) && ( *pt <= '9' ))
				{
					i = *pt - '0' ;		// convertion d'un caractère en sa valeur numérique
					if ( ! apresVirgule )  // on est avant la virgule --> comme pour chaineToEntier
						val = ( 10 * val ) + i ;
					else		// on est après la virgule
					{
						decimal = decimal + ( i * dec ) ;	// calcul itératif de la partie décimale
						dec = dec * 0.1 ;
					}
				}
			}
			else
			{
				if (( *pt == ',' ) || ( *pt == '.' ))	// on teste la virgule ou le point
					apresVirgule = true ;
				else				// caractère non valide
					return 0 ;
			}
			pt++ ;
		}

		val = val + decimal ;	// sommation des deux calculs

		if ( negatif )
			return -val ;
		else
			return val ;
	}

   /* Sous-programme convertissant un entier en chaîne */
    chaine entiertochaine ( entier entier )
	{
		char* pt ;
		int i ;
		long div = 1 ;
		int niv = 0 ;	// nombre de digit composant l'entier
		long val ;
		bool negatif = false ;

		if ( entier < 0 )
		{
			negatif = true ;
			entier = -entier ;	// passage en valeur positive pour réaliser la conversion
		}

		/* boucle permettent de savoir de combien de digit est composé l'entier
		   afin de réaliser la réservation mémoire de la chaîne adéquate */
		while ( entier / div )
		{
			niv++ ;
			div = div *	10 ;
		}
		pt = ( char* ) calloc ( niv + 2, sizeof ( char )) ;
			// allocation mémmoire pour créer la chaîne : niv + 1 pour 0 fin de chaîne + 1 pour signe éventuel

		i = niv  ;
		if ( ! negatif )	// si c'est une valeur positive revenir de 1
			i-- ;

		// Boucle permettant de décomposer la valeur par unité, dizaine, centaine, .... pour en déduire les digits composant la chaîne
		while ( i >= 0 )
		{
			val = entier % 10 ;
			*( pt + i ) = '0' +  val ;	// génération du digit adéquat
			entier = entier / 10 ;
			i-- ;
		}
		if ( negatif )
			*pt = '-' ;

		return pt ;
	}


	/* Sous-programme convertissant un nombre réel de type double en une chaîne.
	  * Le paramètre dec indique le nombre de chiffre après la virgule devant être "affiché", avec arrondi le cas échéant
	  * Le paramètre tronque à true fait que si le nombre réel a en fait une valeur entière seule la partie entière est générée */
	chaine reeltochaine ( reel nb, entier dec, booleen tronque )
	{
		char* pChaine ;
		char* pCour ;
		char* pPoint ;		// charche le '.' décimal
		bool entier = true ;
		int decimale = 0 ;

		pChaine = ( char* ) calloc ( 100, sizeof ( char )) ;
		sprintf (( char* ) pChaine, "%10.10lf", nb ) ;	// convertit la valeur en chaîne
				// 20 chiffres significatifs max dont 10 après la virgule
		pPoint = strchr (( char* ) pChaine, '.' ) ;	// recherche du point décimal

		if ( pPoint )		// S'il existe le remplacer par une virgule
			*pPoint = ',' ;

		// évaluation de la partie décimale
		pCour = pPoint + 1 ;
		while ( *pCour )
		{
			decimale++ ;		// calcul du nombre de décimale
			if ( *pCour != '0' )
				entier = false ;
			pCour++ ;
		}

		if ( tronque )	// on souhaite tronquer si la valeur est entière
			if ( entier )
				*pPoint = '\0' ;
		else
		{
			if ( decimale >= dec )	// il y a plus de décimale que voulu
			{
		   		if ( *( pPoint + dec + 1 ) >= '5' )
			    	*( pPoint + dec )+= 1 ;
		  		*(pPoint + dec + 1 ) = '\0' ;
	    	}
   		}
  		return pChaine ;
	}



	
	/******************************* SOUS-PROGRAMMES DE MISE EN FORME DE CHAINES **********************************/

	/* Sous programme  Trim ( ) de suppression des espaces non voulus
	 * Renvoie false si la chaîne n'est pas valide */
    booleen trim ( chaine unechaine )
    {
		int longueur ;
    	char* pCour = unechaine ;

    	if ( ! unechaine )	// chaine non valide
			return false ;
			
	  	/* 1° Elimination des caractères espaces en tête */
    	while ( *pCour == ' ' ) 		/* tant qu'on a un espace */
		{
			longueur = strlen ( unechaine ) ;	/* calcule la longueur de la chaîne */
			memmove ( pCour , pCour + 1 , longueur ) ; /* décalage de la fin de la chaîne */
		}

		/* 2° : Positionnement en fin de chaine */
		while ( *pCour )
			pCour++ ;

		/* 3° Elimination des caractères espaces en queue  */
		--pCour ;
		while ( *pCour  == ' ' )
		{
			*pCour = 0 ;
			pCour-- ;
		}
		return true ;
    }
    
    	/* Sous-programme convertissant les caractères majuscules de la chaîne ( et rien qu'eux ) en minuscules
	 * Renvoie false si la chaine n'est pas valide */
	booleen miseenminuscule ( chaine unechaine )
	{
		char* pt = unechaine ;

		if ( ! unechaine )	// chaine non valide
			return false ;

		while ( *pt )
		{
			if (( *pt >= 'A' ) && ( *pt <= 'Z' ))		// prise en compte des caractères minuscules normaux
				*pt = *pt + 32 ;
			pt++ ;
		}
		return true ;
	}

	/* Sous-programme convertissant les caractères minuscules de la chaîne ( et rien qu'eux ) en majuscules
	 * Renvoie false si la chaine n'est pas valide */
	booleen miseenmajuscule ( chaine unechaine )
	{
		char* pt = unechaine ;

		if ( ! unechaine )	// chaine non valide
			return false ;

		while ( *pt )
		{
			if (( *pt >= 'a' ) && ( *pt <= 'z' ))	// caractères majuscules normaux
				*pt = *pt - 32 ;
			pt++ ;
		}
		return true ;
	}
	
	
	


    
	
    /*************** SOUS-PROGRAMMES DE GESTION DE TABLEAU DE CHAINES  *********************/

   tableauchaines creertableauchaines ( entier nb )
   {
        return ( char** ) calloc ( nb, sizeof ( char* )) ;
   }

	void detruiretableauchaines ( tableauchaines tab )
	{
		int i = 0 ;

		if ( tab  )       // ne détruit le tableau .... que s'il existe
		{
 			while ( tab [ i ] )		// tant qu'il y a une chaîne
			{
				free ( tab [ i ] ) ;	// libérer sa mémoire
				i++ ;
			}
			free ( tab ) ;		// destruction du tableau
			tab = NULL ;
		}
	}
	
    
   entier nbchaines ( tableauchaines tab )
   {
        int i = 0 ;
        
        if ( ! tab )
            return -1 ;

        while ( tab [ i ] )
            i++ ;
        return i ;
   }

    // sous-programme copiant la chaine située à la position pos ( début à 0 )
	chaine duppliquerchaine ( tableauchaines tab, entier pos )
	{
		int nbCh = nbchaines ( tab ) ;

		if ( ! tab )				   // tableau de chaîne invalide
			return NULL ;
	   if (( pos < 0 ) || ( pos >= nbCh ))
			return NULL ;
      return creerchaineinit ( *( tab + pos  )) ;
	}
	
	
	bool supprimerchainetab  ( tableauchaines tabCh, int i )
	{
      int nbCh = nbchaines ( tabCh ) ;
      
      
      if (( i < 0 ) || ( i >= nbCh ))
         return false ;
      else
      {
         while  ( i < nbCh )
         {
            tabCh [ i ] = tabCh [ i + 1 ] ;
            i++ ;
         }
         return true ;
      }
   }

    // ajoute une chaine à la fin du tableau	
	booleen ajouterchaine ( tableauchaines tab, chaine ch )
	{
        int i = 0 ;
        if ( ! tab )   // tableau invalide
            return false ;
        else
        {
            while ( *( tab + i ))  // positionnement en fin de tableau 
                i++ ;  
               
            *( tab + i ) = creerchaineinit ( ch ) ;  // ajout de la chaine
            return true ;
        }
    }
    
    /* Cherche l'existence d'une chaine dans le tableau de chaines
       Renvoie la position de la chaine si trouvé( 1 = 1° chaine ), -1 si non trouvé ou si chaine non valide */
    entier chercherchaine ( tableauchaines tab, chaine ch )
    {
         int i = 0 ;
         
         if  ( ! tab ) 
            return -1 ;
         
         if ( ch )      // si la chaine est valide
         {
            while ( tab [ i ] )
            {
               if ( strcmp ( tab [ i ], ch ) == 0 )
                  return i ;
               i++ ;
            }
         }
         return -1 ;
   } 
   
     /* Cherche l'existence d'une chaine dans le tableau de chaines à partir de pos
       Renvoie la position de la chaine si trouvé( 1 = 1° chaine ), 
       -1 si non trouvé ou si chaine non valide ou pos non valide */
    entier chercherchainepos ( tableauchaines tab, chaine ch, entier pos )
    {
         int i = pos ;
         
         if ( ! tab )
            return -1 ;

         
         if (( pos < 0 ) || ( pos >= nbchaines ( tab )))
            return -1 ;
            
         if ( ch )      // si la chaine est valide
         {
            while ( tab [ i ] )
            {
               if ( strcmp ( tab [ i ], ch ) == 0 )
                  return i ;
               i++ ;
            }
         }
         return -1 ;
   }
   
   /* Sous programme transférant les chaines d'un tableau de chaines ( tabSour ) dans un tableau de chaines tabDest 
      Ce dernier peut être vide ou contenir déjà des chaines
      Il faut s'assurer que le tableau de destiantion à la capacité de contenir les chaines de tabSour */
   bool copierchaines ( tableauchaines tabDest, tableauchaines tabSour )
   {
    int nb = nbchaines ( tabSour ) ;
        
    if (( ! tabSour ) || ( ! tabDest ))
      return false ;

    for ( int i = 0 ; i < nb ; i++ )
        ajouterchaine ( tabDest, tabSour [ i ] ) ;
    
    return true ;
   }
   
   /* Sous-programme concaténant les chaines contenues dans un tableau de chaines sous forme d'une chaine unique.
      Commence la concaténation à partir de l'élément situé à pos
      ( si pos = 0 -> concatène tout le tableau de chaines )
      Si pos > nb élements du tableau renvoie null
      Rajoute un espace entre chaque chaine concaténée */
   chaine concatchaines ( tableauchaines tabch, int pos  )
   {
      int i, nb = nbchaines ( tabch ) ;
      chaine temp = creerchainevide ( 5000 ) ;
      chaine retour ;
      int longueur; 
      
      if (( !tabch ) || ( ! temp ))
         return NULL ;
      if ( pos > nb )
         return NULL ;
      
      strcpy ( temp, " " ) ;
      for ( i = pos ; i < nb ; i++ )
      {
         strcat ( temp, tabch [ i ] ) ;
         strcat ( temp, " " ) ;
      }

      trim ( temp ) ;
      longueur = strlen ( temp ) ;
      
      retour = creerchainevide ( longueur + 1 ) ;
      if ( retour )
        strcpy ( retour , temp ) ;
      detruirechaine ( temp ) ;
      return retour ;
  }
  
  
    // décompose une chaine en un tableau de chaines en fonction du séparateur passé en paramètre
    tableauchaines split ( chaine unechaine, caractere sep )
	{
		int nbSep = 0 ;	      // nombre de séparateurs contenus dans la chaine
		int i = 0 ;
		int pos = 0 ; 	      // position dans le tableau temporaire
		int longueur ;    // longueurs des différents champs de la chaîne
		char* pcour ;
		char** ptab ;	// tableau de chaînes de caractères
		char* pchaine ;	// une des chaines extraites
		char* souschaine ;
		char* temp = ( char* ) calloc ( 1000, sizeof ( char ));

		if ( unechaine == NULL )
			return NULL ;

      pcour = unechaine ;
		while ( *pcour )		// calcul du nombre de séparateurs
		{
			if ( *pcour == sep )
				nbSep++ ;
		    pcour++ ;
		}
   	// création du tableau de chaînes de caractères
		ptab = ( char** ) calloc ( nbSep + 2 , sizeof ( char* )) ;
      
      if ( ! ptab )
         	return NULL ;
		pcour = unechaine ;
		// décorticage de la chaine
		while ( i < nbSep )
		{
			pos = 0 ;
         while ( *pcour != sep )
			{
            temp [ pos ] = *pcour ;	// stockage du champ
            pos++ ;
            pcour++ ;
         }
			temp [ pos ] = '\0' ;		// constitution d'une chaîne
			longueur = strlen ( temp ) ;
			// création dynamique d'une zone mémoire pouvant contenir la chaîne
			pchaine = ( char* ) calloc ( longueur + 1, sizeof ( char )) ;
			strcpy ( pchaine, temp ) ;	// copie de la chaîne dans cette zone mémoire

			*( ptab + i ) = pchaine ;	// stockage de la chaîne dans le tableau de chaîne
			i++ ;		// case suivante du tableau de chaîne
			pcour++ ;	// saut par dessus le séparateur
  	   }
  	   
		// traitement du dernier champ
		pos = 0 ;
		while ( *pcour )	// tant qu'on n'est pas enfin de chaine
			temp [ pos++ ] = *pcour++ ;		// stockage du champ

		if ( temp [ pos - 1 ] == '\n' )		// constitution d'une chaîne
		    temp [ pos - 1 ] = 0 ;
		else
		    temp [ pos ] = 0 ;
		longueur = strlen( temp ) ;

		if ( longueur )		// il y avait bien un champ après le séparateur
		{
			// création dynamique d'une zone mémoire pouvant contenir la chaîne
			pchaine = ( char* ) calloc ( longueur + 1, sizeof ( char )) ;
			strcpy ( pchaine, temp ) ;	// copie de la chaîne dans cette zone mémoire
			*( ptab + i ) = pchaine ;	// stockage de la chaîne dans le tableau de chaînes
		}
     	//	la dernière case du tableau est à NULL ;
		return ptab ;
	}
	
	
	
/*** 2° PARTIE : SOUS-PROGRAMMES PERMETTANT D'ACCEDER A LA BIBLIOTHEQUE MATH ****/
    
    double getpi ( )
    {
       return atan( 1.0 ) * 4 ;
    }
    
    double degretoradian ( double val )
    {
        return val * getpi ( ) / 180 ;
    }
    
    double cosinus ( double val )
    {
        return cos ( val ) ;
    }
	
	double sinus ( double val )
    {
        return sin ( val ) ;
    }
    
    double tangente ( double val )
    {
        return tan ( val ) ;
    }
    
    double arccosinus ( double val )
    {
        return acos ( val ) ;
    }
	
    double arcsinus ( double val )
    {
        return asin ( val ) ;
    }
    
    double arctangente ( double val )
    {
        return atan ( val ) ;
    }
    
    double cosinushyp ( double val )
    {
        return cosh ( val ) ;
    }
    
    double sinushyp ( double val )
    {
        return sinh ( val ) ;
    }
    
    double tangentehyp ( double val )
    {
        return tanh ( val ) ;
    }
    
    double exponentielle ( double val )
    {
        return exp ( val ) ;
    }
    
    double logarithme ( double val )
    {
        return log ( val ) ;
    }
    
    double logarithme10 ( double val )
    {
        return log10 ( val ) ;
    }
    
    double puissance ( double base, double exp )
    {
        return pow ( base, exp ) ;
    }
    
    
    long factorielle ( int n )
    {
 	    long fact = 1 ;	
	    int i = 1	;	

	    if ( n < 0 )
            return -1 ; 
       
        while ( i <= n  )
	    {
            fact = fact * i ;
		    i++ ;  
        }
        return fact ;	
    }
    
    double racinecarree ( double val )
    {
        return sqrt ( val ) ;
    }
    
    double arrondisup ( double val )
    {
        return ceil ( val ) ;
    }
    
    double arrondiinf ( double val )
    {
        return floor ( val ) ;
    }
    
    double valeurabsolue ( double val )
    {
        return fabs ( val ) ;
    }
    
    double restediv ( double num, double denom ) 
    {
        return fmod ( num, denom ) ;
    }
    
     /*** 3° PARTIE : SOUS-PROGRAMMES D'ACCES AUX FICHIERS   ****/ 
    
    FILE* ouverture ( const chaine nom , chaine mode ) 
    {
        return fopen ( nom , mode ) ;
    }
    
    int fermeture ( desc descfichier ) 
    {
        return fclose ( descfichier ) ;
    }
    
    int videbuffer ( desc descfichier ) 
    {
        return fflush (  descfichier ) ;
    }
    
    int lecture ( void* buffer, int taille, int  nb, desc descfichier ) 
    {
        return  fread ( buffer, taille, nb, descfichier ) ;
    }
    
    int ecriture ( void* buffer, int taille, int nb, desc descfichier ) 
    {
        return  fwrite ( buffer, taille, nb, descfichier ) ;
    }
        
    int findefichier ( desc descfichier ) 
    {
        return feof ( descfichier ) ;
    }
    
    long deplacecurseur ( desc descfichier, long  depl, int orig )
    {
        return fseek ( descfichier, depl, orig ) ;
    } 
    
    long positioncurseur ( desc descfichier ) 
    {
        return ftell ( descfichier ) ;
    }
    
    int chargecaractere ( desc descfichier )
    {
        return fgetc (  descfichier ) ;
    }

    int ecriturecaractere ( int c, desc descfichier )
    {
        return fputc ( c , descfichier ) ;
    }
    
    chaine lectureligne ( chaine buffer, int nb, desc descfichier )
    {
        return fgets ( buffer, nb, descfichier ) ;
    }

    int ecritureligne ( chaine buffer, desc descfichier )
    {
        return fputs ( buffer , descfichier ) ;
    }

  
   /*** 4° PARTIE : SOUS-PROGRAMMES DIVERS   ****/ 

    int nombrealeatoire ( int debut, int fin )
    {
        if ( debut >= fin )
            return 0 ;
    
        // génération du nombre aléatoire compris entre debut ( inclu ) et fin ( exclu )
        return ( rand() % ( fin - debut )) + debut ;
    }
    
    /*
    void modifietailleconsole ( int nbcol, int nblig )
    {
	   char ch [ 80 ] ;

	   sprintf( ch, "mode con: cols=%d lines=%d" , nbcol, nblig ) ;
	   system( ch );
    }
    
    void effaceecran ( )
    {
	   system("CLS");
    }

    /*void pause ( ) // unistd.h :p
    {
	   printf ( "\n" ) ;
       system("PAUSE");
	   printf ( "\n" ) ;
    }*/
    
    /* Routine permettant la gestion des couleurs à l'écran */
    /*void couleur ( int couleurdutexte,int couleurdufond ) // fonction d'affichage de couleurs
    {
        HANDLE H = GetStdHandle ( STD_OUTPUT_HANDLE ) ;
        SetConsoleTextAttribute( H, couleurdufond * 16 + couleurdutexte ) ;

	   /*		0 : Noir
			    1 : Bleu foncé
			    2 : Vert foncé
			    3 : Turquoise
			    4 : Rouge foncé
			    5 : Violet
			    6 : Vert kaki
			    7 : Gris clair
			    8 : Gris foncé
			    9 : Bleu fluo
			    10 : Vert fluo
			    11 : Turquoise
			    12 : Rouge 
			    13 : Rose
			    14 : Jaune
			    15 : Blanc 			*/
    //}
    
    void generateurnbaleatoire ( )       // initialisation du générateur de nombre aléatoire 
    {
        srand ( time( NULL )) ; 
    }
    
