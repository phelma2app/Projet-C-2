#ifndef LEXEME_H_
#define LEXEME_H_

#include <string>
#include <iostream>

using namespace std;

#define NON_DEFINI 0
#define	PONCTUATION NON_DEFINI+1
#define MOT PONCTUATION+1
#define NOMBRE MOT+1
#define COMMENTAIRE NOMBRE+1


class Lexeme {
	friend ostream& operator << (ostream& out, Lexeme l);

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
	int getLigne() const { return n_ligne; }

	void setType(int type) { type_lex=type; }
	int getType() const { return type_lex; }
	string afficheType() const;

	void isPonctuation() { type_lex=PONCTUATION; }
	void isMot() { type_lex=MOT; }
	void isNombre() { type_lex=NOMBRE; }
	void isCommentaire() { type_lex=COMMENTAIRE; }


};

#endif /* LEXEME_H_ */
