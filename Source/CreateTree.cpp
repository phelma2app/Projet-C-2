#include "../Header/CreateTree.h"

using namespace std;

void printTree(tree<Lexeme*> tr)
{
	tree<Lexeme*>::pre_order_iterator itr=tr.begin();
	if(itr!=tr.end())
		++itr;

	while(itr!=tr.end())
	{

		for(int i=0; i<tr.depth(itr); i++)
		{
			cout << " ";
		}
		cout << **itr << endl;
		++itr;
	}
	
}
