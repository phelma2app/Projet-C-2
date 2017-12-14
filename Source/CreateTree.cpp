#include "../Header/CreateTree.h"

using namespace std;

//-------------------------------------------------------------ROOT---------------------------------------------------------

//Fonction qui parcourt la liste de lexeme et quirange les Lexeme dans un arbre en fonction du type qui leur est associé
//Chaque fonction constructTree retourne un booléen qui permet de savoir si une erreur est détectée à la création de l'arbre
tree<Lexeme*> createTree(list<Lexeme*>& lex, bool& erreur)
{
	tree<Lexeme*> tr;
	tree<Lexeme*>::pre_order_iterator top=tr.begin();
	tree<Lexeme*>::pre_order_iterator root,childroot;
	Lexeme* l=new Lexeme("_root",0,NON_DEFINI);
	root=tr.insert(top,l);

	cout << "Tree Root" << endl;

    	erreur=false;
	list<Lexeme*>::iterator itr;
	for(itr=lex.begin(); itr!=lex.end(); itr++)
	{
		switch((*itr)->getType())
		{
			case ARCHITECTURE:
				erreur=constructTreeOnArchitecture(tr,root,lex,itr);
				break;
			case ENTITY:
				erreur=constructTreeOnEntity(tr,root,lex,itr);
				break;
			case LIBRARY:
				erreur=constructTreeOnLibrary(tr,root,lex,itr);
				break;
			case PACKAGE:
				erreur=constructTreeOnPackage(tr,root,lex,itr);
				break;
			case USE:
				erreur=constructTreeOnUse(tr,root,lex,itr);
				break;
			default:
				break;
		}
	if(erreur)
        {
            cout << "Erreur a la creation de l'arbre : operation avortee" << endl;
            return tr;
        }
	}
	return tr;
}

//-------------------------------------------------------------ARCHITECTURE---------------------------------------------------------
bool constructTreeOnAffectationSignal(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& affectation, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Affectation Signal" << endl;
	itr--;	//Pour reperer l'operateur aff
	list<Lexeme*>::iterator itrAff, itrSource;
	tree<Lexeme*>::pre_order_iterator childaffectation,searchOpAff,searchOpSource;
	string typeAff,typeSource;
	//int taille_ref,taille_test; //Tester la taille des vecteurs
	bool source_set=false;
	bool aff_set=false;
	bool source_is_expression=false,source_is_number=false;

	tree<Lexeme*> tr_expression;
	Lexeme* bufLexeme = new Lexeme("root_condition", (*itr)->getLigne(), CONDITION_LOGIC);	//Tampon, amené à être remplacé

	while((*itr)->getType()!=AFFECTATION_END)
	{
		switch((*itr)->getType())
		{
            	case OPERATOR_AFF:
		        searchOpAff=findLexemeInTree(tr.begin(),tr.end(),(*itr)->getLex());
		        if(searchOpAff!=tr.end())
		        {
		            	//Test préliminaire :est-ce un signal ou un port ?
		            	if((*searchOpAff)->getType()!=SIGNAL_ID&&(*searchOpAff)->getType()!=PORT_ID)
		            	{
		                	cout << "Erreur : operande non valide ligne " << (*itr)->getLigne() << endl;
		                	cout << "Type attendu : signal ou port" << endl;
		                	return true;	
		            	}
				else if((*searchOpAff)->getType()==PORT_ID)	//si port, on teste le sens
				{
					int portSense=findSense(tr,searchOpAff);
					if(portSense!=PORT_OUT&&portSense!=PORT_INOUT)
					{
				        	cout << "Erreur : le port affecte n'est pas une sortie ligne " << (*itr)->getLigne() << endl;
				        	return true;	
					}
				}

		            	itrAff=itr;
		            	aff_set=true;
			}
			else
		        {
		            	cout << "Erreur : operande " << (*itr)->getLex() << "non reconnu ligne " << (*itr)->getLigne() << endl;
		                	return true;	
		        }
			break;
		case OPERATOR_IF:
			itrSource=itr;		//Pour sauvegarde
			if(!constructTreeForCondLogic(l,itr,AFFECTATION_END,tr_expression))	//Si on a une expression
			{
				tree<Lexeme*>::pre_order_iterator top_buf=tr_expression.begin();
				childaffectation=tr.append_child(affectation,bufLexeme);
				childaffectation=tr.move_ontop(childaffectation,top_buf);
				source_set=true;
				source_is_expression=true;
				break;
			}
			else //Sinon on se comporte comme un operande source : pas de break et on reprend le 1er itr
			{
				itr=itrSource;
			}
		case OPERATOR_SOURCE:
		//Besoin de tester uniquement le 1er caractère ; si c'est un nombre, les autres caractères le sont forcément
			if(is_number((*itr)->getLex()[0]))	
			{
				itrSource=itr;
				source_set=true;
				source_is_number=true;
			}
			else
			{
		        	searchOpSource=findLexemeInTree(tr.begin(),tr.end(),(*itr)->getLex());
				if(searchOpSource!=tr.end())
				{
					if((*searchOpSource)->getType()==PORT_ID)	//si l'entree est un port, on teste le sens
					{
						int portSense=findSense(tr,searchOpSource);
						if(portSense!=PORT_IN&&portSense!=PORT_INOUT)
						{
							cout << "Erreur : le port affecte n'est pas une entree ligne " << (*itr)->getLigne() << endl;
							return true;	
						}
					}
					itrSource=itr;
					source_set=true;
				}
				else
				{
				    	cout << "Erreur : operande " << (*itr)->getLex() << "non reconnu ligne " << (*itr)->getLigne() << endl;
		                	return true;	
				}
			}
			break;
		default:
			break;
		}
		itr++;
	}

	//Tests de types avant l'affectation
    if(source_set)
    {
		if(aff_set)
		{
			if(!source_is_expression&&!source_is_number) //Si les deux sont des signaux/ports : on teste leur type
			{
				
				cout << "Lexeme Affecte : " << **searchOpAff;
				typeAff=findType(tr,searchOpAff);
				cout << "Type Affecte : " << typeAff << endl;
				cout << "Lexeme Source : " << **searchOpSource;
				typeSource=findType(tr,searchOpSource);
				cout << "Type Source : " << typeSource << endl;
				if(typeAff=="")
				{
				    cout << "Erreur d'affectation : type non reconnu sur " << (*searchOpAff)->getLex()
					<< " ligne " << (*searchOpAff)->getLigne() << endl;
		                	return true;	
				}
				if(typeSource=="")
				{
				    cout << "Erreur d'affectation : type non reconnu sur " << (*searchOpSource)->getLex()
					<< " ligne " << (*searchOpSource)->getLigne() << endl;
		                	return true;	
				}
				if(typeAff!=typeSource)
				{
				    cout << "Erreur d'affectation : types non identiques ligne " << (*itr)->getLigne() << endl;
		                	return true;	
				}
			}
			//Sinon on stocke

			//A placer : tests taille vecteurs

			//Tous les tests sont passés
			//cout << "Lexeme Affecte : " << (*itrAff)->getLex() << endl; 
			childaffectation=tr.append_child(affectation,*itrAff);
			if(!source_is_expression)
			{
				//cout << "Lexeme Source : " << (*itrSource)->getLex() << endl; 
				childaffectation=tr.append_child(childaffectation,*itrSource);
			}
			//Source stockée en enfant de l'opérande affectée
		}
		else
		{
			cout << "Erreur : pas d'operateur affecte ligne " << (*itr)->getLigne() << endl;
                        return true;	//A changer
		}
	}
	else
	{
		cout << "Erreur : pas d'operateur source ligne " << (*itr)->getLigne() << endl;
                return true;	//A changer
	}

	return false;
}

