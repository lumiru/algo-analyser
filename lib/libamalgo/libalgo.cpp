//---------------------------------------------------------------------------
//
// Name:  Biblioth�que de gestion de cha�nes et divers autres fonctionnalit�s pour 
// �tre utilis�e conjointement avec l'analyseur d'algorithmes.
// Author:  MILONE Alain
// Created: Septembre 2011
// Description: Biblioth�que simplifiant la gestion des cha�nes en C++
// en supprimant toute r�f�rence � un pointeur
//
//---------------------------------------------------------------------------
#include "libalgo.h"

/*** 1� PARTIE : SOUS-PROGRAMMES GERANT LES CHAINES ET LES TABLEAUX DE CHAINES ****/
  
  /* Ce sous-programme cr�e dynamiquement une cha�ne vide ayant la taille souhait�e ( + 1 pour le 0 )
   * Renvoie un pointeur sur la zone ainsi allou�e */
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

  /* Ce sous-programme cr�e dynamiquement une cha�ne avec le texte pass� en pamam�tre
   * Elle a la taille du texte ( + 1 pour le 0 )
   * Renvoie un pointeur sur la zone ainsi allou�e */
   chaine creerchaineinit ( chaine unechaine )
   {
		int longueur = 0 ;
		char* ptemp ;
		char* pcour = unechaine ;
		char* pt ;
		int i = 0 ;

		if ( ! unechaine )	// il n'y a pas eu de cha�ne pass�e en param�tre
			return NULL ;

      longueur = strlen ( unechaine ) ;
      pt = ( char* ) calloc ( longueur + 1, sizeof ( char )) ;
      strcpy ( pt, unechaine ) ;


		return pt ;
   }

   /* Sous-programme lib�rant la m�moire d'une cha�ne cr��e par une des fonctions creeChaine ( ) */
   void detruirechaine ( chaine unechaine )
   {
      if ( unechaine )	// il y a bien une cha�ne � d�truire
         free ( unechaine ) ;
   }
   
   /* Sous-programme affichant la chaine pass�e en param�tre. Ajoute un retour chariot si rc = true */
   /* Renvoie false si la cha�ne n'est pas valide */
   booleen affichechaine ( chaine unechaine, booleen rc )
   {
      if ( unechaine ) // il y a bien une cha�ne � afficher
		{
	   	printf ( "%s" , unechaine ) ;
			if ( rc )
				printf ( "\n" ) ;
			return true ;
		}
		return false ;
   }

   /* Programme v�rifiant qu'une chaine est valide ( elle a une zone m�moire attribu�e ) */
   booleen ischainevalide ( chaine unechaine )
   {
		return  ( unechaine ) ? true : false ;
   }

   /* Sous-programme saisissant une chaine au clavier et la stockant dans une zone m�moire de la taille ad�quate
    * Renvoie la chaine ainsi cr��e */
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
			   c = getc ( stdin ) ;		// r�cup�ration synchrone d'un caract�re
			   if ( c == '\n' )
				  *(ch + i ) = '\0' ;		// transformation de l'ENTER en 0 de fin de cha�ne
			   else
				  *(ch + i ) = c ;
		 	    i++ ;
   		} while ( c != '\n' ) ;

   		ptemp = ch ;
   		while ( *ptemp++ )		// calcul de la longueur de la cha�ne pass�e en param�tre
			   longueur++ ;

		   ptemp = ch ;
		   i = 0 ;
		   pt = ( char*) calloc ( longueur + 1, sizeof ( char )) ;
   		
         while ( *( pt + i ) = *ptemp++ )   // �quivalent � strcpy ( ptemp,  uneChaine ) ;
			   i++ ;
   		return pt ;
   }

   /* Sous-programme saisissant une chaine au clavier et la stockant dans une zone m�moire de la taille sp�cifi�e
    * Tronque la chaine saisie si elle a une taille sup�rieure � la taille sp�cifi�e
    * Renvoie la chaine ainsi cr��e */
    chaine saisiechainelimitee ( entier taille )
   {
		char c = 13 ;
   		char ch [ 1000 ] ;		// Tampon de saisie
   		int i = 0 ;
   		int longueur = 0 ;
   		char* pt ;
   		char* ptemp ;

		if ( taille <= 0 )	// la taille n'est pas correcte. Si taille = 1 permet de saisir un seul caract�re
			return NULL ;

  		do {
			   c = getc ( stdin ) ;		// r�cup�ration synchrone d'un caract�re
			   if ( c == '\n' )			// transformation de l'ENTER en 0 de fin de cha�ne
				  *(ch + i ) = '\0' ;
			   else
				  *(ch + i ) = c ;
			   i++ ;
   	} while (( c != '\n' ) && ( i <= taille )) ;

   	if ( i > taille )		// cas o� il y a troncature
   		*(ch + i - 1 ) = '\0' ;

   	ptemp = ch ;
   	while ( *ptemp++ )		// calcul de la longueur de la cha�ne pass�e en param�tre
			   longueur++ ;

		ptemp = ch ;
		i = 0 ;
		pt = ( char*) calloc ( longueur + 1, sizeof ( char )) ;
   	while ((*( pt + i ) = *ptemp++ ) && ( i < longueur ))   // �quivalent � strcpy ( ) ;
			i++ ;
		*( pt + i ) = '\0' ;	// pour s'assurer que c'est une cha�ne
		return pt ;
   }
   
    /* Calcul de la longueur d'une chaine
    * Equivalent � strlen ( )
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

   /* Sous-programme copiant le contenu d'une cha�ne dans une autre
    * Il ne fait aucun contr�le sur la taille de la chaine source
    * ( en particulier elle ne v�rifie pas que la zone m�moire destination est suffisante )
	*  Renvoie le nombre de caract�res copi�s ( -1 si erreur )*/

   chaine copiechaine ( chaine chdest, chaine chsour )
   {
	  	return strcpy ( chdest, chsour ) ;
   }

   /* Sous-programme copiant le contenu d'une cha�ne dans une autre
    * Il ne copie en fait que les n premiers caract�res de la chaine source
    * ( c'est � dire la chaine ou une partie de la chaine )
    * Renvoie le nombre de caract�res copi�s ( -1 si erreur )*/
   chaine copiechainelimitee ( chaine chdest, chaine chsour, entier taille )
   {
        return strncpy ( chdest, chsour, taille ) ;
   }

   /* Sous-programme concat�nant une chaine � une autre
    * Equivalent � strcat ( )
	* Ne v�rifie pas que la chDest peut contenir en plus chSour
	* Renvoie la longueur de la cha�ne r�sultante ou -1 si erreur */
   chaine concatenechaine ( chaine chdest, chaine chsour )
   {
	  return strcat ( chdest, chsour ) ;
   }

     /* Sous-programme comparant 2 chaines entre elles
    * Renvoie 0 si les 2 cha�nes sont �gales, <0 si ch1 < ch2, >0 si ch1 > ch2
    * Equivalent � strcmp ( )
	* Ne fait pas de contr�le sur les cha�nes pass�es en param�tre */
   entier comparechaine ( chaine ch1, chaine ch2 )
   {
	   return strcmp ( ch1, ch2 ) ;
   }
   
    /*************** SOUS-PROGRAMMES DE MANIPULATION DE CARACTERES  *********************/

   /* Sous-programme cherchant la premi�re occurence d'un caract�re dans une cha�ne
    * Renvoie la position du caract�re trouv� ( 1 pour 1� position )
	* Renvoie -1 si non trouv� et -2 si la chaine n'�tait pas valide */
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

   /* Sous-programme cherchant la premi�re occurence d'un caract�re dans une cha�ne
    * � partir de la position pos pass�e en param�tre ( pos = 1 d�but de cha�ne )
	* Renvoie la position du caract�re trouv�.
	* Renvoie -1 si non trouv� ou si pos > taille.
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

   /* Sous-programme changeant le caract�re situ� � la position pos ( pos = 1 -> 1� caract�re ) 
    * dans uneChaine par le caract�re c pass� en param�tre
    * Renvoie -1 si la cha�ne n'est pas valide ou si pos est sup�rieur � la longueur de la chaine */
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
	
	/* Sous-programme ajoutant le caract�re c � la fin de la chaine uneChaine 
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
	
	/* Sous-programme renyoyant le caract�re situ� � la position pos ( pos = 1 -> premier caract�re
	 * Renvoie 0 ( = code ASCII 0 ) si la cha�ne n'est pas valide ou si la position n'est pas valide */
	caractere getcaractere ( chaine unechaine, entier pos )
	{
		int longueur ;

		if ( ! unechaine )	// chaine non valide
			return 0 ;

		longueur = longueurchaine ( unechaine ) ;
		if (( pos > 0 ) && ( pos <= longueur ))
			return *( unechaine + pos - 1 ) ;		// renvoie le caract�re souhait�

		return 0 ;
	}
	
	/* Sous-programme renvoyant le nombre d'occurences du caract�re car dans la chaine uneChaine
	 * Renvoie -1 si la cha�ne n'est pas valide */
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

   /* Sous-programme cherchant la position  du pattern pass� en param�tre dans la chaine uneChaine
    * Renvoie la position du premier caract�re du pattern ( 1 : le pattern est en premi�re position )
	* Renvoie -1 si une des chaines n'est pas valide*/
	entier cherchepattern ( chaine unechaine, chaine pattern )
	{
		int i = 0  ;          	// d�placement par offest dans la cha�ne
		int j ;    				// d�placement par offset dans la cha�ne et le pattern
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
		else	/* Recherche jusqu'� ce qu'on arrive � l'endroit o� il n'est plus possible que le pattern existe */
		{
			while ( i  <  lCh - lPat )
			{
				if  ( *pattern == *( unechaine + i )) 	//   occurrence du 1� caract�re trouv�e
				{
					j = 1 ;
					while (( *( pattern + j ) ==  *( unechaine + i + j )) && ( *( pattern + j )))
				   		j++ ;
					if ( *( pattern + j ) == '\0' )  // on est sorti de la boucle parce qu'on a atteint le fin du pattern
				    	return  i + 1 ;	 // le pattern commence � la position i
			    }		// sinon chercher plus loin
				i++ ;
			}
			return -1 ;
		}
	}
	
  	/* Sous-programme rempla�ant une partie de la chaine uneChaine ( � partir de la position pos ( >= 1 )) par le pattern pattern
  	 * Renvoie true si la modification a eu lieu
     * Renvoie false si elle n'a pas pu �tre r�alis�e ( uneChaine ou pattern invalide, pos < 0, pos + longueur pattern > longueur uneChaine ) */
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

  	/* Sous-programme renvoyant une sous-chaine commen�ant au caract�re d'indice debut ( i = 1 pour 1� caract�re )
	 * et faisant nb caract�res
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

	 /* Sous-programme renvoyant une sous-chaine commen�ant au caract�re d'indice debut ( i = 1 pour 1� caract�re )
	  * jusqu'� la fin de la cha�ne
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
	

	/* Ce sous-programme v�rifie qu'une chaine est � un format num�rique valide.
	 * si le parametre cas = ENTIER les formats valides sont : xxx ou +xxx ou -xxx ( nb de x variable )
	 * si le parametre cas = REEL les formats valides sont : xxx ou +xxx ou -xxx
	            ou xxx.xxx ou xxx,xxx ou +xxx.xxx ou +xxx,xxx ou -xxx.xxx ou -xxx,xxx
	 * Il doit �tre appel� avant toute tentative de conversion.
	 * Renvoie vrai si la cha�ne est conforme
	 * Renvoie faux si le format n'est compatible ou qu'il y a trop de s�parateur d�cimal ou si la chaine n'est pas valide */
	booleen ischainenumerique ( chaine unechaine )
	{
		char* pcour = unechaine ;
		int nbpoint = 0 ;

		if ( ! unechaine )	// chaine non valide
			return false ;

        // test du premier caract�re qui doit �tre un digit ou '+' ou '-'
		if ((( *pcour < '0' ) || ( *pcour > '9' )) && ( *pcour != '-' ) && ( *pcour != '+' ))
			return false ;
		pcour++ ;
        // test des autres caracteres : Digit ou point d�cimal
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
		if ( nbpoint > 1 )    // il ne peut y avoir qu'un d�limiteur d�cimal
		   return false ;

      return true ;
	}


   /* Sous-programme convertissant une cha�ne pass�e en param�tre en entier
    * Renvoie 0 si un des caract�res de la cha�ne n'est pas un digit ( sauf si - ou + )
    * ( Attention 0 peut aussi �tre une valeur valide si la cha�ne repr�sentait 0 )
	* Le sous programme ne fait aucune v�rifiction sur la validit� de la cha�ne */
	entier chainetoentier ( chaine unechaine )
	{
		char* pt ;
		long val = 0 ;
		int i ;
		bool negatif = false ;

		trim ( unechaine ) ; // �limination des espaces en trop en t�te ou en queue de chaine
		pt = unechaine ;
		if ( *pt == '-' )	// prise en compte des valeurs n�gatives
			negatif = true ;

		while ( *pt )
		{
			if ((( *pt >= '0' ) && ( *pt <= '9' )) || ( *pt == '-' ) || ( *pt == '+' ))
			{
				if (( *pt >= '0' ) && ( *pt <= '9' ))
				{
					i = *pt - '0' ;		// convertion d'un caract�re en sa valeur num�rique
					val = ( 10 * val ) + i ;	// calcul it�ratif de la valeur
					// 10 fois la valeur du caract�re pr�c�dent + valeur du caract�re
				}
				pt++ ;
			}
			else
				return 0 ;
		}

		if ( negatif )
			return -val ;	// remise en forme en cas de valeur n�gative
		else
			return val ;
	}

   /* Sous-programme convertissant une cha�ne pass�e en param�tre en un double
    * Renvoie 0 si un des caract�res de la cha�ne n'est pas un digit ( sauf si - ou +  et , ou . )
    * ( Attention 0 peut aussi �tre une valeur valide si la cha�ne repr�sentait 0 )
	* Le sous programme ne fait aucune v�rifiction sur la validit� de la cha�ne */
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

		if ( *pt == '-' )		// prise en compte d'une valeur n�gative
			negatif = true ;

		while (( *pt ) || ( *pt == ',' ) || ( *pt == '.' ))
		{
			if ((( *pt >= '0' ) && ( *pt <= '9' )) || ( *pt == '-' ) || ( *pt == '+' ))
			{
				if (( *pt >= '0' ) && ( *pt <= '9' ))
				{
					i = *pt - '0' ;		// convertion d'un caract�re en sa valeur num�rique
					if ( ! apresVirgule )  // on est avant la virgule --> comme pour chaineToEntier
						val = ( 10 * val ) + i ;
					else		// on est apr�s la virgule
					{
						decimal = decimal + ( i * dec ) ;	// calcul it�ratif de la partie d�cimale
						dec = dec * 0.1 ;
					}
				}
			}
			else
			{
				if (( *pt == ',' ) || ( *pt == '.' ))	// on teste la virgule ou le point
					apresVirgule = true ;
				else				// caract�re non valide
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

   /* Sous-programme convertissant un entier en cha�ne */
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
			entier = -entier ;	// passage en valeur positive pour r�aliser la conversion
		}

		/* boucle permettent de savoir de combien de digit est compos� l'entier
		   afin de r�aliser la r�servation m�moire de la cha�ne ad�quate */
		while ( entier / div )
		{
			niv++ ;
			div = div *	10 ;
		}
		pt = ( char* ) calloc ( niv + 2, sizeof ( char )) ;
			// allocation m�mmoire pour cr�er la cha�ne : niv + 1 pour 0 fin de cha�ne + 1 pour signe �ventuel

		i = niv  ;
		if ( ! negatif )	// si c'est une valeur positive revenir de 1
			i-- ;

		// Boucle permettant de d�composer la valeur par unit�, dizaine, centaine, .... pour en d�duire les digits composant la cha�ne
		while ( i >= 0 )
		{
			val = entier % 10 ;
			*( pt + i ) = '0' +  val ;	// g�n�ration du digit ad�quat
			entier = entier / 10 ;
			i-- ;
		}
		if ( negatif )
			*pt = '-' ;

		return pt ;
	}


	/* Sous-programme convertissant un nombre r�el de type double en une cha�ne.
	  * Le param�tre dec indique le nombre de chiffre apr�s la virgule devant �tre "affich�", avec arrondi le cas �ch�ant
	  * Le param�tre tronque � true fait que si le nombre r�el a en fait une valeur enti�re seule la partie enti�re est g�n�r�e */
	chaine reeltochaine ( reel nb, entier dec, booleen tronque )
	{
		char* pChaine ;
		char* pCour ;
		char* pPoint ;		// charche le '.' d�cimal
		bool entier = true ;
		int decimale = 0 ;

		pChaine = ( char* ) calloc ( 100, sizeof ( char )) ;
		sprintf (( char* ) pChaine, "%10.10lf", nb ) ;	// convertit la valeur en cha�ne
				// 20 chiffres significatifs max dont 10 apr�s la virgule
		pPoint = strchr (( char* ) pChaine, '.' ) ;	// recherche du point d�cimal

		if ( pPoint )		// S'il existe le remplacer par une virgule
			*pPoint = ',' ;

		// �valuation de la partie d�cimale
		pCour = pPoint + 1 ;
		while ( *pCour )
		{
			decimale++ ;		// calcul du nombre de d�cimale
			if ( *pCour != '0' )
				entier = false ;
			pCour++ ;
		}

		if ( tronque )	// on souhaite tronquer si la valeur est enti�re
			if ( entier )
				*pPoint = '\0' ;
		else
		{
			if ( decimale >= dec )	// il y a plus de d�cimale que voulu
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
	 * Renvoie false si la cha�ne n'est pas valide */
    booleen trim ( chaine unechaine )
    {
		int longueur ;
    	char* pCour = unechaine ;

    	if ( ! unechaine )	// chaine non valide
			return false ;
			
	  	/* 1� Elimination des caract�res espaces en t�te */
    	while ( *pCour == ' ' ) 		/* tant qu'on a un espace */
		{
			longueur = strlen ( unechaine ) ;	/* calcule la longueur de la cha�ne */
			memmove ( pCour , pCour + 1 , longueur ) ; /* d�calage de la fin de la cha�ne */
		}

		/* 2� : Positionnement en fin de chaine */
		while ( *pCour )
			pCour++ ;

		/* 3� Elimination des caract�res espaces en queue  */
		--pCour ;
		while ( *pCour  == ' ' )
		{
			*pCour = 0 ;
			pCour-- ;
		}
		return true ;
    }
    
    	/* Sous-programme convertissant les caract�res majuscules de la cha�ne ( et rien qu'eux ) en minuscules
	 * Renvoie false si la chaine n'est pas valide */
	booleen miseenminuscule ( chaine unechaine )
	{
		char* pt = unechaine ;

		if ( ! unechaine )	// chaine non valide
			return false ;

		while ( *pt )
		{
			if (( *pt >= 'A' ) && ( *pt <= 'Z' ))		// prise en compte des caract�res minuscules normaux
				*pt = *pt + 32 ;
			pt++ ;
		}
		return true ;
	}

	/* Sous-programme convertissant les caract�res minuscules de la cha�ne ( et rien qu'eux ) en majuscules
	 * Renvoie false si la chaine n'est pas valide */
	booleen miseenmajuscule ( chaine unechaine )
	{
		char* pt = unechaine ;

		if ( ! unechaine )	// chaine non valide
			return false ;

		while ( *pt )
		{
			if (( *pt >= 'a' ) && ( *pt <= 'z' ))	// caract�res majuscules normaux
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

		if ( tab  )       // ne d�truit le tableau .... que s'il existe
		{
 			while ( tab [ i ] )		// tant qu'il y a une cha�ne
			{
				free ( tab [ i ] ) ;	// lib�rer sa m�moire
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

    // sous-programme copiant la chaine situ�e � la position pos ( d�but � 0 )
	chaine duppliquerchaine ( tableauchaines tab, entier pos )
	{
		int nbCh = nbchaines ( tab ) ;

		if ( ! tab )				   // tableau de cha�ne invalide
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

    // ajoute une chaine � la fin du tableau	
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
       Renvoie la position de la chaine si trouv�( 1 = 1� chaine ), -1 si non trouv� ou si chaine non valide */
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
   
     /* Cherche l'existence d'une chaine dans le tableau de chaines � partir de pos
       Renvoie la position de la chaine si trouv�( 1 = 1� chaine ), 
       -1 si non trouv� ou si chaine non valide ou pos non valide */
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
   
   /* Sous programme transf�rant les chaines d'un tableau de chaines ( tabSour ) dans un tableau de chaines tabDest 
      Ce dernier peut �tre vide ou contenir d�j� des chaines
      Il faut s'assurer que le tableau de destiantion � la capacit� de contenir les chaines de tabSour */
   bool copierchaines ( tableauchaines tabDest, tableauchaines tabSour )
   {
    int nb = nbchaines ( tabSour ) ;
        
    if (( ! tabSour ) || ( ! tabDest ))
      return false ;

    for ( int i = 0 ; i < nb ; i++ )
        ajouterchaine ( tabDest, tabSour [ i ] ) ;
    
    return true ;
   }
   
   /* Sous-programme concat�nant les chaines contenues dans un tableau de chaines sous forme d'une chaine unique.
      Commence la concat�nation � partir de l'�l�ment situ� � pos
      ( si pos = 0 -> concat�ne tout le tableau de chaines )
      Si pos > nb �lements du tableau renvoie null
      Rajoute un espace entre chaque chaine concat�n�e */
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
  
  
    // d�compose une chaine en un tableau de chaines en fonction du s�parateur pass� en param�tre
    tableauchaines split ( chaine unechaine, caractere sep )
	{
		int nbSep = 0 ;	      // nombre de s�parateurs contenus dans la chaine
		int i = 0 ;
		int pos = 0 ; 	      // position dans le tableau temporaire
		int longueur ;    // longueurs des diff�rents champs de la cha�ne
		char* pcour ;
		char** ptab ;	// tableau de cha�nes de caract�res
		char* pchaine ;	// une des chaines extraites
		char* souschaine ;
		char* temp = ( char* ) calloc ( 1000, sizeof ( char ));

		if ( unechaine == NULL )
			return NULL ;

      pcour = unechaine ;
		while ( *pcour )		// calcul du nombre de s�parateurs
		{
			if ( *pcour == sep )
				nbSep++ ;
		    pcour++ ;
		}
   	// cr�ation du tableau de cha�nes de caract�res
		ptab = ( char** ) calloc ( nbSep + 2 , sizeof ( char* )) ;
      
      if ( ! ptab )
         	return NULL ;
		pcour = unechaine ;
		// d�corticage de la chaine
		while ( i < nbSep )
		{
			pos = 0 ;
         while ( *pcour != sep )
			{
            temp [ pos ] = *pcour ;	// stockage du champ
            pos++ ;
            pcour++ ;
         }
			temp [ pos ] = '\0' ;		// constitution d'une cha�ne
			longueur = strlen ( temp ) ;
			// cr�ation dynamique d'une zone m�moire pouvant contenir la cha�ne
			pchaine = ( char* ) calloc ( longueur + 1, sizeof ( char )) ;
			strcpy ( pchaine, temp ) ;	// copie de la cha�ne dans cette zone m�moire

			*( ptab + i ) = pchaine ;	// stockage de la cha�ne dans le tableau de cha�ne
			i++ ;		// case suivante du tableau de cha�ne
			pcour++ ;	// saut par dessus le s�parateur
  	   }
  	   
		// traitement du dernier champ
		pos = 0 ;
		while ( *pcour )	// tant qu'on n'est pas enfin de chaine
			temp [ pos++ ] = *pcour++ ;		// stockage du champ

		if ( temp [ pos - 1 ] == '\n' )		// constitution d'une cha�ne
		    temp [ pos - 1 ] = 0 ;
		else
		    temp [ pos ] = 0 ;
		longueur = strlen( temp ) ;

		if ( longueur )		// il y avait bien un champ apr�s le s�parateur
		{
			// cr�ation dynamique d'une zone m�moire pouvant contenir la cha�ne
			pchaine = ( char* ) calloc ( longueur + 1, sizeof ( char )) ;
			strcpy ( pchaine, temp ) ;	// copie de la cha�ne dans cette zone m�moire
			*( ptab + i ) = pchaine ;	// stockage de la cha�ne dans le tableau de cha�nes
		}
     	//	la derni�re case du tableau est � NULL ;
		return ptab ;
	}
	
	
	
/*** 2� PARTIE : SOUS-PROGRAMMES PERMETTANT D'ACCEDER A LA BIBLIOTHEQUE MATH ****/
    
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
    
     /*** 3� PARTIE : SOUS-PROGRAMMES D'ACCES AUX FICHIERS   ****/ 
    
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

  
   /*** 4� PARTIE : SOUS-PROGRAMMES DIVERS   ****/ 

    int nombrealeatoire ( int debut, int fin )
    {
        if ( debut >= fin )
            return 0 ;
    
        // g�n�ration du nombre al�atoire compris entre debut ( inclu ) et fin ( exclu )
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
    
    /* Routine permettant la gestion des couleurs � l'�cran */
    /*void couleur ( int couleurdutexte,int couleurdufond ) // fonction d'affichage de couleurs
    {
        HANDLE H = GetStdHandle ( STD_OUTPUT_HANDLE ) ;
        SetConsoleTextAttribute( H, couleurdufond * 16 + couleurdutexte ) ;

	   /*		0 : Noir
			    1 : Bleu fonc�
			    2 : Vert fonc�
			    3 : Turquoise
			    4 : Rouge fonc�
			    5 : Violet
			    6 : Vert kaki
			    7 : Gris clair
			    8 : Gris fonc�
			    9 : Bleu fluo
			    10 : Vert fluo
			    11 : Turquoise
			    12 : Rouge 
			    13 : Rose
			    14 : Jaune
			    15 : Blanc 			*/
    //}
    
    void generateurnbaleatoire ( )       // initialisation du g�n�rateur de nombre al�atoire 
    {
        srand ( time( NULL )) ; 
    }
    
