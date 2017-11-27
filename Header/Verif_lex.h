#ifndef VERIFICATION_ORTHOGRAPHE_AJOUT_ETIQUETTE_H_
#define VERIFICATION_ORTHOGRAPHE_AJOUT_ETIQUETTE_H_

#include <iostream>
#include <string>
#include <list>
#include "utilities.h"  // fichier contenant les fonctions is_number, is_letter, is_ponctuation, is_ponctuation2char
#include "Lexeme.h"

using namespace std ; 

bool verif(Lexeme& l, bool *com, int *ligne_com);

#endif //VERIFICATION_ORTHOGRAPHE_AJOUT_ETIQUETTE_H_