bool constructTreeOnAffectationVariable(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& affectation, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Affectation Variable" << endl;
	itr--;	//Pour reperer l'operateur aff
	list<Lexeme*>::iterator itrAff, itrSource;
	tree<Lexeme*>::pre_order_iterator childaffectation,searchOpAff,searchOpSource;
	string typeAff,typeSource;
	//int taille_ref,taille_test; //Tester la taille des vecteurs
	bool source_set=false;
	bool aff_set=false;
	bool source_is_expression=false,source_is_number=false;

	tree<Lexeme*> tr_expression;
	Lexeme* bufLexeme = new Lexeme("root_affectation", (*itr)->getLigne(), CONDITION_LOGIC);	//Tampon, amené à être remplacé

	while((*itr)->getType()!=AFFECTATION_END)
	{
		switch((*itr)->getType())
		{
            	case OPERATOR_AFF:
		            //Test : est-ce déjà stocké ?
		        searchOpAff=findLexemeInTree(tr.begin(),tr.end(),(*itr)->getLex());
		        if(searchOpAff!=tr.end())
		        {
		            //Test : est-ce un signal ou un port ?
		            if((*searchOpAff)->getType()!=VARIABLE_ID)
		            {
		                cout << "Erreur : operande non valide ligne " << (*itr)->getLigne() << endl;
		                cout << "Type attendu : variable" << endl;
		                return true;	
		            }

		            itrAff=itr;
		            aff_set=true;
			}
			else
		        {
		            cout << "Erreur : operande " << (*itr)->getLex() << "non reconnu ligne " << (*itr)->getLigne() << endl;
		                return true;	
		        }
			break;
		case OPERATOR_IF:
			itrSource=itr;		//Pour sauvegarde
			if(!constructTreeForCondLogic(l,itr,AFFECTATION_END,tr_expression))	//Si on a une expression
			{
				cout << "Tree Accepte" << endl;
				tree<Lexeme*>::pre_order_iterator top_buf=tr_expression.begin();
				childaffectation=tr.append_child(affectation,bufLexeme);
				childaffectation=tr.move_ontop(childaffectation,top_buf);
				source_set=true;
				source_is_expression=true;
				break;
			}
			else //Sinon on se comporte comme un operande source : pas de break et on reprend le 1er itr
			{
				itr=itrSource;
			}
		case OPERATOR_SOURCE:
		//Besoin de tester uniquement le 1er caractère ; si c'est un nombre, les autres caractères le sont forcément
			if(is_number((*itr)->getLex()[0]))	
			{
				itrSource=itr;
				source_set=true;
				source_is_number=true;
			}
			else
			{
		        	searchOpSource=findLexemeInTree(tr.begin(),tr.end(),(*itr)->getLex());
				if(searchOpSource!=tr.end())
				{
					if((*searchOpSource)->getType()==PORT_ID)	//si la source est un port, on teste le sens
					{
						int portSense=findSense(tr,searchOpSource);
						if(portSense!=PORT_IN&&portSense!=PORT_INOUT)
						{
							cout << "Erreur : le port affecte n'est pas une entree ligne " << (*itr)->getLigne() << endl;
							return true;	
						}
					}
					itrSource=itr;
					source_set=true;
				}
				else
				{
				    	cout << "Erreur : operande " << (*itr)->getLex() << "non reconnu ligne " << (*itr)->getLigne() << endl;
		                	return true;	
				}
			}
			break;
		default:
			break;
		}
		itr++;
	}

	//Tests de types avant l'affectation
    if(source_set)
    {
		if(aff_set)
		{
			if(!source_is_expression&&!source_is_number) //Si les deux sont des signaux/ports : on teste leur type
			{
				typeAff=findType(tr,searchOpAff);
				typeSource=findType(tr,searchOpSource);
				cout << "Type Affecte : " << typeAff << endl;
				cout << "Type Source : " << typeSource << endl;
				if(typeAff=="")
				{
				    cout << "Erreur d'affectation : type non reconnu sur " << (*searchOpAff)->getLex()
					<< " ligne " << (*searchOpAff)->getLigne() << endl;
		                	return true;	
				}
				if(typeSource=="")
				{
				    cout << "Erreur d'affectation : type non reconnu sur " << (*searchOpSource)->getLex()
					<< " ligne " << (*searchOpSource)->getLigne() << endl;
		                	return true;	
				}
				if(typeAff!=typeSource)
				{
				    cout << "Erreur d'affectation : types non identiques ligne " << (*itr)->getLigne() << endl;
		                	return true;	
				}
			}
			//Sinon on stocke

			//A placer : tests taille vecteurs

			//Tous les tests sont passés
			childaffectation=tr.append_child(affectation,*itrAff);
			if(!source_is_expression)
			{
				//cout << "Lexeme Source : " << (*itrSource)->getLex() << endl; 
				childaffectation=tr.append_child(childaffectation,*itrSource);
			}
			//Source stockée en enfant de l'opérande affectée
		}
		else
		{
			cout << "Erreur : pas d'operateur affecte ligne " << (*itr)->getLigne() << endl;
                        return true;
		}
	}
	else
	{
		cout << "Erreur : pas d'operateur source ligne " << (*itr)->getLigne() << endl;
                return true;
	}

	return false;
}


