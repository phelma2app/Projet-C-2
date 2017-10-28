#include <iostream>
#include <string>
#include "utilities.h"


using namespace std;

// ********************************ENTITY********************************************************************
int parseur_entity (List<Lexeme*>::iterator itr){
	itr++ ; 
	if ((*itr)->getType() == MOT) {
		string identifiant = (*itr)->getLex() ;
		itr++; 
		if ((*itr)->getLex() == "is"){
			itr++; 
			if ((*itr)->getLex() == "port"){
				if (parseur_port(*itr)= 0) {
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
int parseur_port (List<Lexeme*>::iterator itr) {
	bool fin_port = false ;  // bool qui nous permet de gérer le dernier port 
	i++;
	if ((*itr)->getLex()== "("){
		itr++;
		while ((*itr)->getType() == MOT && fin_port == false) {
			itr++;
			while ((*itr)->getLex() != ':') {
				if ((*itr)->getLex()== ",") {
					itr++;
					if ((*itr)->getType() == MOT) {
						itr++;
					} //if ((*itr)->getType() == MOT)
				} //if ((*itr)->getLex()== ",") 
			} //while ((*itr)->getLex() != ':') 
			itr++ ; 
			if ((*itr)->getLex()== "in"){
				if (parseur_type_port(*itr) = 0) {
					return 0 ;
				}
			} // if ((*itr)->getLex()== "in")
			else if ((*itr)->getLex()== "out"){
				if (parseur_type_port(*itr) = 0) {
					return 0 ;
				}
			} // else if 
			else if ((*itr)->getLex()== "inout"){ 
				if (parseur_type_port(*itr) = 0) {
					return 0 ;
				}
			} // else if 
			else {
				return 0 ; 
			} // else
			} // if((*itr)->getLex() == ':')
		} // while
	} // if ((*itr)->getLex()== "(")

} // parseur_port





//**************************************************************TYPE PORT*************************************************************
int parseur_type_port (List<Lexeme*>::iterator itr, bool *fin_port) {
	itr++;
	if type // A COMPLETER
		itr++ ; 
		if ((*itr)->getLex()== ";") {
			return 1 ;
		}
		else if ((*itr)->getLex()== ")") {
			itr++
			fin_port = true ;
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

int parseur_library (List<Lexeme*>::iterator itr){
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


int parseur_use (List<Lexeme*>::iterator itr, string library){
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
}










