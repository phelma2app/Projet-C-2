#include "../Header/Console.h"

//Commandes sur la console pour l'utilisateur
//Retourne un entier qui vaut 0 si erreur, sinon il renvoie une valeur associee a la commande

//Compare deux fichiers et indique s'ils sont differents (permet de vérifier les changements apportés par l'arbre
int commande_compare(string &fichier1, string &fichier2)
{
	cin >> fichier1;
	cin >> fichier2;
	return COMPARE;
}

int commande_compare(string &fichier1, string &fichier2, list<string> commandes, list<string>::iterator itr)
{
	itr++;
	fichier1=(*itr);
	itr++;
	fichier2=(*itr);

	return COMPARE;
}

//Interprete les commandes rentrees par l'utilisateur
int commande_vhdl(string &libraryname, string &sourcename)
{
	string commande;
	cin >> commande;

	return commande_vhdl(libraryname,sourcename,commande);
}

int commande_vhdl(string &libraryname, string &sourcename, string& commande)
{
	//Commande utilisateur

	if(commande=="compare")
	{
		if(commande_compare(sourcename,libraryname)!=ERREUR)
		{
			return COMPARE;
		}
	}
	if(commande=="source")
	{
		if(commande_source(sourcename)!=ERREUR)
		{
			return SOURCE;
		}
	}
	if(commande=="vhdlcomp")
	{
		if(commande_vhdlcomp(libraryname, sourcename)!=ERREUR)
		{
			return VHDLCOMP;
		}
	}
	if(commande=="quit")
	{
		return SORTIE;
	}

	cout << "Erreur : commande inconnue" << endl;
	return ERREUR;
}

int commande_vhdl(string &libraryname, string &sourcename, list<string> commandes, list<string>::iterator itr)
{
	if((*itr)=="compare")
	{
		if(commande_compare(sourcename,libraryname,commandes,itr)!=ERREUR)
		{
			return COMPARE;
		}
	}
	if((*itr)=="source")
	{
		if(commande_source(sourcename,commandes,itr)!=ERREUR)
		{
			return SOURCE;
		}
	}
	if((*itr)=="vhdlcomp")
	{
		if(commande_vhdlcomp(libraryname, sourcename,commandes,itr)!=ERREUR)
		{
			return VHDLCOMP;
		}
	}
	if((*itr)=="quit")
	{
		return SORTIE;
	}
	else
	{
		return ERREUR;
	}
	return ERREUR;
}


//Compilation d'un fichier VHDL
//Optionnel : on peut rajouter le nom d'un fichier librairie par -l
//Dans ce cas l'arbre sera sauvegarde dans ce fichier
int commande_vhdlcomp(string &libraryname, string &sourcename, list<string> commandes, list<string>::iterator itr)
{
	//cout << "On va compiler" << endl;	//pour test
	itr ++;
	if((*itr)=="-l")
	{
		//cout << "Le nom de la librarie est donnee" << endl;
		itr++;
		libraryname=(*itr);
		itr++;
		sourcename=(*itr);
	}
	else
	{
		//cout << "Le nom de la librairie n'est pas donnee" << endl; //pour test
		libraryname="";
		sourcename=(*itr);
	}
	return VHDLCOMP;
}

int commande_vhdlcomp(string &libraryname, string &sourcename)
{
	//cout << "On va compiler" << endl;	//pour test
	string commande;
	cin >> commande;
	if(commande=="-l")
	{
		//cout << "Le nom de la librarie est donnee" << endl;	//pour test
		cin >> libraryname;
		cin >> sourcename;
	}
	else
	{
		//cout << "Le nom de la librairie n'est pas donnee" << endl; //pour test
		libraryname="";
		sourcename=commande;
	}
	return VHDLCOMP;
}

//Permet de lire un fichier script comprenant les differentes commandes
int commande_source(string &sourcename, list<string> commandes, list<string>::iterator itr)
{
	//cout << "On va executer un script" << endl;	//pour test
	itr++;
	sourcename=(*itr);
	return SOURCE;
}

int commande_source(string &sourcename)
{
	//cout << "On va executer un script" << endl;	//pour test
	cin >> sourcename;
	return SOURCE;
}

//Permet d'executer les differentes commandes contenues dans un script
int execute_script(string nom_script)
{
	cout << "--Execute script " << nom_script << "--" << endl;
	ifstream fichier_script(nom_script.c_str(), ios::in);  // on ouvre en lecture
	if(!fichier_script)  // si l'ouverture n'a pas fonctionnee
	{
		cerr << "!!Impossible d'ouvrir le fichier " << nom_script << " !!" << endl;
		return 0;
	}

	//Traitement du fichier
	string buffer ="";
	string libraryname;
	string sourcename;
	list<Lexeme*> lex;
	list<string> commandes;
	// cout << "Le fichier script va être lu" << endl;

	while(!fichier_script.eof())
	{
		fichier_script >> buffer;	//on lit une ligne
		cout << "-" << buffer << endl;
		commandes.push_back(buffer);
	}

    //Traitement des commandes
	list<string>::iterator itr=commandes.begin();
	bool err_tree=false;
	int err_pars;
	tree<Lexeme*> parseur;
	for(itr=commandes.begin();itr!=commandes.end();itr++)
	{
		int commande=commande_vhdl(libraryname,sourcename,commandes,itr);
		int nligne=0;
		switch(commande)
		{
			case COMPARE :
				if(fichiers_identiques(sourcename,libraryname,nligne))
					cout << sourcename << " et " << libraryname << " sont identiques." << endl;
				else
					cout << "!!!" << sourcename << " et " << libraryname << " sont differents ligne " << nligne << "!!!" << endl;
				break;
			case VHDLCOMP :
				lex.clear();
				if(!vhdlcomp(libraryname,sourcename,lex))
				{
					cout << endl << "--Parseur en cours--" << endl;
					err_pars=parseur_root(lex);
					print_lex(lex);

					if(err_pars==1)
					{
						cout << endl << "--Creation de l'arbre--" << endl;
						parseur = createTree(lex,err_tree);
						cout << endl;
						if(!err_tree)
						{
							cout << endl << "--Impression de l'arbre--" << endl;
							printTree(parseur);
							if(libraryname!="")
								saveTree(parseur,libraryname);
						}
						cout << endl << "--Fin de compilation--" << endl << endl;
					}
					else
					{
						cout << endl << "--Erreur de syntaxe--" << endl;
						cout <<  "--Compilation avortée--" << endl << endl;
					}
				}
				else
				{
					cout << endl << "--Erreur orthographique--" << endl;
					cout <<  "--Compilation avortée--" << endl << endl;
				}
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
