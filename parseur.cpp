#include <iostream>
#include <string>
#include "utilities.h"


using namespace std;

int parseur_entity (List<Lexeme*>::iterator itr){
	itr++ ; 
	if ((*itr)->getType() == MOT) {
		itr++;
		string identifiant = lexeme ; 
		if ((*itr)->getLex() == "is"){
			itr++; 
			if ((*itr)->getLex() == "port"){
				if (parseur_port(i)= 0) {
					return 0 ; 
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

int parseur_port (List<Lexeme*>::iterator itr) {
	i++;
	if ((*itr)->getLex()== "("){
		i++;
		while ((*itr)->getType() == MOT) {
			i++;
			while ((*itr)->getLex() != ':') {
				if ((*itr)->getLex()== ",") {
					i++;
					if ((*itr)->getType() == MOT) {
						i++;
					} //if ((*itr)->getType() == MOT)
				} //if ((*itr)->getLex()== ",") 
			} //while ((*itr)->getLex() != ':') 
			i++ ; 
			if ((*itr)->getLex()== "in"){
			// A COMPLETER
			} // if ((*itr)->getLex()== "in")
			else if ((*itr)->getLex()== "out"){
			// A COMPLETER AVEC LE MEME CODE QUE LE "IN"
			} // else if 
			else if ((*itr)->getLex()== "inout"){ 
			// A COMPLETER AVEC LE MEME CODE QUE LE "IN "
			} // else if 
			else {
				return 0 ; 
			} // else
			} // if((*itr)->getLex() == ':')
		} // while
	} // if ((*itr)->getLex()== "(")

} // parseur_port
