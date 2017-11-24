#include "../Header/Console.h"

using namespace std;

//Commandes sur la console pour l'utilisateur
//Retourne un entier qui vaut 0 si erreur, sinon il renvoie une valeur associÃ©e Ã  la commande
int commande_vhdl(string &libraryname, string &sourcename)
{
	string commande;
	cin >> commande;

	//Commande utilisateur
	if(commande=="vhdlcomp")
	{
		if(commande_vhdlcomp(libraryname, sourcename)!=0)
		{
			return VHDLCOMP;
		}
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