bool constructTreeOnArchitecture(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& architecture, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Architecture" << endl;

	tree<Lexeme*>::pre_order_iterator childarchi;
	while((*itr)->getType()!=ARCHITECTURE_END)
	{
		switch((*itr)->getType())
		{
			case ARCHITECTURE_ID:
				childarchi=tr.append_child(architecture,*itr);
				if(constructTreeOnArchitectureID(tr,childarchi,l,itr))
                    			return true;
				break;
			default:
                		itr++;
				break;
		}
	}
	return false;
}

bool constructTreeOnArchitectureID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& architectureid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Architecture ID" << endl;

	tree<Lexeme*>::pre_order_iterator childarchiid;
	while((*itr)->getType()!=ARCHITECTURE_END)
	{
		switch((*itr)->getType())
		{
			case ARCHITECTURE_BEGIN:
		        	childarchiid=tr.append_child(architectureid,*itr);
		        	if(constructTreeOnArchitectureInst(tr,childarchiid,l,itr))
                        		return true;
				break;
			case SIGNAL:
				if(constructTreeOnSignal(tr,architectureid,l,itr))
                    			return true;
				itr++;
				break;
			case TYPE_DECLARE_ID : 
		        	childarchiid=tr.append_child(architectureid,*itr);
				itr++;
		        	if(constructTreeOnTypeID(tr,childarchiid,l,itr))
                        		return true;
				break;
			case VARIABLE_ID:
		        	childarchiid=tr.append_child(architectureid,*itr);
		        	if(constructTreeOnVariableID(tr,childarchiid,l,itr))
                        		return true;
				break;
			default:
				itr++;
				break;
		}
	}
	return false;
}

