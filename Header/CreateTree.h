#ifndef CREATETREE_h_
#define CREATETREE_h_

#include "tree.hh"
#include "Lexeme.h"
#include <list>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include "type_Lexeme.h"

using namespace std;

tree<Lexeme*> createTree(list<Lexeme*>& l);

//------------------------------------Architecture--------------------------------
void constructTreeOnArchitecture(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& architecture, list<Lexeme*>& l, list<Lexeme*>::iterator begin_archi);
void constructTreeOnArchitectureID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& architectureid, list<Lexeme*>& l, list<Lexeme*>::iterator begin_archi_id);
void constructTreeOnProcess(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& process, list<Lexeme*>& l, list<Lexeme*>::iterator begin_process);
void constructTreeOnSignal(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& signal, list<Lexeme*>& l, list<Lexeme*>::iterator begin_signal);
void constructTreeOnSignalID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& signalid, list<Lexeme*>& l, list<Lexeme*>::iterator begin_signalid);

//------------------------------------Entity--------------------------------
void constructTreeOnEntity(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& entity, list<Lexeme*>& l, list<Lexeme*>::iterator begin_entity);
void constructTreeOnEntityID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& entityid, list<Lexeme*>& l, list<Lexeme*>::iterator begin_entityid);
void constructTreeOnPort(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& port, list<Lexeme*>& l, list<Lexeme*>::iterator begin_port);
void constructTreeOnPortId(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& portid, list<Lexeme*>& l, list<Lexeme*>::iterator begin_portid);

//------------------------------------Library--------------------------------
void constructTreeOnLibrary(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& library, list<Lexeme*>& l, list<Lexeme*>::iterator begin_library);
void constructTreeOnUse(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& library, list<Lexeme*>& l, list<Lexeme*>::iterator begin_use);

//------------------------------------Autres--------------------------------
void constructTreeOnVector(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& vec, list<Lexeme*>& l, list<Lexeme*>::iterator begin_vec);

//------------------------------------Print--------------------------------
void printTree(tree<Lexeme*> tr);
int saveTree(tree<Lexeme*> tr, string libraryname);

#endif //CREATETREE_h_
