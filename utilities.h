//--------------------------------------------FONCTIONS UTILES----------------------------------------------

#include <iostream>
#include <string>

using namespace std ;

//Fonction pour mettre toutes les lettres en minuscule, à faire en préambule de toute analyse sur le string
void minus_string(string &to_minus);

//Fonction pour tester la ponctuation
bool is_ponctuation(char ch_test);

//Fonction pour tester la double ponctuation
bool is_ponctuation2char(char ch_test1, char ch_test2);

//Lettre ?
bool is_letter(char ch_test);

//Nombre ?
bool is_number(char ch_test);
