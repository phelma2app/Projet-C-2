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
	tree<Lexeme*> parseur;
	int erreur;
	cout << endl << "---Synthetiseur VHDL Beta 1.0---" << endl << endl;

	bool close=false;
	while(!close)
	{
		cout << "--Ready--" << endl;
		int commande=commande_vhdl(libraryname,sourcename);
		while(commande==ERREUR)
		{
			commande=commande_vhdl(libraryname,sourcename);
		}

        int nligne=0;
		switch(commande)
		{
            case COMPARE :
                if(fichiers_identiques(sourcename,libraryname, nligne))
                    cout << sourcename << " et " << libraryname << " sont identiques." << endl;
                else
                    cout << "!!!" << sourcename << " et " << libraryname << " sont differents ligne " << nligne << "!!!" << endl;
                break;
			case SOURCE :
				execute_script(sourcename);
				cout << endl << "--Fin script--" << endl << endl;
				break;
			case VHDLCOMP :
				lex.clear();
				vhdlcomp(libraryname,sourcename,lex);
				cout << endl << "--Parseur en cours--" << endl;
				erreur=parseur_root(lex);
				print_lex(lex);

				if(erreur==1)
				{
					cout << endl << "--Creation de l'arbre--" << endl;
					parseur = createTree(lex);
					cout << endl;
					cout << endl << "--Impression de l'arbre--" << endl;
					printTree(parseur);
					if(libraryname!="")
						saveTree(parseur,libraryname);
					cout << endl << "--Fin de compilation--" << endl << endl;
				}
				else
				{
					cout << endl << "--Erreur de syntaxe--" << endl;
					cout <<  "--Compilation avortée--" << endl << endl;
				}
				break;
			default: cout << endl << "--Sortie de programme--" << endl << endl;
				close=true;
				break;
		}
	}
}
