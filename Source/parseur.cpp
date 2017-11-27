#include <iostream>
#include <string>
#include <list>
#include "../Header/utilities.h"
#include "../Header/Lexeme.h"
#include "../Header/parseur.h"
#include "../Header/type_Lexeme.h"

using namespace std;

// On retourne "0" s'il y a une erreur et "1" quand il n'y a pas d'erreur

//AJOUTER LES ERREURS A PARTIR DU BEGIN

// ********************************ROOT********************************************************************
int parseur_root (list<Lexeme*>& list_lex){
	list<Lexeme*>::iterator itr;
	for(itr=list_lex.begin();itr!=list_lex.end();itr++)
	{
		if((*itr)->getLex()=="entity"&&(*itr)->getType()!=COMMENTAIRE) {
			parseur_entity(itr);
		}
		if((*itr)->getLex()=="library"&&(*itr)->getType()!=COMMENTAIRE) {
			parseur_entity(itr);
		}
	}
}

// ********************************ENTITY********************************************************************
int parseur_entity (list<Lexeme*>::iterator& itr){
	(*itr)->setType(ENTITY) ; 
	itr++ ; 
	if ((*itr)->getType() == MOT) {
		string identifiant = (*itr)->getLex() ;
		(*itr)->setType(ENTITY_ID) ; 
		itr++; 
		if ((*itr)->getLex() == "is"){
			itr++; 
			if ((*itr)->getLex() == "port"){
				if (parseur_port(itr)== 0) {
					cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme dans le port" << endl ;
					return 0 ; 		// indique que l'on a une erreur
				} // if (parseur_port(i)= 0) {
				else {
					itr++;
					cout << (**itr) << endl;
					if ((*itr)->getLex() == "end"){
						(*itr)->setType(ENTITY_END) ; 
						itr++;
						if ((*itr)->getLex() == identifiant){
							return 1; 
						} // if (lexeme = identifiant){
						else {
							cout << "ERREUR ligne " << (*itr)->getLigne() << ": l'identifiant est mal orthographie" << endl ;
						} //else
					} //if (lexeme = 'end')
				} // else
			} // if (lexeme = 'port')
		} // if ((*itr)->getLex() = 'is')
	} // if ((*itr)->getType() = mot) 
	cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme dans l'entite" << endl ;
	return 0 ; 
} // parseur_entity 



// *****************************************************PORT**********************************************************
int parseur_port (list<Lexeme*>::iterator& itr) {
	bool fin_port = false ;  // bool qui nous permet de gerer le dernier port 
	(*itr)->setType(PORT) ; 
	itr++;
	if ((*itr)->getLex()== "("){
		itr++;
		while ((*itr)->getType() == MOT && fin_port == false) {
			(*itr)->setType(PORT_ID) ; 
			itr++;
			while ((*itr)->getLex() != ":") {
				if ((*itr)->getLex()== ",") {
					itr++;
					if ((*itr)->getType() == MOT) {
						(*itr)->setType(PORT_ID) ; 
						itr++;
					} //if ((*itr)->getType() == MOT)
				} //if ((*itr)->getLex()== ",") 
			} //while ((*itr)->getLex() != ':') 
			itr++ ; 
			if ((*itr)->getLex()== "in"){
				(*itr)->setType(PORT_IN) ; 
				if (parseur_type_port(itr, &fin_port) == 0) {
					cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme port in type port" << endl ;
					return 0 ;
				}
			} // if ((*itr)->getLex()== "in")
			else if ((*itr)->getLex()== "out"){
				(*itr)->setType(PORT_OUT) ; 
				if (parseur_type_port(itr, &fin_port) == 0) {
					cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme port out type port " << endl ;
					return 0 ;
				}
			} // else if 
			else if ((*itr)->getLex()== "inout"){ 
				(*itr)->setType(PORT_INOUT) ; 
				if (parseur_type_port(itr, &fin_port) == 0) {
					cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme port inout type port" << endl ;
					return 0 ;
				}
			} // else if 
			else {
				cout << "ERREUR ligne " << (*itr)->getLigne() << ": le type de port n'est pas reconnu (mettre in, out ou inout " << endl ;
				return 0 ; 
			} // else
		} // while
	return 1 ; 
	} // if ((*itr)->getLex()== "(")

} // parseur_port



