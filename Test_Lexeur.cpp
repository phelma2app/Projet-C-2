#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "utilities.h"
#include "Lexeme.h"

using namespace std;

string read_line(ifstream& fichier);
string add_space_on_string(string str, int length);
void stock_lexemes(string buffer, int ligne, list<Lexeme*>& Lex_VHDL);
int commande_vhdl(string &libraryname, string &sourcename);

int main ()
{
	string libraryname;
	string sourcename;

	if(commande_vhdl(libraryname,sourcename)!=0)
	{
		cout << "Erreur : commande inconnue" << endl;
		return 1;
	}

	//Ouverture du fichier
	ifstream fichier(sourcename.c_str(), ios::in);  // on ouvre en lecture
	if(!fichier)  // si l'ouverture n'a pas fonctionnée
	{
		cerr << "Impossible d'ouvrir le fichier " << sourcename << " !" << endl;
		return 1;
	}

	//Traitement du fichier
	list<Lexeme*> list_lex;
	int n_ligne=0;
	do
	{
		string buffer ="";
		buffer = read_line(fichier);	//on lit une ligne
		stock_lexemes(buffer,n_ligne,list_lex);		//on sépare les lexemes
		n_ligne++;
	}while(!fichier.eof());

	list<Lexeme*>::iterator itr;

	for(itr=list_lex.begin();itr!=list_lex.end();itr++)
	{
		cout << **itr;
	}
	cout << endl <<  "Nombre de lignes dans le fichier : " << n_ligne-1;		//pour test
}

//Commandes sur la console pour l'utilisateur
//Retourne un entier qui vaut 0 si les commandes ont été comprises
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
			cout << "Le nom de la librarie est donné" << endl;	//pour test
			cin >> libraryname;
			cin >> sourcename;
		}
		else
		{
			cout << "Le nom de la librairie n'est pas donné" << endl; //pour test
			sourcename=commande;
		}
	}
	else
	{
		cout << "Erreur : commande inconnue." << endl;
		return 1;
	}
	return 0;
}

//Fonction pour stocker chaque lexème d'une ligne dans une liste, avec leur numéro de ligne
//Pré-condition : les lexèmes doivent être séparés avec des espaces
void stock_lexemes(string buffer, int ligne, list<Lexeme*>& Lex_VHDL)
{
	char* ch_buff;	//Buffer
	ch_buff = strtok(&buffer[0]," ");
	while(ch_buff!=NULL)
	{
		//	cout << ch_buff << endl;	//pour test
		Lexeme *lex_buff = new Lexeme(ch_buff,ligne,0);
		Lex_VHDL.push_back(lex_buff);
		ch_buff = strtok(NULL," ");
	}
}

//Fonction pour lire une ligne dans un fichier et lui ajouter des espaces entre les caractères
//Retourne la ligne lue et formatée
string read_line(ifstream& fichier)
{
	//Récupération de la ligne
	string buffer="";
	getline(fichier, buffer);	//traitement d'une ligne à chaque boucle
	buffer+="\n"; //on rajoute un espace pour bien être sûr de séparer la fin de la ligne du début de la ligne suivante  
	//cout << buffer << endl;	//pour test

	//Reformatage de la ligne
	minus_string(buffer);		//Caractères passés en miniscule
	//buffer = add_space_on_string(buffer, buffer.length());	//Ajout des espaces
	//cout << buffer << endl;	//pour test
	
	return add_space_on_string(buffer, buffer.length());
}

//Fonction pour ajouter des espaces sur un string
//Retourne un nouveau string reformaté
string add_space_on_string(string str, int length)
{
	int i=0;		//incrément pour str
	char temp[length*2];	//pour la recopie : dans le pire cas, on ajoute un espace entre chaque caractère, donc length*2
	int j=0;		//incrément pour temp

	while(str[i]!='\0')	//boucle tant qu'on n'est pas arrivé à la fin du string
	{
		if(str[i]=='	'||str[i]=='\n')	// la tabulation et le saut de ligne sont traités comme un espace "classique"
		{
			str[i]=' ';
		}

		if(j==0)	// Premier caractère recopié : le premier caractère non-espace
		{
			if(!(str[i]==' '))
			{
				temp[j]=str[i];
				j++;

				if(is_ponctuation2char(str[i],str[i+1]))	//Si le lexème est une ponctuation à 2 chars : on recopie le 2e caractère
				{
					i++;
					temp[j]=str[i];
					j++;
				}

				if(is_ponctuation(str[i])&&!(str[i+1]==' '))	//Si ponctuation & pas d'espace après : on rajoute un espace
				{
					temp[j]=' ';
					j++;
				}
			}
		}
		else		// Caractères suivants
		{
			if(is_ponctuation(str[i]))	//si ponctuation
			{
				//Recopie du premier caractère

				if(temp[j-1]==' ')	//si on a recopié un espace auparavent, on ne recopie que la ponctuation
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

				//Tests : rajouter un espace ? Recopier un deuxième caractère ?

				if(is_ponctuation2char(str[i], str[i+1]))	//si les 2 ponctuations qui se suivent sont une affectation ou un commentaire, on recopie directement le caractère suivant
				{
					i++;		//caractère suivant
					temp[j]=str[i]; //on recopie
					j++;

				}

				if(str[i+1]!=' ') // si le caractère suivant le lexème n'est pas un espace, on en rajoute un
				{
					temp[j]=' ';
					j++;
				}
			}
			else	//si pas ponctuation
			{
				if(!(str[i]==' '&&temp[j-1]==' '))	//si on a déjà stocké un espace précédemment, on n'en stocke plus
				{
					temp[j]=str[i];			//dans tous les autres cas, on recopie
					j++;
				}
			}
		}
		i++;	//on passe à la recopie du caractère suivant
	}
	temp[j]='\0';	//sortie de la boucle = fin de chaîne, on le signale dans temp

	//cout << str << endl;		//Pour le test
	//cout << temp << endl;
	str = temp;
	return str;
}
