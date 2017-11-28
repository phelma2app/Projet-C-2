#$@  	Le nom de la cible
#$< 	Le nom de la premiÃÂ¨re dÃÂ©pendance
#$^ 	La liste des dÃÂ©pendances
#$* 	Le nom du fichier sans suffixe

CC=g++ -std=c++11

DIR=/users/phelma/phelma2016/margotan/Documents/ProjetC/ProjetC-master
SRCDIR=$(DIR)/Source

CFLAGS=-g -I$(DIR)/Header 
LDFLAGS=

SRC= $(SRCDIR)/main.cpp $(SRCDIR)/Console.cpp $(SRCDIR)/CreateTree.cpp $(SRCDIR)/Lexeme.cpp $(SRCDIR)/Lexeur.cpp $(SRCDIR)/parseur.cpp $(SRCDIR)/utilities.cpp $(SRCDIR)/Verif_lex.cpp

OBJ=$(SRC:.cpp=.o)

all: TestLexeme 

TestLexeme: 
	$(shell $(CC) $(SRC) -o TestLex)
	
#%.o	:%.cpp
#	$(CC) -c $< $(CFLAGS)

clean :
	rm -f $(OBJ)  *~
