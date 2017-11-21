#$@  	Le nom de la cible
#$< 	Le nom de la premiÃ¨re dÃ©pendance
#$^ 	La liste des dÃ©pendances
#$* 	Le nom du fichier sans suffixe

CC=g++ -std=c++11

DIR=/tp/xph2app/xph2app001/Documents/Projet-C-2/ProjetC-master
SRCDIR=$(DIR)/Source

CFLAGS=-g -I$(DIR)/Header 
LDFLAGS=

SRC= $(SRCDIR)/main.cpp $(SRCDIR)/Console.cpp $(SRCDIR)/CreateTree.cpp $(SRCDIR)/Lexeme.cpp $(SRCDIR)/Lexeur.cpp $(SRCDIR)/utilities.cpp $(SRCDIR)/Verification_orthographe_ajout_etiquette.cpp

OBJ=$(SRC:.cpp=.o)

all: TestLexeme 

TestLexeme: 
	$(shell $(CC) $(SRC) -o TestLex)
	
#%.o	:%.cpp
#	$(CC) -c $< $(CFLAGS)

clean :
	rm -f $(OBJ)  *~
