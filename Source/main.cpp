#include "../Header/Console.h"
#include "../Header/CreateTree.h"
#include "../Header/Lexeur.h"
#include "../Header/Lexeme.h"
#include "../Header/parseur.h"
#include "../Header/tree.hh"
#include <string>
#include <list>
#include <iostream>


using namespace std;

int main()
{
	string libraryname;
	string sourcename;
	list<Lexeme*> lex;

	bool close=false;
	while(!close)
	{
		int commande=commande_vhdl(libraryname,sourcename);
		while(commande==ERREUR)
		{
			commande=commande_vhdl(libraryname,sourcename);
		}

		switch(commande)
		{
			case VHDLCOMP : 
				vhdlcomp(libraryname,sourcename,lex);
				break;
			default: cout << "Sortie de programme" << endl;
				close=true;
				break;
		}		

		cout << "Parseur en cours" << endl;
		parseur_root(lex);
		print_lex(lex);
		cout << "Creation de l'arbre" << endl;
		tree<Lexeme*> parseur = createTree(lex);
		cout << endl;
		cout << "Impression de l'arbre" << endl;
		printTree(parseur);

	}


}
