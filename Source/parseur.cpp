#include <iostream>
#include <string>
#include <list>
#include "Header/utilities.h"
#include "Header/Lexeme.h"
#include "Header/parseur.h"

using namespace std;

// On retourne "0" s'il y a une erreur et "1" quand il n'y a pas d'erreur

// ********************************ENTITY********************************************************************
int parseur_entity (list<Lexeme*>::iterator itr){
	itr++ ; 
	if ((*itr)->getType() == MOT) {
		string identifiant = (*itr)->getLex() ;
		itr++; 
		if ((*itr)->getLex() == "is"){
			itr++; 
			if ((*itr)->getLex() == "port"){
				if (parseur_port(itr)== 0) {
					return 0 ; 		// indique que l'on a une erreur
				} // if (parseur_port(i)= 0) {
				else {
					itr++;
					if ((*itr)->getLex() == "end"){
						itr++;
						if ((*itr)->getLex() == identifiant){
							return 1; 
						} // if (lexeme = identifiant){
						else {
							cout << "ERREUR ligne " << (*itr)->getLigne() << ": l'identifiant est mal orthographié" << endl ;
						} //else
					} //if (lexeme = 'end')
				} // else
			} // if (lexeme = 'port')
		} // if ((*itr)->getLex() = 'is')
	} // if ((*itr)->getType() = mot) 
	return 0 ; 
} // parseur_entity 



// *****************************************************PORT**********************************************************
int parseur_port (list<Lexeme*>::iterator itr) {
	bool fin_port = false ;  // bool qui nous permet de gérer le dernier port 
	itr++;
	if ((*itr)->getLex()== "("){
		itr++;
		while ((*itr)->getType() == MOT && fin_port == false) {
			itr++;
			while ((*itr)->getLex() != ":") {
				if ((*itr)->getLex()== ",") {
					itr++;
					if ((*itr)->getType() == MOT) {
						itr++;
					} //if ((*itr)->getType() == MOT)
				} //if ((*itr)->getLex()== ",") 
			} //while ((*itr)->getLex() != ':') 
			itr++ ; 
			if ((*itr)->getLex()== "in"){
				if (parseur_type_port(itr, &fin_port) == 0) {
					return 0 ;
				}
			} // if ((*itr)->getLex()== "in")
			else if ((*itr)->getLex()== "out"){
				if (parseur_type_port(itr, &fin_port) == 0) {
					return 0 ;
				}
			} // else if 
			else if ((*itr)->getLex()== "inout"){ 
				if (parseur_type_port(itr, &fin_port) == 0) {
					return 0 ;
				}
			} // else if 
			else {
				return 0 ; 
			} // else
		} // while
	} // if ((*itr)->getLex()== "(")

} // parseur_port





//**************************************************************TYPE PORT*************************************************************
int parseur_type_port (list<Lexeme*>::iterator itr, bool *fin_port) {
	itr++;
	if type { // A COMPLETER
		itr++ ; 
		if ((*itr)->getLex()== ";") {
			return 1 ;
		}
		else if ((*itr)->getLex()== ")") {
			itr++;
			*fin_port = true ;
			if ((*itr)->getLex()== ";") {
			return 1 ;
			}
		}
		else {
			return 0 ; 
		}
	}


} // parseur type_port 











//******************************************************LIBRARY*************************************************************************

int parseur_library (list<Lexeme*>::iterator itr){
	itr++ ; 
	if ((*itr)->getType() == MOT) {
		string library = (*itr)->getLex() ;
		itr++; 
		if ((*itr)->getLex() == ";"){
			itr++ ; 
			while ((*itr)->getLex() == "use"){
				if (parseur_library(*itr, *library)==0){
					return 0 ; 
				} //if (parseur_library(*itr)==0){
			} //while
			return 1 ;
		} //if ((*itr)->getLex() == ";"){
	} //if ((*itr)->getType() == MOT) {
	return 0 ; 
} //parseur_library 



//****************************************************USE*******************************************************************************


int parseur_use (list<Lexeme*>::iterator itr, string library){
	itr++ ; 
	if ((*itr)->getLex() == library) {
		itr ++;
		if ((*itr)->getLex() == ".") {
			itr++;
			if ((*itr)->getType() == MOT) {
				string name = itr->getLex() ; 
				itr++ ;
				if ((*itr)->getLex() == ".") {
					itr++;
					// a compléter lexeme all ou autres 
					
				}
			}
		}
	}
	return 0;
}

//**************************************************ARCHITECTURE************************************************************************

int parseur_architecture (list<Lexeme*>::iterator itr){
	itr++ ; 
	if ((*itr)->getType() == MOT) {
		string identifiant = (*itr)->getLex() ;
		itr++;
		if ((*itr)->getLex() == "of"){
			i++ ; 
			if (){ // vérifier que l'entité existe 
				i++;
				if ((*itr)->getLex() == "is"){
					i++ ;
					if ((*itr)->getLex() == "signal"){
						if (parseur_signal(itr)== 0) {
							return 0 ; 		// indique que l'on a une erreur
						}
					}
					else if ((*itr)->getLex() == "component"){
						if (parseur_component(itr)== 0) {
						return 0 ; 		// indique que l'on a une erreur
						}
					}
					if ((*itr)->getLex() == "begin"){
						i++ ;
					}
				}
			}

		}
	}
	return 0 ; 
}


//****************************************************************SIGNAL****************************************************************
int parseur_signal (list<Lexeme*>::iterator itr){
	itr++ ; 
	if ((*itr)->getType() == MOT) {
		i++ ; 
		if ((*itr)->getLex() == ":") {
			itr++;
			if // vérif type
			}
		}
	}
}
//*************************************************************COMPONENT****************************************************************
int parseur_component (list<Lexeme*>::iterator itr){
	itr++ ; 
	if ((*itr)->getType() == MOT) {
	}
}
//*************************************************************PROCESS******************************************************************
int parseur_process (list<Lexeme*>::iterator itr){
	itr++ ; 
	if ((*itr)->getType() == MOT) {
	}
}