//**************************************************************TYPE PORT*************************************************************
int parseur_type_port (list<Lexeme*>::iterator& itr, bool *fin_port) {
	itr++;
	if (is_type((*itr)->getLex())==true) {			// is_type est unefonction definie dans utilities qui permet de verifier qu'on est bien un type attendue
		(*itr)->setType(PORT_TYPE) ; 
		if (parseur_type(itr)== 0) {			// parseur_type traite les type afin de verifier qu'on est les info attendue
			cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme sur le type " << endl ;
			return 0 ; 		
		}
		itr++ ; 
		if ((*itr)->getLex()== ";") {
			(*itr)->setType(PORT_ID_END) ; 
			return 1 ;
		}
		else if ((*itr)->getLex()== ")") {
			(*itr)->setType(PORT_ID_END) ; 
			itr++;
			if ((*itr)->getLex()== ";") {
			*fin_port = true ;
			(*itr)->setType(PORT_END) ; 
			return 1 ;
			}
		}
		else {
			cout << "ERREUR ligne " << (*itr)->getLigne() << ": il manque une ')' ou un ';' " << endl ;
			return 0 ; 
		}
	}


} // parseur type_port 



//******************************************************LIBRARY*************************************************************************

int parseur_library (list<Lexeme*>::iterator& itr){
	itr++ ; 
	if ((*itr)->getType() == MOT) {
		string library = (*itr)->getLex() ;
		itr++; 
		if ((*itr)->getLex() == ";"){
			itr++ ; 
			while ((*itr)->getLex() == "use"){
				if (parseur_use(itr, library)==0){
					cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme dans le parseur use" << endl ;
					return 0 ; 
				} //if (parseur_use(*itr)==0){
			} //while
			return 1 ;
		} //if ((*itr)->getLex() == ";"){
	} //if ((*itr)->getType() == MOT) {
	cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme on s'attend a avoir un mot" << endl ;
	return 0 ; 
} //parseur_library 



//****************************************************USE*******************************************************************************


int parseur_use (list<Lexeme*>::iterator& itr, string library){
	itr++ ; 
	if ((*itr)->getLex() == library) {
		itr ++;
		if ((*itr)->getLex() == ".") {
			itr++;
			if ((*itr)->getType() == MOT) {
				string name = (*itr)->getLex() ; 
				itr++ ;
				if ((*itr)->getLex() == ".") {
					itr++;
					while ((*itr)->getLex() == ".") {
						itr++;
						if ((*itr)->getType() == MOT) {
							itr++ ;	
						}
						else {
						cout << "ERREUR ligne " << (*itr)->getLigne() << ": on s'attend a avoir un mot " << endl ;
						return 0 ; 
						}
							
					}
					itr++; 
					if ((*itr)->getLex() == ";") {
						return 1 ; 
					}
				}
			}
		}
	}
	return 0;
}

//**************************************************ARCHITECTURE************************************************************************


int parseur_architecture (list<Lexeme*>::iterator& itr){
	itr++ ; 
	if ((*itr)->getType() == MOT) {
		string identifiant = (*itr)->getLex() ;
		itr++;
		if ((*itr)->getLex() == "of"){
			itr++ ; 
			if (){ // VERIFIER QUE L'ENTITY EXISTE 
				itr++;
				if ((*itr)->getLex() == "is"){
					itr++ ;
					while ((*itr)->getLex() != "begin"){
						if ((*itr)->getLex() == "signal"){
							if (parseur_signal(itr)== 0) {
								cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme dans le signal " << endl ;
								return 0 ; 		// indique que l'on a une erreur
							}
						}
						else if ((*itr)->getLex() == "component"){
							if (parseur_component(itr)== 0) {
							cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme dans le component " << endl ;
							return 0 ; 		// indique que l'on a une erreur
							}
						}
						else {
							cout << "ERREUR ligne " << (*itr)->getLigne() << ": on s'attend a avoir 'signal ou 'component' sachant qu'on a pas de begin " << endl ;
							return 0 ;
						}
					}
					itr++ ;  	//premier lexeme apres le begin 
					while ((*itr)->getLex() != "end") {
						if ((*itr)->getLex()=="process"){
							if (parseur_process(itr)==0){
								cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme dans le process" << endl ;
								return 0;
									}
						}						
						else if ((*itr)->getType() != MOT) {
							itr++;
							if ((*itr)->getLex() == "<="){
								if ((*itr)->getType() != MOT) {
								itr++;
									while ((*itr)->getLex() != ";"){
										if ((*itr)->getLex()== "and"|(*itr)->getLex()== "or"|(*itr)->getLex()== "xor"|(*itr)->getLex()== "not"){
											itr++;
											if ((*itr)->getType() != MOT) {
												itr++;
											}
										}
									}
								}
							}
							else if ((*itr)->getLex() == ":"){
								itr--;   // pour recuperer le label du process
								itr++;
								itr++; 
								if ((*itr)->getLex() == "process"){
									if (parseur_process(itr)==0){
										cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme dans le process" << endl ;
										return 0;
									}
								}

							}
						}
						itr++;	
						
					}
					itr++;
					if ((*itr)->getLex()== identifiant){
						return 1 ;
					}
				}
			}

		}
	}
	cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme dans l'architecture" << endl ;
	return 0 ; 
}


