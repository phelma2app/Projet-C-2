#include <iostream>
#include <string>
#include <fstream>
#include "../Header/utilities.h"

using namespace std;

void delete_com(list<Lexeme*>& list_lex)
{
	list<Lexeme*>::iterator itr;
	for(itr=list_lex.begin();itr!=list_lex.end();itr++)
	{
		while((*itr)->getType()==COMMENTAIRE)
		{
			itr=list_lex.erase(itr);
		}
	}
}

//Fonction pour mettre toutes les lettres en minuscule, a faire en preambule de toute analyse sur le string
void minus_string(string &to_minus)
{
	for(int i=0;i<to_minus.length();i++)
	{
		to_minus[i]=tolower(to_minus[i]);
	}
}

//Fonction pour tester la ponctuation
bool is_ponctuation(char ch_test)
{
	if(ch_test==','||ch_test=='.'||ch_test=='\n'||ch_test==';'||ch_test==':'||ch_test=='('||ch_test==')'||ch_test=='['||ch_test==']'||ch_test=='!'||ch_test=='-'||ch_test=='+'||ch_test=='<'||ch_test=='='||ch_test=='>'||ch_test=='"'||ch_test=='\'')	//Liste des ponctuations
	{
		return true;
	}
	return false;
}

//Fonction pour tester la double ponctuation
bool is_ponctuation2char(char ch_test1, char ch_test2)
{
	if((ch_test1==':'&&ch_test2=='=')||(ch_test1=='='&&ch_test2=='>')||(ch_test1=='<'&&ch_test2=='=')||(ch_test1=='-'&&ch_test2=='-'))
	{
		return true;
	}
	return false;
}

//Lettre ?
bool is_letter(char ch_test)
{
	if(ch_test>='a'&&ch_test<='z')
	{
		return true;
	}
	return false;
}

//Nombre ?
bool is_number(char ch_test)
{
	if(ch_test>='0'&&ch_test<='9')
	{
		return true;
	}
	return false;
}

//Fonction pour tester le type 
bool is_type(string st_test)
{
	if(st_test=="std_logic"||st_test=="std_logic_vector"||st_test=="bit"||st_test=="bit_vector")	
	{
		return true;
	}
	return false;
}


//Fonction pour comparer les fichiers

bool fichiers_identiques (std::string fichier1, std::string fichier2){
    	ifstream fich1(fichier1.c_str(),ios::in);
    	ifstream fich2(fichier2.c_str(),ios::in);
    	if (fich1 && fich2 ){
		string lignef1;
		cout << "on est dans le if" << endl ;
		string lignef2;
		while (getline (fich1, lignef1) && getline(fich2 , lignef2)){
			cout << "on est dans le while" << endl ; 
			cout << lignef1 << endl;
			cout << lignef2 << endl;
			if (lignef1.compare(lignef2)!=0) {
	       			return false;
	        	}
		}
	}
	return true;
}