bool constructTreeOnArchitectureInst(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& architectureinst, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Architecture Inst" << endl;

	tree<Lexeme*>::pre_order_iterator childarchiinst;
	while((*itr)->getType()!=ARCHITECTURE_END)
	{
		switch((*itr)->getType())
		{
        		case AFFECTATION_SIGNAL:
                    		childarchiinst=tr.append_child(architectureinst,*itr);
                    		if(constructTreeOnAffectationSignal(tr,childarchiinst,l,itr))
                        		return true;
                    		break;
        		case AFFECTATION_VARIABLE:
                    		childarchiinst=tr.append_child(architectureinst,*itr);
                    		if(constructTreeOnAffectationVariable(tr,childarchiinst,l,itr))
                        		return true;
                    		break;
			case MAP_ID:
                    		childarchiinst=tr.append_child(architectureinst,*itr);
                    		if(constructTreeOnPortMap(tr,childarchiinst,l,itr))
                        		return true;
                    		break;
		    	case PROCESS:
		        	childarchiinst=tr.append_child(architectureinst,*itr);
		        	if(constructTreeOnProcess(tr,childarchiinst,l,itr))
                        		return true;
		        	break;
              		case PROCESS_ID:
		        	childarchiinst=tr.append_child(architectureinst,*itr);
		        	if(constructTreeOnProcess(tr,childarchiinst,l,itr))
                        		return true;
				break;
			default:
				itr++;
				break;
		}
	}
	return false;
}

bool constructTreeOnPortMap(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& portmap, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Port Map" << endl;
	list<Lexeme*>::iterator itr_mem=itr;
	tree<Lexeme*>::pre_order_iterator childportmap;
	while((*itr)->getType()!=MAP_END)
	{
		switch((*itr)->getType())
		{

			case AFFECTATION_MAP:
                		childportmap=tr.append_child(portmap,*itr);
				if(constructTreeOnPortMapAffectation(tr,childportmap,l,itr_mem))
                    			return true;
				itr++;
				break;
			case MAP_OPERATOR:
				childportmap=tr.append_child(portmap,*itr);
			    	itr++;
				break;
			default:
			    	itr++;
				break;
		}
	}
	return false;
}

bool constructTreeOnPortMapAffectation(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& portmapaff, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Port Aff" << endl;
	tree<Lexeme*>::pre_order_iterator childportmapaff;
	bool affSet=false, sourceSet=false;
	while((*itr)->getType()!=MAP_END&&(!affSet||!sourceSet))	//on sort dès que les deux conditions bool sont remplies
	{
		switch((*itr)->getType())
		{

			case MAP_OPERATOR_AFF:
                		childportmapaff=tr.append_child(portmapaff,*itr);
				affSet=true;
				itr++;
				break;
			case MAP_OPERATOR_SOURCE:
				childportmapaff=tr.append_child(portmapaff,*itr);
				sourceSet=true;
			    	itr++;
				break;
			default:
			    	itr++;
				break;
		}
	}

	//Test
	if(!affSet||!sourceSet)
	{
		cout << "Port Map : port non affecte ligne " << (*itr)->getLigne() << endl;
		return true;
	}
	return false;
}


bool constructTreeOnSignal(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& signal, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Signal" << endl;

	tree<Lexeme*>::pre_order_iterator childsignal;
	while((*itr)->getType()!=SIGNAL_END)
	{
		switch((*itr)->getType())
		{
			case SIGNAL_ID:
                		childsignal=tr.append_child(signal,*itr);
				if(constructTreeOnSignalID(tr,childsignal,l,itr))
                    			return true;
				break;
			default:
			    	itr++;
				break;
		}
	}
	return false;
}

bool constructTreeOnSignalID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& signalid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Signal ID" << endl;

	tree<Lexeme*>::pre_order_iterator childsignalid;
	while((*itr)->getType()!=SIGNAL_END)
	{
		switch((*itr)->getType())
		{
			case SIGNAL_TYPE:
                		childsignalid=tr.append_child(signalid,*itr);
				break;
			case TYPE_VECTOR:
           			childsignalid=tr.append_child(signalid,*itr);
				if(constructTreeOnVector(tr,childsignalid,l,itr))
                    			return true;
				break;
			default:
				break;
		}
		itr++;
	}
	return false;
}

bool constructTreeOnTypeID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& _typeid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Type ID" << endl;
	cout << **itr;

	tree<Lexeme*>::pre_order_iterator childtypeid,searchType;
	bool vectorType=false;
	Lexeme* bufVector = new Lexeme("is",(*itr)->getLigne(),TYPE_VECTOR);
	string buf;
	while((*itr)->getType()!=TYPE_DECLARE_END)
	{
		switch((*itr)->getType())
		{
			case TYPE_DECLARE_ID:

				if(!(is_type((*itr)->getLex())))
				{
					searchType=findLexemeInTree(tr.begin(),tr.end(),(*itr)->getLex());     
					if((*searchType)->getType()!=TYPE_DECLARE_ID||searchType==tr.end())
					{
						cout << "Erreur : type non declare ligne " << (*itr)->getLigne() << endl;
						return true;
					}
				}
				
				if(!vectorType)
				{
					cout << **itr;
					cout << "Erreur : n'est pas le vecteur d'un autre type ligne " << (*itr)->getLigne() << endl;
					return true;
				}
				childtypeid=tr.append_child(_typeid,*itr);
				break;
			case TYPE_DECLARE_VAL:
				childtypeid=tr.append_child(_typeid,*itr);
				break;
			case TYPE_VECTOR_BEGIN:
				cout << "Type Vecteur" << endl;
           			childtypeid=tr.append_child(_typeid,bufVector);
				if(constructTreeOnVector(tr,childtypeid,l,itr))
                    			return true;
				vectorType=true;
				break;
			default:
				break;
		}
		itr++;
	}
	return false;	
}

