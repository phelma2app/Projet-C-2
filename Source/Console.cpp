#include "../Header/Console.h"

//Commandes sur la console pour l'utilisateur
//Retourne un entier qui vaut 0 si erreur, sinon il renvoie une valeur associee Ã  la commande
int commande_vhdl(string &libraryname, string &sourcename)
{
	string commande;
	cin >> commande;

	return commande_vhdl(libraryname,sourcename,commande);	
}

int commande_vhdl(string &libraryname, string &sourcename, string& commande)
{
	//Commande utilisateur
	if(commande=="vhdlcomp")
	{
		if(commande_vhdlcomp(libraryname, sourcename)!=ERREUR)
		{
			return VHDLCOMP;
		}
	}
	if(commande=="source")
	{
		if(commande_source(sourcename)!=ERREUR)
		{
			cout << "On retourne source" << endl;
			return SOURCE;
		}
	}
	if(commande=="\0")
	{
		return SORTIE;
	}
	else
	{
		cout << "Erreur : commande inconnue" << endl;
		return ERREUR;
	}
	return ERREUR;
}

int commande_vhdl(string &libraryname, string &sourcename, list<string> commandes, list<string>::iterator itr)
{
	if((*itr)=="vhdlcomp")
	{
		if(commande_vhdlcomp(libraryname, sourcename,commandes,itr)!=ERREUR)
		{
			return VHDLCOMP;
		}
	}
	if((*itr)=="source")
	{
		if(commande_source(sourcename,commandes,itr)!=ERREUR)
		{
			cout << "On retourne source" << endl;
			return SOURCE;
		}
	}
	if((*itr)=="\0")
	{
		return SORTIE;
	}
	else
	{
		cout << "Erreur : commande inconnue" << endl;
		return ERREUR;
	}
	return ERREUR;
}


//Commande VHDLCOMP
//
int commande_vhdlcomp(string &libraryname, string &sourcename, list<string> commandes, list<string>::iterator itr)
{
	cout << "On va compiler" << endl;	//pour test
	itr ++;
	if((*itr)=="-l")
	{
		cout << "Le nom de la librarie est donnee" << endl;	//pour test
		itr++;
		libraryname=(*itr);
		itr++;
		sourcename=(*itr);
	}
	else
	{
		cout << "Le nom de la librairie n'est pas donnee" << endl; //pour test
		sourcename=(*itr);
	}
	return VHDLCOMP;
}

int commande_vhdlcomp(string &libraryname, string &sourcename)
{
	cout << "On va compiler" << endl;	//pour test
	string commande;
	cin >> commande;
	if(commande=="-l")
	{
		cout << "Le nom de la librarie est donnee" << endl;	//pour test
		cin >> libraryname;
		cin >> sourcename;
	}
	else
	{
		cout << "Le nom de la librairie n'est pas donnee" << endl; //pour test
		sourcename=commande;
	}
	return VHDLCOMP;
}

int commande_source(string &sourcename, list<string> commandes, list<string>::iterator itr)
{
	cout << "On va executer un script" << endl;	//pour test
	itr++;
	sourcename=(*itr);
	return SOURCE;
}

int commande_source(string &sourcename)
{
	cout << "On va executer un script" << endl;	//pour test
	cin >> sourcename;
	return SOURCE;
}

int execute_script(string nom_script)
{
	cout << "Execute script " << nom_script << endl;
	ifstream fichier_script(nom_script.c_str(), ios::in);  // on ouvre en lecture
	if(!fichier_script)  // si l'ouverture n'a pas fonctionnee
	{
		cerr << "Impossible d'ouvrir le fichier " << nom_script << " !" << endl;
		return 0;
	}

	//Traitement du fichier
	string buffer ="";
	string libraryname;
	string sourcename;
	list<Lexeme*> lex;
	list<string> commandes;
	cout << "Le fichier script va être lu" << endl;

	while(!fichier_script.eof())
	{
		fichier_script >> buffer;	//on lit une ligne
		cout << "-" << buffer << endl;
		commandes.push_back(buffer);
	}

	//cout << "Commande vhdl va etre lance" << endl;	//Pour test
	list<string>::iterator itr=commandes.begin();
	cout << "commandes.begin()=" << (*itr) << endl;
	bool sortie=false;
	tree<Lexeme*> parseur;
	for(itr=commandes.begin();itr!=commandes.end();itr++)
	{
		int commande=commande_vhdl(libraryname,sourcename,commandes,itr);
		switch(commande)
		{
			case VHDLCOMP : 
				//cout << "VHDLCOMP" << endl;	//Pour test
				lex.clear();
				vhdlcomp(libraryname,sourcename,lex);
				cout << "Parseur en cours" << endl;
				parseur_root(lex);
				print_lex(lex);
				cout << "Creation de l'arbre" << endl;
				parseur = createTree(lex);
				cout << endl;
				cout << "Impression de l'arbre" << endl;
				printTree(parseur);
				break;
			case SOURCE:
				execute_script(sourcename);
				break;
			default:
				//cout << "Commande non reconnue : "<< (*itr) << endl;	//Pour test
				break;
		}
	}		

	return 1;	
}
