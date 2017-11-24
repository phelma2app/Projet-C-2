//--------------------------------------------FONCTIONS UTILES----------------------------------------------

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <iostream>
#include <string>

using namespace std;

//Fonction pour mettre toutes les lettres en minuscule, ÃÂ  faire en prÃÂ©ambule de toute analyse sur le string
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

#endif //UTILITIES_H_
