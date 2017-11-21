#include "../Header/Console.h"
#include "../Header/CreateTree.h"
#include "../Header/Lexeur.h"
#include "../Header/Lexeme.h"
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
	tree<Lexeme*>::pre_order_iterator top=parseur.begin();
	tree<Lexeme*>::pre_order_iterator i1,i2;
	Lexeme* l=new Lexeme("_root");
	i1=parseur.insert(top,l);

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
		list<Lexeme*>::iterator itr=lex.begin();
		for(itr=lex.begin();itr!=lex.end();++itr)
		{
			i2=parseur.append_child(i1,*itr);
			i1=i2;
		}
		printTree(parseur);
	}


}
