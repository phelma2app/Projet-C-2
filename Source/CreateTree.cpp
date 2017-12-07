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
				constructTreeOnArchitecture(tr,root,lex,itr);
				break;
			case ENTITY:
				constructTreeOnEntity(tr,root,lex,itr);
				break;
			case LIBRARY:
				constructTreeOnLibrary(tr,root,lex,itr);
				break;
			case USE:
				constructTreeOnUse(tr,root,lex,itr);
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
				constructTreeOnSignal(tr,childarchiid,l,itr);
				break;
			default:
				break;
		}
		itr++;
	}
}

void constructTreeOnProcess(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& process, list<Lexeme*>& l, list<Lexeme*>::iterator begin_process)
{
	cout << "Tree Process" << endl;

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
            		case PROCESS_SENSIBILITY:
                		childprocess=tr.append_child(process,*itr);
				break;
			default:
				break;
		}
		itr++;
	}
}


void constructTreeOnSignal(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& signal, list<Lexeme*>& l, list<Lexeme*>::iterator begin_signal)
{
	cout << "Tree Signal" << endl;

	list<Lexeme*>::iterator itr=begin_signal;
	tree<Lexeme*>::pre_order_iterator childsignal;
	while((*itr)->getType()!=SIGNAL_END)
	{
		switch((*itr)->getType())
		{
			case SIGNAL_ID:
                		childsignal=tr.append_child(signal,*itr);
				constructTreeOnSignalID(tr,childsignal,l,itr);
				break;
			default:
				break;
		}
		itr++;
	}
}

void constructTreeOnSignalID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& signalid, list<Lexeme*>& l, list<Lexeme*>::iterator begin_signalid)
{
	cout << "Tree Signal ID" << endl;

	list<Lexeme*>::iterator itr=begin_signalid;
	tree<Lexeme*>::pre_order_iterator childsignalid;
	while((*itr)->getType()!=SIGNAL_END)
	{
		switch((*itr)->getType())
		{
			case SIGNAL_TYPE:
                		childsignalid=tr.append_child(signalid,*itr);
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
			case TYPE_VECTOR:
				childportid=tr.append_child(portid,*itr);
				constructTreeOnVector(tr,childportid,l,itr);
				break;
			default:
				break;
		}
		itr++;
	}
}

//-------------------------------------------------------------LIBRARY---------------------------------------------------------

//Pour l'instant ne stocke rien : c'est use qui se charge de stocker la bonne librairie
void constructTreeOnLibrary(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& library, list<Lexeme*>& l, list<Lexeme*>::iterator begin_library)
{
	cout << "Tree Library" << endl;

	list<Lexeme*>::iterator itr=begin_library;
	tree<Lexeme*>::pre_order_iterator childlibrary;
	while((*itr)->getType()!=LIBRARY_END)
	{
		switch((*itr)->getType())
		{
			default:
				break;
		}
		itr++;
	}
}

//A faire : use qui cherche la bonne librairie (pour l'instant c'est lui qui la stocke)
void constructTreeOnUse(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& library, list<Lexeme*>& l, list<Lexeme*>::iterator begin_use)
{
	cout << "Tree Use" << endl;

	list<Lexeme*>::iterator itr=begin_use;
	tree<Lexeme*>::pre_order_iterator childuse,buf,library_id;
	buf=library;
	bool defineLibraryId=false;
	while((*itr)->getType()!=USE_END)
	{
		switch((*itr)->getType())
		{
			case LIBRARY_ID:
				if(!defineLibraryId)
				{
					defineLibraryId=true;
					library_id=tr.append_child(buf,*itr);
				    	buf=library_id;
				}
				break;
			case USE_ID:
				if(defineLibraryId)
				{
		            		childuse=tr.append_child(buf,*itr);
		            		buf=childuse;
				}				
				else
				{
				    cout << "Erreur : identifiant librairie non trouvee" << endl;
				}
                		break;
			default:
				break;
		}
		itr++;
	}
}



//-------------------------------------------------------------AUTRES---------------------------------------------------------


void constructTreeOnVector(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& vec, list<Lexeme*>& l, list<Lexeme*>::iterator begin_vec)
{
    cout << "Tree Vector" << endl;

	list<Lexeme*>::iterator itr=begin_vec;
	tree<Lexeme*>::pre_order_iterator childvec;
	while((*itr)->getType()!=TYPE_VECTOR_END)
	{
		switch((*itr)->getType())
		{
		    case TYPE_VECTOR_BEGIN:
		        childvec=tr.append_child(vec,*itr);
		        break;
		    case TYPE_VECTOR_SENSE:
		        childvec=tr.append_child(vec,*itr);
		        break;
		    case TYPE_VECTOR_END:
		        childvec=tr.append_child(vec,*itr);
               		break;
		    default:
			break;
		}
		itr++;
	}

	if((*itr)->getType()==TYPE_VECTOR_END)
		childportvec=tr.append_child(vec,*itr);
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

int saveTree(tree<Lexeme*> tr, string libraryname)
{
	ofstream fichier(libraryname, ios::out | ios::trunc);
	if(!fichier)
	{
		cout << "Erreur a l'ecriture de " << libraryname << endl;
		return 0;
	}
	tree<Lexeme*>::pre_order_iterator itr=tr.begin();
	if(itr!=tr.end())
		++itr;

	while(itr!=tr.end())
	{

		for(int i=0; i<tr.depth(itr); i++)
		{
			fichier << "	";
		}
		fichier << (**itr);
		++itr;
	}
}