bool constructTreeOnVariableID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& variableid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Variable ID" << endl;

	tree<Lexeme*>::pre_order_iterator childvariableid;
	while((*itr)->getType()!=VARIABLE_END)
	{
		switch((*itr)->getType())
		{
			case VARIABLE_TYPE:
                		childvariableid=tr.append_child(variableid,*itr);
				break;
			case TYPE_VECTOR:
                		childvariableid=tr.append_child(variableid,*itr);
				if(constructTreeOnVector(tr,childvariableid,l,itr))
                    return true;
				break;
			default:
				break;
		}
		itr++;
	}
	return false;
}

//-------------------------------------------------------------ENTITY---------------------------------------------------------

bool constructTreeOnEntity(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& entity, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Entity" << endl;

	tree<Lexeme*>::pre_order_iterator childentity;
	while((*itr)->getType()!=ENTITY_END)
	{
		switch((*itr)->getType())
		{
			case ENTITY_ID:
				childentity=tr.append_child(entity,*itr);
				if(constructTreeOnEntityID(tr,childentity,l,itr))
                    return true;
				break;
			default:
			    itr++;
				break;
		}
	}
	return false;
}

bool constructTreeOnEntityID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& entityid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Entity ID" << endl;

	tree<Lexeme*>::pre_order_iterator childentityid;
	while((*itr)->getType()!=ENTITY_END)
	{
		switch((*itr)->getType())
		{
   			case GENERIC:
				childentityid=tr.append_child(entityid,*itr);
				if(constructTreeOnGeneric(tr,childentityid,l,itr))
                    return true;
				break;
			case PORT:
				childentityid=tr.append_child(entityid,*itr);
				if(constructTreeOnPort(tr,childentityid,l,itr))
                    return true;
				break;
			default:
				itr++;
				break;
		}
	}
	return false;
}

bool constructTreeOnGeneric(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& generic, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Generic" << endl;

	tree<Lexeme*>::pre_order_iterator childgeneric;
	while((*itr)->getType()!=GENERIC_END)
	{
		switch((*itr)->getType())
		{
			case GENERIC_ID:
				childgeneric=tr.append_child(generic,*itr);
				if(constructTreeOnGenericId(tr,childgeneric,l,itr))
                    return true;
				break;
			default:
				break;
		}
		itr++;
	}
	return false;
}

bool constructTreeOnGenericId(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& genericid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Generic ID" << endl;

	tree<Lexeme*>::pre_order_iterator childgenericid;
	while((*itr)->getType()!=GENERIC_ID_END)
	{
		switch((*itr)->getType())
		{
			case GENERIC_TYPE:
				childgenericid=tr.append_child(genericid,*itr);
				break;
			case TYPE_VECTOR:
				childgenericid=tr.append_child(genericid,*itr);
				if(constructTreeOnVector(tr,childgenericid,l,itr))
                    return true;
				break;
			default:
				break;
		}
		itr++;
	}
	return false;
}

bool constructTreeOnPort(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& port, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Port" << endl;

	tree<Lexeme*>::pre_order_iterator childport;
	while((*itr)->getType()!=PORT_END)
	{
		switch((*itr)->getType())
		{
			case PORT_ID:
				childport=tr.append_child(port,*itr);
				if(constructTreeOnPortId(tr,childport,l,itr))
                    return true;
				break;
			default:
				break;
		}
		itr++;
	}
}

bool constructTreeOnPortId(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& portid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Port ID" << endl;

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
				if(constructTreeOnVector(tr,childportid,l,itr))
                    return true;
				break;
			default:
				break;
		}
		itr++;
	}
	return false;
}

//-------------------------------------------------------------LIBRARY---------------------------------------------------------

//Pour l'instant ne stocke rien : c'est use qui se charge de stocker la bonne librairie
bool constructTreeOnLibrary(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& library, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Library" << endl;

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

	return false;
}

bool constructTreeOnUse(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& library, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Use" << endl;

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
				    library_id=findLexemeInTree(tr.begin(),tr.end(),(*itr)->getLex());
				    if(library_id!=tr.end())
                    {
				    	buf=library_id;
                        defineLibraryId=true;
                    }
                    else
                    {
                        cout << "Erreur : librairie " << (*itr)->getLex() << " non reconnue" << endl;
                        return true;
                    }
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
				    return true;
				}
                break;
			default:
				break;
		}
		itr++;
	}
	return false;
}


//-------------------------------------------------------------PACKAGE---------------------------------------------------------

