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
		case ARCHITECTURE_BEGIN:
		    return "Begin Architecture";
		case ARCHITECTURE_END:
		    return "End Architecture";
		case ARCHITECTURE_ID:
		    return "Identifiant Architecture";
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
		case LIBRARY_END:
			return "End Library";
		case LIBRARY_ID :
			return "Identifiant Librairie";
		case MOT :
			return "Mot";
		case NOMBRE :
			return "Nombre";
		case PROCESS:
		    return "Process";
		case PROCESS_BEGIN:
		    return "Begin Process";
		case PROCESS_END:
		    return "End Process";
		case PROCESS_ID:
		    return "Identifiant Process";
		case PROCESS_SENSIBILITY:
		    return "Process Sensibility";
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
		case PORT_VECTOR:
		    return "Port Vector";
		case PORT_VECTOR_BEGIN:
		    return "Begin Port Vector";
		case PORT_VECTOR_END:
		    return "End Port Vector";
		case PORT_VECTOR_SENSE:
		    return "Sense Port Vector";
		case SIGNAL:
		    return "Signal";
		case USE:
			return "Use";
		case USE_END:
			return "End Use";
		case USE_ID:
			return "Identifiant Use";
		default :
			return "Non Defini";
	}
}

ostream& operator << (ostream& out, const Lexeme& l)
{
	out << l.getLex() << "	|	";
	out << l.getLigne() << "	|	";
	out << l.afficheType() << endl;
	return out;
}
