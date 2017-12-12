#include <iostream>
#include <string>

using namespace std;

int parseur_root (list<Lexeme*>& list_lex);

int parseur_entity (list<Lexeme*>::iterator& itr) ; 

int parseur_port (list<Lexeme*>::iterator& itr) ; 

int parseur_type_port (list<Lexeme*>::iterator& itr, bool *fin_port);

int parseur_library (list<Lexeme*>::iterator& itr) ;

int parseur_use (list<Lexeme*>::iterator& itr);

int parseur_package (list<Lexeme*>::iterator& itr);

int parseur_architecture (list<Lexeme*>::iterator& itr);

int parseur_signal (list<Lexeme*>::iterator& itr) ; 

int parseur_component (list<Lexeme*>::iterator& itr);

int parseur_generic (list<Lexeme*>::iterator& itr) ;

int parseur_process (list<Lexeme*>::iterator& itr);

int parseur_begin (list<Lexeme*>::iterator& itr);

int parseur_type (list<Lexeme*>::iterator& itr);

int parseur_if (list<Lexeme*>::iterator& itr);

int expr_if_elsif (list<Lexeme*>::iterator& itr, int c,string end_cond);

int verif_cond_if(list<Lexeme*>::iterator& itr);

int parseur_then (list<Lexeme*>::iterator& itr);

int verif_instr(list<Lexeme*>::iterator& itr) ;

int parseur_else (list<Lexeme*>::iterator& itr);

int parseur_elsif (list<Lexeme*>::iterator& itr);

int parseur_declar_type (list<Lexeme*>::iterator& itr);

int parseur_variable(list<Lexeme*>::iterator& itr);

int parseur_map(list<Lexeme*>::iterator& itr) ; 