bool constructTreeOnComponentId(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& componentid, list<Lexeme*>& l, list<Lexeme*>::iterator &itr)
{
	cout << "Tree Component ID" << endl;

	tree<Lexeme*>::pre_order_iterator childcomponentid;
	while((*itr)->getType()!=COMPONENT_END)
	{
		switch((*itr)->getType())
		{
   			case GENERIC:
				childcomponentid=tr.append_child(componentid,*itr);
				if(constructTreeOnGeneric(tr,childcomponentid,l,itr))
                    return true;
				break;
			case PORT:
				childcomponentid=tr.append_child(componentid,*itr);
				if(constructTreeOnPort(tr,childcomponentid,l,itr))
                    return true;
				break;
			default:
                		itr++;
				break;
		}
	}
	return false;
}

bool constructTreeOnPackage(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& package, list<Lexeme*>& l, list<Lexeme*>::iterator &itr)
{
	cout << "Tree Package" << endl;

	tree<Lexeme*>::pre_order_iterator childpackage;
	while((*itr)->getType()!=PACKAGE_END)
	{
		switch((*itr)->getType())
		{
			case PACKAGE_ID:
				childpackage=tr.append_child(package,*itr);
                if(constructTreeOnPackageId(tr,childpackage,l,itr))
                    return true;
				break;
			default:
                		itr++;
				break;
		}
	}
	return false;
}

bool constructTreeOnPackageId(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& packageid, list<Lexeme*>& l, list<Lexeme*>::iterator &itr)
{
	cout << "Tree Package ID" << endl;

	tree<Lexeme*>::pre_order_iterator childpackageid;
	while((*itr)->getType()!=PACKAGE_END)
	{
		switch((*itr)->getType())
		{
			case COMPONENT_ID:
				childpackageid=tr.append_child(packageid,*itr);
                		if(constructTreeOnComponentId(tr,childpackageid,l,itr))
                    			return true;
				//itr++; //temporaire
				break;
			default:
                itr++;
				break;
		}
	}
	return false;
}

//-------------------------------------------------------------PROCESS---------------------------------------------------------

bool constructTreeForCondLogic(list<Lexeme*>& l, list<Lexeme*>::iterator& itr, int type_fin, tree<Lexeme*>& buf_conditions)
{
	cout << "Tree Condition" << endl;

	tree<Lexeme*> tree_cond_logic,tree_parenthesis;
	tree<Lexeme*>::pre_order_iterator top_buf=buf_conditions.begin(),top_cond_tree,top_parenth_tree,bufroot;
	Lexeme* bufLexeme = new Lexeme("root_condition", (*itr)->getLigne(), CONDITION_LOGIC);	//Tampon, amené à être remplacé par d'autres arbres
	//bufroot=buf_conditions.insert(top_buf,bufLexeme);

	bool set_logic=false, set_parenthesis=false, set_scalar=false;
	list<Lexeme*>::iterator itr_2=itr;				//On parcourt 2 fois les conditions
	tree<Lexeme*>::pre_order_iterator itercondition,childcondition;

	//1ère boucle pour les conditions et les parenthèses
	while((*itr)->getType()!=type_fin)
	{
		switch((*itr)->getType())
		{

			case CONDITION_LOGIC:
				bufroot=buf_conditions.insert(top_buf,*itr);
				itr++;					//On passe au Lexeme suivant avant de construire un nouvel arbre

				if(!constructTreeForCondLogic(l,itr,type_fin,tree_cond_logic))
				{
					itercondition=buf_conditions.append_child(bufroot,bufLexeme);
					top_cond_tree=tree_cond_logic.begin();
					top_cond_tree=buf_conditions.move_ontop(itercondition,top_cond_tree);
					
				}
				if(set_parenthesis)
				{
					cout << "On stocke l'arbre parenthese sous condition logique1" << endl;
					itercondition=buf_conditions.append_child(bufroot,bufLexeme);
					top_parenth_tree=tree_parenthesis.begin();
					top_parenth_tree=buf_conditions.move_ontop(itercondition,top_parenth_tree);
				}
				else
				{
					cout << "Pas de parentheses" << endl;
				}

				cout << "set logic ok" << endl;
				set_logic=true;
				break;
			case CONDITION_SCALAR:
				bufroot=buf_conditions.insert(top_buf,*itr);
				itr++;	
				set_scalar=true;
				break;

			case IF_PARENTHESE_OUV:
				//cout << "Parenthese trouve " << endl;
				itr++;
				if(!constructTreeForCondLogic(l,itr,IF_PARENTHESE_FER,tree_parenthesis))
				{
					cout << "set_parenthesis ok" << endl;
					set_parenthesis=true;
					printTree(tree_parenthesis);
					if(set_logic)
					{
						cout << "On stocke l'arbre parenthese sous condition logique2" << endl;
						itercondition=buf_conditions.append_child(itercondition,bufLexeme);
						top_parenth_tree=tree_parenthesis.begin();
						top_parenth_tree=buf_conditions.move_ontop(itercondition,top_parenth_tree);
					}
					else
					{
						cout << "Pas de logique" << endl;
					}
				}

			default:
                		itr++;
				break;
		}
	}

	//2e boucle pour les opérateurs
	if(set_logic||set_scalar)	//Condition stockée : on effectue la deuxième boucle
	{
		while((*itr_2)->getType()!=type_fin)
		{
			switch((*itr_2)->getType())
			{
				case OPERATOR_IF :
					//si pas stocké : on le met dans l'arbre
					if(!isLexemeInTree(buf_conditions.begin(),buf_conditions.end(),*itr_2))
					{
						childcondition=buf_conditions.append_child(bufroot,*itr_2);
					}
					else
					{
						cout << "Lexeme deja stocke dans l'arbre" << endl;
					}
					itr_2++;
					break;
				default:
		        		itr_2++;
					break;
			}
		}
	}

	//si on avait juste des parenthèses mais sans logique associée
	if(set_parenthesis&&!set_logic)
	{
		buf_conditions=tree_parenthesis;
	}

	printTree(buf_conditions);	//Pour test
	cout << "/Tree Condition" << endl;

	if(buf_conditions.empty())
	{
		//cout << "Arbre vide" << endl;
		return true;
	}

	//printTree(buf_conditions);	//Pour test
	return false;
}

