#include "../Header/Lexeme.h"
#include <string>
#include <iostream>

using namespace std;

Lexeme::~Lexeme() {
	// TODO Auto-generated destructor stub
}

string Lexeme::afficheType() const
{
	switch(type_lex)
	{
		case ARCHITECTURE :
			return "Architecture";		
		case COMMENTAIRE :
			return "Commentaire";
		case ENTITY :
			return "Entity";
		case ENTITY_END :
			return "End Entity";
		case ENTITY_ID :
			return "Identifiant Entity";
		case LIBRARY :
			return "Library";
		case MOT :
			return "Mot";
		case NOMBRE :
			return "Nombre";
		case PONCTUATION :
			return "Ponctuation";
		case PORT :
			return "Port";
		case PORT_END:
			return "End Port";
		case PORT_ID:
			return "Identifiant Port";
		case PORT_ID_END:
			return "End Identifiant Port";
		case PORT_IN:
			return "Port In";
		case PORT_INOUT :
			return "Port In/Out";
		case PORT_OUT:
			return "Port Out";
		case PORT_TYPE:
			return "Type Port";
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
