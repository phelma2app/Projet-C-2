#include "Lexeme.h"
#include <string>
#include <iostream>

grdjojh<fauiuyuiyui

using namespace std;

Lexeme::~Lexeme() {
	// TODO Auto-generated destructor stub
}

string Lexeme::afficheType() const
{
	switch(type_lex)
	{
		case PONCTUATION :
			return "Ponctuation";
		case MOT :
			return "Mot";
		case NOMBRE :
			return "Nombre";
		case COMMENTAIRE :
			return "Commentaire";
		default :
			return "Non Defini";
	}
}

ostream& operator << (ostream& out, Lexeme l)
{
	out << l.getLex() << "	|	";
	out << l.getLigne() << "	|	";
	out << l.afficheType() << endl;
	return out;
}
