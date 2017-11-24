#ifndef CREATETREE_h_
#define CREATETREE_h_

#include "tree.hh"
#include "Lexeme.h"
#include <list>
#include <algorithm>
#include <string>
#include <iostream>
#include "type_Lexeme.h"

using namespace std;

tree<Lexeme*> createTree(list<Lexeme*>& l);

void constructTreeOnEntity(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& entity, list<Lexeme*>& l, list<Lexeme*>::iterator begin_entity);
void constructTreeOnEntityID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& entityid, list<Lexeme*>& l, list<Lexeme*>::iterator begin_entityid);
void constructTreeOnPort(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& port, list<Lexeme*>& l, list<Lexeme*>::iterator begin_port);
void constructTreeOnPortId(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& portid, list<Lexeme*>& l, list<Lexeme*>::iterator begin_portid);

void printTree(tree<Lexeme*> tr);

#endif //CREATETREE_h_