//****************************************************************SIGNAL****************************************************************

int parseur_signal (list<Lexeme*>::iterator& itr){
	itr++ ; 
	if ((*itr)->getType() == MOT) {
		itr++ ; 
		if ((*itr)->getLex() == ":") {
			itr++;
			if (is_type((*itr)->getLex())==true) {
				if (parseur_type(itr)== 0) {
					cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme avec le type " << endl ;
					return 0 ;
				}
				else {
					return 1 ; 
				} 		
			}
		}
	}
}

//*************************************************************COMPONENT****************************************************************
int parseur_component (list<Lexeme*>::iterator& itr){
	itr++ ; 
	if ((*itr)->getType() == MOT) {
		string component_name = (*itr)->getLex() ;
		itr++;
		if ((*itr)->getLex() == "port"){
			if (parseur_port(itr)== 0) {
				cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme avec le port " << endl ;
				return 0 ; 		
			}
			else if ((*itr)->getLex() == "generic"){
				if (parseur_generic(itr)== 0) {
					cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme dans le generic " << endl ;
					return 0 ; 
				}
				else {
					return 1 ; 		
				}	
			}
		}
	}
}



//***********************************************************GENERIC********************************************************************
int parseur_generic (list<Lexeme*>::iterator& itr) {
	itr++;
	if ((*itr)->getLex()== "("){
		itr++;
		if ((*itr)->getType() == MOT) {
			string component_name = (*itr)->getLex() ;
			itr++; 
			if ((*itr)->getLex() == ":") {
				itr++;
				if (is_type((*itr)->getLex())==true) {
					if (parseur_type(itr)== 0) {
						cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme avec le type" << endl ;
						return 0 ; 		
					}
					itr++;
					if ((*itr)->getLex() == ")"){
						itr++;
						if ((*itr)->getLex() == ";"){
							return 1 ; 
						}	
					}
				}	
			}
		}
	}
	return 0 ; 
}

//*************************************************************PROCESS******************************************************************
int parseur_process (list<Lexeme*>::iterator& itr){
	bool sensibilite = false ; 
	itr++ ; 
	while ((*itr)->getLex() == "begin") {
		if ((*itr)->getType() == MOT) {
			if (verif_instr(itr)==0){
			cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme dans l'instruction" << endl ;
			return 0; 
			}
		}
		else if ((*itr)->getLex() == "(" && sensibilite == false) {
			itr++;
			if ((*itr)->getType() == MOT) {     				//CHANGER MOT EN SIGNAL
				itr++;
				while ((*itr)->getLex() == ")"){
		 			if ((*itr)->getLex() == ",") {
						itr++;
						if ((*itr)->getType() == MOT) {		//CHANGER MOT EN SIGNAL
						itr++;
						}
					}
				}
			}
			sensibilite = true ; 
		}
		else {
			cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme on s'attend a avoir une liste de sensibilité ou une instruction sachant que l'on a pas de 'begin' " << endl ;
			return 0;
		}
		itr++;
	}
	if (parseur_begin(itr)==0){
		cout << "ERREUR ligne " << (*itr)->getLigne() << ": probleme dasn le begin " << endl ;
		return 0; 
	}
	else {return 1;}
}


//**********************begin
int parseur_begin (list<Lexeme*>::iterator& itr) {
	itr++;
	if (verif_instr(itr)==0){
		return 0 ;
	}
	itr++; 
	if ((*itr)->getLex() == "end") {
		itr++;
		if ((*itr)->getLex() == "end") {
			return 1 ;
		}
	}
	return 0;
}
 

/*
Apres le process 
soit liste de sensibilité 
soit declaration de variable (:=)
soit une declaration de constante 
soit BEGIN puis instr jusqu'au end process 



 */ 

