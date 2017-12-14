#ifndef LEXEUR_H_
#define LEXEUR_H_

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"
#include "Lexeme.h"
#include "Verif_lex.h"

using namespace std;

string read_line(ifstream& fichier);
string add_space_on_string(string str, int length);
bool stock_lexemes(string buffer, int ligne, list<Lexeme*>& Lex_VHDL);
bool vhdlcomp(string libraryname, string sourcename, list<Lexeme*>& list_lex);
void print_lex(const list<Lexeme*>& list_lex);

#endif //LEXEUR_H_