bool constructTreeOnIf(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& _if, list<Lexeme*>& l, list<Lexeme*>::iterator &itr)
{
	cout << "Tree If" << endl;

	list<Lexeme*>::iterator mem_if=itr;	//On mémorise la position de itr car on a besoin de parcourir 2 fois le if
	tree<Lexeme*>::pre_order_iterator childif;

	//Création de l'arbre pour les conditions
	//En cours de construction
	tree<Lexeme*> buf_conditions;
	Lexeme* bufLexeme = new Lexeme("root_condition", (*itr)->getLigne(), CONDITION_LOGIC);	//Tampon, amené à être remplacé
	if(!constructTreeForCondLogic(l,mem_if,THEN,buf_conditions))
	{
		tree<Lexeme*>::pre_order_iterator top_buf=buf_conditions.begin();
		childif=tr.append_child(_if,bufLexeme);
		childif=tr.move_ontop(childif,top_buf);
	}
	else
    	{
        	cout << "Erreur : pas de conditions sur le if ligne " << (*itr)->getLigne() << endl;
        	return true;
    	}


	while((*itr)->getType()!=IF_END)
	{
		switch((*itr)->getType())
		{
			case ELSE:
				childif=tr.append_child(_if,*itr);
                		if(constructTreeOnIfInst(tr,childif,l,itr))
                    			return true;
				break;
			case ELSIF:
				childif=tr.append_child(_if,*itr);
                		if(constructTreeOnIfInst(tr,childif,l,itr))
                    			return true;
				break;
			case THEN:
				childif=tr.append_child(_if,*itr);
				if(constructTreeOnIfInst(tr,childif,l,itr))
                    			return true;
				break;
			default:
                		itr++;
				break;
		}
	}


    	return false;
}

bool constructTreeOnIfInst(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& if_inst, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree If Instructions" << endl;

    	itr++;
	tree<Lexeme*>::pre_order_iterator childifinst;
	while((*itr)->getType()!=IF_END&&(*itr)->getType()!=ELSE&&(*itr)->getType()!=ELSIF)
	{
		switch((*itr)->getType())
		{
        		case AFFECTATION_SIGNAL:
                		childifinst=tr.append_child(if_inst,*itr);
            			if(constructTreeOnAffectationSignal(tr,childifinst,l,itr))
                            return true;
				break;
        		case AFFECTATION_VARIABLE:
                		childifinst=tr.append_child(if_inst,*itr);
            			if(constructTreeOnAffectationVariable(tr,childifinst,l,itr))
                            return true;
				break;
            		case IF:
                		childifinst=tr.append_child(if_inst,*itr);
                        if(constructTreeOnIf(tr,childifinst,l,itr))
                            return true;
                		break;
			default:
				break;
		}
		itr++;
	}
	return false;
}

bool constructTreeOnProcess(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& process, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Process" << endl;

	tree<Lexeme*>::pre_order_iterator childprocess;

	while((*itr)->getType()!=PROCESS_END)
	{
		switch((*itr)->getType())
		{
            case PROCESS_BEGIN:
                childprocess=tr.append_child(process,*itr);
				if(constructTreeOnProcessInst(tr,childprocess,l,itr))
                    return true;
                break;
            case PROCESS_SENSIBILITY:
                childprocess=tr.append_child(process,*itr);
                itr++;
				break;
			case VARIABLE_ID:
		        	childprocess=tr.append_child(process,*itr);
		        	if(constructTreeOnVariableID(tr,childprocess,l,itr))
                        return true;
				break;
			default:
                		itr++;
				break;
		}
	}

	return false;
}

