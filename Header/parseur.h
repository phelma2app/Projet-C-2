#include <iostream>
#include <string>

using namespace std;

int parseur_entity (list<Lexeme*>::iterator itr) ; 

int parseur_port (list<Lexeme*>::iterator itr) ; 

int parseur_type_port (list<Lexeme*>::iterator itr, bool *fin_port);

int parseur_library (list<Lexeme*>::iterator itr) ;

int parseur_use (list<Lexeme*>::iterator itr, string library);

int parseur_architecture (list<Lexeme*>::iterator itr);
