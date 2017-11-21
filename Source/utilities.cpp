#include <iostream>
#include <string>
#include "../Header/utilities.h"


using namespace std;


//Fonction pour mettre toutes les lettres en minuscule, Ã  faire en prÃ©ambule de toute analyse sur le string
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
	if(ch_test==','||ch_test=='\n'||ch_test==';'||ch_test==':'||ch_test=='('||ch_test==')'||ch_test=='['||ch_test==']'||ch_test=='!'||ch_test=='-'||ch_test=='+'||ch_test=='<'||ch_test=='='||ch_test=='>'||ch_test=='\'')	//Liste des ponctuations
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
	if(st_test=="std_logic"||st_test=="std_logic_vector")	
	{
		return true;
	}
	return false;
}