bool constructTreeOnProcessInst(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& process_inst, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Process Instructions" << endl;

	tree<Lexeme*>::pre_order_iterator childprocessinst;
	while((*itr)->getType()!=PROCESS_END)
	{
		switch((*itr)->getType())
		{
        		case AFFECTATION_SIGNAL:
            			childprocessinst=tr.append_child(process_inst,*itr);
            			if(constructTreeOnAffectationSignal(tr,childprocessinst,l,itr))
                            return true;
				break;
        		case AFFECTATION_VARIABLE:
            			childprocessinst=tr.append_child(process_inst,*itr);
            			if(constructTreeOnAffectationVariable(tr,childprocessinst,l,itr))
                            return true;
				break;
            		case IF:
                		childprocessinst=tr.append_child(process_inst,*itr);
				if(constructTreeOnIf(tr,childprocessinst,l,itr))
                    return true;
                		break;
			default:
				break;
		}
		itr++;
	}
	return false;
}

//-------------------------------------------------------------AUTRES---------------------------------------------------------


bool constructTreeOnVector(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& vec, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
    cout << "Tree Vector" << endl;

	tree<Lexeme*>::pre_order_iterator childvec;

	bool setBegin=false,setSense=false,setEnd=false;
	while((*itr)->getType()!=TYPE_VECTOR_END)
	{
		switch((*itr)->getType())
		{
		    case TYPE_VECTOR_BEGIN:
		        childvec=tr.append_child(vec,*itr);
		        setBegin=true;
		        break;
		    case TYPE_VECTOR_SENSE:
		        childvec=tr.append_child(vec,*itr);
		        setSense=true;
		        break;
		    case TYPE_VECTOR_END:
		        childvec=tr.append_child(vec,*itr);
		        setEnd=true;
                break;
		    default:
			break;
		}
		itr++;
	}

	//Stockage de la fin (on sort du while avant)
	if((*itr)->getType()==TYPE_VECTOR_END)
    	{
        	childvec=tr.append_child(vec,*itr);
        	setEnd=true;
    	}

	//Test
    	if(!setBegin||!setEnd||!setSense)
    	{
        	cout << "Erreur : vecteur incomplet ligne " << (*itr)->getLigne() << endl;
        	return true;
    	}
    	return false;
}

//-------------------------------------------------------------FIND---------------------------------------------------------

tree<Lexeme*>::pre_order_iterator findLexemeInTree(tree<Lexeme*>::pre_order_iterator begin_search, tree<Lexeme*>::pre_order_iterator end_search, string lexeme)
{
	tree<Lexeme*>::pre_order_iterator result=begin_search;
	while(result!=end_search)
	{
		if((*result)->getLex()==lexeme)
		{
			return result;
		}
		result++;
	}
	return end_search;
}

int findSense(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator parent)
{
    tree<Lexeme*>::post_order_iterator searchSense;
    for(searchSense=tr.begin_leaf(parent);searchSense!=tr.end_leaf(parent);searchSense++)
    {
        switch((*searchSense)->getType())
        {
            case PORT_IN:
            case PORT_INOUT:
            case PORT_OUT:
                return (*searchSense)->getType();
        }
    }

    return NON_DEFINI;
}

int findSizeOnVector(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator parent)
{
    tree<Lexeme*>::leaf_iterator searchSize;
    int debut=0;
    int fin=0;
    bool downto=false;
    for(searchSize=tr.begin_leaf(parent);searchSize!=tr.end_leaf(parent);searchSize++)
    {
         switch((*searchSize)->getType())
        {
            case TYPE_VECTOR_BEGIN:
                debut=stoi((*searchSize)->getLex());
                break;
            case TYPE_VECTOR_SENSE:
                if((*searchSize)->getLex()=="downto")
                    downto=true;
                break;
            case TYPE_VECTOR_END:
                fin=stoi((*searchSize)->getLex());
                break;
        }
    }
    if(downto)
        return debut-fin;

    return fin-debut;
}

string findType(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator parent)
{
    tree<Lexeme*>::post_order_iterator searchType;

    for(searchType=tr.begin_leaf(parent);searchType!=tr.end_leaf(parent);searchType++)
    {
        switch((*searchType)->getType())
        {
            case PORT_TYPE:
                return (*searchType)->getLex();
            case SIGNAL_TYPE:
                return (*searchType)->getLex();
            case TYPE_VECTOR:
                return (*searchType)->getLex();
            case VARIABLE_TYPE:
                return (*searchType)->getLex();
        }
    }

    return "";
}

bool isLexemeInTree(tree<Lexeme*>::pre_order_iterator begin_search, tree<Lexeme*>::pre_order_iterator end_search, Lexeme* l_searched)
{
    cout << "Lexeme cherche : " << l_searched->getLex() << endl;
    tree<Lexeme*>::pre_order_iterator result=begin_search;
    while(result!=end_search)
    {
        if(*result==l_searched)
        {
		cout << "Lexeme trouve !" << endl;
            	return true;
        }
        result++;
    }
    return false;
}

//-------------------------------------------------------------PRINT---------------------------------------------------------

void printTree(const tree<Lexeme*>& tr)
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
		cout << (**itr);
		++itr;
	}
}

int saveTree(const tree<Lexeme*>& tr, string libraryname)
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

	return 1;
}