//***********************************************************TYPE***********************************************************************
int parseur_type (list<Lexeme*>::iterator& itr) {
	//itr++;
	if ((*itr)->getLex()== "std_logic"){
		return 1 ; 
	}
	else if ((*itr)->getLex()== "std_logic_vector"){
		itr++;
		if ((*itr)->getType() == NOMBRE) { 
			itr++;
			if ((*itr)->getLex()== "downto") { 
				itr++;
				if ((*itr)->getType() == NOMBRE) { 
					return 1 ; 
				}
			}
		}
	}
	else if ((*itr)->getLex()== "bit"){
		return 1 ; 
	}
	else if ((*itr)->getLex()== "boolean"){
		return 1 ; 		
	}
	else if ((*itr)->getLex()== "bit_vector"){
		itr++;
		if ((*itr)->getType() == NOMBRE) { 
			itr++;
			if ((*itr)->getLex()== "downto") { 
				itr++;
				if ((*itr)->getType() == NOMBRE) { 
					return 1 ; 
				}
			}
		}
	}
	return 0 ; 
}


//*****************************************************************IF*******************************************************************
int parseur_if (list<Lexeme*>::iterator& itr) {
	itr++;
	if ((*itr)->getLex() == "(") {
		itr++;
		if (verif_cond_if(itr)== 0) {
			return 0 ; 		
		}
		itr++;
		if ((*itr)->getLex() == ")") {
		}
	}
	else if (verif_cond_if(itr)== 0) {
			return 0 ; 		
	}
	itr++; 
	while ((*itr)->getLex()== "and"|(*itr)->getLex()== "or"|(*itr)->getLex()== "xor"|(*itr)->getLex()== "not"){
		itr++;
		if ((*itr)->getLex() == "(") {
			itr++;
			if (verif_cond_if(itr)== 0) {
				return 0 ; 		
			}
			itr++;
			if ((*itr)->getLex() == ")") {
			}
		}
		else if (verif_cond_if(itr)== 0) {
				return 0 ; 		
		}
	}
	itr++;
	if ((*itr)->getLex() == "then") {
		if(parseur_then(itr)== 0) {
			return 0 ; 		
		}
		if ((*itr)->getLex() == "end") {
			itr++;
			if ((*itr)->getLex() == "if") {
				itr++;
				if ((*itr)->getLex() == ";") {
					return 1 ; 
				}
			}
		}
	}
	return 0 ; 	
}


//******************Cond_if***********
int verif_cond_if(list<Lexeme*>::iterator& itr) {
	if ((*itr)->getType() == MOT) {
		itr++;
		if ((*itr)->getLex()== "="|(*itr)->getLex()== "<="|(*itr)->getLex()== ">="|(*itr)->getLex()== "<"|(*itr)->getLex()== ">"){
			itr++;
			if ((*itr)->getType() == MOT|(*itr)->getType() == NOMBRE) {
				return 1;
			}
			else if ((*itr)->getLex()== "'"){
				itr++;
				if ((*itr)->getType() == MOT|(*itr)->getType() == NOMBRE) {
					itr++;
					if ((*itr)->getLex()== "'"){
						return 1;
					}
				}
			}
		}
	}
}
//*****************************************************************THEN*****************************************************************
int parseur_then (list<Lexeme*>::iterator& itr) {
	itr++;
	if ((*itr)->getLex()== "if") {
		if (parseur_if(itr)== 0) {
			return 0 ; 		
		}

	}
	else if ((*itr)->getLex()== "elsif") {
		if (parseur_if(itr)== 0) {
			return 0 ; 		
		}

	}
	else if ((*itr)->getLex()== "else") {
		if (parseur_if(itr)== 0) {
			return 0 ; 		
		}


	}
        else if ((*itr)->getType() == MOT){
		if (verif_instr(itr)==0) {
		return 0 ; 
		}
	
	}
	
}


//******************instr***********
int verif_instr(list<Lexeme*>::iterator& itr) {
	if ((*itr)->getType() == MOT) {
		itr++;
		if ((*itr)->getLex()== ":="|(*itr)->getLex()== "<="){
			itr++;
			if ((*itr)->getType() == MOT|(*itr)->getType() == NOMBRE) {
				if((*itr)->getLex()== ";"){
				return 1;
				}
			}
			else if ((*itr)->getLex()== "'"){
				itr++;
				if ((*itr)->getType() == MOT|(*itr)->getType() == NOMBRE) {
					itr++;
					if ((*itr)->getLex()== "'"){
						if ((*itr)->getLex()== ";"){
							return 1;
						}
					}
				}
			}
		}
	}
}
//*****************************************************************ELSE*****************************************************************
int parseur_else (list<Lexeme*>::iterator& itr) {
	if (parseur_then(itr)== 0) {
		return 0 ; 		
	}
	else {
	return 1 ; 	
	}
}

//*****************************************************************ELSIF****************************************************************
int parseur_elsif (list<Lexeme*>::iterator& itr) {
	if (parseur_if(itr)== 0) {
		return 0 ; 		
	}
	else {
		return 1 ; 	
	}
}
