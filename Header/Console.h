#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "Lexeur.h"

using namespace std;

//Definition des commandes
#define ERREUR 0
#define SOURCE ERREUR+1
#define SORTIE SOURCE+1
#define VHDLCOMP SORTIE+1

//Commandes sur la console pour l'utilisateur
//Retourne un entier qui permet au main d'appeler la bonne commande
int commande_source(string &sourcename);
int commande_source(string &sourcename, list<string> commandes, list<string>::iterator itr);
int commande_vhdl(string &libraryname, string &sourcename);
int commande_vhdl(string &libraryname, string &sourcename, string& commande);
int commande_vhdl(string &libraryname, string &sourcename, list<string> commandes, list<string>::iterator itr);
int commande_vhdlcomp(string &libraryname, string &sourcename);
int commande_vhdlcomp(string &libraryname, string &sourcename, list<string> commandes, list<string>::iterator itr);
int execute_script(string nom_script);

#endif //CONSOLE_H_
