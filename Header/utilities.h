//--------------------------------------------FONCTIONS UTILES----------------------------------------------

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <iostream>
#include <string>
#include "Lexeme.h"
#include "type_Lexeme.h"
#include <list>

using namespace std;

//Fonction pour enlever les commentaires d'une liste de lexeme
void delete_com(list<Lexeme*>& list_lex);

//Fonction pour mettre toutes les lettres en minuscule, a  faire en preambule de toute analyse sur le string
void minus_string(string &to_minus);

//Fonction pour tester la ponctuation
bool is_ponctuation(char ch_test);

//Fonction pour tester la double ponctuation
bool is_ponctuation2char(char ch_test1, char ch_test2);

//Lettre ?
bool is_letter(char ch_test);

//Nombre ?
bool is_number(char ch_test);

//Fonction pour tester le type
bool is_type(string st_test);

//Fonction pour comparer les fichiers
bool fichiers_identiques (std::string fichier1, std::string fichier2) ;

#endif //UTILITIES_H_
