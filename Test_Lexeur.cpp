#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Header/utilities.h"
#include "../Header/Lexeme.h"
#include "../Header/Verification_orthographe_ajout_etiquette.h"

using namespace std;

string read_line(ifstream& fichier);
string add_space_on_string(string str, int length);
void stock_lexemes(string buffer, int ligne, list<Lexeme*>& Lex_VHDL);
int commande_vhdl(string &libraryname, string &sourcename);
int vhdlcomp(string libraryname, string sourcename, list<Lexeme*>& list_lex);

//#include <algorithm>
//#include "tree.hh"

int main()
{
	string libraryname;
	string sourcename;
	
	list<Lexeme*> list_lex;
	while(commande_vhdl(libraryname,sourcename)!=0);
	vhdlcomp(libraryname,sourcename,list_lex);
	
}

int vhdlcomp(string libraryname, string sourcename, list<Lexeme*>& list_lex)
{
	//Ouverture du fichier
	ifstream fichier(sourcename.c_str(), ios::in);  // on ouvre en lecture
	if(!fichier)  // si l'ouverture n'a pas fonctionnÃ©e
	{
		cerr << "Impossible d'ouvrir le fichier " << sourcename << " !" << endl;
		return 1;
	}

	//Traitement du fichier
	int n_ligne=0;
	do
	{
		string buffer ="";
		buffer = read_line(fichier);	//on lit une ligne
		stock_lexemes(buffer,n_ligne,list_lex);		//on sÃ©pare les lexemes
		n_ligne++;
	}while(!fichier.eof());

	list<Lexeme*>::iterator itr;

	for(itr=list_lex.begin();itr!=list_lex.end();itr++)
	{
		cout << **itr;
	}
	cout << endl <<  "Nombre de lignes dans le fichier : " << n_ligne-1;		//pour test
	return 0;
}

//Commandes sur la console pour l'utilisateur
//Retourne un entier qui vaut 0 si les commandes ont Ã©tÃ© comprises
int commande_vhdl(string &libraryname, string &sourcename)
{
	string commande;
	cin >> commande;

	//Commande utilisateur
	if(commande=="vhdlcomp")
	{
		cout << "On va compiler" << endl;	//pour test
		cin >> commande;
		if(commande=="-l")
		{
			cout << "Le nom de la librarie est donnÃ©" << endl;	//pour test
			cin >> libraryname;
			cin >> sourcename;
		}
		else
		{
			cout << "Le nom de la librairie n'est pas donnÃ©" << endl; //pour test
			sourcename=commande;
		}
	}
	else
	{
		cout << "Erreur : commande inconnue" << endl;
		return 1;
	}
	return 0;
}

//Fonction pour stocker chaque lexÃ¨me d'une ligne dans une liste, avec leur numÃ©ro de ligne
//PrÃ©-condition : les lexÃ¨mes doivent Ãªtre sÃ©parÃ©s avec des espaces
void stock_lexemes(string buffer, int ligne, list<Lexeme*>& Lex_VHDL)
{
	char* ch_buff;	//Buffer
	ch_buff = strtok(&buffer[0]," ");
	int ligne_com=0;
	bool is_com=false;
	while(ch_buff!=NULL)
	{
		//	cout << ch_buff << endl;	//pour test
		Lexeme *lex_buff = new Lexeme(ch_buff,ligne,0);

		if(!verif(*lex_buff,&is_com,&ligne_com))
			cout << "Erreur lexicale detectee" << endl;
			//exit(-1);

		Lex_VHDL.push_back(lex_buff);
		ch_buff = strtok(NULL," ");
	}
}

//Fonction pour lire une ligne dans un fichier et lui ajouter des espaces entre les caractÃ¨res
//Retourne la ligne lue et formatÃ©e
string read_line(ifstream& fichier)
{
	//RÃ©cupÃ©ration de la ligne
	string buffer="";
	getline(fichier, buffer);	//traitement d'une ligne Ã  chaque boucle
	buffer+="\n"; //on rajoute un espace pour bien Ãªtre sÃ»r de sÃ©parer la fin de la ligne du dÃ©but de la ligne suivante  
	//cout << buffer << endl;	//pour test

	//Reformatage de la ligne
	minus_string(buffer);		//CaractÃ¨res passÃ©s en miniscule
	//buffer = add_space_on_string(buffer, buffer.length());	//Ajout des espaces
	//cout << buffer << endl;	//pour test
	
	return add_space_on_string(buffer, buffer.length());
}

//Fonction pour ajouter des espaces sur un string
//Retourne un nouveau string reformatÃ©
string add_space_on_string(string str, int length)
{
	int i=0;		//incrÃ©ment pour str
	char temp[length*2];	//pour la recopie : dans le pire cas, on ajoute un espace entre chaque caractÃ¨re, donc length*2
	int j=0;		//incrÃ©ment pour temp

	while(str[i]!='\0')	//boucle tant qu'on n'est pas arrivÃ© Ã  la fin du string
	{
		if(str[i]=='	'||str[i]=='\n')	// la tabulation et le saut de ligne sont traitÃ©s comme un espace "classique"
		{
			str[i]=' ';
		}

		if(j==0)	// Premier caractÃ¨re recopiÃ© : le premier caractÃ¨re non-espace
		{
			if(!(str[i]==' '))
			{
				temp[j]=str[i];
				j++;

				if(is_ponctuation2char(str[i],str[i+1]))	//Si le lexÃ¨me est une ponctuation Ã  2 chars : on recopie le 2e caractÃ¨re
				{
					i++;
					temp[j]=str[i];
					j++;
				}

				if(is_ponctuation(str[i])&&!(str[i+1]==' '))	//Si ponctuation & pas d'espace aprÃ¨s : on rajoute un espace
				{
					temp[j]=' ';
					j++;
				}
			}
		}
		else		// CaractÃ¨res suivants
		{
			if(is_ponctuation(str[i]))	//si ponctuation
			{
				//Recopie du premier caractÃ¨re

				if(temp[j-1]==' ')	//si on a recopiÃ© un espace auparavent, on ne recopie que la ponctuation
				{
					temp[j]=str[i];
					j++;
				}
				else			//sinon, on ajoute un espace avant
				{
					temp[j]=' ';
					j++;
					temp[j]=str[i];
					j++;
				}

				//Tests : rajouter un espace ? Recopier un deuxiÃ¨me caractÃ¨re ?

				if(is_ponctuation2char(str[i], str[i+1]))	//si les 2 ponctuations qui se suivent sont une affectation ou un commentaire, on recopie directement le caractÃ¨re suivant
				{
					i++;		//caractÃ¨re suivant
					temp[j]=str[i]; //on recopie
					j++;

				}

				if(str[i+1]!=' ') // si le caractÃ¨re suivant le lexÃ¨me n'est pas un espace, on en rajoute un
				{
					temp[j]=' ';
					j++;
				}
			}
			else	//si pas ponctuation
			{
				if(!(str[i]==' '&&temp[j-1]==' '))	//si on a dÃ©jÃ  stockÃ© un espace prÃ©cÃ©demment, on n'en stocke plus
				{
					temp[j]=str[i];			//dans tous les autres cas, on recopie
					j++;
				}
			}
		}
		i++;	//on passe Ã  la recopie du caractÃ¨re suivant
	}
	temp[j]='\0';	//sortie de la boucle = fin de chaÃ®ne, on le signale dans temp

	//cout << str << endl;		//Pour le test
	//cout << temp << endl;
	str = temp;
	return str;
}
