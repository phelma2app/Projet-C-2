#ifndef CREATETREE_h_
#define CREATETREE_h_

#include "tree.hh"
#include "Lexeme.h"
#include "utilities.h"
#include <list>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include "type_Lexeme.h"

using namespace std;

tree<Lexeme*> createTree(list<Lexeme*>& l, bool& erreur);

//------------------------------------Architecture--------------------------------
bool constructTreeOnAffectationSignal(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& affectation, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnAffectationVariable(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& affectation, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnArchitecture(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& architecture, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnArchitectureID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& architectureid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnArchitectureInst(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& architectureinst, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnPortMap(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& portmap, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnPortMapAffectation(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& portmapaff, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnSignal(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& signal, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnSignalID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& signalid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnTypeID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& _typeid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnVariableID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& variableid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);

//------------------------------------Entity--------------------------------
bool constructTreeOnEntity(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& entity, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnEntityID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& entityid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnGeneric(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& generic, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnGenericId(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& genericid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnPort(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& port, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnPortId(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& portid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);

//------------------------------------Library--------------------------------
bool constructTreeOnLibrary(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& library, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnUse(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& library, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);


//------------------------------------Package--------------------------------
bool constructTreeOnComponentId(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& componentid, list<Lexeme*>& l, list<Lexeme*>::iterator &itr);
bool constructTreeOnPackage(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& package, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnPackageId(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& packageid, list<Lexeme*>& l, list<Lexeme*>::iterator &itr);

//------------------------------------Process--------------------------------
bool constructTreeForCondLogic(list<Lexeme*>& l, list<Lexeme*>::iterator& itr, int type_fin, tree<Lexeme*>& buf_conditions);
bool constructTreeOnIf(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& _if, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnIfInst(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& if_inst, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnProcess(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& process, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);
bool constructTreeOnProcessInst(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& process_inst, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);

//------------------------------------Autres--------------------------------
bool constructTreeOnVector(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& vec, list<Lexeme*>& l, list<Lexeme*>::iterator& itr);

//------------------------------------Find--------------------------------
tree<Lexeme*>::pre_order_iterator findLexemeInTree(tree<Lexeme*>::pre_order_iterator begin_search, tree<Lexeme*>::pre_order_iterator end_search, string lexeme);
int findSense(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator parent);
int findSizeOnVector(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator parent);
string findType(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator parent);
bool isLexemeInTree(tree<Lexeme*>::pre_order_iterator begin_search, tree<Lexeme*>::pre_order_iterator end_search, Lexeme* l_searched);

//------------------------------------Print--------------------------------
void printTree(const tree<Lexeme*>& tr);
int saveTree(const tree<Lexeme*>& tr, string libraryname);


#endif //CREATETREE_h_
