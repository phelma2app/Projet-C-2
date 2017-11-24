#ifndef LEXEME_H_
#define LEXEME_H_

#include <string>
#include <iostream>
#include "type_Lexeme.h"

using namespace std;

class Lexeme {
	friend ostream& operator << (ostream& out, const Lexeme& l);

private:
	string lex;
	int n_ligne;
	int type_lex;


public:
	Lexeme(string i_lex="", int i_n_ligne=0, int i_type=0):
		lex(i_lex),n_ligne(i_n_ligne),type_lex(i_type)
	{
	}

	virtual ~Lexeme();

	void setLex(string str) { lex=str; }
	string getLex() const { return lex; }

	void setLigne(int ligne) { n_ligne=ligne; }

	void setType(int type) { type_lex=type; }
	int getType() const { return type_lex; }
	int getLigne() const { return n_ligne; }
	string afficheType() const;

	void isPonctuation() { type_lex=PONCTUATION; }
	void isMot() { type_lex=MOT; }
	void isNombre() { type_lex=NOMBRE; }
	void isCommentaire() { type_lex=COMMENTAIRE; }
};

#endif /* LEXEME_H_ */
