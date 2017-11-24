#include "../Header/Lexeur.h"

using namespace std;

int vhdlcomp(string libraryname, string sourcename, list<Lexeme*>& list_lex)
{
	//Ouverture du fichier
	ifstream fichier(sourcename.c_str(), ios::in);  // on ouvre en lecture
	if(!fichier)  // si l'ouverture n'a pas fonctionnÃÂ©e
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
		stock_lexemes(buffer,n_ligne,list_lex);		//on sÃÂ©pare les lexemes
		n_ligne++;
	}while(!fichier.eof());


	print_lex(list_lex);
	cout << endl <<  "Nombre de lignes dans le fichier : " << n_ligne-1 << endl;		//pour test
	return 0;
}

void print_lex(list<Lexeme*>& list_lex)
{
	list<Lexeme*>::iterator itr;
	for(itr=list_lex.begin();itr!=list_lex.end();itr++)
	{
		cout << **itr;
	}

}

//Fonction pour stocker chaque lexÃÂ¨me d'une ligne dans une liste, avec leur numÃÂ©ro de ligne
//PrÃÂ©-condition : les lexÃÂ¨mes doivent ÃÂªtre sÃÂ©parÃÂ©s avec des espaces
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

		if(verif(*lex_buff,&is_com,&ligne_com))
			cout << "Erreur lexicale detectee" << endl;
			//exit(-1);

		Lex_VHDL.push_back(lex_buff);
		ch_buff = strtok(NULL," ");
	}
}

//Fonction pour lire une ligne dans un fichier et lui ajouter des espaces entre les caractÃÂ¨res
//Retourne la ligne lue et formatÃÂ©e
string read_line(ifstream& fichier)
{
	//RÃÂ©cupÃÂ©ration de la ligne
	string buffer="";
	getline(fichier, buffer);	//traitement d'une ligne ÃÂ  chaque boucle
	buffer+="\n"; //on rajoute un espace pour bien ÃÂªtre sÃÂ»r de sÃÂ©parer la fin de la ligne du dÃÂ©but de la ligne suivante  
	//cout << buffer << endl;	//pour test

	//Reformatage de la ligne
	minus_string(buffer);		//CaractÃÂ¨res passÃÂ©s en miniscule
	//buffer = add_space_on_string(buffer, buffer.length());	//Ajout des espaces
	//cout << buffer << endl;	//pour test
	
	return add_space_on_string(buffer, buffer.length());
}

//Fonction pour ajouter des espaces sur un string
//Retourne un nouveau string reformatÃÂ©
string add_space_on_string(string str, int length)
{
	int i=0;		//incrÃÂ©ment pour str
	char temp[length*2];	//pour la recopie : dans le pire cas, on ajoute un espace entre chaque caractÃÂ¨re, donc length*2
	int j=0;		//incrÃÂ©ment pour temp

	while(str[i]!='\0')	//boucle tant qu'on n'est pas arrivÃÂ© ÃÂ  la fin du string
	{
		if(str[i]=='	'||str[i]=='\n')	// la tabulation et le saut de ligne sont traitÃÂ©s comme un espace "classique"
		{
			str[i]=' ';
		}

		if(j==0)	// Premier caractÃÂ¨re recopiÃÂ© : le premier caractÃÂ¨re non-espace
		{
			if(!(str[i]==' '))
			{
				temp[j]=str[i];
				j++;

				if(is_ponctuation2char(str[i],str[i+1]))	//Si le lexÃÂ¨me est une ponctuation ÃÂ  2 chars : on recopie le 2e caractÃÂ¨re
				{
					i++;
					temp[j]=str[i];
					j++;
				}

				if(is_ponctuation(str[i])&&!(str[i+1]==' '))	//Si ponctuation & pas d'espace aprÃÂ¨s : on rajoute un espace
				{
					temp[j]=' ';
					j++;
				}
			}
		}
		else		// CaractÃÂ¨res suivants
		{
			if(is_ponctuation(str[i]))	//si ponctuation
			{
				//Recopie du premier caractÃÂ¨re

				if(temp[j-1]==' ')	//si on a recopiÃÂ© un espace auparavent, on ne recopie que la ponctuation
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

				//Tests : rajouter un espace ? Recopier un deuxiÃÂ¨me caractÃÂ¨re ?

				if(is_ponctuation2char(str[i], str[i+1]))	//si les 2 ponctuations qui se suivent sont une affectation ou un commentaire, on recopie directement le caractÃÂ¨re suivant
				{
					i++;		//caractÃÂ¨re suivant
					temp[j]=str[i]; //on recopie
					j++;

				}

				if(str[i+1]!=' ') // si le caractÃÂ¨re suivant le lexÃÂ¨me n'est pas un espace, on en rajoute un
				{
					temp[j]=' ';
					j++;
				}
			}
			else	//si pas ponctuation
			{
				if(!(str[i]==' '&&temp[j-1]==' '))	//si on a dÃÂ©jÃÂ  stockÃÂ© un espace prÃÂ©cÃÂ©demment, on n'en stocke plus
				{
					temp[j]=str[i];			//dans tous les autres cas, on recopie
					j++;
				}
			}
		}
		i++;	//on passe ÃÂ  la recopie du caractÃÂ¨re suivant
	}
	temp[j]='\0';	//sortie de la boucle = fin de chaÃÂ®ne, on le signale dans temp

	//cout << str << endl;		//Pour le test
	//cout << temp << endl;
	str = temp;
	return str;
}
