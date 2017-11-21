#ifndef CONSOLE_H_
#define CONSOLE_H_


#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define ERREUR 0
#define VHDLCOMP ERREUR+1

//Commandes sur la console pour l'utilisateur
//Retourne un entier qui permet au main d'appeler la bonne commande
int commande_vhdl(string &libraryname, string &sourcename);


int commande_vhdlcomp(string &libraryname, string &sourcename);

#endif //CONSOLE_H_
