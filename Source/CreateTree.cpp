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
				constructTreeOnArchitecture(tr,childroot,lex,itr);
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

//-------------------------------------------------------------ARCHITECTURE---------------------------------------------------------

void constructTreeOnArchitecture(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& architecture, list<Lexeme*>& l, list<Lexeme*>::iterator begin_archi)
{
	cout << "Tree Architecture" << endl;

	list<Lexeme*>::iterator itr=begin_archi;
	tree<Lexeme*>::pre_order_iterator childarchi;
	while((*itr)->getType()!=ARCHITECTURE_END)
	{
		switch((*itr)->getType())
		{
			case ARCHITECTURE_ID:
				childarchi=tr.append_child(architecture,*itr);
				constructTreeOnArchitectureID(tr,childarchi,l,itr);
				break;
			default:
				break;
		}
		itr++;
	}
}

void constructTreeOnArchitectureID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& architectureid, list<Lexeme*>& l, list<Lexeme*>::iterator begin_archi_id)
{
	cout << "Tree Architecture ID" << endl;

	list<Lexeme*>::iterator itr=begin_archi_id;
	tree<Lexeme*>::pre_order_iterator childarchiid;
	while((*itr)->getType()!=ARCHITECTURE_END)
	{
		switch((*itr)->getType())
		{
            case PROCESS:
                childarchiid=tr.append_child(architectureid,*itr);
                constructTreeOnProcess(tr,childarchiid,l,itr);
                break;
			case SIGNAL:
				childarchiid=tr.append_child(architectureid,*itr);
//				constructTreeOnSignal(tr,childarchiid,l,itr);       //A construire par la suite
				break;
			default:
				break;
		}
		itr++;
	}
}

void constructTreeOnProcess(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& process, list<Lexeme*>& l, list<Lexeme*>::iterator begin_process)
{
	cout << "Tree Architecture ID" << endl;

	list<Lexeme*>::iterator itr=begin_process;
	tree<Lexeme*>::pre_order_iterator childprocess;
	while((*itr)->getType()!=PROCESS_END)
	{
		switch((*itr)->getType())
		{
            case PROCESS_BEGIN:
                childprocess=tr.append_child(process,*itr);
                break;
			case PROCESS_ID:
                childprocess=tr.append_child(process,*itr);
				break;
            case SENSIBILITY_SIGNAL:
                childprocess=tr.append_child(process,*itr);
				break;
			default:
				break;
		}
		itr++;
	}
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
	bool defineLibrary=false;
	while((*itr)->getType()!=LIBRARY_END)
	{
		switch((*itr)->getType())
		{
			case LIBRARY_ID:
				childlibrary=tr.append_child(library,*itr);
				defineLibrary=true;
                break;
			case USE:
			    if(defineLibrary)
                {
                    //constructTreeOnUse(tr,library,l,itr);
                }
                else
                {
                    cout << "Erreur : appel de use sans avoir de librairie definie" << endl;
                }
                break;
			default:
				break;
		}
		itr++;
	}
}

/*
void constructTreeOnUse(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& library, list<Lexeme*>& l, list<Lexeme*>::iterator begin_use)
{
	cout << "Tree Use" << endl;

	list<Lexeme*>::iterator itr=begin_use;
	tree<Lexeme*>::pre_order_iterator library_id,childuse,buf,use;
	buf=library;
	bool libraryfound=false;
	while((*itr)->getType()!=USE_END)
	{
		switch((*itr)->getType())
		{
            case LIBRARY_ID:
                library_id=library.first_child();
                do
                {
                    if(*(library_id)->getLex()==(*itr)->getLex)
                    {
                        libraryfound=true;
                    }
                    library_id=library_id.next_sibling();
                } while(library_id!=library.last_child());
                if(*(library_id)->getLex()==(*itr)->getLex)
                {
                    libraryfound=true;
                }
                break;
			case USE_ID:
                if(libraryfound)
                {
                    childuse=tr.append_child(buf,*itr);
                    buf=childuse;
                }
                else
                {
                    cout << "Erreur : librairie non définie avant le use" << endl;
                }
                break;
			default:
				break;
		}
		itr++;
	}
}
*/


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
				constructTreeOnPortId(tr,childport,l,itr);
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
            case PORT_VECTOR:
                childportid=tr.append_child(portid,*itr);
                constructTreeOnPortVector(tr,childportid,l,itr);
			default:
				break;
		}
		itr++;
	}
}

void constructTreeOnPortVector(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& portvec, list<Lexeme*>& l, list<Lexeme*>::iterator begin_portvec)
{
    cout << "Tree Port Vector" << endl;

	list<Lexeme*>::iterator itr=begin_portid;
	tree<Lexeme*>::pre_order_iterator childportvec;
	while((*itr)->getType()!=PORT_VECTOR_END)
	{
		switch((*itr)->getType())
		{
            case PORT_VECTOR_BEGIN:
                childportvec=tr.append_child(portvec,*itr);
                break;
            case PORT_VECTOR_SENSE:
                childportvec=tr.append_child(portvec,*itr);
                break;
            case PORT_VECTOR_END:
                childportvec=tr.append_child(portvec,*itr);
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
