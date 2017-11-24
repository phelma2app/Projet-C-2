#include "../Header/CreateTree.h"

using namespace std;

//-------------------------------------------------------------ROOT---------------------------------------------------------

tree<Lexeme*> createTree(list<Lexeme*>& lex)
{
	tree<Lexeme*> tr;
	tree<Lexeme*>::pre_order_iterator top=tr.begin();
	tree<Lexeme*>::pre_order_iterator root,childroot;
	Lexeme* l=new Lexeme("_root",0,NON_DEFINI);
	root=tr.insert(top,l);

	cout << "Tree Root" << endl;

	list<Lexeme*>::iterator itr;
	for(itr=lex.begin(); itr!=lex.end(); itr++)
	{
		switch((*itr)->getType())
		{
			case ARCHITECTURE:
				childroot=tr.append_child(root,*itr);
				break;
			case ENTITY:
				childroot=tr.append_child(root,*itr);
				constructTreeOnEntity(tr,childroot,lex,itr);
				break;			
			case LIBRARY:
				childroot=tr.append_child(root,*itr);
				break;
			default:
				break;
		}
	}
	return tr;
}

//-------------------------------------------------------------ENTITY---------------------------------------------------------

void constructTreeOnEntity(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& entity, list<Lexeme*>& l, list<Lexeme*>::iterator begin_entity)
{
	cout << "Tree Entity" << endl;

	list<Lexeme*>::iterator itr=begin_entity;
	tree<Lexeme*>::pre_order_iterator childentity;
	while((*itr)->getType()!=ENTITY_END)
	{
		switch((*itr)->getType())
		{
			case ENTITY_ID:
				childentity=tr.append_child(entity,*itr);
				constructTreeOnEntityID(tr,childentity,l,itr);
				break;
			default:
				break;
		}
		itr++;
	}
}

void constructTreeOnEntityID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& entityid, list<Lexeme*>& l, list<Lexeme*>::iterator begin_entityid)
{
	cout << "Tree Entity ID" << endl;

	list<Lexeme*>::iterator itr=begin_entityid;
	tree<Lexeme*>::pre_order_iterator childentityid;
	while((*itr)->getType()!=ENTITY_END)
	{
		switch((*itr)->getType())
		{
			case PORT:
				childentityid=tr.append_child(entityid,*itr);
				constructTreeOnPort(tr,childentityid,l,itr);
				break;
			default:
				break;
		}
		itr++;
	}
}

//-------------------------------------------------------------LIBRARY---------------------------------------------------------
void constructTreeOnLibrary(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& library, list<Lexeme*>& l, list<Lexeme*>::iterator begin_library)
{
	cout << "Tree Library" << endl;

	list<Lexeme*>::iterator itr=begin_library;
	tree<Lexeme*>::pre_order_iterator childlibrary;
	while((*itr)->getType()!=LIBRARY_END)
	{
		switch((*itr)->getType())
		{
			case LIBRARY_ID:
				childlibrary=tr.append_child(library,*itr);
				break;
			default:
				break;
		}
		itr++;
	}
}

void constructTreeOnUse(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& use, list<Lexeme*>& l, list<Lexeme*>::iterator begin_use)
{
	cout << "Tree Library ID" << endl;

	list<Lexeme*>::iterator itr=begin_use;
	tree<Lexeme*>::pre_order_iterator childuse,buf;
	buf=use;
	while((*itr)->getType()!=USE_END)
	{
		switch((*itr)->getType())
		{
			case USE_ID:
				childuse=tr.append_child(buf,*itr);
				break;
			default:
				break;
		}
		itr++;
	}
}



//-------------------------------------------------------------PORT---------------------------------------------------------

void constructTreeOnPort(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& port, list<Lexeme*>& l, list<Lexeme*>::iterator begin_port)
{
	cout << "Tree Port" << endl;

	list<Lexeme*>::iterator itr=begin_port;
	tree<Lexeme*>::pre_order_iterator childport;
	while((*itr)->getType()!=PORT_END)
	{
		switch((*itr)->getType())
		{
			case PORT_ID:
				childport=tr.append_child(port,*itr);
				//constructTreeOnPortId(tr,childport,l,itr);
				break;
			default:
				break;
		}
		itr++;
	}
}

void constructTreeOnPortId(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& portid, list<Lexeme*>& l, list<Lexeme*>::iterator begin_portid)
{
	cout << "Tree Port ID" << endl;

	list<Lexeme*>::iterator itr=begin_portid;
	tree<Lexeme*>::pre_order_iterator childportid;
	while((*itr)->getType()!=PORT_ID_END)
	{
		switch((*itr)->getType())
		{
			case PORT_IN:
				childportid=tr.append_child(portid,*itr);
				break;
			case PORT_INOUT:
				childportid=tr.append_child(portid,*itr);
				break;
			case PORT_OUT:
				childportid=tr.append_child(portid,*itr);
				break;
			case PORT_TYPE:
				childportid=tr.append_child(portid,*itr);
				break;
			default:
				break;
		}
		itr++;
	}
}


//-------------------------------------------------------------PRINT---------------------------------------------------------

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
		cout << (*itr)->getLex() << endl;
		++itr;
	}
	
}
