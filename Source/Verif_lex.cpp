/*
#include <iostream>
#include <string>
#include <list>
#include "utilities.cpp"  // fichier contenant les fonctions is_number, is_letter, is_ponctuation, is_ponctuation2char
#include "Lexeme.h"
*/

#include "../Header/Verification_orthographe_ajout_etiquette.h"

using namespace std ; 


bool verif(Lexeme& l, bool *com, int *ligne_com) {  
	string a = l.getLex() ;
	int i =0 ; 
	bool erreur = false ;
if (*com == true && *ligne_com == l.getLigne()){ 	// ici on est dans le cas ou on a eu la ponctuation commentaire, si on est toujours sur la 
	l.isCommentaire() ; 				//meme ligne que ce dernier on place le lexeme en commentaire et on ne fait rien d'autre
	return erreur ; 
}
else {							// SInon on teste le lexeme pour vÃ©rifier l'orthographe et mettre la bonne etiquette 
	*com = false ;
	if (is_letter(a[0])){
		l.isMot() ;
		i++;
		while (a[i]!='\0'){
			if (is_letter(a[0])||is_number(a[0])||a[i]=='_'){}
			else { cout << "ERREUR ligne " << l.getLigne() << ": Un mot commencant par une lettre peut contenir seulement des lettres, des chiffres ou un underscore" << endl ; 
			erreur = true ; 
			}
			i++ ; 
		}
		if (a[i-1]=='_'){
		cout << "ERREUR ligne " << l.getLigne() << " : un mot commencant par une lettre ne peut pas se terminer par le caractere '_'" << endl ; 
		//cout numero de la ligne du lexÃ¨me
		erreur = true ; 
		}
	}
	else if (is_number(a[0])){
		l.isNombre() ; 
		i++ ; 
		while (a[i]!='\0'){
			if(is_number(a[i])){}
			else {
				cout << "ERREUR ligne " << l.getLigne() << ": Un mot commencant par un chiffre peut contenir seulement des chiffres" << endl ; 
				//cout numero de la ligne du lexÃ¨me 
			 	erreur = true ; 
			}
			i=i++ ; 
		}
	}
	else if (is_ponctuation(a[0])){
		if (a[1]=='\0'){
			l.isPonctuation() ; 
		}
		else if (is_ponctuation(a[1])){
			if(is_ponctuation2char(a[0],a[1])){
				if (a[0]=='-'&&a[0]=='-'){
					l.isCommentaire() ;
					*ligne_com = l.getLigne() ;  
					*com = true ;
				}
				else {
					l.isPonctuation() ;
				}
			}
			else {
				cout << "ERREUR ligne " << l.getLigne() << ": La double ponctuation n'existe pas" << endl ; 
				//cout numero de la ligne 
				erreur = true ; 
			}
			if(a[2]!='\0'){
			cout << "ERREUR ligne " << l.getLigne() << " : On ne peut pas avoir plus de 2 ponctuations Ã  la suite" << endl ;
			// + n ligne
			erreur = true ; 
			} 
		}
		else {
			cout << "ERREUR ligne " << l.getLigne() << " : On ne peut pas avoir d'autres caractÃ¨res qu'une ponctuation aprÃ¨s une ponctuation" << endl ; 
			// + n ligne 
			erreur = true ; 
		}

	}
}
	return erreur ; 
}

/*
list<Lexeme *>::iterator itr
bool com = FALSE ;
for(itr = l.begin() ; itr != l.end() ; ++itr) 
{
	Lexemes* a=*itr ;
	
}*/
